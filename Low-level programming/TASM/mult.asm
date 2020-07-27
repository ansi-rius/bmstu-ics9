assume cs: code, ds: data

data segment
str1 db 10, 9 dup (0)
str2 db 10, 9 dup (0)
ennd db 0dh,0ah, '$'
res db 10, 9 dup (0)
data ends

code segment

mult proc
	push bp
	mov bp, sp

	mov si, [bp+4] ; str1
	mov di, [bp+6] ; цифра

	mov al, [si+1] ;n1
	mov bl, [di+1] ;n2

	cmp al, bl
	jge x1   ;n1 >= n2
	mov cl, bl
	jmp x2
x1: 
	mov cl, al
x2:
	add si, ax
	add di, bx

	add si, 1 ;последний элемент str2
	add di, 1 ;последний элемент str1

	mov dl, 2
	mov bh, 0

lapa:
	mov al, [si]
	sub al, 30h

	mov bl, [di]
	sub bl, 30h

	mul bl
	cmp al, 10
	jl x11 ;al<10
	;al>=10
	add al, bh ; плюсую десяток, если есть
	mov bl, 10
	div bl
	mov bh, al
	mov al, ah
	jmp x22
x11:
	add al, bh
	mov bh, 0
x22:
	push si
	mov si, [bp+8] ;res
	mov bl, [si+1]
	inc bl
	mov [si+1], bl
	add si, dx
	add al, 30h
	mov [si], al
	inc dl

	pop si

	dec si
	loop lapa

	cmp bh, 0
	je eds; bh=0
	;bh>0
	push si
	mov si, [bp+8] ;res
	mov al, [si+1]
	inc al
	mov [si+1], al
	add si, dx
	add bh, 30h
	mov [si], bh

	inc dl
eds:
	mov di, [bp+8]
	mov si, [bp+8] ;res
	mov cl, [si+1]
	mov cl, al
	mov dl, al
	mov dh, 0
	mov ah, 0
	mov bl, 2
	div bl
	mov bl, 0
	mov cl, al
	add si, 1

	mov cl, [si]
	
	add di, dx
lop11:
	mov bh, [di]
	mov [si], bh
	dec di
	inc si
	loop lop11

	pop si
	pop bp

	ret
mult endp

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
	mov bh, 0

lopa:
	mov al, [si]
	sub al, 30h

	mov bl, [di]
	sub bl, 30h

	add al, bl

	mov bl, 10

	cmp al, bl
	jl ww	; al<10

	; al>=10
	sub al, bl	; единица в al
	add al, bh	; к единице плюсуем десяток, если он есть
	mov bh, 1
	cmp al, bl
	jl result 	; al<10

	;al>=10
	sub al, bl
	mov bh, 1	; десяток помещаем
	jmp result

ww: 		; al<10
	add al, bh
	cmp al, bl
	jl hlppp	; al<10

	;al>=10
	sub al, bl
	mov bh, 1
hlppp:
	mov bh, 0

result:
	push si
	mov si, [bp+8] ;res

	add si, dx
	add al, 30h
	mov [si], al
	inc dl

	pop si

	dec si
	dec di

	loop lopa

	mov di, [bp+4] ;str2
	mov si, [bp+6] ;str1
	mov al, [si+1] ;n1
	mov bl, [di+1] ;n2

	cmp al, bl
	jg qq1 ;n1>n2
	cmp al, bl
	je qq2 ;n1=n2

	;n2>n1
	push si ;n2> пушим короткую, она не нужна
	mov si, [bp+8]
	mov dl, al
	mov dh, 0
	mov ch, 0
	mov cl, [di+1]
	sub cl, al ;из большей вычитаю длину 2го слагаемого
	add di, 1
	add si, 2 ;res
	add di, cx ;
	add si, dx ;

lep1:
	mov al, [di]
	sub al, 30h
	add al, bh
	mov bl, 10
	cmp al, bl
	jl resu1 	;al<10

	;al>=10
	sub al, bl
	mov bh, 1	; десяток помещаем

resu1:
	add al, 30h
	mov [si], al
	mov bh, 0
	dec di
	inc si
	loop lep1
	pop si
	jmp ed

qq1:
	;n2<n1
	push di ;n2> пушим короткую, она не нужна
	mov di, [bp+8]
	mov dl, bl
	mov dh, 0
	mov ch, 0
	mov cl, [si+1]
	sub cl, bl ;из большей вычитаю длину 2го слагаемого
	add si, 1
	add di, 2 ;res
	mov ah, 0
	add di, dx ;
	add si, cx ;

lep2:
	mov al, [si]
	sub al, 30h
	add al, bh
	mov bl, 10
	cmp al, bl
	jl ssd 	;al<10

	;al>=10
	sub al, bl
	mov bh, 1	; десяток помещаем
	;inc cl
	jmp resu2
ssd:
	mov bh, 0
resu2:	
	add al, 30h
	mov [di], al
	dec si
	inc di
	loop lep2
	cmp bh, 0
	je sds
	add bh, 30h
	mov [di], bh

sds:
	pop di
	jmp ed

qq2:
	;n1=n2
	cmp bh, 0
	je ed
	push si ;n2> пушим короткую, она не нужна
	mov si, [bp+8]
	mov al, [di+1]
	mov ah, 0
	add si, 2 ;res
	add si, ax ;
	add bh, 30h
	mov [si], bh
	pop si

ed:
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

	mov al, str1[1]
	mov bl, str2[1]

	cmp al, 2
	jl ee1	; al<2

	;al>=2
	cmp bl, 2
	jl ee2	; bl<2

	;bl>=2
ee1:cmp al, bl
	jl ee4	; al<bl

	; al>=bl 
	push offset res ; al<2 && al>=bl
	push offset str1
	push offset str2

	jmp ee3
ee2:
	push offset res
	push offset str2
	push offset str1
	jmp ee3
ee4:
	push offset res
	push offset str1
	push offset str2
	jmp ee3
ee3:
	call mult
	;pop ax
	;pop bx
	;pop cx

	mov dx, offset res
	mov si, dx
	;mov ah, 09h
	;int 21h
	add si, 2
	mov cl, 5
outp:
	mov dl, [si]
	;sub dl, 30h
	mov ah, 02h
	int 21h
	inc si
	loop outp
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