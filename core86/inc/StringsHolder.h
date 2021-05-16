/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    StringsHolder.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#ifndef CPP_STRINGSHOLDER
#define CPP_STRINGSHOLDER
#include <cstddef>

class StringsHolder
{
protected:
    char*       buffer_;
    size_t      capacity_;
    size_t      size_;

    size_t      roundPow2_(size_t x);

public:
    class StringIter
    {
    protected:
        StringsHolder*      holder;
        size_t              begin;

    public:
        char const*         get(void) const;
        StringsHolder*      getHolder(void);
        static StringIter   makeStringIter(StringsHolder* holder_, size_t begin_);

    };


    void                    makeStringsHolder(void);
    static StringsHolder*   newStringsHolder(void);

    StringIter              insert(char const* source, size_t length = 0);
};

#endif //!CPP_STRINGSHOLDER