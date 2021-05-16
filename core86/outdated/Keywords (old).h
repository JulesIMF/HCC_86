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

static char const* _begin   = "Во имя Отца и Сына и Святаго Духа";
static char const* _end     = "Аминь.";
static char const* _expr    = "Так говорит Господь:";
static char const* _if      = "ежели";
static char const* _else    = "а ежели нет";
static char const* _loop    = "крестным ходом шествуйте, пока";
static char const* _def     = "Да приидет царствие";
static char const* _with    = "на все просторы";
static char const* _asgn    = "нарекаю Я";
static char const* _dvar    = "благословляю Я как";
static char const* _main    = "Помолясь, приступим";
static char const* _return  = "вот приношение от Аарона:";
static char const* _call	= "явление";
static char const* _fdelim  = "†";
static char const* _left    = "(";
static char const* _right   = ")";
static char const* _comma   = ",";

static char const* _add     = "+";
static char const* _sub     = "-";
static char const* _mul     = "*";
static char const* _div     = "/";
static char const* _not     = "!";
static char const* _eq      = "=";
static char const* _neq     = "=/=";
static char const* _less    = "<";
static char const* _gtr     = ">";
static char const* _leq     = "<=";
static char const* _geq     = ">=";
static char const* _or      = "\\/";
static char const* _and     = "/\\";
static char const* _comment = "Спрячем иконы:";


static char const* _begin = "{";
static char const* _end = "}";
static char const* _expr = "!";
static char const* _if = "if";
static char const* _else = "else";
static char const* _loop = "while";
static char const* _def = "def";
static char const* _with = "with";
static char const* _asgn = "<-";
static char const* _dvar = "is";
static char const* _main = "main";
static char const* _return = "return";
static char const* _call = "call";
static char const* _fdelim = "|";
static char const* _left = "(";
static char const* _right = ")";
static char const* _comma = ",";

static char const* _add = "+";
static char const* _sub = "-";
static char const* _mul = "*";
static char const* _div = "/";
static char const* _not = "!";
static char const* _eq = "=";
static char const* _neq = "=/=";
static char const* _less = "<";
static char const* _gtr = ">";
static char const* _leq = "<=";
static char const* _geq = ">=";
static char const* _or = "\\/";
static char const* _and = "/\\";
static char const* _comment = ";";


//static char const* _

/*
666 Программа для вычисления чисел Фибоначчи

Да приидет царствие Fibonacci на все просторы n
Во имя Отца и Сына и Святаго Духа
    Так говорит Господь: ans благославляю Я, имя ему Целковый
    Так говорит Господь: ежели ++ n = 0 ++ 
                            Так говорит Господь: вот приношение от Аарона: 0

    Так говорит Господь: ежели ++ n = 1 ++ 
                            Так говорит Господь: вот приношение от Аарона: 1

    Так говорит Господь: ans нарекаю Я явление Fibonacci ++ n - 1 ++ + явление Fibonacci ++ n - 2 ++
    Так говорит Господь: вот приношение от Аарона: ans
Аминь.


Помолясь, приступим

Во имя Отца и Сына и Святаго Духа
    Так говорит Господь: явление Пророка 666 Вывод
                            ++
                                явление Fibonacci
                                        ++
                                            явление Моисея 666 Ввод числа
                                        ++
                            ++
Аминь.    
*/

/*

Grammar:


PGM         ::=     FNC+ MAIN '\0'
FNC         ::=     _def ID {_with ID {',' ID}*}? STMT_CAT
MAIN        ::=     _main STMT_CAT
ID          ::=     <alpha> ['0'-'9' <alpha>]+
STMT_CAT    ::=     _begin {STMT}+ _end
STMT        ::=     _stmt {CALL | ASGN | LOOP | DVAR | COND | RET} | STMT_CAT

ASGN        ::=     ID _asgn EXPR
LOOP        ::=     _loop '†' EXPR '†' STMT
DVAR        ::=     ID _dvar TYPE
COND        ::=     _if '†' EXPR '†' STMT {_else STMT}?
RET         ::=     _return EXPR

EXPR        ::=     COMP {'/\' '\/' COMP}*
COMP        ::=     FORM ['=/=' '=' '>=' '>' '<=' '<'] FORM
FORM        ::=     TERM {['+' '-'] TERM}*
TERM        ::=     PRIM {['*' '/'] PRIM}*
PRIM        ::=     ['!' '-']? PRIM | CALL | '(' EXPR ')' | N | VARV
CALL        ::=     _call ID _delim {EXPR {',' EXPR}*}? _delim
VARV        ::=     ID
TYPE        ::=     ID
NUMB        ::=     ['0' - '9']+ {'.'['0' - '9']+}?

*/


