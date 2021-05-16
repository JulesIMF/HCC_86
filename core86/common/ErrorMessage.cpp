/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    ErrorMessage.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include "../inc/ErrorMessage.h"

static bool debugLevel = false;

int errorMessage(char const* format, ...)
{
    va_list list = {};
    va_start(list, format);
    fprintf(stderr, "\e[1;91m"  "Ошибка: " "\e[1;39m");
    int returned = vfprintf(stderr, format, list);
    va_end(list);
    fprintf(stderr, "\e[m");
    return returned;
}

int warningMessage(char const* format, ...)
{
    va_list list = {};
    va_start(list, format);
    fprintf(stderr, "\e[1;95m"  "Предупреждение: " "\e[1;39m");
    int returned = vfprintf(stderr, format, list);
    va_end(list);
    fprintf(stderr, "\e[m");
    return returned;
}

int debugMessage(char const *format, ...)
{
    if(!debugLevel)
        return 0;
    va_list list = {};
    va_start(list, format);
    fprintf(stderr, "\e[1;94m"
                    "debug: "
                    "\e[1;39m");
    int returned = vfprintf(stderr, format, list);
    va_end(list);
    fprintf(stderr, "\e[m\n");
    return returned;
}

void setDebug(bool newMode)
{
    debugLevel = newMode;
}

void printfMagenta(char const* format, ...)
{
    va_list list = {};
    va_start(list, format);
    vprintf(format, list);
    va_end(list);
    va_end(list);   
}

