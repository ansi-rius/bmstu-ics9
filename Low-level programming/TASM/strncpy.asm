assume cs: code, ds: data

data segment
wh db 10, 9 dup (0)
where db 10,9 dup (0)
n db 100
res db 10, 9 dup (0)
ennd db 0dh,0ah, '$'
data ends

code segment

strncpy proc
	push bp
	mov bp, sp
	mov cx, [bp+4] ; n
	sub cx, 30h
	mov si, [bp+8] ; what
	mov di, [bp+6] ; where
	mov dl, [di]
	;sub dl, [di+1]
	sub dl, 2
	add si, 2 ;на 1ый символ указ
	add di, 2 ;на 1ый символ указ
	cmp dl, cl
	jl ed 
iter:
	mov al, [si]
	mov [di], al
	inc di
	inc si
	mov al, 0
	loop iter
ed:	
	pop bp
	pop ax ; адрес возврата
	pop bx ; n
	pop cx ; where
	;add cx, 2
	push cx ; where
	push ax ; адрес возврата

	ret
strncpy endp

start:
	mov ax, data
	mov ds, ax
	mov dx, offset wh ; в dx перемещаем адрес строки
	mov si, dx
	mov ax, 0
	mov ah, 0Ah ; ввод
	int 21h

	mov dx, offset ennd ; кинули в конец строки EOL
	;mov dx, offset wh
	mov ah, 09h	; вывод
	int 21h

	;mov dx, offset wh
	;add dx, 2

	;mov ah, 09h	; вывод
	;int 21h
			
	mov dx, offset n ;;;;;;
	mov si, dx
	mov ah, 0Ah
	int 21h

	mov dx, offset ennd
	mov ah, 09h
	int 21h

	;mov dx, offset n
	;add dx, 2

	;mov ah, 09h	; вывод
	;int 21h

	mov ah, 0
	push offset wh ;указатель на строку
	push offset where ;указатель на строку, куда копировать
	mov al, n[2]
	push ax ;ограничение длины копирки
	call strncpy

	pop di ;возвращает указатель на строку
	add di, 2
	mov dx, di
	;mov res[0], al
	;mov dx, offset res
	
	mov ah, 09h
	int 21h

	mov ah, 4ch
	int 21h
	code ends
	end start