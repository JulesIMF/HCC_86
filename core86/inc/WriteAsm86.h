/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    WriteAsm86.cpp

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#ifndef CPP_WRITEASM86
#define CPP_WRITEASM86

namespace AssemblerGenerator
{
    enum class WriteAsmError
    {
        NO_ERROR,
        FAILED_TO_OPEN,
    };

    WriteAsmError writeToAsmFile(char const *fileName, Compiled flow);
}

#endif //!CPP_WRITEASM86