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
	mov di, [bp+4] ;str2
	mov si, [bp+6] ;str1

	mov al, [si+1] ;n1
	mov bl, [di+1] ;n2

	cmp al, bl
	jge setIter   ;n1 >= n2
	mov cl, al
	jmp skip
setIter: 
	mov cl, bl
skip:
	
	add si, ax
	add di, bx

	add si, 1 ;последний элемент str2
	add di, 1 ;последний элемент str1

	mov dl, 2

lopa:
	mov al, 0
	mov bl, 0
	mov ah, 0
	mov bh, 0

	mov al, [si]
	sub al, 30h

	mov bl, [di]
	sub bl, 30h

	add al, bl ; в ah сумма

	cmp al, 10
	jne ww
	mov bh, 1
	mov al, 0
	jmp go
ww:
	mov bl, 10
	div bl

	cmp al, 0 ;10/10 = 1 и 0
	je go
	cmp ah, 0 ;есть ли остаток
	je go
	mov bh, al ;если есть тут хранится десяток
go: 		  ;если нет
	push si
	mov si, [bp+8] ;res

	add si, dx
	add ah, 30h
	mov [si], ah ;переместили единицу в результат
	inc dl

	pop si
	dec si
	;add si, cx ;указывает на предпоследний эл

	cmp bh, 0 ;есть ли десяток
	je zz ;dl=0
	mov al, [si] ;dl!=0
	sub al, 30h
	add al, bh
	add al, 30h
	mov [si], al 
zz:
	dec di
	loop lopa

	cmp bh, 0 ;остался ли в итоге десяток
	je zq ;bh=0

	mov di, [bp+4] ;str2
	mov si, [bp+6] ;str1
	mov al, [si+1] ;n1
	mov bl, [di+1] ;n2

	cmp al, bl ;n1>=n2
	jge qq1 ;n1>
	push si ;n2> пушим короткую, она не нужна
	mov si, [bp+8]
	mov ch, 0
	mov cl, [di+1]
	sub cl, al ;из большей вычитаю длину 2го слагаемого
	add di, 1
	add si, 2 ;res
	add di, cx ;
	add si, cx ;
	mov al, [di]
	sub al, 30h
	add al, bh
	add al, 30h
lep21:
	mov al, [di]
	mov [si], al
	dec di
	inc si
	loop lep21
	jmp skpp
qq1:
	push di ;n2> пушим короткую, она не нужна
	mov di, [bp+8]
	;mov di, 0
	mov ch, 0
	mov cl, [si+1]
	sub cl, bl ;из большей вычитаю длину 2го слагаемого
	add si, 1
	add di, 2 ;res
	add si, cx ;
	add di, cx ;
lep22:
	mov al, [si]
	mov [di], al
	dec si
	inc di
	loop lep22
	jmp skppp


zq: ;десяток не остался
	mov di, [bp+4] ;str2
	mov si, [bp+6] ;str1
	mov al, [si+1] ;n1
	mov bl, [di+1] ;n2

	cmp al, bl ;n1>=n2
	jge qq ;n1>
	push si ;n2> пушим короткую, она не нужна
	mov si, [bp+8]
	mov ch, 0
	mov cl, [di+1]
	sub cl, al ;из большей вычитаю длину 2го слагаемого
	add di, 1
	add si, 2 ;res
	add di, cx ;
	add si, cx ;
lep11:
	mov al, [di]
	mov [si], al
	dec di
	inc si
	loop lep11
	jmp skp
qq:
	push di ;n2> пушим короткую, она не нужна
	mov di, [bp+8]
	;mov di, 0
	mov ch, 0
	mov cl, [si+1]
	sub cl, bl ;из большей вычитаю длину 2го слагаемого
	add si, 1
	add di, 2 ;res
	add si, cx ;
	add di, cx ;
lep12:
	mov al, [si]
	mov [di], al
	dec si
	inc di
	loop lep12
skp:
skpp:
skppp:
	pop si
	pop bp
	pop ax
	pop bx
	pop cx
	pop dx
	;push si
	push cx
	push bx
	push dx
	push ax

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

	mov dx, offset res
	mov si, dx
	;mov ah, 09h	; вывод
	;int 21h
;	mov dx, si
;	add dx, 2
;	mov ah, 09h
;	int 21
	;mov si, 5
	add si, 5
	mov ch, 0
	mov cx, 4 
	;mov si, 5
	;add si, cx
	mov dl, 0
	mov dh, 0

outp:
	mov dl, [si]
	;sub dl, 30h
	mov ah, 02h
	int 21h
	dec si
	loop outp
		
;	mov ah, 09h
;	int 21h

	mov ah, 4ch
	int 21h
	code ends
	end start