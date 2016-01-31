org 100h
section .text
	mov ah, 40h
	mov bx, 1
	mov cx, 11
	mov dx, msg
	int 21h
	mov al,	1
	mov ah, 4Ch
	int 21h
section .data
	msg db "hello world"



