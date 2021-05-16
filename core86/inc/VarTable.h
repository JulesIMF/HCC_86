/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    VarTable.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    20.12.2020 14:23

Edit Notes:
    
**********************************************************************/

#ifndef CPP_VARTABLE
#define CPP_VARTABLE

#include "Vector.h"
#include "StringsHolder.h"
#include "Table.h"

class VarTable
{
    using StringIter = StringsHolder::StringIter;
public:
    struct Var
    {
        int shift;
        bool isInt = false;
        bool isArray = false;
    };

protected:
    Vector<Table<Var>> stack; //По модификации это стек, по доступу это вектор
    int index;

public:
    void init(void)
    {
        stack.init();
        index = -1;
    }

    void deInit(void)
    {
        stack.deInit();
    }

    /**
     * Ищет смещение в таблице имен.
     *
     * \param iter
     * \return необходимое смещение в первой встреченной области видимости, -1 в случае отсутствия
     */
    Var get(StringIter iter)
    {
        auto currentIndex = index;

        while (currentIndex >= 0)
        {
            auto pair = stack.at(currentIndex)->find(iter.get());
            if (pair)
                return pair->value;
            else
                currentIndex--;
        }

        return { -1 };
    }

    void insert(StringIter iter, int shift, bool isInt = false, bool isArray = false)
    {
        assert("assertion in insert" && index > -1);
        Var var { shift, isInt };
        stack.at(index)->insert(iter, var);
    }

    void pushNamespace(void)
    {
        stack.pushBack(Table<Var>());
        index++;
        stack.at(index)->initTable();
    }

    void popNamespace(void)
    {
        stack.at(index)->freeTable();
        stack.popBack();
        index--;
    }
};
#endif
