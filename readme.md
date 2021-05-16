# HCC
HCC (originally called "Holy Cross Cross") is a tiny language that supports:
- Qword signed integers (int)
- Recursive functions
- if-else
- while
- different expressions: arythmetical (+, -, *, /), comparison operators (=, =/=, <, >, <=, >=), logical operators (/\\, \\/) calling functions'
- standard functions: scanInt, printInt, newLine

# Grammar
Current grammar and keywords are to be described in kernel86/common/Keywords.h

    PGM         ::=     FNC+ MAIN '\0'  
    FNC         ::=     _def ID {_with ID {',' ID}*}? STMT_CAT  
    MAIN        ::=     _main STMT_CAT  
    ID          ::=     <alpha> ['0'-'9' <alpha>]+  
    STMT_CAT    ::=     _begin {STMT}+ _end  
    STMT        ::=     _stmt {CALL | ASGN | LOOP | DVAR | COND | RET} | STMT_CAT  

    ASGN        ::=     ID _asgn EXPR  
    LOOP        ::=     _loop '|' EXPR '|' STMT  
    DVAR        ::=     ID _dvar TYPE  
    COND        ::=     _if '|' EXPR '|' STMT {_else STMT}?  
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

# Example
Here is an example of programm that recursively computes Fibonacci number:

    def Fib with a
    {
        ! if | a = 0 |
            ! return 0

        ! if | a = 1 |
            ! return 1
    
        ! return call Fib |a - 1| + call Fib |a - 2|
    }

    main
    {
        ! n is int
        ! n gets call scanInt ||
        ! call printInt | call Fib | n | |
        ! call newLine ||
    }

# Compiler flags
The compiler supprots several flags:
- **-o \<filename\>** specifies output biniary filename
- **-ast** generates AST tree image
- **-con** convolutes constants
- **-lexer** prints lexer dump
- **-s** prouces intel-syntax asm file (without std library source)
- **-g** inserts trap interruption (int 3) before the entry