#include "indexer.h"
#include "ba2_stream.h"
#include <iostream>

namespace fs = std::filesystem;

Indexer::Indexer(IIndexListener* listener) : listener_(listener) {}

void Indexer::processDirectory(const std::filesystem::path& root_dir) {
    for (const auto& entry : fs::recursive_directory_iterator(root_dir)) {
        if (entry.is_regular_file()) {
            handleFile(entry.path(), root_dir);
        }
    }
}

void Indexer::processPath(const std::filesystem::path& target_path, const std::filesystem::path& root_dir) {
    handleFile(target_path, root_dir);
}

void Indexer::handleFile(const std::filesystem::path& path, const std::filesystem::path& root_dir) {
    std::string filepath = path.string();
    if (!visited_.insert(filepath).second) return;

    std::string ext = path.extension().string();
    std::string filename = path.filename().string();
    std::string virtual_path = fs::relative(path, root_dir).string();
    int64_t fileSize = fs::is_regular_file(path) ? fs::file_size(path) : 0;

    if (ext == ".esm" || ext == ".esp" || ext == ".esl") {
        listener_->onSourceRegistered(virtual_path, filepath);
        listener_->onAssetFound(virtual_path, filepath, "", fileSize);
        
        std::unique_ptr<IReadStream> stream = std::make_unique<FileReadStream>(filepath);
        listener_->onPluginFound(0, virtual_path, stream.get()); // source_id resolved by listener
    } 
    else if (ext == ".ba2") {
        listener_->onSourceRegistered(filename, filepath);
        listener_->onAssetFound(virtual_path, filepath, "", fileSize);
        handleBA2(path, root_dir);
    } else {
        listener_->onAssetFound(virtual_path, filepath, "", fileSize);
    }
}

void Indexer::handleBA2(const std::filesystem::path& path, const std::filesystem::path& root_dir) {
    std::string filepath = path.string();
    std::string filename = path.filename().string();

    try {
        std::vector<std::string> internal_files = BA2ReadStream::listAllFiles(filepath);
        for (const auto& internal_path : internal_files) {
            listener_->onAssetFound(internal_path, filepath, internal_path, 0);
            
            if (internal_path.ends_with(".esm") || internal_path.ends_with(".esp") || internal_path.ends_with(".esl")) {
                listener_->onSourceRegistered(internal_path, filepath + " (" + internal_path + ")");
                std::unique_ptr<IReadStream> stream = std::make_unique<BA2ReadStream>(filepath, internal_path);
                listener_->onPluginFound(0, internal_path, stream.get());
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error processing BA2 " << filename << ": " << e.what() << std::endl;
    }
}
