mov 5000 rdx
call _init_table
call main
hlt
;main
main:
;statement 'I' at 4
;const at 0
push 0
;const at 0
push 0
;const at 4
push 5
;operator '-' at 4
pop rbx
pop rax
sub rax rbx
;operator '!' at 4
pop rbx
pop rax
cmp rax 0
je _nt_zero_p411547792
push 1.0
jmp _nt_one_p411547792
_nt_zero_p411547792:
push 0.0
_nt_one_p411547792:
pop rax
cmp rax 0
je _else_p411547408
jmp _endif_p411547408
_else_p411547408:
_endif_p411547408:
ret
_init_table:
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

