#pragma once
#include <ranges>
#include <tuple>
#include <variant>

template<typename... ViewTypes>
class VariantView {
    using valueType = std::ranges::range_value_t<std::tuple_element_t<0, std::tuple<ViewTypes...>>>;
public:
    class Iterator {
        std::variant<decltype(std::ranges::begin(std::declval<ViewTypes>()))...> it;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = valueType;
        using reference = value_type&;

        template<typename T>
        Iterator(T it_p) : it(it_p) {}

        Iterator& operator++() {
            return *this;
        }

        reference operator*() {
            static value_type tmp{};
            return tmp;
        }

        friend bool operator==(const Iterator& f, const Iterator& s) { return f.it == s.it; }
    };

    template<typename T>
    VariantView(T&& v) : begin_v(std::ranges::begin(v)), end_v(std::ranges::end(v)) {}
    [[nodiscard]] Iterator begin() { return begin_v; }
    [[nodiscard]] Iterator end() { return end_v; }

private:
    Iterator begin_v, end_v;
};