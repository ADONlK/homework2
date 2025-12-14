#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <cassert>

class SparseVector
{
private:
    struct node
    {
        int index;
        int value;
        node* next;
        node(int i, int v, node* n = nullptr) : index(i), value(v), next(n) {}
    };

    int size;
    node* head;

    // helpers
    void clear();
    void copyList(const SparseVector& sv);
    void setNonzeroElem(int index, int value);
    void removeElem(int index);
    void removeZeros();
    void addSubVector(const SparseVector& sv, bool add);
    void checkListOrder() const;

public:
    explicit SparseVector(int size);
    SparseVector(const SparseVector& sv);
    ~SparseVector();

    SparseVector& operator=(const SparseVector& sv);

    int getSize() const;
    int getElem(int index) const;
    void setElem(int index, int value);

    SparseVector& operator+=(const SparseVector& sv);
    SparseVector& operator-=(const SparseVector& sv);

    SparseVector operator+(const SparseVector& sv) const;
    SparseVector operator-(const SparseVector& sv) const;

    bool operator==(const SparseVector& sv) const;
    bool operator!=(const SparseVector& sv) const;
};

#endif
