mov 5000 rdx
call _init_table
call main
hlt
;main
main:
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
ret

������:
getch
pop rax
pop rbx
push rax
push rbx
ret

