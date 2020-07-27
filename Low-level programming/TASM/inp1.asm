assume cs: code, ds: data

data segment
dummy db 0Ah, '$'
string db 100, 99 dup (0)
data ends

code segment
start:	mov ax, data
		mov ds, ax
		mov dx, offset string ;в dx перемещаем адрес строки
		mov si, dx
		mov ax, 0
		mov ah, 0Ah ;input-func
		int 21h
		
		mov dx, offset dummy ;кинули в конец строки EOL
		mov ah, 09h ;output
		int 21h
		
		mov dx, offset string ;???
		add dx, 2 ;???
		
		mov ah, 09h ;display string
		int 21h

		mov ah, 4ch
		int 21h
		code ends
		end start