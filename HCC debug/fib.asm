mov 5000 rdx
call _init_table
call main
hlt
;funcDecl
fib:
;statement 'I' at 3
;var n at 3
push [rdx+0]
;const at 3
push 0.000000
;operator '=' at 3
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p2046073296
push 0
jmp _eq_zero_p2046073296
_eq_one_p2046073296:
push 1.0
_eq_zero_p2046073296:
pop rax
cmp rax 0
je _else_p2046072848
;statement 'R' at 4
;const at 4
push 0
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p2046072848
_else_p2046072848:
_endif_p2046072848:
;statement 'I' at 6
;var n at 6
push [rdx+0]
;const at 6
push 1.000000
;operator '=' at 6
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p2046074528
push 0
jmp _eq_zero_p2046074528
_eq_one_p2046074528:
push 1.0
_eq_zero_p2046074528:
pop rax
cmp rax 0
je _else_p2046075680
;statement 'R' at 7
;const at 7
push 1.000000
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p2046075680
_else_p2046075680:
_endif_p2046075680:
;statement 'R' at 9
;calling fib at 9
;var n at 9
push [rdx+0]
;const at 9
push 1.000000
;operator '-' at 9
pop rbx
pop rax
fsub rax rbx
;end of evaluation - calling fib at 9
mov [2000] rax
sub rdx rax
pop rdx
pop [rdx+0]
call fib
mov [2000] rax
add rdx rax
pop rdx
;calling fib at 9
;var n at 9
push [rdx+0]
;const at 9
push 2.000000
;operator '-' at 9
pop rbx
pop rax
fsub rax rbx
;end of evaluation - calling fib at 9
mov [2000] rax
sub rdx rax
pop rdx
pop [rdx+0]
call fib
mov [2000] rax
add rdx rax
pop rdx
;operator '+' at 9
pop rbx
pop rax
fadd rax rbx
pop rax
pop rbx
push rax
push rbx
ret
pop rax
push 0
push rax
ret
;main
main:
;statement 'C' at 15
;calling Пророка at 15
;calling fib at 17
;calling Ангелов at 19
;end of evaluation - calling Ангелов at 19
mov 0 rax
sub rdx rax
pop rdx
call Ангелов
mov 0 rax
add rdx rax
pop rdx
;end of evaluation - calling fib at 17
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call fib
mov 1 rax
add rdx rax
pop rdx
;end of evaluation - calling Пророка at 15
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
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

