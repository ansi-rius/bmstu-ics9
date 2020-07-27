assume cs: code, ds: data

data segment
msg db "Hello, World!$"
data ends

code segment
start:	mov ax, data
		mov ds, ax

		mov ah, 09h
		mov dx, offset msg
		int 21h
		
		mov ax, 4c00h
		int 21h
		code ends
		end start