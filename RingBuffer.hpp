
#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>


template<typename T, std::size_t N>
class RingBuffer {
public:
    static_assert(N > 0, "Size must be greater than zero");

    // Стандартные алиасы
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    // Вложенный forward-итератор
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(RingBuffer* buf, size_type pos, size_type count)
            : buf_(buf), pos_(pos), traveled_(count) {
        }

        reference operator*() const { return buf_->buffer_[pos_]; }
        pointer operator->() const { return &buf_->buffer_[pos_]; }

        iterator& operator++() {
            pos_ = (pos_ + 1) % N;
            ++traveled_;
            return *this;
        }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const iterator& other) const { return traveled_ == other.traveled_; }
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        RingBuffer* buf_;
        size_type pos_;
        size_type traveled_;
    };

    using const_iterator = typename std::add_const<iterator>::type;

    // Конструктор
    RingBuffer() : head_(0), tail_(0), count_(0) {}

    // Добавление элемента
    void push(const T& item) {
        buffer_[head_] = item;
        head_ = (head_ + 1) % N;
        if (count_ < N) {
            ++count_;
        }
        else {
            tail_ = (tail_ + 1) % N;
        }
    }

    // Извлечение элемента
    bool pop(T& item) {
        if (empty()) return false;
        item = buffer_[tail_];
        tail_ = (tail_ + 1) % N;
        --count_;
        return true;
    }

    // Очистка буфера
    void clear() noexcept {
        head_ = tail_ = count_ = 0;
    }

    // Оператор доступа по индексу
    reference operator[](size_type index) {
        return buffer_[(tail_ + index) % N];
    }
    const_reference operator[](size_type index) const {
        return buffer_[(tail_ + index) % N];
    }

    // Итераторы для range-based for
    iterator begin() {
        return iterator(this, tail_, 0);
    }
    iterator end() {
        return iterator(this, head_, count_);
    }
    const_iterator begin() const {
        return const_iterator(const_cast<RingBuffer*>(this), tail_, 0);
    }
    const_iterator end() const {
        return const_iterator(const_cast<RingBuffer*>(this), head_, count_);
    }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend()   const { return end(); }

    // Свойства
    bool empty() const noexcept { return count_ == 0; }
    bool full()  const noexcept { return count_ == N; }
    size_type size() const noexcept { return count_; }
    constexpr size_type capacity() const noexcept { return N; }

private:
    T buffer_[N] = {};
    size_type head_, tail_, count_;
};

#endif // RING_BUFFER_HPP