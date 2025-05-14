// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_TVECTOR_TVECTOR_H_
#define GAMESTORE_TVECTOR_TVECTOR_H_

#include <iostream>

#define STEP_OF_CAPACITY 15

enum State { empty, busy, deleted };

template <class T>
class TVector {
    T* _data;
    size_t _capacity;
    size_t _size;

 public:
    explicit TVector(size_t size = 0) noexcept;
    TVector(size_t, const T*) noexcept;
    TVector(size_t, std::initializer_list<T>) noexcept;
    TVector(std::initializer_list<T>) noexcept;
    TVector(const TVector<T>&);
    TVector(size_t, const T&) noexcept;

    ~TVector();

    inline bool is_empty() const noexcept;

    inline T* data() noexcept;  // setters
    inline T& front();
    inline T& back();
    inline T* begin() noexcept;
    inline T* end() noexcept;

    inline const T* data() const noexcept;  // getters
    inline const size_t size() const noexcept;
    inline const size_t capacity() const noexcept;
    inline const T& front() const;
    inline const T& back() const;
    inline const T* begin() const noexcept;
    inline const T* end() const noexcept;

    void push_front(const T&) noexcept;
    void push_back(const T&) noexcept;
    void insert(size_t, const T&);

    void pop_front();
    void pop_back();
    void erase(size_t);

    void replace(size_t, const T&);

    void assign(size_t, const T&);
    inline T& at(size_t);
    void clear() noexcept;

    void shrink_to_fit() noexcept;
    void reserve(size_t) noexcept;
    void resize(size_t) noexcept;

    TVector<T>& operator = (const TVector<T>&);
    bool operator == (const TVector<T>&) const;
    bool operator != (const TVector<T>&) const;
    inline const T& operator[] (size_t) const;

    template <class T>
    friend void shuffle(TVector<T>&) noexcept;
    template <class T>
    friend void sort_hoare(TVector<T>&) noexcept;
    template <class T>
    friend void sort_rec(TVector<T>&, size_t, size_t) noexcept;

    template <class T>
    friend int find_first(const TVector<T>&, T);
    template <class T>
    friend int find_last(const TVector<T>&, T);
    template <class T>
    friend int* find_all(const TVector<T>&, T);

 private:
    size_t _deleted;
    State* _states;

    void reset_memory() noexcept;
    void reset_memory_for_delete() noexcept;
    inline bool is_full() const noexcept;
    inline size_t get_right_position(size_t) const noexcept;
    inline void swap_positions(size_t, size_t) noexcept;
};

template <class T>
TVector<T>::TVector(size_t size) noexcept : _size(size) {
    _deleted = 0;
    _capacity = ((_size / STEP_OF_CAPACITY) + 1) * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];

    size_t i = 0;
    for (; i < _size; i++) {
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
TVector<T>::TVector(size_t size, const T* data) noexcept : _size(size) {
    _deleted = 0;
    _capacity = ((_size / STEP_OF_CAPACITY) + 1) * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];

    size_t i = 0;
    for (; i < _size; i++) {
        _data[i] = data[i];
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
TVector<T>::TVector(size_t size, std::initializer_list<T> data) noexcept : 
    _size(size) {
    _deleted = 0;
    _capacity = ((_size / STEP_OF_CAPACITY) + 1) * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];

    size_t i = 0;
    auto it = data.begin();
    for (; i < _size; i++) {
        _data[i] = *it;
        _states[i] = busy;
        it++;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
TVector<T>::TVector(std::initializer_list<T>data) noexcept {
    _size = data.size();
    _deleted = 0;
    _capacity = ((_size / STEP_OF_CAPACITY) + 1) * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];

    size_t i = 0;
    auto it = data.begin();
    for (; it != data.end(); i++) {
        _data[i] = *it;
        _states[i] = busy;
        it++;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
TVector<T>::TVector(const TVector<T>& other) {
    if (&other == NULL) throw std::logic_error
        ("Error in copy constructor: other vector doesn't exist!");
    _size = other._size;
    _deleted = other._deleted;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _states = new State[_capacity];

    size_t i = 0;
    for (; i < _size; i++) {
        _data[i] = other._data[i];
    }
    for (; i < _capacity; i++) {
        _states[i] = other._states[i];
    }
}

template <class T>
TVector<T>::TVector(size_t size, const T& value) noexcept : _size(size) {
    _deleted = 0;
    _capacity = ((_size / STEP_OF_CAPACITY) + 1) * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];

    size_t i = 0;
    for (; i < _size; i++) {
        _data[i] = value;
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
TVector<T>::~TVector() {
    delete[] _data;
    delete[] _states;
}

template <class T>
inline T* TVector<T>::data() noexcept {
    return _data;
}

template <class T>
inline const T* TVector<T>::data() const noexcept {
    return _data;
}

template <class T>
inline const size_t TVector<T>::size() const noexcept {
    return _size;
}

template <class T>
inline const size_t TVector<T>::capacity() const noexcept {
    return _capacity;
}

#endif  // GAMESTORE_TVECTOR_TVECTOR_H_
