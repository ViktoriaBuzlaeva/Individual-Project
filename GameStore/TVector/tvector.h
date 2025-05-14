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
    explicit TVector(size_t size = 0);
    TVector(size_t, const T*);
    TVector(size_t, std::initializer_list<T>);
    TVector(std::initializer_list<T>);
    TVector(const TVector<T>&);
    TVector(size_t, const T&);

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
    void insert(size_t, size_t, const T&);
    void insert(size_t, std::initializer_list<T>);

    void pop_front();
    void pop_back();
    void erase(size_t);
    void erase(size_t, size_t);

    void replace(size_t, const T&);

    void assign(size_t, const T&) noexcept;
    void assign(std::initializer_list<T>) noexcept;
    inline const T& at(size_t) const;
    inline T& at(size_t);
    void clear() noexcept;

    void reserve(size_t) noexcept;
    void shrink_to_fit() noexcept;
    void resize(size_t) noexcept;
    void resize(size_t, const T&) noexcept;

    TVector<T>& operator = (const TVector<T>&) noexcept;

    bool operator == (const TVector<T>&) const noexcept;
    bool operator != (const TVector<T>&) const noexcept;

    inline const T& operator[] (size_t) const noexcept;
    inline T& operator[] (size_t) noexcept;

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

    void set_memory(size_t) noexcept;
    void reset_memory() noexcept;
    void reset_memory_for_delete() noexcept;
    inline bool is_full() const noexcept;
    inline size_t get_right_position(size_t) const noexcept;
    inline void swap_positions(size_t, size_t) noexcept;
};

