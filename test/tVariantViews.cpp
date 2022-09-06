#include "variantView.hpp"
#include "gtest/gtest.h"
#include <vector>
#include <list>
#include <ranges>

TEST(VariantViewTest, iterable) {
    std::vector<int> c1{2, 3};
    std::list<int> c2;
    auto v1 = c1 | std::views::all;
    auto v2 = c2 | std::views::all;
    VariantView<decltype(v1), decltype(v2)> vv{v1};
    for(auto it = std::ranges::begin(c1); const auto& e : vv) {
        ASSERT_EQ(e, *it);
        std::ranges::advance(it, 1);
    }
}

TEST(OwningVariantViewTest, iterable) {
    std::vector<int> c1{2, 3};
    std::list<int> c2{5, 8, 11};
    auto v1 = c1 | std::views::all;
    auto copy = c2;
    VariantView<decltype(v1), decltype(c2)> vv{c2};
    for(auto it = std::ranges::begin(copy); const auto& e : vv) {
        ASSERT_EQ(e, *it);
        std::ranges::advance(it, 1);
    }
}