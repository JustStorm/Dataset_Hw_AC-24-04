#pragma once

#include <vector>
#include <cstring>
#include <algorithm>

template<typename Dataset, typename Getter>
void merge_sort(Dataset& ds, int size, Getter get) {
    if (size <= 1) return;

    std::vector<int> indices(size);
    for (int i = 0; i < size; ++i) {
        indices[i] = i;
    }

    std::vector<int> temp(size);

    auto merge = [&](int left, int mid, int right) {
        int i = left;
        int j = mid;
        int k = left;

        while (i < mid && j < right) {
            auto val_i = get(indices[i]);
            auto val_j = get(indices[j]);

            if (val_i <= val_j) {
                temp[k++] = indices[i++];
            }
            else {
                temp[k++] = indices[j++];
            }
        }

        while (i < mid) {
            temp[k++] = indices[i++];
        }

        while (j < right) {
            temp[k++] = indices[j++];
        }

        for (int idx = left; idx < right; ++idx) {
            indices[idx] = temp[idx];
        }
        };

    for (int width = 1; width < size; width *= 2) {
        for (int left = 0; left < size; left += 2 * width) {
            int mid = std::min(left + width, size);
            int right = std::min(left + 2 * width, size);

            if (mid < right) {
                merge(left, mid, right);
            }
        }
    }

    std::vector<bool> placed(size, false);
    for (int cycle_start = 0; cycle_start < size; ++cycle_start) {
        if (placed[cycle_start] || indices[cycle_start] == cycle_start) {
            placed[cycle_start] = true;
            continue;
        }

        int current = cycle_start;
        while (!placed[current]) {
            placed[current] = true;
            int next = indices[current];
            if (next != cycle_start && !placed[next]) {
                ds.swapitems(current, next);
            }
            current = next;
        }
    }
}

template<typename Dataset, typename Getter>
void merge_sort_string(Dataset& ds, int size, Getter get) {
    if (size <= 1) return;

    std::vector<int> indices(size);
    for (int i = 0; i < size; ++i) {
        indices[i] = i;
    }

    std::vector<int> temp(size);

    auto merge = [&](int left, int mid, int right) {
        int i = left;
        int j = mid;
        int k = left;

        while (i < mid && j < right) {
            const char* str_i = get(indices[i]);
            const char* str_j = get(indices[j]);

            if (std::strcmp(str_i, str_j) <= 0) {
                temp[k++] = indices[i++];
            }
            else {
                temp[k++] = indices[j++];
            }
        }

        while (i < mid) {
            temp[k++] = indices[i++];
        }

        while (j < right) {
            temp[k++] = indices[j++];
        }

        for (int idx = left; idx < right; ++idx) {
            indices[idx] = temp[idx];
        }
        };

    for (int width = 1; width < size; width *= 2) {
        for (int left = 0; left < size; left += 2 * width) {
            int mid = std::min(left + width, size);
            int right = std::min(left + 2 * width, size);

            if (mid < right) {
                merge(left, mid, right);
            }
        }
    }

    std::vector<bool> placed(size, false);
    for (int cycle_start = 0; cycle_start < size; ++cycle_start) {
        if (placed[cycle_start] || indices[cycle_start] == cycle_start) {
            placed[cycle_start] = true;
            continue;
        }

        int current = cycle_start;
        while (!placed[current]) {
            placed[current] = true;
            int next = indices[current];
            if (next != cycle_start && !placed[next]) {
                ds.swapitems(current, next);
            }
            current = next;
        }
    }
}
