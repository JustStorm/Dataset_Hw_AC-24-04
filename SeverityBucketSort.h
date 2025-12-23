#pragma once
#include <vector>
#include <cstddef>

template <class Dataset, typename getter>
inline void bucket_sort_by_severity(Dataset& ds, int n, getter get) {
    if (n <= 1) return;

    auto mn = get(0);
    auto mx = mn;
    for (int i = 1; i < n; ++i) {
        auto s = get(i);
        if (s < mn) mn = s;
        if (s > mx) mx = s;
    }

    const int k = static_cast<int>(mx - mn + 1);
    if (k <= 0) return;

    std::vector<std::size_t> cnt(static_cast<std::size_t>(k), 0);
    for (int i = 0; i < n; ++i) {
        const int b = static_cast<int>(get(i) - mn);
        ++cnt[static_cast<std::size_t>(b)];
    }

    std::vector<std::size_t> start(cnt.size(), 0);
    for (std::size_t b = 1; b < cnt.size(); ++b)
        start[b] = start[b - 1] + cnt[b - 1];

    std::vector<std::size_t> order(static_cast<std::size_t>(n));
    auto write_pos = start;
    for (int i = 0; i < n; ++i) {
        const int b = static_cast<int>(get(i) - mn);
        const std::size_t pos = write_pos[static_cast<std::size_t>(b)]++;
        order[pos] = static_cast<std::size_t>(i);
    }

    std::vector<std::size_t> label_at_pos(static_cast<std::size_t>(n));
    std::vector<std::size_t> pos_of_label(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        label_at_pos[static_cast<std::size_t>(i)] = static_cast<std::size_t>(i);
        pos_of_label[static_cast<std::size_t>(i)] = static_cast<std::size_t>(i);
    }

    for (int pos = 0; pos < n; ++pos) {
        const std::size_t want = order[static_cast<std::size_t>(pos)];
        const std::size_t cur = label_at_pos[static_cast<std::size_t>(pos)];
        if (cur == want) continue;

        const std::size_t p2 = pos_of_label[want];
        ds.swapitems(pos, static_cast<int>(p2));

        const std::size_t a = label_at_pos[static_cast<std::size_t>(pos)];
        const std::size_t b = label_at_pos[p2];
        label_at_pos[static_cast<std::size_t>(pos)] = b;
        label_at_pos[p2] = a;
        pos_of_label[a] = p2;
        pos_of_label[b] = static_cast<std::size_t>(pos);
    }
}
