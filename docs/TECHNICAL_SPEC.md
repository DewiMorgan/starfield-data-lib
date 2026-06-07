# SDL Technical Specification

This document serves as the "Rosetta Stone" for the Starfield Data Library.

## 0. Other Files

`./starfield/vendor/tes5edit/` - this is a copy of the repo for xEdit, an editor written in Pascal. Valuable reference for all data types, etc.

`/mnt/c/Games/Steam/steamapps/common/Starfield/Data` is where the data files we'll be parsing are held, if you want to examine them. Beware: very large, 4G files.

## 1. File Structure (.esm)
- **Main Header**: Starts with `TES4`. Uses a TLV (Tag-Length-Value) structure for metadata (Author, Description, etc.).
- **Record Header (24 bytes)**:
  - `Signature`: 4 bytes (e.g., `WEAP`, `KYWD`, `GRUP`)
  - `Data Size`: 4 bytes (uint32, size of the data following the header)
  - `Flags`: 4 bytes
  - `FormID`: 4 bytes
  - `VCS1`: 4 bytes
  - `Version`: 2 bytes
  - `VCS2`: 2 bytes
- **Total Record Size**: `Data Size + 24 bytes`.

## 2. Record Data (TLV Encoding)
Almost all record data is stored as a sequence of TLV blocks:
- **Tag**: 4 bytes (e.g., `EDID` for EditorID, `WNAM` for Weapon Name) - defines the record type
- **Length**: 2 bytes (uint16, length of the value)
- **Value**: `Length` bytes of binary data.

The tes5edit filenames, variables, etc with "SF" or "SF1" in the names are usually for StarField. 
Others are FO3, FNV, FO4, FO75 (about FallOut), TES3, TES4, TES5 (about The Elder Scrolls).
Things beginning 'wb' (world building?) seem to be about dealing with the ESM file structure.

Check in ./starfield/vendor/tes5edit/Core/wbDefinitionsSF1.pas (200k+ lines) which contains consts and structures to define the tags/record types for Starfield.
Lines 10709-11131: *big* list of tags to human names

## 3. Special Records
- **GRUP (Group Records)**: These act as containers for other records. They have the same 24-byte header but their "Data" contains a list of record offsets.

## 4. MySQL Mapping
user=root pass=root db=starfield
- `records` table: Maps `offset` $\rightarrow$ `form_id` and `signature`.
- `edids` table: Maps `edid` $\rightarrow$ `offset`.

## 6. Deserialization Schema
The library uses a schema-driven approach to convert raw TLV data into structured information.
see: src/schema.h

### Schema Components
- **FieldType**: Defines the expected data type of a tag (`String`, `Int32`, `Float`, `FormID`, `Unknown`).
- **TagInfo**: Maps a 4-character tag (e.g., `WWEI`) to a human-readable label (e.g., "Weight") and a `FieldType`.
- **RecordSchema**: Maps a record signature (e.g., `WEAP`) to its specific set of tags.

The schema is automatically generated from the `wbDefinitionsSF1.pas` source file to ensure comprehensive coverage and consistency with xEdit.

### Universal Tags
Certain tags are common across almost all record types (e.g., `EDID` for EditorID, `FULL` for Full Name).

## 7. Quality Assurance (TDD)
The SDL employs Test-Driven Development to ensure binary compatibility.
- **Binary Mocking**: Tests construct raw binary buffers representing specific record fields.
- **Parser Verification**: The `Parser::parseRecord` function is validated against these buffers to ensure types (Int, Float, String) are extracted correctly.
- **Ground Truth**: Tests are designed to match known xEdit outputs for specific records.

To run tests:
exec("g++ -Istarfield/src starfield/src/parser.cpp starfield/test/test_parser.cpp -o starfield/bin/test_parser && ./starfield/bin/test_parser")

### Git
./starfield is project root.
Within the starfield folder, /test/, /src/, /bin/, /doc/ etc folders exist.
Always commit once tests pass, and after every goal is reached.
