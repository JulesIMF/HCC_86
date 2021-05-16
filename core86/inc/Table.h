/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Table.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#ifndef CPP_TABLE
#define CPP_TABLE
#include <cstring>
#include <cstdlib>
#include "StringsHolder.h"
#include "List.h"

template <typename Value>
class Table
{
public:
    class Pair
    {
    public:
        StringsHolder::StringIter   string;
        Value                       value;
    };

protected:
    Pair* pairs_;
    size_t size_;
    size_t capacity_;
    StringsHolder holder;

public:
    void initTable(void)
    {
        this->size_ = 0;
        this->capacity_ = 1;
        this->pairs_ = (Pair*)calloc(1, sizeof(Pair));
        this->holder.makeStringsHolder();
    }

    static Table* newTable(void)
    {
        Table* table = (Table*)calloc(1, sizeof(Table));
        table->initTable();
        return table;
    }

    void freeTable(void)
    {
        free(this->pairs_);
    }

    static void deleteTable(Table* table)
    {
        if (table) free(table->pairs_);
        free(table);
    }

    Pair* find(char const* key)
    {
        for (int i = 0; i != size_; i++)
        {
            if (!strcmp(key, pairs_[i].string.get()))
                return pairs_ + i;
        }
        return nullptr;
    }

    Pair* insert(char const* key, Value value)
    {
        auto iter = holder.insert(key, strlen(key));

        pairs_[size_++] = { iter, value };
        if (size_ == capacity_)
            capacity_ <<= 1,
            pairs_ = (Pair*)realloc(pairs_, capacity_ * sizeof(Pair));

        return &pairs_[size_ - 1];
    }

    Pair* insert(StringsHolder::StringIter iter, Value value)
    {
        pairs_[size_++] = { iter, value };
        if (size_ == capacity_)
            capacity_ <<= 1,
            pairs_ = (Pair*)realloc(pairs_, capacity_ * sizeof(Pair));

        return &pairs_[size_ - 1];
    }

    auto size(void) { return size_; }
};
#endif