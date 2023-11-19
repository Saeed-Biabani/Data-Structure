#ifndef __SPARSE_H__
#define __SPARSE_H__

#include <iostream>
#include <fstream>
#include <assert.h>
#include <filesystem>
#include <sstream>

#include "StringUtils.hxx"

using namespace std;
using namespace filesystem;

struct Header {
    size_t numRows;
    size_t numCols;
    size_t numNoneZero;
};


template <typename _T>
struct CELL {
    int x;
    int y;
    _T key;
};


template <typename _T>
class Sparse {
    private:
        mutable string name;
        mutable Header header;
        mutable CELL<_T> *row;

    public:
        Sparse() = default;
        Sparse(string name, Header header, CELL<_T> *row);
        void LoadMatrixFromFile(string fname) const noexcept;
        Sparse<_T> Transpose() const noexcept;
        void View() const noexcept;
};


template <typename _T>
inline Sparse<_T>::Sparse(string name, Header header, CELL<_T> *row) {
    this->name = name;
    this->header = header;
    this->row = row;
}


template <typename _T>
inline void Sparse<_T>::LoadMatrixFromFile(string fname) const noexcept {
    path PATH(fname);
    assert(PATH.extension() == ".txt");

    this->name = PATH.stem();

    fstream file_;
    file_.open(PATH, ios :: in);

    string line;

    getline(file_, line);
    auto bag = Split<_T>(line, ' ', 3);
    this->header.numRows = bag[0];
    this->header.numCols = bag[1];
    this->header.numNoneZero = bag[2];

    this->row = new CELL<_T>[this->header.numNoneZero];

    for (int i = 0; i < this->header.numNoneZero; i++) {
        getline(file_, line);
        bag = Split<_T>(line, ' ', 3);

        this->row[i].x = bag[0];
        this->row[i].y = bag[1];
        this->row[i].key = bag[2];
    }
}


template <typename _T>
inline void Sparse<_T>::View() const noexcept{
    cout << this->name << endl;
    cout << this->header.numRows << ' ' << this->header.numCols << ' ' << this->header.numNoneZero << endl;
    for (int i = 0; i < this->header.numNoneZero; i++) {
        cout << this->row[i].x << ' ' << this->row[i].y << ' ' << this->row[i].key << endl;
    }
}


template <typename _T>
inline Sparse<_T> Sparse<_T>::Transpose() const noexcept {
    stringstream Tname;
    Tname << this->name << '-' << "Transpose";

    Header Theader;
    Theader.numRows = this->header.numCols;
    Theader.numCols = this->header.numRows;
    Theader.numNoneZero = this->header.numNoneZero;

    CELL<_T> *Trow = new CELL<_T>[this->header.numNoneZero];
 
    int *count = new int[this->header.numCols];
    fill(count, count + this->header.numCols + 1, 0);

    for (int i = 0; i < this->header.numNoneZero; i++)
        count[this->row[i].y]++;

    int *indx = new int[this->header.numCols];
    indx[0] = 0;

    for (int i = 1; i < this->header.numCols; i++) {
        indx[i] = indx[i - 1] + count[i - 1];
    }

    int pos;
    for (int i = 0; i < this->header.numNoneZero; i++) {
        pos = indx[this->row[i].y]++;
        Trow[pos].x = this->row[i].y;
        Trow[pos].y = this->row[i].x;
        Trow[pos].key = this->row[i].key;
    }

    return Sparse<_T>(Tname.str(), Theader, Trow);
}


#endif //!__SPARSE_H__