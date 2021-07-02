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
#include "../../inc/Vector.h"
#include "../../inc/StringsHolder.h"
#include "../../inc/Table.h"

class VarTable
{
    using StringIter = StringsHolder::StringIter;
public:
    struct Var
    {
        int shift;
        bool isInt = false;
    };

    void init(void);

    void deInit(void);

    /**
     * Ищет смещение в таблице имен.
     *
     * \param iter
     * \return необходимое смещение в первой встреченной области видимости, -1 в случае отсутствия
     */
    Var get(StringIter iter);

    void insert(StringIter iter, int shift, bool isInt = false);

    void pushNamespace(void);

    void popNamespace(void);
};
#endif
