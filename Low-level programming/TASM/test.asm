assume cs: code, ds: data

data segment
str1 db 10, 9 dup (0)
str2 db 10, 9 dup (0)
ennd db 0dh,0ah, '$'
res db 10, 9 dup (0)
data ends

code segment ;-31h

calc proc
	push bp
	mov bp, sp
	mov di, [bp+4] ;str2
	mov si, [bp+6] ;str1

	mov al, [si+2]
	cmp al, 41h
	jl hh ;al<A
	add al, 10
	sub al, 'A'
hh:	mov bl, [di+2]
	sub bl, 30h

	add al, bl
	;sub al, 16

	sub al, 10
	add al, 'A'

	mov dl, al
	mov ah, 02h
	int 21h

	pop bp
	ret
calc endp


start:
	mov ax, data
	mov ds, ax
	mov dx, offset str1 ; в dx перемещаем адрес строки
	mov si, dx
	mov ax, 0
	mov ah, 0Ah ; ввод
	int 21h

	mov dx, offset ennd ; кинули в конец строки EOL
	;mov dx, offset wh
	mov ah, 09h	; вывод
	int 21h

	mov dx, offset str2 ; в dx перемещаем адрес строки
	mov si, dx
	mov ah, 0Ah ; ввод
	int 21h

	mov dx, offset ennd ; кинули в конец строки EOL
	;mov dx, offset wh
	mov ah, 09h	; вывод
	int 21h

	mov ah, 0
	push offset res
	push offset str1
	push offset str2
	call calc


	;mov dl, [si+6]
	;mov ah, 02h
	;int 21h
	;mov dl, [si+5]
	;mov ah, 02h
	;int 21h
	;mov dl, [si+4]
	;mov ah, 02h
	;int 21h
	;mov dl, [si+3]
	;mov ah, 02h
	;int 21h
	;mov dl, [si+2]
	;mov ah, 02h
	;int 21h
	

	mov ah, 4ch
	int 21h
	code ends
	end start