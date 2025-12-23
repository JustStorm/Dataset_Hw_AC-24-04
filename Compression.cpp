#include "Compression.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// LZW Implementation
vector<uint16_t> LZWCompressor::compress(const string& input) {
    unordered_map<string, uint16_t> dictionary;
    vector<uint16_t> output;

    // Initialize dictionary with all possible characters
    for (int i = 0; i < 256; i++) {
        dictionary[string(1, static_cast<char>(i))] = i;
    }

    uint16_t next_code = 256;
    string current;

    for (char c : input) {
        string combined = current + c;
        if (dictionary.find(combined) != dictionary.end()) {
            current = combined;
        }
        else {
            output.push_back(dictionary[current]);
            if (next_code < 65535) {
                dictionary[combined] = next_code++;
            }
            current = string(1, c);
        }
    }

    if (!current.empty()) {
        output.push_back(dictionary[current]);
    }

    return output;
}

string LZWCompressor::decompress(const vector<uint16_t>& compressed) {
    unordered_map<uint16_t, string> dictionary;
    string output;

    // Initialize dictionary with all possible characters
    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, static_cast<char>(i));
    }

    uint16_t next_code = 256;

    string prev = dictionary[compressed[0]];
    output += prev;

    for (size_t i = 1; i < compressed.size(); i++) {
        uint16_t code = compressed[i];
        string current;

        if (dictionary.find(code) != dictionary.end()) {
            current = dictionary[code];
        }
        else if (code == next_code) {
            current = prev + prev[0];
        }

        output += current;

        if (next_code < 65535) {
            dictionary[next_code++] = prev + current[0];
        }

        prev = current;
    }

    return output;
}

// LZ77 Implementation
vector<LZ77Compressor::LZ77Token> LZ77Compressor::compress(const string& input, size_t window_size, size_t lookahead_buffer) {
    vector<LZ77Token> output;
    size_t input_len = input.length();
    size_t pos = 0;

    while (pos < input_len) {
        size_t match_offset = 0;
        size_t match_length = 0;
        char next_char = input[pos];

        size_t search_start = (pos > window_size) ? pos - window_size : 0;
        size_t max_match = min(lookahead_buffer, input_len - pos);

        for (size_t i = search_start; i < pos; i++) {
            size_t j = 0;
            while (j < max_match && input[i + j] == input[pos + j]) {
                j++;
            }

            if (j > match_length) {
                match_length = j;
                match_offset = pos - i;

                if (match_length < max_match) {
                    next_char = input[pos + j];
                }
                else {
                    next_char = '\0';
                }
            }
        }

        if (match_length > 0) {
            output.emplace_back(match_offset, match_length, next_char);
            pos += match_length + (next_char != '\0' ? 1 : 0);
        }
        else {
            output.emplace_back(0, 0, next_char);
            pos++;
        }
    }

    return output;
}

string LZ77Compressor::decompress(const vector<LZ77Token>& compressed) {
    string output;

    for (const auto& token : compressed) {
        if (token.length > 0) {
            size_t start = output.length() - token.offset;
            for (size_t i = 0; i < token.length; i++) {
                output += output[start + i];
            }
        }

        if (token.next_char != '\0') {
            output += token.next_char;
        }
    }

    return output;
}

// LZ78 Implementation
vector<LZ78Compressor::LZ78Token> LZ78Compressor::compress(const string& input) {
    unordered_map<string, uint16_t> dictionary;
    vector<LZ78Token> output;

    dictionary[""] = 0;
    uint16_t next_code = 1;

    string current;

    for (char c : input) {
        string combined = current + c;

        if (dictionary.find(combined) != dictionary.end()) {
            current = combined;
        }
        else {
            output.emplace_back(dictionary[current], c);

            if (next_code < 65535) {
                dictionary[combined] = next_code++;
            }

            current = "";
        }
    }

    if (!current.empty()) {
        output.emplace_back(dictionary[current], '\0');
    }

    return output;
}

string LZ78Compressor::decompress(const vector<LZ78Token>& compressed) {
    vector<string> dictionary;
    dictionary.push_back("");

    string output;

    for (const auto& token : compressed) {
        string entry = dictionary[token.index] + token.next_char;
        output += entry;
        dictionary.push_back(entry);
    }

    return output;
}

