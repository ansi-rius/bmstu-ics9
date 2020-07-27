assume cs: code, ds: data

data segment
str1 db 10, 9 dup (0)
str2 db 10, 9 dup (0)
ennd db 0dh,0ah, '$'
res db 10, 9 dup (0)
data ends

code segment

calc proc
	push bp
	mov bp, sp
	mov ax, [bp+4]
	mov bx, [bp+6]

	add ax, bx

	mov bl, 10
	div bl
	cmp ah, 0
	je go
	mov bl, 1
go: 
	mov bh, al
	pop bp
	pop cx
	push bx
	push cx
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
	mov si, offset str1
	mov bl, [si+1] ;n1
	mov di, offset str2
	mov bh, [di+1] ; n2
	cmp bl, bh
	jge setIter   ;n1 >= n2
	mov cl, bh
setIter: 
	mov cl, bl
	;lea dl, 1
	mov dl, 1 ; count
	mov dh, 0

	mov si, cx ;n1 str1 3
	mov di, cx ;n2 str2 2
	inc si
	inc di
oops:
	mov al, [si]
	mov bl, [di]
	sub al, 30h
	sub bl, 30h
	push ax
	push bx
	call calc
	pop ax ;рез сложения
	;add di, cx
	;mov [di], ah
	mov dl, ah
	mov ah, 02h

	cmp al, 1
	jne suda
	add al, 1

suda:	
	dec cl
	loop oops

	mov dx, offset res
	mov ah, 09h
	int 21

	mov ah, 4ch
	int 21h
	code ends
	end start