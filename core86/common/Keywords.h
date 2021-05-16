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

#ifndef CPP_KEYWORDS
#define CPP_KEYWORDS

static char const* _begin = "{";
static char const* _end = "}";
static char const* _expr = "!";
static char const* _if = "if";
static char const* _else = "else";
static char const* _loop = "while";
static char const* _def = "def";
static char const* _with = "with";
static char const* _asgn = "gets";
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
static char const* _not = "~";
static char const* _eq = "=";
static char const* _neq = "=/=";
static char const* _less = "<";
static char const* _gtr = ">";
static char const* _leq = "<=";
static char const* _geq = ">=";
static char const* _or = "\\/";
static char const* _and = "/\\";
static char const* _comment = ";";

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
    UNDEFINED_TYPE,
    UNDEFINED_FNC
};

char const* errorToStr(CompileError error);

#endif //!CPP_KEYWORDS