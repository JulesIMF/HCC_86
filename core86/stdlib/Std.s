.intel_syntax noprefix
.global printInt
.global newLine
.global scanInt

/*------------------------------------------------*/
    /* rdx == nBytes      */
    /* rsi == buf         */
    /* rdi == fd          */
    /* rax == syscall num */
/*------------------------------------------------*/




/*------------------------------------------------
Имя:
    newLine

Назначение:
    Перевод на новую строку

------------------------------------------------*/
newLine:
    push    '\n'
    mov     rax, 1
    mov     rdx, 1
    mov     rsi, rsp
    mov     rdi, 1
    syscall    
    pop     rax
    ret


/*------------------------------------------------
Имя:
    printInt

Назначение:
    Вывод целого числа со знаком

------------------------------------------------*/

printInt:
    mov     r8, [rsp+8]
    cmp     r8, 0
    jnl     printInt_notZero
    push    '-'
    mov     rax, 1
    mov     rdx, 1
    mov     rsi, rsp
    mov     rdi, 1
    syscall
    pop     rax
    neg     r8

printInt_notZero:
    xor     r9, r9
    mov     rbx, 10
    mov     rax, r8

printInt_loop:
    xor     rdx, rdx
    idiv    rbx
    add     rdx, '0'
    push    rdx
    inc     r9
    test    rax, rax
    jnz     printInt_loop

printInt_print:
    mov     rdi, 1
    mov     rdx, 1
    mov     rsi, rsp
    mov     rax, 1
    syscall
    pop     rax
    dec     r9
    test    r9, r9
    jnz     printInt_print

    xor     rax, rax
    ret


/*------------------------------------------------
Имя:
    scanInt

Назначение:
    Ввод целого знакового числа с клавиатуры

------------------------------------------------*/

scanInt:
    xor     r9, r9      /* индикатор минуса */
    xor     rbx, rbx    /* аккумулятор */
    mov     r8, 10
    push    rbx

scanInt_scaning:
    xor     rax, rax
    xor     rdi, rdi
    mov     rsi, rsp
    mov     rdx, 1
    syscall

    mov     rdi, [rsp]
    cmp     rdi, '-'
    jne     scanInt_notMinus
    test    r9, r9
    jz      scanInt_firstMinus

    int     4
    pop     rax
    xor     rax, rax
    ret

scanInt_firstMinus:
    mov     r9, 1
    jmp     scanInt_scaning

scanInt_notMinus:
    cmp     rdi, '0'
    jl      scanInt_notDigit
    cmp     rdi, '9'
    jg      scanInt_notDigit
    sub     rdi, '0'
    imul    rbx, r8
    add     rbx, rdi
    jmp     scanInt_scaning

scanInt_notDigit:
    cmp     rdi, '\n'
    jne     scanInt_notNewLine
    test    r9, r9
    jz      scanInt_notNegative
    neg     rbx

scanInt_notNegative:
    pop     rax
    mov     rax, rbx
    ret

scanInt_notNewLine:
    int     4
    pop     rax
    xor     rax, rax
    ret
