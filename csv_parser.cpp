#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>

std::mutex queue_mutex;
std::queue<std::vector<std::vector<std::string>>> parsed_data_queue;
std::atomic<bool> done(false);

void parse_chunk(std::string &&chunk, char delimiter) {
    std::vector<std::vector<std::string>> parsed_chunk;
    std::istringstream stream(chunk);
    std::string line;
    
    while (std::getline(stream, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        
        while (std::getline(ss, cell, delimiter)) {
            row.push_back(std::move(cell));  // Move semantics in action
        }
        parsed_chunk.push_back(std::move(row));  // Move semantics in action
    }

    std::lock_guard<std::mutex> lock(queue_mutex);
    parsed_data_queue.push(std::move(parsed_chunk));  // Move parsed chunk
}

void process_file(const std::string &filename, char delimiter, size_t num_threads) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file\n";
        return;
    }

    std::vector<std::thread> threads;
    std::string chunk;
    size_t chunk_size = 1024 * 1024;  // 1MB chunk size

    while (file) {
        chunk.clear();
        chunk.reserve(chunk_size);
        std::string line;

        while (file.tellg() < static_cast<std::streampos>(chunk_size) && std::getline(file, line)) {
            chunk += line + "\n";
        }

        if (!chunk.empty()) {
            threads.emplace_back(parse_chunk, std::move(chunk), delimiter);
            if (threads.size() >= num_threads) {
                for (auto &t : threads) t.join();
                threads.clear();
            }
        }
    }

    for (auto &t : threads) t.join();
    done = true;
}

int main() {
    std::string filename = "large.csv";
    char delimiter = ',';
    size_t num_threads = std::thread::hardware_concurrency();

    std::cout << "Parsing file with " << num_threads << " threads...\n";
    process_file(filename, delimiter, num_threads);

    std::cout << "Parsing complete! Processed chunks: " << parsed_data_queue.size() << "\n";
    return 0;
}