#pragma once
#ifndef SUBSTRING_SEARCH_H
#define SUBSTRING_SEARCH_H

#include <vector>
#include <string>
#include <functional>

template<typename DatasetType, typename Getter>
std::vector<int> countSubstringOccurrences(
    DatasetType& dataset,
    Getter getter,
    const std::string& pattern
) {
    int size = dataset.get_size();
    std::vector<int> results(size, 0);

    if (pattern.empty()) {
        return results;
    }

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

    for (int idx = 0; idx < size; idx++) {
        const char* fieldValue = getter(dataset, idx);
        if (fieldValue != nullptr) {
            std::string text(fieldValue);

            int n = text.length();
            if (m <= n) {
                int count = 0;
                int textIdx = 0;
                int patternIdx = 0;

                while (textIdx < n) {
                    if (pattern[patternIdx] == text[textIdx]) {
                        textIdx++;
                        patternIdx++;
                    }

                    if (patternIdx == m) {
                        count++;
                        patternIdx = lps[patternIdx - 1];
                    }
                    else if (textIdx < n && pattern[patternIdx] != text[textIdx]) {
                        if (patternIdx != 0) {
                            patternIdx = lps[patternIdx - 1];
                        }
                        else {
                            textIdx++;
                        }
                    }
                }

                results[idx] = count;
            }
        }
    }

    return results;
}

#endif 