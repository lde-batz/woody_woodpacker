global _start

section .text

_start:
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push rsp
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	pushfq
	call woody

_end:
	popfq
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsp
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax
	jmp 0xffffffff

print_woody:
	mov rdi, 0x1
	pop rsi
	mov rdx, 0xf
	mov rax, 0x1
	syscall
	jmp rc4

woody:
	call print_woody
	.string db "....WOODY....", 10, 0

rc4:
	call rc4_1
	.string db "0123456789abcdef", 0