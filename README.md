# Starfield Data Library (SDL)

A native C++20 toolset for analyzing, indexing, and eventually modifying `.esm` files from the Bethesda game Starfield. 

## Purpose
The eventual goal is to provide a headless, high-performance way for an AI or developer to query game data and generate mods from the command line.
The SDL was created to remove the dependency on proprietary Delphi compilers and GUI-based tools (like xEdit) for Starfield modding.

## Current Status: "The Eyes"
The library can currently "see" and understand the game's data.
- **Binary Parsing**: Implemented a native reader for the `TES4` main header and a robust Record Iterator.
- **Indexing**: A high-speed indexer that scans millions of records and populates a MySQL database.
- **Instant Search**: A CLI tool (`sdl_search`) that allows querying records by EditorID (EDID) and jumping directly to the binary offset.
- **Deserialization**: Implemented a generic **Tag-Length-Value (TLV)** parser. 
- **Supported Records**: Most record types are now comprehensively mapped via automated extraction from xEdit specifications, allowing for wide-scale data extraction.

## Architecture
- **Language**: C++17 (Native WSL2)
- **Index**: MySQL (Localhost)
- **Core Logic**: Uses xEdit source as a specification for binary layouts.

## How to Use
### 1. Index the game
```bash
./bin/starfield_reader --index /path/to/Starfield.esm
```

### 2. Search for a record
```bash
./bin/sdl_search --edid Razorback
```

## Future Roadmap
- [x] **Expanded Mapping**: Support for `NPC_`, `ARMO`, `ITEM` and several others are in schema.h: add all others. Prioritize tags that are simple types  (`String`, `Int32`, `Float`, `FormID`).
- [ ] **The "Hands" (Serializer)**: Implement the ability to write changes back to a new `.esp` file.
- [ ] **Validation**: Build a suite of tests to verify binary compatibility with xEdit.