enum CompileError
{
    NO_ERROR_,
    PROCEEDED_ERROR,
    EXPECTED_SPACE,
    UNEXPECTED_ALPHA,
    UNEXPECTED_DIGIT,
    UNRECOGNIZED_TOKEN,
    EXPECTED_MAIN,
    EXPECTED_ID,
    EXPECTED_BEGIN,
    EXPECTED_END,
    EXPECTED_STMT_BEGIN,
    EXPECTED_STMT,
    EXPECTED_STMT_CAT,
    EXPECTED_EXPR,
    UNEXPECTED_END,
    EXPECTED_CROSS,
    EXPECTED_BRACKET,
    EXPECTED_PRIM,
    WRONG_NARG,
    UNDEFINED_VAR,
    UNDEFINED_FNC
};

char const* errorToStr(CompileError error)
{
    switch (error)
    {
    case CompileError::NO_ERROR_:
        return "ты безгрешен (NO_ERROR_)";
    case CompileError::PROCEEDED_ERROR:
        return "грехи уже были отпущены священником (PROCEEDED_ERROR)";
    case CompileError::EXPECTED_SPACE:
        return "пропущен божественный пробел (EXPECTED_SPACE)";
    case CompileError::UNEXPECTED_ALPHA:
        return "богомерзкая литера (UNEXPECTED_ALPHA)";
    case CompileError::UNEXPECTED_DIGIT:
        return "богомерзкая цифра (UNEXPECTED_DIGIT)";
    case CompileError::UNRECOGNIZED_TOKEN:
        return "богомерзкий токен (UNEXPECTED_TOKEN)";
    case CompileError::EXPECTED_MAIN:
        return "не приступил к молитве (EXPECTED_MAIN)";
    case CompileError::EXPECTED_ID:
        return "забыл имя своего благодетеля (EXPECTED_ID)";
    case CompileError::EXPECTED_BEGIN:
        return "сделал приношение не во имя Господа (EXPECTED_ID)";
    case CompileError::EXPECTED_END:
        return "не попросил Господа исполнить молитву (EXPECTED_END)";
    case CompileError::EXPECTED_STMT:
        return "отвлекся от чтения Евангелия (EXPECTED_STMT)";
    case CompileError::EXPECTED_STMT_BEGIN:
        return "пропустил восхваление Господа (EXPECTED_STMT_BEGIN)";
    case CompileError::EXPECTED_STMT_CAT:
        return "не проявил должного почитания к молитвам (EXPECTED_STMT_CAT)";
    case CompileError::EXPECTED_EXPR:
        return "не внимал словам родителей (EXPECTED_EXPR)";
    case CompileError::EXPECTED_CROSS:
        return "хула на Крест (EXPECTED_CROSS)";
    case CompileError::UNEXPECTED_END:
        return "прервал чтение молитвы (UNEXPECTED_END)";
    case CompileError::EXPECTED_BRACKET:
        return "пропущена божественная скобка (EXPECTED_BRACKET)";
    case CompileError::EXPECTED_PRIM:
        return "непраильно процитировал заповеди моисеевы (EXPECTED_PRIM)";
    case CompileError::WRONG_NARG:
        return "излишне или недостаточно молился (WRONG_NARG)";
    case CompileError::UNDEFINED_VAR:
        return "богомерзкая переменная (UNDEFINED_VAR)";
    case CompileError::UNDEFINED_FNC:
        return "богомерзкая функция (UNDEFINED_FNC)";
    default:
        return "какое-то иное прегрешение";
    }
}