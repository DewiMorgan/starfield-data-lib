#include "extractor.hpp"
#include "parser.hpp"
#include <fstream>
#include <iostream>

namespace starfield {

Extractor::Extractor(std::shared_ptr<IReadStream> stream) : m_stream(std::move(stream)) {}

std::vector<uint8_t> Extractor::extractRecord(uint64_t offset) {
    if (!m_stream) return {};

    m_stream->seek(offset);

    // Read the header to find out how big the record is
    RecordHeader header;
    size_t bytesRead = m_stream->read(reinterpret_cast<uint8_t*>(&header), sizeof(RecordHeader));
    
    if (bytesRead != sizeof(RecordHeader)) {
        return {};
    }

    // The total size is the header plus the data size
    uint32_t totalSize = sizeof(RecordHeader) + header.dataSize;
    
    // We've already read the header, so we need (totalSize - sizeof(RecordHeader)) more bytes
    std::vector<uint8_t> blob(totalSize);
    
    // Copy the header we already read into the start of the blob
    std::memcpy(blob.data(), &header, sizeof(RecordHeader));
    
    // Read the rest of the record
    size_t remaining = totalSize - sizeof(RecordHeader);
    if (remaining > 0) {
        size_t readRemaining = m_stream->read(blob.data() + sizeof(RecordHeader), remaining);
        if (readRemaining != remaining) {
            blob.resize(sizeof(RecordHeader) + readRemaining);
        }
    }

    return blob;
}

bool Extractor::extractToFile(uint64_t offset, const std::string& outputPath) {
    auto blob = extractRecord(offset);
    if (blob.empty()) return false;

    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile) return false;

    outFile.write(reinterpret_cast<const char*>(blob.data()), blob.size());
    return outFile.good();
}

} // namespace starfield
