mov 5000 rdx
call _init_table
call main
hlt
;funcDecl
Фибоначчи:
;statement 'D' at 3
;statement 'D' at 4
;statement 'A' at 5
;const at 5
push 0
pop [rdx+0]
;statement 'A' at 6
;const at 6
push 1
pop [rdx+1]
;statement 'D' at 7
;statement 'A' at 8
;calling Ангелов at 8
;end of evaluation - calling Ангелов at 8
mov 0 rax
sub rdx rax
pop rdx
call Ангелов
mov 0 rax
add rdx rax
pop rdx
pop [rdx+2]
;statement 'L' at 9
_loop_p347070864:
;var n at 9
push [rdx+2]
;const at 9
push 0
;operator '~' at 9
pop rbx
pop rax
fcmp rax rbx
jne _ne_one_p347069712
push 0
jmp _ne_zero_p347069712
_ne_one_p347069712:
push 1.0
_ne_zero_p347069712:
pop rax
cmp rax 0
je _break_p347070864
;statement 'D' at 11
;statement 'A' at 12
;var a at 12
push [rdx+0]
;var b at 12
push [rdx+1]
;operator '+' at 12
pop rbx
pop rax
fadd rax rbx
pop [rdx+3]
;statement 'A' at 13
;var b at 13
push [rdx+1]
pop [rdx+0]
;statement 'A' at 14
;var tmp at 14
push [rdx+3]
pop [rdx+1]
;statement 'A' at 15
;var n at 15
push [rdx+2]
;const at 15
push 1
;operator '-' at 15
pop rbx
pop rax
fsub rax rbx
pop [rdx+2]
jmp _loop_p347070864
_break_p347070864:
;statement 'C' at 18
;calling Машиаха at 18
;var a at 18
push [rdx+0]
;end of evaluation - calling Машиаха at 18
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Машиаха
mov 1 rax
add rdx rax
pop rdx
pop rsp
pop rax
push 0
push rax
ret
;main
main:
;statement 'C' at 25
;calling Фибоначчи at 25
;end of evaluation - calling Фибоначчи at 25
mov 4 rax
sub rdx rax
pop rdx
call Фибоначчи
mov 4 rax
add rdx rax
pop rdx
pop rsp
;statement 'C' at 26
;calling Монаха at 26
;end of evaluation - calling Монаха at 26
mov 0 rax
sub rdx rax
pop rdx
call Монаха
mov 0 rax
add rdx rax
pop rdx
pop rsp
ret
_init_table:
mov 4 [2000]
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

