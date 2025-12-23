#pragma once
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <sstream>

class LZWCompressor {
public:
    static std::vector<uint16_t> compress(const std::string& input);
    static std::string decompress(const std::vector<uint16_t>& compressed);
};

class LZ77Compressor {
public:
    struct LZ77Token {
        uint16_t offset;
        uint16_t length;
        char next_char;

        LZ77Token(uint16_t o, uint16_t l, char n) : offset(o), length(l), next_char(n) {}
    };

    static std::vector<LZ77Token> compress(const std::string& input, size_t window_size = 4096, size_t lookahead_buffer = 18);
    static std::string decompress(const std::vector<LZ77Token>& compressed);
};

class LZ78Compressor {
public:
    struct LZ78Token {
        uint16_t index;
        char next_char;

        LZ78Token(uint16_t i, char n) : index(i), next_char(n) {}
    };

    static std::vector<LZ78Token> compress(const std::string& input);
    static std::string decompress(const std::vector<LZ78Token>& compressed);
};

class DatasetCompression {
private:
    static std::string convertDatasetToString(const std::string& filename);

public:
    static void testAllCompressionAlgorithms(const std::string& datasetFile);
    static void benchmarkCompression(const std::string& datasetFile);
    static void runCompressionDemo();
};