# Starfield ESM File Structure
The .esm file format is a contiguous stream of records. There is no separate global file header or fixed-size metadata block.

- The file begins immediately with the first record.
- The first record is the "File Header record".
- This first record is structurally identical to all other records in the file, consisting of a `RecordHeader` (24 bytes) and a data payload consisting of TLVs.
- The signature of this first record is always "TES4".
- To a parser, an .esm file is effectively a `std::vector<Record>`, where `records[0]` is the file header.
