mov 5000 rdx
call _init_table
call main
hlt
;main
main:
;statement 'C' at 5
;calling ������� at 5
;const at 0
push 0
;const at 5
push 0
;const at 5
push 0
;operator '=' at 5
pop rbx
pop rax
cmp rax rbx
je _eq_one_p992197168
push 0
jmp _eq_zero_p992197168
_eq_one_p992197168:
push 1.0
_eq_zero_p992197168:
;operator '!' at 5
pop rbx
pop rax
cmp rax 0
je _not_zero_p992196720
push 1.0
jmp _not_one_p992196720
_not_zero_p992196720:
push 0.0
_not_one_p992196720:
;end of evaluation - calling ������� at 5
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call �������
mov 1 rax
add rdx rax
pop rdx
pop rsp
ret
_init_table:
ret
�������:
push [rdx]
out lf
pop rsp
pop rax
push 0
push rax
ret

�������:
push [rdx]
out
pop rsp
pop rax
push 0
push rax
ret

�������:
in
pop rax
pop rbx
push rax
push rbx
ret

��������:
sqrt [rdx]
pop rax
pop rbx
push rax
push rbx