template <class T>
TVector<T>::TVector(size_t size) {
    set_memory(size);

    size_t i = 0;
    for (; i < _size; i++) {
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
TVector<T>::TVector(size_t size, const T* data) {
    set_memory(size);

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
TVector<T>::TVector(size_t size, std::initializer_list<T> data) {
    set_memory(size);

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
TVector<T>::TVector(std::initializer_list<T>data) {
    set_memory(data.size());

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
    for (; i < _size + _deleted; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
    for (; i < _capacity; i++) {
        _states[i] = other._states[i];
    }
}

template <class T>
TVector<T>::TVector(size_t size, const T& value) {
    set_memory(size);

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
inline T& TVector<T>::front() {
    if (is_empty()) throw std::logic_error
        ("Error in front method: vector is empty!");
    return _data[0];
}

template <class T>
inline T& TVector<T>::back() {
    if (is_empty()) throw std::logic_error
        ("Error in back method: vector is empty!");
    return _data[_size + _deleted - 1];
}

template <class T>
inline T* TVector<T>::begin() noexcept {
    return _data;
}

template <class T>
inline T* TVector<T>::end() noexcept {
    return _data + _size + _deleted;
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

template <class T>
inline bool TVector<T>::is_empty() const noexcept {
    return _size == 0;
}

template <class T>
inline const T& TVector<T>::front() const {
    if (is_empty()) throw std::logic_error
        ("Error in front method: vector is empty!");
    return _data[0];
}

template <class T>
inline const T& TVector<T>::back() const {
    if (is_empty()) throw std::logic_error
        ("Error in back method: vector is empty!");
    return _data[_size + _deleted - 1];
}

template <class T>
inline const T* TVector<T>::begin() const noexcept {
    return _data;
}

template <class T>
inline const T* TVector<T>::end() const noexcept {
    return _data + _size + _deleted;
}

template <class T>
void TVector<T>::push_front(const T& value) noexcept {
    _size++;
    if (is_full()) reset_memory();
    for (size_t i = _size + _deleted - 1; i > 0; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[0] = value;
    _states[0] = busy;
}

template <class T>
void TVector<T>::push_back(const T& value) noexcept {
    _size++;
    if (is_full()) reset_memory();
    _data[_size + _deleted - 1] = value;
    _states[_size + _deleted - 1] = busy;
}

template <class T>
void TVector<T>::insert(size_t pos, const T& value) {
    if (pos > _size + _deleted) throw std::logic_error
        ("Error in insert method: position out of range!");
    if (pos == 0) {
        push_front(value);
        return;
    }
    if (pos == _size + _deleted) {
        push_back(value);
        return;
    }
    _size++;
    if (is_full()) reset_memory();
    pos = get_right_position(pos);
    for (size_t i = _size + _deleted - 1; i > pos; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[pos] = value;
    _states[pos] = busy;
}

template <class T>
void TVector<T>::insert(size_t pos, size_t count, const T& value) {
    if (pos > _size + _deleted) throw std::logic_error
        ("Error in insert method: position out of range!");
    _size += count;
    if (is_full()) reset_memory();
    pos = get_right_position(pos);
    for (size_t i = _size + _deleted; i > pos + count; i--) {
        _data[i] = _data[i - 1 - count];
        _states[i] = _states[i - 1 - count];
    }
    for (size_t i = pos, j = 0; j < count; i++, j++) {
        _data[i] = value;
        _states[i] = busy;
    }
}

template <class T>
void TVector<T>::insert(size_t pos, std::initializer_list<T> data) {
    if (pos > _size + _deleted) throw std::logic_error
        ("Error in insert method: position out of range!");
    _size += data.size();
    if (is_full()) reset_memory();
    pos = get_right_position(pos);
    for (size_t i = _size + _deleted; i > pos + data.size(); i--) {
        _data[i] = _data[i - 1 - data.size()];
        _states[i] = _states[i - 1 - data.size()];
    }
    auto it = data.begin();
    for (size_t i = pos, j = 0; j < data.size(); i++, j++) {
        _data[i] = *it;
        _states[i] = busy;
        it++;
    }
}

template <class T>
void TVector<T>::pop_front() {
    if (is_empty()) throw std::logic_error
        ("Error in pop front method: vector is empty!");
    _size--;
    _deleted++;
    _states[0] = deleted;
    reset_memory_for_delete();
}

template <class T>
void TVector<T>::pop_back() {
    if (is_empty()) throw std::logic_error
        ("Error in pop back method: vector is empty!");
    _size--;
    _states[_size + _deleted] = empty;
}

template <class T>
void TVector<T>::erase(size_t pos) {
    if (is_empty()) throw std::logic_error
        ("Error in pop back method: vector is empty!");
    if (pos > _size + _deleted) throw std::logic_error
        ("Error in erase method: position out of range!");
    if (pos == _size + _deleted - 1) {
        pop_back();
    } else {
        _size--;
        pos = get_right_position(pos);
        _deleted++;
        _states[pos] = deleted;
    }
    reset_memory_for_delete();
}

template <class T>
void TVector<T>::erase(size_t pos, size_t count) {
    if (is_empty()) throw std::logic_error
        ("Error in pop back method: vector is empty!");
    if (pos + count >= _size + _deleted) throw std::logic_error
        ("Error in erase method: position out of range!");
    if (pos == _size + _deleted - 1 && count == 1) {
        pop_back();
    } else {
        _size -= count;
        pos = get_right_position(pos);
        _deleted += count;
        for (size_t i = pos, j = 0; j < count; i++, j++) {
            while (_states[i] == deleted) i++;
            _states[i] = deleted;
        }
    }
    reset_memory_for_delete();
}

template <class T>
void TVector<T>::assign(size_t size, const T& value) noexcept {
    _deleted = 0;
    _size = size;
    if (is_full()) {
        set_memory(size);
        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = empty;
        }
    }
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
void TVector<T>::assign(std::initializer_list<T> data) noexcept {
    _deleted = 0;
    _size = data.size();
    if (is_full()) {
        set_memory(data.size());
        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = empty;
        }
    }
    auto it = data.begin();
    size_t i = 0;
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
inline const T& TVector<T>::at(size_t pos) const {
    if (pos >= _size) throw std::logic_error
        ("Error in at method: position out of range!");
    pos = get_right_position(pos);
    return _data[pos];
}

template <class T>
void TVector<T>::clear() noexcept {
    set_memory(0);
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
inline T& TVector<T>::at(size_t pos) {
    if (pos >= _size) throw std::logic_error
        ("Error in at method: position out of range!");
    pos = get_right_position(pos);
    return _data[pos];
}

template <class T>
void TVector<T>::reserve(size_t new_capacity) noexcept {
    if (new_capacity > _capacity) {
        _capacity = new_capacity;

        T* new_data = new T[_capacity];
        State* new_states = new State[_capacity];

        size_t i = 0;
        for (; i < _size + _deleted; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }
        for (; i < _capacity; i++) {
            new_states[i] = empty;
        }

        delete[] _data;
        delete[] _states;

        _data = new_data;
        _states = new_states;
    }
}

template <class T>
void TVector<T>::resize(size_t new_size) noexcept {
    if (new_size != _size) {
        size_t old_size = _size;
        _size = new_size;

        reset_memory();

        if (_size > old_size) {
            for (size_t i = old_size + _deleted; i < _size; i++) {
                _states[i] = busy;
            }
        }
    }
}

template <class T>
void TVector<T>::resize(size_t new_size, const T& value) noexcept {
    if (new_size != _size) {
        size_t old_size = _size;
        resize(new_size);

        if (_size > old_size) {
            for (size_t i = old_size + _deleted; i < _size; i++) {
                _data[i] = value;
            }
        }
    }
}

template <class T>
TVector<T>& TVector<T>::operator = (const TVector<T>& other) noexcept {
    if (this != &other) {
        delete[] _data;
        delete[] _states;

        _deleted = other._deleted;
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        _states = new State[_capacity];

        size_t i = 0;
        for (; i < _size + _deleted; i++) {
            _data[i] = other._data[i];
            _states[i] = other._states[i];
        }
        for (; i < _capacity; i++) {
            _states[i] = empty;
        }
    }
    return *this;
}

template <class T>
bool TVector<T>::operator == (const TVector<T>& other) const noexcept {
    if (_size != other._size) return false;
    for (size_t i = 0, j = 0; i < _size + _deleted; i++, j++) {
        while (_states[i] != busy) i++;
        while (other._states[j] != busy) j++;
        if (_data[i] != other._data[j]) return false;
    }
    return true;
}

template <class T>
bool TVector<T>::operator != (const TVector<T>& other) const noexcept {
    return !(*this == other);
}

template <class T>
inline const T& TVector<T>::operator[] (size_t pos) const noexcept {
    get_right_position(pos);
    return _data[pos];
}

template <class T>
inline T& TVector<T>::operator[] (size_t pos) noexcept {
    get_right_position(pos);
    return _data[pos];
}

template <class T>
void TVector<T>::set_memory(size_t size) noexcept {
    delete[] _data;
    delete[] _states;
    _deleted = 0;
    if (_size != size) _size = size;
    _capacity = ((_size + _deleted) / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
}

template <class T>
void TVector<T>::reset_memory() noexcept {
    _capacity = ((_size + _deleted) / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;

    T* new_data = new T[_capacity];
    State* new_states = new State[_capacity];

    size_t i = 0;
    for (; i < _size + _deleted; i++) {
        new_data[i] = _data[i];
        new_states[i] = _states[i];
    }
    for (; i < _capacity; i++) {
        new_states[i] = empty;
    }

    delete[] _data;
    delete[] _states;

    _data = new_data;
    _states = new_states;
}

template <class T>
void TVector<T>::reset_memory_for_delete() noexcept {
    if (_size == 0) {
        clear();
    } else if (_deleted >= 0.15 * _size) {
        _deleted = 0;
        _capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;

        T* new_data = new T[_capacity];
        State* new_states = new State[_capacity];

        size_t j = 0;
        for (size_t i = 0; j < _size + _deleted; i++) {
            if (_states[i] == busy) {
                new_data[j] = _data[i];
                new_states[j] = busy;
                j++;
            }
        }
        for (; j < _capacity; j++) {
            new_states[j] = empty;
        }

        delete[] _data;
        delete[] _states;

        _data = new_data;
        _states = new_states;
    }
}

template <class T>
inline bool TVector<T>::is_full() const noexcept {
    return _size + _deleted >= _capacity;
}

template <class T>
size_t TVector<T>::get_right_position(size_t pos) const noexcept {
    if (_deleted == 0) return pos;
    size_t count_busy = 0;
    for (size_t i = 0; i != pos; i++) {
        if (_states[i] == busy) {
            if (pos == count_busy) return i;
            count_busy++;
        }
    }
}

#endif  // GAMESTORE_TVECTOR_TVECTOR_H_
