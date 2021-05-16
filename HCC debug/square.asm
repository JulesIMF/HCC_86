mov 5000 rdx
call _init_table
call main
hlt
;funcDecl
Дискриминанта:
;statement 'R' at 3
;var b at 3
push [rdx+1]
;var b at 3
push [rdx+1]
;operator '*' at 3
pop rbx
pop rax
fmul rax rbx
;const at 3
push 4.000000
;var a at 3
push [rdx+0]
;operator '*' at 3
pop rbx
pop rax
fmul rax rbx
;var c at 3
push [rdx+2]
;operator '*' at 3
pop rbx
pop rax
fmul rax rbx
;operator '-' at 3
pop rbx
pop rax
fsub rax rbx
pop rax
pop rbx
push rax
push rbx
ret
pop rax
push 0
push rax
ret
;funcDecl
Решения:
;statement 'I' at 9
;var a at 9
push [rdx+0]
;const at 9
push 0
;operator '=' at 9
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3666531568
push 0
jmp _eq_zero_p3666531568
_eq_one_p3666531568:
push 1.0
_eq_zero_p3666531568:
;var b at 9
push [rdx+1]
;const at 9
push 0
;operator '=' at 9
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3666529392
push 0
jmp _eq_zero_p3666529392
_eq_one_p3666529392:
push 1.0
_eq_zero_p3666529392:
;operator '&' at 9
pop rbx
pop rax
fcmp rax 0
je _nd_zero_p3666527984
cmp rbx 0
je _nd_zero_p3666527984
push 1.0
jmp _nd_one_p3666527984
_nd_zero_p3666527984:
push 0
_nd_one_p3666527984:
;var c at 9
push [rdx+2]
;const at 9
push 0
;operator '=' at 9
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3666539216
push 0
jmp _eq_zero_p3666539216
_eq_one_p3666539216:
push 1.0
_eq_zero_p3666539216:
;operator '&' at 9
pop rbx
pop rax
fcmp rax 0
je _nd_zero_p3666529648
cmp rbx 0
je _nd_zero_p3666529648
push 1.0
jmp _nd_one_p3666529648
_nd_zero_p3666529648:
push 0
_nd_one_p3666529648:
pop rax
cmp rax 0
je _else_p3666528752
;statement 'C' at 11
;calling Пророка at 11
;const at 11
push 9221120237041090560
;end of evaluation - calling Пророка at 11
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'R' at 12
;const at 12
push 0
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p3666528752
_else_p3666528752:
_endif_p3666528752:
;statement 'I' at 15
;var a at 15
push [rdx+0]
;const at 15
push 0
;operator '=' at 15
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3666534864
push 0
jmp _eq_zero_p3666534864
_eq_one_p3666534864:
push 1.0
_eq_zero_p3666534864:
;var b at 15
push [rdx+1]
;const at 15
push 0
;operator '=' at 15
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3666532688
push 0
jmp _eq_zero_p3666532688
_eq_one_p3666532688:
push 1.0
_eq_zero_p3666532688:
;operator '&' at 15
pop rbx
pop rax
fcmp rax 0
je _nd_zero_p3666533968
cmp rbx 0
je _nd_zero_p3666533968
push 1.0
jmp _nd_one_p3666533968
_nd_zero_p3666533968:
push 0
_nd_one_p3666533968:
pop rax
cmp rax 0
je _else_p3666532816
;statement 'C' at 17
;calling Пророка at 17
;const at 17
push 0.000000
;end of evaluation - calling Пророка at 17
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'R' at 18
;const at 18
push 0
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p3666532816
_else_p3666532816:
_endif_p3666532816:
;statement 'I' at 21
;var a at 21
push [rdx+0]
;const at 21
push 0
;operator '=' at 21
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3666538576
push 0
jmp _eq_zero_p3666538576
_eq_one_p3666538576:
push 1.0
_eq_zero_p3666538576:
pop rax
cmp rax 0
je _else_p3666534352
;statement 'C' at 23
;calling Пророка at 23
;const at 23
push 1.000000
;end of evaluation - calling Пророка at 23
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'C' at 24
;calling Пророка at 24
;const at 0
push 0
;var b at 24
push [rdx+1]
;operator '-' at 24
pop rbx
pop rax
fsub rax rbx
;var c at 24
push [rdx+2]
;operator '/' at 24
pop rbx
pop rax
fdiv rax rbx
;end of evaluation - calling Пророка at 24
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'R' at 25
;const at 25
push 1.000000
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p3666534352
_else_p3666534352:
_endif_p3666534352:
;statement 'D' at 28
;statement 'D' at 29
;statement 'A' at 30
;calling Дискриминанта at 30
;var a at 30
push [rdx+0]
;var b at 30
push [rdx+1]
;var c at 30
push [rdx+2]
;end of evaluation - calling Дискриминанта at 30
mov 3 rax
sub rdx rax
pop rdx
pop [rdx+2]
pop [rdx+1]
pop [rdx+0]
call Дискриминанта
mov 3 rax
add rdx rax
pop rdx
pop [rdx+4]
;statement 'A' at 31
;calling КорняЗла at 31
;calling Дискриминанта at 31
;var a at 31
push [rdx+0]
;var b at 31
push [rdx+1]
;var c at 31
push [rdx+2]
;end of evaluation - calling Дискриминанта at 31
mov 3 rax
sub rdx rax
pop rdx
pop [rdx+2]
pop [rdx+1]
pop [rdx+0]
call Дискриминанта
mov 3 rax
add rdx rax
pop rdx
;end of evaluation - calling КорняЗла at 31
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call КорняЗла
mov 1 rax
add rdx rax
pop rdx
pop [rdx+3]
;statement 'I' at 33
;var D at 33
push [rdx+4]
;const at 33
push 0
;operator '>' at 33
pop rbx
pop rax
fcmp rax rbx
jg _g_one_p3666545952
push 0
jmp _g_zero_p3666545952
_g_one_p3666545952:
push 1.0
_g_zero_p3666545952:
pop rax
cmp rax 0
je _else_p3666544160
;statement 'C' at 35
;calling Пророка at 35
;const at 35
push 2.000000
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
;statement 'C' at 36
;calling Пророка at 36
;const at 0
push 0
;var b at 36
push [rdx+1]
;operator '-' at 36
pop rbx
pop rax
fsub rax rbx
;var d at 36
push [rdx+3]
;operator '+' at 36
pop rbx
pop rax
fadd rax rbx
;const at 36
push 2.000000
;var a at 36
push [rdx+0]
;operator '*' at 36
pop rbx
pop rax
fmul rax rbx
;operator '/' at 36
pop rbx
pop rax
fdiv rax rbx
;end of evaluation - calling Пророка at 36
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'C' at 37
;calling Пророка at 37
;const at 0
push 0
;var b at 37
push [rdx+1]
;operator '-' at 37
pop rbx
pop rax
fsub rax rbx
;var d at 37
push [rdx+3]
;operator '-' at 37
pop rbx
pop rax
fsub rax rbx
;const at 37
push 2.000000
;var a at 37
push [rdx+0]
;operator '*' at 37
pop rbx
pop rax
fmul rax rbx
;operator '/' at 37
pop rbx
pop rax
fdiv rax rbx
;end of evaluation - calling Пророка at 37
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'R' at 38
;const at 38
push 0
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p3666544160
_else_p3666544160:
_endif_p3666544160:
;statement 'I' at 42
;var D at 42
push [rdx+4]
;const at 42
push 0
;operator '=' at 42
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3666559216
push 0
jmp _eq_zero_p3666559216
_eq_one_p3666559216:
push 1.0
_eq_zero_p3666559216:
pop rax
cmp rax 0
je _else_p3666558576
;statement 'C' at 44
;calling Пророка at 44
;const at 44
push 1.000000
;end of evaluation - calling Пророка at 44
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'C' at 45
;calling Пророка at 45
;const at 0
push 0
;var b at 45
push [rdx+1]
;operator '-' at 45
pop rbx
pop rax
fsub rax rbx
;const at 45
push 2.000000
;var a at 45
push [rdx+0]
;operator '*' at 45
pop rbx
pop rax
fmul rax rbx
;operator '/' at 45
pop rbx
pop rax
fdiv rax rbx
;end of evaluation - calling Пророка at 45
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'R' at 46
;const at 46
push 0
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p3666558576
_else_p3666558576:
_endif_p3666558576:
;statement 'I' at 49
;var D at 49
push [rdx+4]
;const at 49
push 0
;operator '<' at 49
pop rbx
pop rax
fcmp rax rbx
jl _l_one_p3666558192
push 0
jmp _l_zero_p3666558192
_l_one_p3666558192:
push 1.0
_l_zero_p3666558192:
pop rax
cmp rax 0
je _else_p3666557936
;statement 'C' at 51
;calling Пророка at 51
;const at 51
push 0.000000
;end of evaluation - calling Пророка at 51
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'R' at 52
;const at 52
push 0
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p3666557936
_else_p3666557936:
_endif_p3666557936:
pop rax
push 0
push rax
ret
;main
main:
;statement 'D' at 60
;statement 'D' at 61
;statement 'D' at 62
;statement 'A' at 63
;calling Ангелов at 63
;end of evaluation - calling Ангелов at 63
mov 0 rax
sub rdx rax
pop rdx
call Ангелов
mov 0 rax
add rdx rax
pop rdx
pop [rdx+0]
;statement 'A' at 64
;calling Ангелов at 64
;end of evaluation - calling Ангелов at 64
mov 0 rax
sub rdx rax
pop rdx
call Ангелов
mov 0 rax
add rdx rax
pop rdx
pop [rdx+1]
;statement 'A' at 65
;calling Ангелов at 65
;end of evaluation - calling Ангелов at 65
mov 0 rax
sub rdx rax
pop rdx
call Ангелов
mov 0 rax
add rdx rax
pop rdx
pop [rdx+2]
;statement 'C' at 67
;calling Решения at 67
;var a at 67
push [rdx+0]
;var b at 67
push [rdx+1]
;var c at 67
push [rdx+2]
;end of evaluation - calling Решения at 67
mov 5 rax
sub rdx rax
pop rdx
pop [rdx+2]
pop [rdx+1]
pop [rdx+0]
call Решения
mov 5 rax
add rdx rax
pop rdx
pop rsp
ret
_init_table:
mov 3 [2000]
mov 5 [2001]
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

