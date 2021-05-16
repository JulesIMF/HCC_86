mov 5000 rdx
call _init_table
call main
hlt
;funcDecl
Fact:
;statement 'I' at 5
;var n at 5
push [rdx+0]
;const at 5
push 0.000000
;operator '=' at 5
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p2237906064
push 0
jmp _eq_zero_p2237906064
_eq_one_p2237906064:
push 1.0
_eq_zero_p2237906064:
pop rax
cmp rax 0
je _else_p2237905616
;statement 'R' at 6
;const at 6
push 1.000000
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p2237905616
_else_p2237905616:
_endif_p2237905616:
;statement 'R' at 8
;calling Fact at 8
;var n at 8
push [rdx+0]
;const at 8
push 1.000000
;operator '-' at 8
pop rbx
pop rax
fsub rax rbx
;end of evaluation - calling Fact at 8
mov [2000] rax
sub rdx rax
pop rdx
pop [rdx+0]
call Fact
mov [2000] rax
add rdx rax
pop rdx
;var n at 8
push [rdx+0]
;operator '*' at 8
pop rbx
pop rax
fmul rax rbx
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
;statement 'D' at 15
;statement 'A' at 16
;const at 16
push 1.000000
pop [rdx+0]
;statement 'L' at 18
_loop_p2237909088:
;var n at 18
push [rdx+0]
;const at 18
push 11.000000
;operator '~' at 18
pop rbx
pop rax
fcmp rax rbx
jne _ne_one_p2237915072
push 0
jmp _ne_zero_p2237915072
_ne_one_p2237915072:
push 1.0
_ne_zero_p2237915072:
pop rax
cmp rax 0
je _break_p2237909088
;statement 'C' at 20
;calling Пророка at 20
;calling Fact at 20
;var n at 20
push [rdx+0]
;end of evaluation - calling Fact at 20
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Fact
mov 1 rax
add rdx rax
pop rdx
;end of evaluation - calling Пророка at 20
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'A' at 21
;var n at 21
push [rdx+0]
;const at 21
push 1.000000
;operator '+' at 21
pop rbx
pop rax
fadd rax rbx
pop [rdx+0]
jmp _loop_p2237909088
_break_p2237909088:
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

