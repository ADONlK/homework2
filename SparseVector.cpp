#include "SparseVector.h"



SparseVector::SparseVector(int size) : size(size), head(nullptr)
{
    assert(size >= 0);
}

SparseVector::SparseVector(const SparseVector& sv) : size(0), head(nullptr)
{
    copyList(sv);
}

SparseVector::~SparseVector()
{
    clear();
}


void SparseVector::clear()
{
    node* curr = head;
    while (curr)
    {
        node* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;
}

void SparseVector::copyList(const SparseVector& sv)
{
    clear();
    size = sv.size;

    if (!sv.head)
        return;

    head = new node(sv.head->index, sv.head->value);
    node* dst = head;
    node* src = sv.head->next;

    while (src)
    {
        dst->next = new node(src->index, src->value);
        dst = dst->next;
        src = src->next;
    }

    checkListOrder();
}

void SparseVector::checkListOrder() const
{
    node* curr = head;
    while (curr && curr->next)
    {
        assert(curr->index < curr->next->index);
        curr = curr->next;
    }
}



SparseVector& SparseVector::operator=(const SparseVector& sv)
{
    if (this != &sv)
        copyList(sv);
    return *this;
}



int SparseVector::getSize() const
{
    return size;
}

int SparseVector::getElem(int index) const
{
    assert(index >= 0 && index < size);
    checkListOrder();

    node* curr = head;
    while (curr)
    {
        if (curr->index == index)
            return curr->value;
        if (curr->index > index)
            return 0;
        curr = curr->next;
    }
    return 0;
}



void SparseVector::setElem(int index, int value)
{
    assert(index >= 0 && index < size);

    if (value == 0)
        removeElem(index);
    else
        setNonzeroElem(index, value);
}

void SparseVector::setNonzeroElem(int index, int value)
{
    assert(value != 0);

    node* curr = head;
    node* prev = nullptr;

    while (curr && curr->index < index)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr && curr->index == index)
    {
        curr->value = value;
    }
    else
    {
        node* n = new node(index, value, curr);
        if (prev)
            prev->next = n;
        else
            head = n;
    }

    checkListOrder();
}

void SparseVector::removeElem(int index)
{
    node* curr = head;
    node* prev = nullptr;

    while (curr && curr->index < index)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr && curr->index == index)
    {
        if (prev)
            prev->next = curr->next;
        else
            head = curr->next;
        delete curr;
    }

    checkListOrder();
}



bool SparseVector::operator==(const SparseVector& sv) const
{
    if (size != sv.size)
        return false;

    node* a = head;
    node* b = sv.head;

    while (a && b)
    {
        if (a->index != b->index || a->value != b->value)
            return false;
        a = a->next;
        b = b->next;
    }

    return a == nullptr && b == nullptr;
}

bool SparseVector::operator!=(const SparseVector& sv) const
{
    return !(*this == sv);
}



SparseVector& SparseVector::operator+=(const SparseVector& sv)
{
    addSubVector(sv, true);
    return *this;
}

SparseVector& SparseVector::operator-=(const SparseVector& sv)
{
    addSubVector(sv, false);
    return *this;
}

SparseVector SparseVector::operator+(const SparseVector& sv) const
{
    SparseVector result(*this);
    result += sv;
    return result;
}

SparseVector SparseVector::operator-(const SparseVector& sv) const
{
    SparseVector result(*this);
    result -= sv;
    return result;
}



void SparseVector::addSubVector(const SparseVector& sv, bool add)
{
    assert(size == sv.size);

    int sign = add ? 1 : -1;

    node* a = head;
    node* b = sv.head;

    while (b)
    {
        setNonzeroElem(b->index, getElem(b->index) + sign * b->value);
        b = b->next;
    }

    removeZeros();
}

void SparseVector::removeZeros()
{
    node* curr = head;
    node* prev = nullptr;

    while (curr)
    {
        if (curr->value == 0)
        {
            node* toDelete = curr;
            curr = curr->next;

            if (prev)
                prev->next = curr;
            else
                head = curr;

            delete toDelete;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}
