mov 5000 rdx
call _init_table
call main
hlt
;funcDecl
Фибоначчи:
;statement 'I' at 6
;var n at 6
push [rdx+0]
;const at 6
push 0.000000
;operator '<' at 6
pop rbx
pop rax
fcmp rax rbx
jl _l_one_p4021141248
push 0
jmp _l_zero_p4021141248
_l_one_p4021141248:
push 1.0
_l_zero_p4021141248:
pop rax
cmp rax 0
je _else_p4021140800
;statement 'R' at 7
;const at 0
push 0
;const at 7
push 1.000000
;operator '-' at 7
pop rbx
pop rax
fsub rax rbx
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p4021140800
_else_p4021140800:
;statement 'I' at 11
;var n at 11
push [rdx+0]
;const at 11
push 0.000000
;operator '=' at 11
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p4021141584
push 0
jmp _eq_zero_p4021141584
_eq_one_p4021141584:
push 1.0
_eq_zero_p4021141584:
pop rax
cmp rax 0
je _else_p4021143888
;statement 'R' at 12
;const at 12
push 0
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p4021143888
_else_p4021143888:
;statement 'I' at 17
;var n at 17
push [rdx+0]
;const at 17
push 1.000000
;operator '=' at 17
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p4021143376
push 0
jmp _eq_zero_p4021143376
_eq_one_p4021143376:
push 1.0
_eq_zero_p4021143376:
pop rax
cmp rax 0
je _else_p4021143120
;statement 'R' at 18
;const at 18
push 1.000000
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p4021143120
_else_p4021143120:
_endif_p4021143120:
;statement 'R' at 20
;calling Фибоначчи at 20
;var n at 20
push [rdx+0]
;const at 20
push 1.000000
;operator '-' at 20
pop rbx
pop rax
fsub rax rbx
;end of evaluation - calling Фибоначчи at 20
mov [2000] rax
sub rdx rax
pop rdx
pop [rdx+0]
call Фибоначчи
mov [2000] rax
add rdx rax
pop rdx
;calling Фибоначчи at 20
;var n at 20
push [rdx+0]
;const at 20
push 2.000000
;operator '-' at 20
pop rbx
pop rax
fsub rax rbx
;end of evaluation - calling Фибоначчи at 20
mov [2000] rax
sub rdx rax
pop rdx
pop [rdx+0]
call Фибоначчи
mov [2000] rax
add rdx rax
pop rdx
;operator '+' at 20
pop rbx
pop rax
fadd rax rbx
pop rax
pop rbx
push rax
push rbx
ret
_endif_p4021143888:
_endif_p4021140800:
pop rax
push 0
push rax
ret
;main
main:
;statement 'D' at 30
;statement 'A' at 31
;const at 31
push 1.000000
pop [rdx+0]
;statement 'L' at 33
_loop_p4021152688:
;var n at 33
push [rdx+0]
;const at 33
push 11.000000
;operator '~' at 33
pop rbx
pop rax
fcmp rax rbx
jne _ne_one_p4021151152
push 0
jmp _ne_zero_p4021151152
_ne_one_p4021151152:
push 1.0
_ne_zero_p4021151152:
pop rax
cmp rax 0
je _break_p4021152688
;statement 'C' at 35
;calling Пророка at 35
;calling Фибоначчи at 35
;var n at 35
push [rdx+0]
;end of evaluation - calling Фибоначчи at 35
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Фибоначчи
mov 1 rax
add rdx rax
pop rdx
;end of evaluation - calling Пророка at 35
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'A' at 36
;var n at 36
push [rdx+0]
;const at 36
push 1.000000
;operator '+' at 36
pop rbx
pop rax
fadd rax rbx
pop [rdx+0]
jmp _loop_p4021152688
_break_p4021152688:
ret
_init_table:
mov 1 [2000]
ret

Пророка:
push [rdx]
out lf
pop rsp
pop rax
push 0
push rax
ret

Машиаха:
push [rdx]
out
pop rsp
pop rax
push 0
push rax
ret

Ангелов:
in
pop rax
pop rbx
push rax
push rbx
ret

КорняЗла:
sqrt [rdx]
pop rax
pop rbx
push rax
push rbx
ret

Монаха:
getch
pop rax
pop rbx
push rax
push rbx
ret

