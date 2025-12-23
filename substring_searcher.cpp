#include "substring_searcher.h"
#include <cstring>
#include <algorithm>

std::vector<int> SubstringSearcher::computeLPS(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}
int SubstringSearcher::kmpSearch(const std::string& text, const std::string& pattern) {
    if (pattern.empty()) return 0;

    int n = text.length();
    int m = pattern.length();

    if (m > n) return 0;

    std::vector<int> lps = computeLPS(pattern);
    int count = 0;
    int i = 0; 
    int j = 0; 

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            count++; 
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    return count;
}