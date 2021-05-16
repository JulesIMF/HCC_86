/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Vector.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#ifndef CPP_VECTOR
#define CPP_VECTOR
#include <cassert>
#include <cstdlib>

template<typename T>
class Vector
{
protected:
    size_t      capacity_, size_;
    T* data_;

    void resize_(size_t newCapacity)
    {
        assert("assert in function "  && newCapacity >= size_);
        data_ = (T*)realloc(data_, sizeof(T) * newCapacity);
        capacity_ = newCapacity;
    }

public:
    void        init(void)
    {
        size_ = 0;
        capacity_ = 1;
        data_ = (T*)calloc(1, sizeof(T));
    }

    void        deInit(void)
    {
        free(data_);
    }

    static Vector* newVector()
    {
        auto vector = (Vector*)calloc(1, sizeof(Vector));
        vector->init();
        return vector;
    }

    static void
        deleteVector(Vector* vector)
    {
        if (vector)
            vector->deInit(),
            free(vector);
    }

    size_t      size(void)
    {
        return size_;
    }

    T*          at(size_t index)
    {
        assert("assert in function "  && index < size_);
        return data_ + index;
    }

    void        popBack(void)
    {
        assert("assert in Vector function "  && size_--);
        if (capacity_ >= (size_ << 2))
            resize_(capacity_ >> 1);
    }

    void        pushBack(T const& value)
    {
        data_[size_++] = value;
        if (size_ >= capacity_)
            resize_(capacity_ << 1);
    }
};

#endif