; nasm -f bin -o hello_world.com hello_world.asm
org 100h
section .text
	mov ah, 40h
	mov bx, 1
	mov cx, 12
	mov dx, msg
	int 21h
	mov al,	1
	mov ah, 4Ch
	int 21h
section .data
	msg db "Hello, world"



