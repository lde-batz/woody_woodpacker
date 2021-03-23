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
	jmp woody


_end:
	add rsp, 0x110	; clear stack

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
	pop rsi
	mov rdi, 0x1
	mov rdx, 0xf
	mov rax, 0x1
	syscall
	jmp rc4


woody:
	call print_woody
	.string db "....WOODY....", 10, 0


; useless, used to change the adresse of _text to that of the section .text
_text:
	ret


; initialization
rc4_1:
	pop r8							; key string			(kstr)
	mov r9, 0x10					; key length			(klen)
	lea r10, [rel _text]			; sectin .text			(tstr)
	mov r11, 0xaaaaaaaa				; section .text length	(tlen)

	sub rsp, 0x110					; S[256]	(+16: security)
	xor rcx, rcx					; i = 0


; initialization S[256]
rc4_2:
	mov byte[rsp + rcx], cl			; S[i] = i

	inc rcx							; i++

	cmp rcx, 0x100
	jl rc4_2						; for (i; i < 256; i++)

	xor rcx, rcx					; i = 0
	xor r12, r12					; j = 0


; mix S with the key
rc4_3:
; j = (j + S[i] + key[i % len]) % 256;
	xor rdx, rdx
	mov rax, rcx
	mov rbx, r9
	div rbx							; rdx = i % klen

	xor r13, r13
	mov r13b, byte[r8 + rdx]		; r13 = key[i % klen]

	xor r14, r14
	mov r14b, byte[rsp + rcx]		; r14 = S[i]

	add r12, r13					; j += r13
	add r12, r14					; j += r14

	mov rax, r12
	mov rbx, 0x100
	div rbx							; rbx = j % 256
	mov r12, rdx					; j = j % 256

; swap = S[i];
; S[i] = S[j];
; S[j] = swap;
	mov r13b, byte[rsp + rcx]		; r13 = S[i]

	mov r14b, byte[rsp + r12]		; r14 = S[j]

	mov byte[rsp + rcx], r14b		; S[i] = S[j]
	mov byte[rsp + r12], r13b		; S[j] = S[i]


	inc rcx							; i++

	cmp rcx, 0x100
	jl rc4_3						; for (i; i < 256; i++)

	xor rcx, rcx					; k = 0
	xor r12, r12					; i = 0
	xor r13, r13					; j = 0

; decrypt the section .text byte by byte
rc4_4:
; i = (i + 1) % 256;
	inc r12							; i++
	xor rdx, rdx
	mov rax, r12
	mov rbx, 0x100
	div rbx							; rbx = i % 256
	mov r12, rdx					; i = i % 256

; j = (j + S[i]) % 256;
	xor r14, r14
	mov r14b, byte[rsp + rcx]		; r14 = S[i]
	add r13, r14					; j += S[i]
	mov rax, r13
	mov rbx, 0x100
	div rbx
	mov r13, rdx					; j = j % 256

; swap = S[i];
; S[i] = S[j];
; S[j] = swap;
	mov r14b, byte[rsp + r12]		; r14 = S[i]

	xor r15, r15
	mov r15b, byte[rsp + r13]		; r15 = S[j]

	mov byte[rsp + r12], r15b		; S[i] = S[j]
	mov byte[rsp + r13], r14b		; S[j] = S[i]

; cipher = S[(S[i] + S[j]) % 256];
	add r14, r15					; r14 = S[i] + S[j]
	mov rax, r14
	mov rbx, 0x100
	div rbx
	mov r14, rdx					; r14 = (S[i] + S[j]) % 256
	mov r15b, byte[rsp + r14]		; r15 = S[(S[i] + S[j]) % 256]

; message[k] = cipher ^ message[k];
	xor byte[r10], r15b

	inc rcx							; k++

	cmp rcx, r11
	jl rc4_4						; while (k < slen)

	jmp _end


rc4:
	call rc4_1
	.string db "0123456789abcdefghijklmnopqrstuv", 0