#include <iostream>
#include <sstream>
#include <assert.h>

using namespace std;

template <typename _T, size_t _C>
class Stack {
    public:
        size_t __capacity = _C;
        int __top;
        _T *__begin;

    public:
        Stack();
        
        void View();
        
        constexpr bool IsEmpty() const;
        constexpr bool IsFull() const;

        void Push(_T value) noexcept;
        const _T Pop() noexcept;
        constexpr _T Peek() const noexcept;
};


template <typename _T, size_t _C>
Stack<_T, _C>::Stack() {
    this->__top = 0;
    this->__begin = new _T[this->__capacity];
}


template <typename _T, size_t _C>
void Stack<_T, _C>::View() {
    stringstream ss;

    ss << "[ ";
    for (int i = 0; i < this->__top; i++) {
        ss << this->__begin[i] << ' ';
    }
    ss << ']';

    cout << ss.str() << endl;
}


template <typename _T, size_t _C>
constexpr bool Stack<_T, _C>::IsEmpty() const {
    return this->__top == 0;
}


template <typename _T, size_t _C>
constexpr bool Stack<_T, _C>::IsFull() const {
    return this->__top == this->__capacity;
}


template <typename _T, size_t _C>
void Stack<_T, _C>::Push(_T value) noexcept {
    assert(!this->IsFull());

    this->__begin[this->__top] = value;
    this->__top++;
}


template <typename _T, size_t _C>
const _T Stack<_T, _C>::Pop() noexcept {
    assert(!this->IsEmpty());

    _T item = this->__begin[this->__top];
    this->__top--;
    
    return item;
}