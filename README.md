# High-Performance CSV Parser 🚀  

## Overview  
This project implements a high-performance CSV parser in C++ using **multi-threading** and **move semantics** to efficiently process large CSV files. It reads the file in chunks, parses them concurrently, and stores the processed data in a thread-safe queue.  

## Features  
✅ **Multi-threaded Parsing** – Utilizes multiple CPU cores for fast processing.  
✅ **Move Semantics Optimization** – Reduces unnecessary data copies.  
✅ **Efficient Chunk Processing** – Reads large files in 1MB chunks.  
✅ **Thread-Safe Queue** – Stores parsed data safely across threads.  
✅ **Automatic Thread Management** – Dynamically assigns threads based on system capability.  

## Technologies Used  
- C++ (Modern C++17/20)  
- Multi-threading (`std::thread`, `std::mutex`, `std::atomic`)  
- File Handling (`std::ifstream`)  
- Data Processing (`std::vector`, `std::queue`, `std::string`)  

## Installation & Usage  

### Prerequisites  
Ensure you have:  
✅ A C++17 or newer compiler (GCC, Clang, MSVC)  
✅ A large CSV file for testing  

### Compilation  
Use the following command to compile:  
```bash
g++ -std=c++17 -pthread -o csv_parser csv_parser.cpp
```
### Running the Parser
```
./csv_parser <filename> <delimiter>
```
Example:
```
./csv_parser large.csv ,
```
This will parse large.csv using , as the delimiter and utilize all available CPU cores for processing.

### Expected Output
``` bash
Parsing file with 8 threads...
Parsing complete! Processed chunks: 15
```


### Performance Considerations
- The program automatically selects the optimal number of threads (`std::thread::hardware_concurrency()`).
- Uses `std::move` for efficient memory management.
- Processes files in 1MB chunks to balance I/O and computation.

### Future Enhancements
🔹 Support for different chunk sizes based on file size.  
🔹 Error handling for malformed CSVs.  
🔹 Writing parsed data to an output file.

### License
📜 MIT License

### Author
👤 Srinath Duvvuri
📧 duvvurisrinath@gmail.com
