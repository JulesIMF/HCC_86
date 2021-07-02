# HCC

HCC (originally called "Holy Cross Cross") is a tiny language and self-named compiler developing infrastructure that supports:
- Qword signed integers (int)
- Recursive functions
- if-else
- while with break and continue
- static arrays on stack
- different expressions: arythmetical (+, -, *, /), comparison operators (=, =/=, <, >, <=, >=), logical operators (/\\, \\/, ~), calling functions
- standard functions: scanInt, printInt, newLine

Here we implement an x86 compiler (System V) for this language. Let us take a look at the language.

# Grammar

Current grammar and keywords are to be described in *core86/common/Keywords.h*

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
    PRIM        ::=     ['~' '-']? PRIM | CALL | '(' EXPR ')' | NUMB | VARV
    CALL        ::=     _call ID _delim {EXPR {',' EXPR}*}? _delim
    VARV        ::=     ID | ID '[' EXPR ']'
    TYPE        ::=     ID {'['NUMB']'}
    NUMB        ::=     ['0' - '9']+ {'.'['0' - '9']+}? 

Things that you should know to write code:
1. Conditions and arguments are passed within two vertical bars, e.g. `! while | n =/= 10 |`
2. Call functions with placing "call" before function name: `call printInt | n |`
3. In HCC operators look like in logic. And is "/\\", or is "\\/", equals is "=" and not equals is "=/="
4. Define functions with word "def". Function may not have any argumets, but if it has, they are to be
declared using word "with", e.g. `def Accerman with n, m` or `def print5`
5. Any statement starts with "!" `! call newLine ||` or placed within a block of curly brackets
6. Assignment is described with word "gets": `! n gets call scanInt ||`
7. Variables are declared with word "is", like `! n is int`. Declare arrays with square brackets: `! myArray is int[10]`.
Size should be a constant (no dynamic memory).


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

# Compiler architecture
The main program is "HCC". It operates front-end, middle-end and back-end modules:
- **Front-end** module gets source file and produces parsed tree;
- **Middle-end** module gets this tree and optimizes this (currently only converses constants);
- **Back-end** module gets optimized tree and produces binary executive file.

This allows to create only n + m modules for n languages and m architectures (instead n + m). 
Currently, the author has implemented only HCC language front-end and x86 System V back-end.

# Front-end details
Front-end has two main steps: lexicographic analysis (lexing) and parsing:
- Lexer divides source into tokens (such as keywords, operators, separators, identifiers, ...) to simplify further parsing
- Parser creates AST (abstract syntax tree) from parsed tokens

# Back-end details
Back-end proceeding also has two steps: code generating and translating:
- Generator produces instruction flow from AST, but does not translate it into binary code, so one can (((potentially))) analyze the flow and optimize it (or print assembly code)
- Translator generates the end (executed) file from this flow



# Compiler flags

The compiler supprots several flags:
- **-o \<filename\>** specifies output biniary file name
- **-ast** generates AST tree image
- **-con** convolutes constants
- **-lexer** prints lexer dump
- **-s** produces intel-syntax asm file (without std library source)
- **-g** inserts trap interruption (int 3) before the entry
- **-help** outputs this message


