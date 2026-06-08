# Roadmap: Extract & Serialize

This document outlines the TDD-driven plan to move from a searchable index to a full extraction and serialization toolkit for Starfield `.esm` files.

## The Goal
Achieve a perfect "Round-Trip": 
`Original ESM` $\rightarrow$ `Index` $\rightarrow$ `Extract Record` $\rightarrow$ `Modify Field` $\rightarrow$ `Serialize` $\rightarrow$ `Pack ESM` $\rightarrow$ `Bitwise identical (except for the modified field)`.

---

## Phased Execution Plan

### Phase 1: Raw Binary Extraction (The "Blob" Phase)
**Objective**: Isolate specific records as raw bytes without parsing their internals.
- **TDD Focus**: 
    - `test_extract_raw`: Extract by offset $\rightarrow$ Compare against `hexdump`.
    - `test_extract_by_edid`: Use DB index to find offset $\rightarrow$ Extract $\rightarrow$ Verify blob.
- **MVP**: `sdl_extract` CLI tool to dump a record to a `.bin` file.

### Phase 2: Structural Decomposition (The "Object" Phase)
**Objective**: Move from a streaming parser to a stateful `Record` object.
- **TDD Focus**:
    - `test_record_object`: Parse record into object $\rightarrow$ `record.getTlv("TAG")` returns correct value.
    - `test_record_traversal`: Iterate all TLVs without relying on the schema.
- **MVP**: A `Record` class that encapsulates binary data and provides a structured API.

### Phase 3: The Serialization Engine (The "Write" Phase)
**Objective**: Convert `Record` objects back into valid binary sequences.
- **TDD Focus**:
    - `test_serialize_simple`: Manual object $\rightarrow$ Serialize $\rightarrow$ Compare against known-good binary.
    - **The Round-Trip**: `Parse` $\rightarrow$ `Serialize` $\rightarrow$ `Parse`. Final object must be identical to the first.
- **MVP**: A `RecordWriter` class.

### Phase 4: File Reassembly (The "Packer" Phase)
**Objective**: Wrap serialized records into a valid `.esm` container.
- **TDD Focus**:
    - `test_header_generation`: Create a valid ESM header for a set of records.
    - `test_full_roundtrip`: Read small ESM $\rightarrow$ Serialize all $\rightarrow$ Pack into new ESM $\rightarrow$ `diff` with original.
- **MVP**: A tool to re-pack modified records into a new `.esm` file.

### Phase 5: Asset Extraction (The "Resource" Phase)
**Objective**: Link records to their external assets in `.ba2` archives.
- **TDD Focus**:
    - `test_asset_lookup`: Map record (e.g., `WEAP`) to asset path (e.g., `.nif`).
    - `test_ba2_extraction`: Extract asset from BA2 $\rightarrow$ Verify magic bytes/header.
- **MVP**: `sdl_extract_assets` tool to dump all files associated with an EDID.

---

## Definition of Done
The milestone is complete when we can modify a single field in a record and produce a new `.esm` file that the game recognizes as valid and is bit-for-bit identical to the original in all other aspects.
