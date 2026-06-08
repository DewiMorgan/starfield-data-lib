#pragma once

#include "vfs.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <zlib.h>
#include <cstring>

class BA2ReadStream : public IReadStream {
    struct BA2Header {
        char magic[4];
        uint32_t version;
        char type[4];
        uint32_t numFiles;
        uint64_t nameTableOffset;
        uint32_t unknown[3];
    };

    struct BA2FileEntry {
        uint32_t nameHash;
        char extension[4];
        uint32_t dirHash;
        uint32_t flags;
        uint64_t offset;
        uint32_t compressedSize;
        uint32_t realSize;
        uint32_t align;
    };

    std::vector<uint8_t> decompressedBuffer;
    uint64_t position = 0;

public:
    BA2ReadStream(const std::string& ba2Path, const std::string& targetPlugin) {
        std::ifstream ba2File(ba2Path, std::ios::binary);
        if (!ba2File) throw std::runtime_error("Could not open BA2: " + ba2Path);

        BA2Header header;
        ba2File.read(reinterpret_cast<char*>(&header), sizeof(BA2Header));

        // We need to find the target plugin. 
        // BAE source says we read NumFiles entries.
        std::vector<BA2FileEntry> entries(header.numFiles);
        ba2File.read(reinterpret_cast<char*>(entries.data()), header.numFiles * sizeof(BA2FileEntry));

        // Handle Name Table if present
        if (header.nameTableOffset > 0) {
            ba2File.seekg(header.nameTableOffset, std::ios::beg);
            for (uint32_t i = 0; i < header.numFiles; ++i) {
                uint16_t len;
                ba2File.read(reinterpret_cast<char*>(&len), sizeof(len));
                std::vector<char> nameBuf(len);
                ba2File.read(nameBuf.data(), len);
                std::string filename(nameBuf.data(), len);

                if (filename == targetPlugin) {
                    extractFile(ba2File, entries[i]);
                    return;
                }
            }
        } else {
            // If no name table, we can't easily find by name unless we hash the name.
            // But the BAE source suggests NameTable is standard for BA2.
            throw std::runtime_error("BA2 has no name table, cannot find plugin by name");
        }

        throw std::runtime_error("Plugin not found in BA2: " + targetPlugin);
    }

    void extractFile(std::ifstream& ba2File, const BA2FileEntry& entry) {
        ba2File.seekg(entry.offset, std::ios::beg);
        
        if (entry.compressedSize > 0 && entry.compressedSize != entry.realSize) {
            std::vector<uint8_t> compressedData(entry.compressedSize);
            ba2File.read(reinterpret_cast<char*>(compressedData.data()), entry.compressedSize);

            decompressedBuffer.resize(entry.realSize);
            uLongf destLen = entry.realSize;
            int res = uncompress(decompressedBuffer.data(), &destLen, compressedData.data(), entry.compressedSize);
            
            if (res == Z_OK) {
                return;
            }
            
            if (res == Z_DATA_ERROR) {
                // Fallback: treat as stored data if zlib fails
                decompressedBuffer.assign(compressedData.begin(), compressedData.end());
                decompressedBuffer.resize(entry.realSize);
                return;
            }

            throw std::runtime_error("zlib decompression failed with error: " + std::to_string(res));
        } else {
            decompressedBuffer.resize(entry.realSize);
            ba2File.read(reinterpret_cast<char*>(decompressedBuffer.data()), entry.realSize);
        }
    }

    size_t read(void* target, size_t size) override {
        if (position >= decompressedBuffer.size()) return 0;
        size_t available = decompressedBuffer.size() - position;
        size_t toRead = std::min(size, available);
        std::memcpy(target, decompressedBuffer.data() + position, toRead);
        position += toRead;
        return toRead;
    }

    void seek(uint64_t offset) override {
        if (offset > decompressedBuffer.size()) {
            throw std::out_of_range("Seek offset beyond buffer size");
        }
        position = offset;
    }

    uint64_t tell() override {
        return position;
    }

    uint64_t size() override {
        return decompressedBuffer.size();
    }

    static std::vector<std::string> listAllFiles(const std::string& ba2Path) {
        std::ifstream ba2File(ba2Path, std::ios::binary);
        if (!ba2File) return {};

        BA2Header header;
        ba2File.read(reinterpret_cast<char*>(&header), sizeof(BA2Header));

        if (header.nameTableOffset == 0) return {};

        std::vector<std::string> files;
        ba2File.seekg(header.nameTableOffset, std::ios::beg);

        for (uint32_t i = 0; i < header.numFiles; ++i) {
            uint16_t len;
            if (!ba2File.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
            std::vector<char> nameBuf(len);
            if (!ba2File.read(nameBuf.data(), len)) break;
            files.emplace_back(nameBuf.data(), len);
        }
        return files;
    }

    static std::vector<std::string> listPlugins(const std::string& ba2Path) {
        std::vector<std::string> allFiles = listAllFiles(ba2Path);
        std::vector<std::string> plugins;
        for (const auto& f : allFiles) {
            if (f.ends_with(".esm") || f.ends_with(".esp") || f.ends_with(".esl")) {
                plugins.push_back(f);
            }
        }
        return plugins;
    }
};
