#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <cstring>

class IReadStream {
public:
    virtual ~IReadStream() = default;
    virtual size_t read(void* buffer, size_t size) = 0;
    virtual void seek(uint64_t offset) = 0;
    virtual uint64_t tell() = 0;
    virtual uint64_t size() = 0;
};

class FileReadStream : public IReadStream {
    std::ifstream file;
    uint64_t fileSize;

public:
    FileReadStream(const std::string& path) {
        file.open(path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + path);
        }
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
    }

    size_t read(void* buffer, size_t size) override {
        file.read(static_cast<char*>(buffer), size);
        return file.gcount();
    }

    void seek(uint64_t offset) override {
        file.seekg(offset, std::ios::beg);
    }

    uint64_t tell() override {
        return file.tellg();
    }

    uint64_t size() override {
        return fileSize;
    }
};

class MemoryReadStream : public IReadStream {
    std::vector<uint8_t> buffer;
    uint64_t position = 0;

public:
    MemoryReadStream(std::vector<uint8_t> data) : buffer(std::move(data)) {}

    size_t read(void* target, size_t size) override {
        if (position >= buffer.size()) return 0;
        size_t available = buffer.size() - position;
        size_t toRead = std::min(size, available);
        std::memcpy(target, buffer.data() + position, toRead);
        position += toRead;
        return toRead;
    }

    void seek(uint64_t offset) override {
        if (offset > buffer.size()) {
            throw std::out_of_range("Seek offset beyond buffer size");
        }
        position = offset;
    }

    uint64_t tell() override {
        return position;
    }

    uint64_t size() override {
        return buffer.size();
    }
};
