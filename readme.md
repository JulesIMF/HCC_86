# HCC

HCC (originally called "Holy Cross Cross") is a tiny language that supports:
- Qword signed integers (int)
- Recursive functions
- if-else
- while with break and continue
- static arrays on stack
- different expressions: arythmetical (+, -, *, /), comparison operators (=, =/=, <, >, <=, >=), logical operators (/\\, \\/) calling functions'
- standard functions: scanInt, printInt, newLine

# Grammar

Current grammar and keywords are to be described in core86/common/Keywords.h

    PGM         ::=     FNC+ MAIN '\0'  
    FNC         ::=     _def ID {_with ID {',' ID}*}? STMT_CAT  
    MAIN        ::=     _main STMT_CAT  
    ID          ::=     <alpha> ['0'-'9' <alpha>]+  
    STMT_CAT    ::=     _begin {STMT}+ _end  
    STMT        ::=     _stmt { _break | _cont | CALL | ASGN | LOOP | DVAR | COND | RET} | STMT_CAT  

    LOOP        ::=     _loop '|' EXPR '|' STMT  
    DVAR        ::=     ID _dvar TYPE  
    COND        ::=     _if '|' EXPR '|' STMT {_else STMT}? 
    RET         ::=     _return EXPR  
    ASGN        ::=     VARV _asgn EXPR  

    EXPR        ::=     COMP {'/\' '\/' COMP}*  
    COMP        ::=     FORM ['=/=' '=' '>=' '>' '<=' '<'] FORM  
    FORM        ::=     TERM {['+' '-'] TERM}*  
    TERM        ::=     PRIM {['*' '/'] PRIM}*  
    PRIM        ::=     ['!' '-']? PRIM | CALL | '(' EXPR ')' | NUMB | VARV
    CALL        ::=     _call ID _delim {EXPR {',' EXPR}*}? _delim
    VARV        ::=     ID | ID '[' EXPR ']'
    TYPE        ::=     ID {'['NUMB']'}
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

And sorting:

    def printArr with array, size
    {
        ! i is int
        ! call newLine | |
        ! i gets 0
        ! while | i =/= size |
        {
            ! call printInt | array[i] |
            ! call newLine ||
           ! i gets i + 1
        }   
    }

    def sort with array, size
    {
        ! tmp is int
        ! i is int
        ! count is int
        ! count gets 0
        ! while | count < size |
        {
            ! i gets 0
            ! while | i < size - 1 |
            {
                ! if | array[i] > array[i+1] |
                {
                    ! tmp gets array[i]
                    ! array[i] gets array[i + 1]
                    ! array[i+1] gets tmp
                }

                ! i gets i + 1
            }

            ! count gets count + 1
        }
    }

    main
    {
        ! i is int
        ! n is int[10]
        ! i gets 0
        ! while | i =/= 10 |
        {
            ! n[i] gets call scanInt| |
            ! i gets i + 1
        }
        ! call sort | n, 10 |
        ! call printArr | n, 10 |
    }

# Compiler flags

The compiler supprots several flags:
- **-o \<filename\>** specifies output biniary filename
- **-ast** generates AST tree image
- **-con** convolutes constants
- **-lexer** prints lexer dump
- **-s** prouces intel-syntax asm file (without std library source)
- **-g** inserts trap interruption (int 3) before the entry