/**********************************************************************
 * 
Copyright (c) 2020  MIPT

Module Name:
    StringsHolder.cpp

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../inc/StringsHolder.h"


size_t StringsHolder::roundPow2_(size_t x)
{
    size_t ans = 1;
    while (ans < x)
        ans <<= 1;
    return ans;
}


void StringsHolder::makeStringsHolder(void)
{
    this->capacity_ = 1;
    this->size_ = 1;
    this->buffer_ = (char*)calloc(1, sizeof(char));
    this->buffer_[0] = '\0';
}


char const* StringsHolder::StringIter::get(void) const
{
    return &(holder->buffer_[begin]);
}

StringsHolder* StringsHolder::StringIter::getHolder(void)
{
    return this->holder;
}


StringsHolder::StringIter StringsHolder::StringIter::makeStringIter(StringsHolder* holder_, size_t begin_)
{
    StringsHolder::StringIter iter;
    iter.holder = holder_;
    iter.begin = begin_;
    return iter;
}

StringsHolder* StringsHolder::newStringsHolder(void)
{
    auto holder = (StringsHolder*)calloc(1, sizeof(StringsHolder));
    holder->makeStringsHolder();
    return holder;
}

void StringsHolder::deleteStringsHolder(StringsHolder* holder)
{
    if(holder)
        free(holder->buffer_);
        
    free(holder);
}


StringsHolder::StringIter StringsHolder::insert(char const* source, size_t length)
{
    if(!length)
        length = strlen(source);
    
    size_t newSize = size_ + length + 1;

    size_t oldSize = size_;

    if (newSize > capacity_)
    {
        capacity_ = roundPow2_(newSize);
        buffer_ = (char*)realloc(buffer_, capacity_);
    }

    char* returned = buffer_;

    for (size_t i = 0; i != length && source[i]; i++)
    {
        buffer_[size_++] = source[i];
    }

    buffer_[size_++] = '\0';

    //for (int i = 0; i != size_; i++) printf("%c", buffer_[i]); printf("\n");

    return StringsHolder::StringIter::makeStringIter(this, oldSize);
}
