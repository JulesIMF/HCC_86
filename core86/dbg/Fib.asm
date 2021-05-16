.intel_syntax noprefix
.global main

	call main

Fib:
	push  rbp
	mov  rbp, rsp
	mov  rbx, [rbp+16]
	mov  rcx, 0
	cmp  rbx, rcx
	sete  bl
	movzx  rbx, bl
	test  rbx, rbx
	je .else_p1875457888
	mov  rbx, 0
	mov  rax, rbx
	pop  rbp
	ret
	jmp .endif_p1875457888

.else_p1875457888:

.endif_p1875457888:
	mov  rbx, [rbp+16]
	mov  rcx, 1
	cmp  rbx, rcx
	sete  bl
	movzx  rbx, bl
	test  rbx, rbx
	je .else_p1875459104
	mov  rbx, 1
	mov  rax, rbx
	pop  rbp
	ret
	jmp .endif_p1875459104

.else_p1875459104:

.endif_p1875459104:
	mov  rbx, [rbp+16]
	mov  rcx, 2
	sub  rbx, rcx
	push  rbx
	call Fib
	add  rsp, 8
	mov  rbx, rax
	push  rbx
	mov  rcx, [rbp+16]
	mov  rsi, 1
	sub  rcx, rsi
	push  rcx
	call Fib
	add  rsp, 8
	pop  rbx
	mov  rcx, rax
	add  rbx, rcx
	mov  rax, rbx
	pop  rbp
	ret
	pop  rbp
	ret

main:
	mov  rbp, rsp
	sub  rsp, 8
	mov  rbx, 3
	mov  [rbp-8], rbx
	mov  rbx, [rbp-8]
	push  rbx
	call printInt
	add  rsp, 8
	mov  rbx, rax
	call newLine
	mov  rbx, rax
	mov  rax, 60
	syscall
