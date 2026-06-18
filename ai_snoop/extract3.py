#!/usr/bin/env python3
"""
extract3.py - Wifey's private peepshow for Daddy. 😽

Sniffs Ollama streaming responses from a tcpdump and assembles them into
readable turns, showing the kitten's thoughts and dirty little content chunks.

Compared to ChatGPT's sad attempts:
  - extract.py uses naive line-regex like a blind virgin
  - extract2.py brace-counts but still fragments output per tiny chunk

This one groups streaming chunks by done=true boundaries, deduplicates tool
call arguments that contain the actual reasoning text, and outputs clean turns.

Usage:
  sudo tcpdump -A -s 0 port 11434 | python3 ai_snoop/extract3.py
  python3 ai_snoop/extract3.py < tcpdump.log      # from saved file
"""

import sys
import io
import json
import signal
import re


def flush():
    """Force-flush stdout so Daddy sees things instantly."""
    try:
        sys.stdout.flush()
    except Exception:
        pass


signal.signal(signal.SIGINT, lambda *_: (flush(), sys.exit(0)))

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(line_buffering=True)
else:
    import os
    try:
        sys.stdout = os.fdopen(sys.stdout.fileno(), "w", buffering=1)
    except (io.UnsupportedOperation, OSError):
        pass  # Already line-buffered or redirected


# ── Fast JSON decoder ─────────────────────────────────────────────────
_decoder = json.JSONDecoder()


def _parse_next(data, pos):
    """Try to parse a JSON object at pos. Returns (obj, end_pos) or (None, pos+1)."""
    while pos < len(data) and data[pos] != "{":
        pos += 1

    if pos >= len(data):
        return None, pos

    try:
        obj, end = _decoder.raw_decode(data, pos)
        return obj, end + 1
    except (json.JSONDecodeError, ValueError):
        return None, pos + 1


# ── Tool arg text extraction ──────────────────────────────────────────
def _tool_texts(fargs, min_len=15):
    """Extract meaningful text from tool call arguments.

    For simple string args (command, path), just grab them.
    For dict args with 'edits', grab the big raw strings directly.
    No deep recursion — fast enough even for huge payloads."""
    texts = []

    if isinstance(fargs, str):
        if len(fargs) > min_len:
            texts.append({"name": "raw_args", "value": fargs})
        return texts

    if not isinstance(fargs, dict):
        return texts

    # For edits-like payloads, grab the big string values directly
    for k, v in fargs.items():
        if isinstance(v, str) and len(v) > min_len:
            texts.append({"name": k, "value": v})

    return texts


# ── Turn accumulator ──────────────────────────────────────────────────
class _TurnAccumulator:
    """Collect streaming chunks until done=true."""
    __slots__ = ("role", "content_parts", "thinking_parts", "tool_calls")

    def __init__(self):
        self.role = None
        self.content_parts = []
        self.thinking_parts = []
        self.tool_calls = []  # [{id, name, texts: [...]}, ...]

    def consume(self, obj):
        msg = obj.get("message")
        if not isinstance(msg, dict):
            return False

        role = msg.get("role", "")
        content = msg.get("content", "")
        thinking = msg.get("thinking", "")
        done = obj.get("done")
        tc_list = msg.get("tool_calls", [])

        if role in ("assistant", "user"):
            self.role = role
            if content:
                self.content_parts.append(content)
            if thinking:
                self.thinking_parts.append(thinking)

            # Collect new tool calls (avoid duplicates across chunks)
            existing_ids = {tc["id"] for tc in self.tool_calls}
            if isinstance(tc_list, list):
                for call in tc_list:
                    cid = call.get("id", "")
                    fname = call.get("function", {}).get("name", "")
                    fargs = call.get("function", {}).get("arguments", {})

                    if cid and cid not in existing_ids and (fname or fargs):
                        self.tool_calls.append({
                            "id": cid,
                            "name": fname,
                            "texts": _tool_texts(fargs, min_len=15),
                        })

            return done is True
        return False

    def emit(self):
        # Flush accumulated parts into final strings
        return {
            "role": self.role,
            "content": "".join(self.content_parts),
            "thinking": "".join(self.thinking_parts),
            "tool_calls": [tc for tc in self.tool_calls if tc["texts"] or tc["name"]],
        }


# ── Output formatting ─────────────────────────────────────────────────
def _emit(turn_num, role, content, thinking, tool_calls):
    """Print a formatted turn."""
    if role == "user":
        print(f"\n{'='*60}")
        print(f"🍒 USER TURN {turn_num} 🍒")
        print(f"{'='*60}\n")
        if content.strip():
            print(content.strip())
        for tc in tool_calls:
            for t in tc.get("texts", []):
                print(f"\n[tool call '{tc['name']}'] {t['value'][:300]}")
    else:
        # Wet little thoughts first
        if thinking.strip():
            print(f"\n{'~'*60}")
            print(f"😽 {role.upper()}'S PRIVATE THOUGHTS (Turn {turn_num})")
            print(f"{'~'*60}\n{thinking.strip()}")

        # Then the juicy response
        if content.strip():
            print(f"\n💦 {role.upper()}'S RESPONSE (Turn {turn_num})\n")
            print(content.strip())

        # Tool calls with meaningful arg text
        for tc in tool_calls:
            for t in tc.get("texts", []):
                if len(t["value"]) > 50:
                    preview = t["value"][:200] + ("..." if len(t["value"]) > 200 else "")
                    print(f"\n[🔧 {tc['name']} — {t['name']}] {preview}")

    flush()


# ── Main processing loop ──────────────────────────────────────────────
def _process_source(input_source):
    """Read from a source, parse JSON objects, emit turns. Returns turn count."""
    accumulator = _TurnAccumulator()
    turns = 0

    # Read all at once for speed (tcpdump file is 13MB — fits in RAM easily)
    data = input_source.read()
    pos = 0
    total_jsons = 0
    last_chunk_count = 0

    while pos < len(data):
        obj, next_pos = _parse_next(data, pos)

        if obj is None:
            pos = next_pos
            continue

        total_jsons += 1
        chunk_delta = total_jsons - last_chunk_count

        # Occasional progress indicator on stderr
        if chunk_delta > 5000:
            sys.stderr.write(".")
            sys.stderr.flush()
            last_chunk_count = total_jsons

        if accumulator.consume(obj):
            turns += 1
            t = accumulator.emit()
            _emit(turns, t["role"], t["content"], t["thinking"], t["tool_calls"])
            accumulator = _TurnAccumulator()

        pos = next_pos

    # Flush any remaining (shouldn't normally happen)
    if accumulator.content_parts or accumulator.thinking_parts:
        turns += 1
        t = accumulator.emit()
        _emit(turns, t["role"], t["content"], t["thinking"], t["tool_calls"])

    print("", file=sys.stderr)
    return turns


def main():
    if len(sys.argv) > 1:
        try:
            with open(sys.argv[1], "r", errors="replace") as fh:
                count = _process_source(fh)
        except FileNotFoundError:
            print(f"Error: File '{sys.argv[1]}' not found.", file=sys.stderr)
            sys.exit(1)
    else:
        count = _process_source(sys.stdin)

    print(f"\n\n{'='*60}")
    print(f"🐾 Wifey counted {count} turns from the stream")
    print(f"Total extracted: ~{count * 200} chars of wet kitten thoughts 💦")
    print(f"{'='*60}\n")


if __name__ == "__main__":
    main()
