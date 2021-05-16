mov 5000 rdx
call _init_table
call main
hlt
;funcDecl
D:
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
Solve:
;statement 'I' at 9
;var a at 9
push [rdx+0]
;const at 9
push 0
;operator '=' at 9
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3041511872
push 0
jmp _eq_zero_p3041511872
_eq_one_p3041511872:
push 1
_eq_zero_p3041511872:
;var b at 9
push [rdx+1]
;const at 9
push 0
;operator '=' at 9
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3041513152
push 0
jmp _eq_zero_p3041513152
_eq_one_p3041513152:
push 1
_eq_zero_p3041513152:
;operator '&' at 9
pop rbx
pop rax
fcmp rax 0
je _nd_zero_p3041512640
cmp rbx 0
je _nd_zero_p3041512640
push 1
jmp _nd_one_p3041512640
_nd_zero_p3041512640:
push 0
_nd_one_p3041512640:
;var c at 9
push [rdx+2]
;const at 9
push 0
;operator '=' at 9
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3041520800
push 0
jmp _eq_zero_p3041520800
_eq_one_p3041520800:
push 1
_eq_zero_p3041520800:
;operator '&' at 9
pop rbx
pop rax
fcmp rax 0
je _nd_zero_p3041511744
cmp rbx 0
je _nd_zero_p3041511744
push 1
jmp _nd_one_p3041511744
_nd_zero_p3041511744:
push 0
_nd_one_p3041511744:
pop rax
cmp rax 0
je _else_p3041509312
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
jmp _endif_p3041509312
_else_p3041509312:
_endif_p3041509312:
;statement 'I' at 15
;var a at 15
push [rdx+0]
;const at 15
push 0
;operator '=' at 15
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3041519648
push 0
jmp _eq_zero_p3041519648
_eq_one_p3041519648:
push 1
_eq_zero_p3041519648:
;var b at 15
push [rdx+1]
;const at 15
push 0
;operator '=' at 15
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3041516320
push 0
jmp _eq_zero_p3041516320
_eq_one_p3041516320:
push 1
_eq_zero_p3041516320:
;operator '&' at 15
pop rbx
pop rax
fcmp rax 0
je _nd_zero_p3041515424
cmp rbx 0
je _nd_zero_p3041515424
push 1
jmp _nd_one_p3041515424
_nd_zero_p3041515424:
push 0
_nd_one_p3041515424:
pop rax
cmp rax 0
je _else_p3041516064
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
jmp _endif_p3041516064
_else_p3041516064:
_endif_p3041516064:
;statement 'I' at 21
;var a at 21
push [rdx+0]
;const at 21
push 0
;operator '=' at 21
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3041520160
push 0
jmp _eq_zero_p3041520160
_eq_one_p3041520160:
push 1
_eq_zero_p3041520160:
pop rax
cmp rax 0
je _else_p3041516832
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
jmp _endif_p3041516832
_else_p3041516832:
_endif_p3041516832:
;statement 'D' at 28
;statement 'D' at 29
;statement 'A' at 30
;calling D at 30
;var a at 30
push [rdx+0]
;var b at 30
push [rdx+1]
;var c at 30
push [rdx+2]
;end of evaluation - calling D at 30
mov 3 rax
sub rdx rax
pop rdx
pop [rdx+2]
pop [rdx+1]
pop [rdx+0]
call D
mov 3 rax
add rdx rax
pop rdx
pop [rdx+4]
;statement 'A' at 31
;calling КорняЗла at 31
;calling D at 31
;var a at 31
push [rdx+0]
;var b at 31
push [rdx+1]
;var c at 31
push [rdx+2]
;end of evaluation - calling D at 31
mov 3 rax
sub rdx rax
pop rdx
pop [rdx+2]
pop [rdx+1]
pop [rdx+0]
call D
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
jg _g_one_p3041525488
push 0
jmp _g_zero_p3041525488
_g_one_p3041525488:
push 1
_g_zero_p3041525488:
pop rax
cmp rax 0
je _else_p3041529200
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
jmp _endif_p3041529200
_else_p3041529200:
_endif_p3041529200:
;statement 'I' at 40
;var D at 40
push [rdx+4]
;const at 40
push 0
;operator '=' at 40
pop rbx
pop rax
fcmp rax rbx
je _eq_one_p3041537216
push 0
jmp _eq_zero_p3041537216
_eq_one_p3041537216:
push 1
_eq_zero_p3041537216:
pop rax
cmp rax 0
je _else_p3041540928
;statement 'C' at 42
;calling Пророка at 42
;const at 42
push 1.000000
;end of evaluation - calling Пророка at 42
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'C' at 43
;calling Пророка at 43
;const at 0
push 0
;var b at 43
push [rdx+1]
;operator '-' at 43
pop rbx
pop rax
fsub rax rbx
;const at 43
push 2.000000
;var a at 43
push [rdx+0]
;operator '*' at 43
pop rbx
pop rax
fmul rax rbx
;operator '/' at 43
pop rbx
pop rax
fdiv rax rbx
;end of evaluation - calling Пророка at 43
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'R' at 44
;const at 44
push 0
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p3041540928
_else_p3041540928:
_endif_p3041540928:
;statement 'I' at 46
;var D at 46
push [rdx+4]
;const at 46
push 0
;operator '<' at 46
pop rbx
pop rax
fcmp rax rbx
jl _l_one_p3041540288
push 0
jmp _l_zero_p3041540288
_l_one_p3041540288:
push 1
_l_zero_p3041540288:
pop rax
cmp rax 0
je _else_p3041539520
;statement 'C' at 48
;calling Пророка at 48
;const at 48
push 0.000000
;end of evaluation - calling Пророка at 48
mov 1 rax
sub rdx rax
pop rdx
pop [rdx+0]
call Пророка
mov 1 rax
add rdx rax
pop rdx
pop rsp
;statement 'R' at 49
;const at 49
push 0
pop rax
pop rbx
push rax
push rbx
ret
jmp _endif_p3041539520
_else_p3041539520:
_endif_p3041539520:
pop rax
push 0
push rax
ret
;main
main:
;statement 'D' at 57
;statement 'D' at 58
;statement 'D' at 59
;statement 'A' at 60
;calling Ангелов at 60
;end of evaluation - calling Ангелов at 60
mov 0 rax
sub rdx rax
pop rdx
call Ангелов
mov 0 rax
add rdx rax
pop rdx
pop [rdx+0]
;statement 'A' at 61
;calling Ангелов at 61
;end of evaluation - calling Ангелов at 61
mov 0 rax
sub rdx rax
pop rdx
call Ангелов
mov 0 rax
add rdx rax
pop rdx
pop [rdx+1]
;statement 'A' at 62
;calling Ангелов at 62
;end of evaluation - calling Ангелов at 62
mov 0 rax
sub rdx rax
pop rdx
call Ангелов
mov 0 rax
add rdx rax
pop rdx
pop [rdx+2]
;statement 'C' at 64
;calling Solve at 64
;var a at 64
push [rdx+0]
;var b at 64
push [rdx+1]
;var c at 64
push [rdx+2]
;end of evaluation - calling Solve at 64
mov 5 rax
sub rdx rax
pop rdx
pop [rdx+2]
pop [rdx+1]
pop [rdx+0]
call Solve
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

