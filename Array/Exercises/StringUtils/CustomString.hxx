#ifndef __CUSTOM_STRING_H__
#define __CUSTOM_STRING_H__


#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>


using namespace std;


inline void Copy(const char *begin, const char *end, char *res) noexcept {
    while (begin != end) {
        *res = *begin;
        res++;
        begin++;
    }
}


inline void CopyBackward(const char *begin, const char *end, char *res) noexcept {
    char *ptr = res;
    end--;
    while (end != begin - 1) {
        *ptr = *end;
        ptr++;
        end--;
    }
}


inline const char* Slice(const char *str, int start, int end) noexcept {
    char *new_ = new char[end - start];
    Copy(str+start, str+end, new_);
    return new_;
}


inline const int Length(const char *str) noexcept {
    int size = 0;
    while (str[size] != '\0') size++;
    return size;
}


inline const char* Concatenate(const char *str_1, const char *str_2) noexcept {
    size_t str_1_len = Length(str_1);
    size_t str_2_len = Length(str_2);

    char *new_ = new char[str_1_len + str_2_len];

    Copy(str_1, str_1+str_1_len, new_);
    Copy(str_2, str_2+str_2_len, new_ + str_1_len);

    return new_;
}


inline const char* Concatenate(const char *str_1, const char *str_2, const char sep) noexcept {
    size_t str_1_len = Length(str_1);
    size_t str_2_len = Length(str_2);

    char *new_ = new char[str_1_len + str_2_len + 1];

    Copy(str_1, str_1+str_1_len, new_);
    *(new_ + str_1_len) = sep;
    Copy(str_2, str_2+str_2_len, new_ + str_1_len + 1);

    return new_;
}


inline const char* Reverse(const char *str) noexcept {
    size_t str_len = Length(str);
    char *new_ = new char[str_len];
    CopyBackward(str, str + str_len, new_);
    return new_;
}


inline int Find(const char *begin, const char *end, const char key) noexcept {
    int tmp = 0, indx = -1;
    while (begin != end) {
        if (*begin == key) {
            indx = tmp;
            break;
        }
        tmp++;
        begin++;
    }
    return indx;
}


inline vector<const char*> Split(const char *str, const char delim) noexcept {
    vector<const char*> res;
    int indx = 0;
    const char *token;
    size_t str_len = Length(str);

    while (true) {
        indx = Find(str, str + Length(str), delim);
        if (indx == -1) {
            token = Slice(str, 0, Length(str));
            res.push_back(token);
            break;
        } else {
            token = Slice(str, 0, indx);
            str = Slice(str, indx + 1, Length(str));
            res.push_back(token);
        }
    }
    return res;
}

inline const char* Inject(const char *str, const int pos, const char *key) noexcept {
    size_t str_len = Length(str);
    size_t key_len = Length(key);
    char *new_ = new char[str_len + key_len];

    Copy(str, str + pos, new_);
    Copy(key, key + key_len, new_ + pos);
    Copy(str + pos, str + str_len, new_ + pos + key_len);

    return new_;
}

#endif // !__CUSTOM_STRING_H__