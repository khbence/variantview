#pragma once
#include <ranges>
#include <tuple>
#include <variant>
template<typename... ViewTypes>
class VariantView {
    using valueType = std::ranges::range_value_t<std::tuple_element_t<0, std::tuple<ViewTypes...>>>;
public:
    class Iterator {
        std::variant<std::ranges::iterator_t<ViewTypes>...> it;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = valueType;
        using pointer = value_type*;
        using reference = value_type&;
        template<typename T>
        Iterator(T it_p) : it(it_p) {}
       // reference operator*()  const{ return *it; }
        pointer operator->() { return it; }
        Iterator& operator++() {
            std::visit([](auto&& arg) { ++arg; }, it);
            return *this;
        }
        Iterator& operator--() {
            std::visit([](auto&& arg) { --arg; }, it);
            return *this;
        }
        value_type operator*() const {
            return std::visit([](auto&& arg) { return *arg; }, it);
        }
        friend bool operator==(const Iterator& f, const Iterator& s) { return f.it == s.it; }
    };
    template<typename T>
    VariantView(T&& v) : begin_v(std::ranges::begin(v)), end_v(std::ranges::end(v)) {}
    VariantView() = default;
    [[nodiscard]] Iterator begin() const { return begin_v; }
    [[nodiscard]] Iterator end() const { return end_v; }
protected:
    Iterator begin_v, end_v;
};

template<typename... ViewTypes>
class OwningVariantView : public VariantView<ViewTypes...> {
    std::variant<ViewTypes...> data;
public:
    template<typename T>
    OwningVariantView(T v) : VariantView<ViewTypes...>(), data(std::move(v)) {
        VariantView<ViewTypes...>::begin_v = std::visit([](auto&& arg) { return arg.begin(); }, data);
        VariantView<ViewTypes...>::end_v = std::visit([](auto&& arg) { return arg.end(); }, data);
    }
};