// Dataset Compression Utility
string DatasetCompression::convertDatasetToString(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void DatasetCompression::testAllCompressionAlgorithms(const string& datasetFile) {
    cout << "\n=== COMPRESSION ALGORITHMS TESTING ===" << endl;

    try {
        string data = convertDatasetToString(datasetFile);
        size_t original_size = data.size();

        cout << "Original size: " << original_size << " bytes" << endl << endl;

        // LZW
        auto start = chrono::high_resolution_clock::now();
        auto lzw_compressed = LZWCompressor::compress(data);
        auto lzw_end = chrono::high_resolution_clock::now();

        size_t lzw_compressed_size = lzw_compressed.size() * sizeof(uint16_t);
        auto lzw_decompressed = LZWCompressor::decompress(lzw_compressed);
        auto lzw_decompress_end = chrono::high_resolution_clock::now();

        cout << "LZW Algorithm:" << endl;
        cout << "  Compression time: "
            << chrono::duration_cast<chrono::milliseconds>(lzw_end - start).count()
            << " ms" << endl;
        cout << "  Decompression time: "
            << chrono::duration_cast<chrono::milliseconds>(lzw_decompress_end - lzw_end).count()
            << " ms" << endl;
        cout << "  Compressed size: " << lzw_compressed_size << " bytes" << endl;
        cout << "  Compression ratio: " << fixed << setprecision(3) << (double)lzw_compressed_size / original_size << endl;
        cout << "  Efficiency: " << fixed << setprecision(1) << (1.0 - (double)lzw_compressed_size / original_size) * 100.0 << "%" << endl;
        cout << "  Correctness: " << (data == lzw_decompressed ? "PASSED" : "FAILED") << endl << endl;

        // LZ77
        start = chrono::high_resolution_clock::now();
        auto lz77_compressed = LZ77Compressor::compress(data);
        auto lz77_end = chrono::high_resolution_clock::now();

        size_t lz77_compressed_size = lz77_compressed.size() * sizeof(LZ77Compressor::LZ77Token);
        auto lz77_decompressed = LZ77Compressor::decompress(lz77_compressed);
        auto lz77_decompress_end = chrono::high_resolution_clock::now();

        cout << "LZ77 Algorithm:" << endl;
        cout << "  Compression time: "
            << chrono::duration_cast<chrono::milliseconds>(lz77_end - start).count()
            << " ms" << endl;
        cout << "  Decompression time: "
            << chrono::duration_cast<chrono::milliseconds>(lz77_decompress_end - lz77_end).count()
            << " ms" << endl;
        cout << "  Compressed size: " << lz77_compressed_size << " bytes" << endl;
        cout << "  Compression ratio: " << fixed << setprecision(3) << (double)lz77_compressed_size / original_size << endl;
        cout << "  Efficiency: " << fixed << setprecision(1) << (1.0 - (double)lz77_compressed_size / original_size) * 100.0 << "%" << endl;
        cout << "  Correctness: " << (data == lz77_decompressed ? "PASSED" : "FAILED") << endl << endl;

        // LZ78
        start = chrono::high_resolution_clock::now();
        auto lz78_compressed = LZ78Compressor::compress(data);
        auto lz78_end = chrono::high_resolution_clock::now();

        size_t lz78_compressed_size = lz78_compressed.size() * sizeof(LZ78Compressor::LZ78Token);
        auto lz78_decompressed = LZ78Compressor::decompress(lz78_compressed);
        auto lz78_decompress_end = chrono::high_resolution_clock::now();

        cout << "LZ78 Algorithm:" << endl;
        cout << "  Compression time: "
            << chrono::duration_cast<chrono::milliseconds>(lz78_end - start).count()
            << " ms" << endl;
        cout << "  Decompression time: "
            << chrono::duration_cast<chrono::milliseconds>(lz78_decompress_end - lz78_end).count()
            << " ms" << endl;
        cout << "  Compressed size: " << lz78_compressed_size << " bytes" << endl;
        cout << "  Compression ratio: " << fixed << setprecision(3) << (double)lz78_compressed_size / original_size << endl;
        cout << "  Efficiency: " << fixed << setprecision(1) << (1.0 - (double)lz78_compressed_size / original_size) * 100.0 << "%" << endl;
        cout << "  Correctness: " << (data == lz78_decompressed ? "PASSED" : "FAILED") << endl << endl;

        // Find best algorithm
        cout << "=== BEST ALGORITHM BY EFFICIENCY ===" << endl;
        double best_efficiency = 0;
        string best_algorithm;

        double lzw_efficiency = (1.0 - (double)lzw_compressed_size / original_size) * 100.0;
        double lz77_efficiency = (1.0 - (double)lz77_compressed_size / original_size) * 100.0;
        double lz78_efficiency = (1.0 - (double)lz78_compressed_size / original_size) * 100.0;

        if (lzw_efficiency >= lz77_efficiency && lzw_efficiency >= lz78_efficiency) {
            best_efficiency = lzw_efficiency;
            best_algorithm = "LZW";
        }
        else if (lz77_efficiency >= lzw_efficiency && lz77_efficiency >= lz78_efficiency) {
            best_efficiency = lz77_efficiency;
            best_algorithm = "LZ77";
        }
        else {
            best_efficiency = lz78_efficiency;
            best_algorithm = "LZ78";
        }

        cout << "Algorithm: " << best_algorithm
            << " (efficiency: " << fixed << setprecision(1) << best_efficiency << "%)" << endl;

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void DatasetCompression::benchmarkCompression(const string& datasetFile) {
    cout << "\n=== COMPRESSION ALGORITHMS BENCHMARK ===" << endl;
    cout << "=========================================" << endl;

    // Table header
    cout << left << setw(10) << "Algorithm"
        << right << setw(12) << "Compress(ms)"
        << setw(12) << "Decompress(ms)"
        << setw(12) << "Original"
        << setw(10) << "Compressed"
        << setw(10) << "Ratio"
        << setw(10) << "Efficiency%" << endl;

    cout << string(80, '-') << endl;

    try {
        string data = convertDatasetToString(datasetFile);
        size_t original_size = data.size();

        // LZW Benchmark
        auto start = chrono::high_resolution_clock::now();
        auto lzw_compressed = LZWCompressor::compress(data);
        auto lzw_compress_time = chrono::duration_cast<chrono::milliseconds>(
            chrono::high_resolution_clock::now() - start);

        start = chrono::high_resolution_clock::now();
        auto lzw_decompressed = LZWCompressor::decompress(lzw_compressed);
        auto lzw_decompress_time = chrono::duration_cast<chrono::milliseconds>(
            chrono::high_resolution_clock::now() - start);

        size_t lzw_size = lzw_compressed.size() * sizeof(uint16_t);
        double lzw_ratio = (double)lzw_size / original_size;
        double lzw_efficiency = (1.0 - lzw_ratio) * 100.0;

        cout << left << setw(10) << "LZW"
            << right << setw(12) << lzw_compress_time.count()
            << setw(12) << lzw_decompress_time.count()
            << setw(12) << original_size
            << setw(10) << lzw_size
            << setw(10) << fixed << setprecision(3) << lzw_ratio
            << setw(10) << fixed << setprecision(1) << lzw_efficiency << "%" << endl;

        // LZ77 Benchmark
        start = chrono::high_resolution_clock::now();
        auto lz77_compressed = LZ77Compressor::compress(data);
        auto lz77_compress_time = chrono::duration_cast<chrono::milliseconds>(
            chrono::high_resolution_clock::now() - start);

        start = chrono::high_resolution_clock::now();
        auto lz77_decompressed = LZ77Compressor::decompress(lz77_compressed);
        auto lz77_decompress_time = chrono::duration_cast<chrono::milliseconds>(
            chrono::high_resolution_clock::now() - start);

        size_t lz77_size = lz77_compressed.size() * sizeof(LZ77Compressor::LZ77Token);
        double lz77_ratio = (double)lz77_size / original_size;
        double lz77_efficiency = (1.0 - lz77_ratio) * 100.0;

        cout << left << setw(10) << "LZ77"
            << right << setw(12) << lz77_compress_time.count()
            << setw(12) << lz77_decompress_time.count()
            << setw(12) << original_size
            << setw(10) << lz77_size
            << setw(10) << fixed << setprecision(3) << lz77_ratio
            << setw(10) << fixed << setprecision(1) << lz77_efficiency << "%" << endl;

        // LZ78 Benchmark
        start = chrono::high_resolution_clock::now();
        auto lz78_compressed = LZ78Compressor::compress(data);
        auto lz78_compress_time = chrono::duration_cast<chrono::milliseconds>(
            chrono::high_resolution_clock::now() - start);

        start = chrono::high_resolution_clock::now();
        auto lz78_decompressed = LZ78Compressor::decompress(lz78_compressed);
        auto lz78_decompress_time = chrono::duration_cast<chrono::milliseconds>(
            chrono::high_resolution_clock::now() - start);

        size_t lz78_size = lz78_compressed.size() * sizeof(LZ78Compressor::LZ78Token);
        double lz78_ratio = (double)lz78_size / original_size;
        double lz78_efficiency = (1.0 - lz78_ratio) * 100.0;

        cout << left << setw(10) << "LZ78"
            << right << setw(12) << lz78_compress_time.count()
            << setw(12) << lz78_decompress_time.count()
            << setw(12) << original_size
            << setw(10) << lz78_size
            << setw(10) << fixed << setprecision(3) << lz78_ratio
            << setw(10) << fixed << setprecision(1) << lz78_efficiency << "%" << endl;

        // Determine best algorithm
        double best_efficiency = max({ lzw_efficiency, lz77_efficiency, lz78_efficiency });
        string best_algorithm;

        if (best_efficiency == lzw_efficiency) best_algorithm = "LZW";
        else if (best_efficiency == lz77_efficiency) best_algorithm = "LZ77";
        else best_algorithm = "LZ78";

        cout << "\nBEST ALGORITHM: " << best_algorithm
            << " (efficiency: " << fixed << setprecision(1) << best_efficiency << "%)" << endl;

    }
    catch (const exception& e) {
        cout << "Error during benchmarking: " << e.what() << endl;
    }
}

void DatasetCompression::runCompressionDemo() {
    cout << "\n=== COMPRESSION ALGORITHMS DEMONSTRATION ===" << endl;

    string test_data = "ABABABABABABABABABABABABABABABABABABABABABABABABAB"
        "CDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCD"
        "EFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEFEF";

    cout << "Test data pattern: ABAB...CDCD...EFEF..." << endl;
    cout << "Test data size: " << test_data.size() << " bytes" << endl;

    // LZW Demo
    cout << "\n--- LZW Compression Demo ---" << endl;
    auto lzw_result = LZWCompressor::compress(test_data);
    string lzw_decompressed = LZWCompressor::decompress(lzw_result);
    cout << "LZW compressed size: " << lzw_result.size() * sizeof(uint16_t) << " bytes" << endl;
    cout << "LZW test: " << (test_data == lzw_decompressed ? "PASSED" : "FAILED") << endl;

    // LZ77 Demo
    cout << "\n--- LZ77 Compression Demo ---" << endl;
    auto lz77_result = LZ77Compressor::compress(test_data);
    string lz77_decompressed = LZ77Compressor::decompress(lz77_result);
    cout << "LZ77 compressed size: " << lz77_result.size() * sizeof(LZ77Compressor::LZ77Token) << " bytes" << endl;
    cout << "LZ77 test: " << (test_data == lz77_decompressed ? "PASSED" : "FAILED") << endl;

    // LZ78 Demo
    cout << "\n--- LZ78 Compression Demo ---" << endl;
    auto lz78_result = LZ78Compressor::compress(test_data);
    string lz78_decompressed = LZ78Compressor::decompress(lz78_result);
    cout << "LZ78 compressed size: " << lz78_result.size() * sizeof(LZ78Compressor::LZ78Token) << " bytes" << endl;
    cout << "LZ78 test: " << (test_data == lz78_decompressed ? "PASSED" : "FAILED") << endl;

    cout << "\nAll compression algorithms tested successfully!" << endl;
}