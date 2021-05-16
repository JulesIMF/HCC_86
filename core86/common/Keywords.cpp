/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Keywords.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#include "Keywords.h"

char const* errorToStr(CompileError error)
{
    switch (error)
    {
    case CompileError::NO_ERROR_:
        return "нет ошибок (NO_ERROR_)";
    case CompileError::PROCEEDED_ERROR:
        return "ошибка была обработана раннее в процесе парсинга (PROCEEDED_ERROR)";
    case CompileError::EXPECTED_SPACE:
        return "пропущен пробел (EXPECTED_SPACE)";
    case CompileError::UNEXPECTED_ALPHA:
        return "неожиданное появление буквы (UNEXPECTED_ALPHA)";
    case CompileError::UNEXPECTED_DIGIT:
        return "неожиданное появление цифры (UNEXPECTED_DIGIT)";
    case CompileError::UNRECOGNIZED_TOKEN:
        return "не удается распознать токен (UNRECOGNIZED_TOKEN)";
    case CompileError::EXPECTED_MAIN:
        return "не найдена точка входа в программу (EXPECTED_MAIN)";
    case CompileError::EXPECTED_ID:
        return "пропущен идентификатор (EXPECTED_ID)";
    case CompileError::EXPECTED_BEGIN:
        return "пропущена открывающая фигурная скобка (EXPECTED_BEGIN)";
    case CompileError::EXPECTED_END:
        return "пропущена закрывающая фигурная скобка (EXPECTED_END)";
    case CompileError::EXPECTED_STMT:
        return "ожидается инструкция (EXPECTED_STMT)";
    case CompileError::EXPECTED_STMT_BEGIN:
        return "ожидается символ начала инструкции (EXPECTED_STMT_BEGIN)";
    case CompileError::EXPECTED_STMT_CAT:
        return "... (EXPECTED_STMT_CAT)";
    case CompileError::EXPECTED_EXPR:
        return "ожидается выражение (EXPECTED_EXPR)";
    case CompileError::EXPECTED_CROSS:
        return "пропущен функциональный разделитель (EXPECTED_CROSS)";
    case CompileError::UNEXPECTED_END:
        return "неожиданное появление закрывающей фигурной скобки (UNEXPECTED_END)";
    case CompileError::EXPECTED_BRACKET:
        return "пропущена скобка (EXPECTED_BRACKET)";
    case CompileError::EXPECTED_PRIM:
        return "ожидается первичное выражение (EXPECTED_PRIM)";
    case CompileError::WRONG_NARG:
        return "количество переданных переменных не соответствует сигнатуре (WRONG_NARG)";
    case CompileError::UNDEFINED_VAR:
        return "использование неопределенной переменной (UNDEFINED_VAR)";
    case CompileError::UNDEFINED_FNC:
        return "вызов неопределенной функции (UNDEFINED_FNC)";
    case CompileError::EXPECTED_RIGHTS:
        return "ожидается закрывающая квадратная скобка (EXPECTED_RIGHTS)";
    case CompileError::EXPECTED_TYPE:
        return "ожидается задание типа (EXPECTED_TYPE)";
    case CompileError::BREAK_WITHOUT_LOOP:
        return "не допускается использование \"break\" вне цикла";
    case CompileError::CONT_WITHOUT_LOOP:
        return "не допускается использование \"continue\" вне цикла";
    default:
        return "неизвестная ошибка (default)";
    }
}