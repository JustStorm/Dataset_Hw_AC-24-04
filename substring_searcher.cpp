#include "substring_searcher.h"
#include <cstring>
#include <algorithm>

// Вычисление префикс-функции для KMP алгоритма
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

// Поиск всех вхождений подстроки в текст с помощью KMP
int SubstringSearcher::kmpSearch(const std::string& text, const std::string& pattern) {
    if (pattern.empty()) return 0;

    int n = text.length();
    int m = pattern.length();

    if (m > n) return 0;

    std::vector<int> lps = computeLPS(pattern);
    int count = 0;
    int i = 0; // индекс для текста
    int j = 0; // индекс для паттерна

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            count++; // найдено вхождение
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