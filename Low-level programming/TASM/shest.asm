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

	cmp al, 41h
	jl hh1 ; al<A
	add al, 10	;делаю из буквы цифру
	sub al, 'A'
	jmp next1
hh1:
	sub al, 30h ;цифра 
next1:
	mov bl, [di]

	cmp bl, 41h
	jl hh2 ; bl<A
	add bl, 10	;делаю из буквы цифру
	sub bl, 'A'
	jmp next2
hh2:
	sub bl, 30h ;цифра 
next2:

	add al, bl

	mov bl, 16

	cmp al, bl
	jl ww	; al<16

	; al>=16
	sub al, bl	; единица в al
	add al, bh	; к единице плюсуем десяток, если он есть
	mov bh, 1
	cmp al, bl
	jl result 	; al<16

	;al>=16
	sub al, bl
	mov bh, 1	; десяток помещаем
	jmp result

ww: 		; al<16
	add al, bh
	cmp al, bl
	jl result	; al<16

	;al>=16
	sub al, bl
	mov bh, 1

result:
	push si
	mov si, [bp+8] ;res

	add si, dx

	cmp al, 10
	jl a1 ; al<10
	;al>=10
	cmp al, 16
	jl a2 ; al<16
	; al>=16 значит жопа, надо делить
	sub al, 16
	mov bh, 1
	jmp next3
a2: sub al, 10
	add al, 'A' ;закодировано и готово к вписке в строку
	mov bh, 0
	jmp next3

a1:	add al, 30h
next3:
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

	cmp al, 41h
	jl hh11 ; al<A
	add al, 10	;делаю из буквы цифру
	sub al, 'A'
	jmp next11
hh11:
	sub al, 30h ;цифра 
next11:
	add al, bh

	cmp al, 10
	jl a21 ; al<10
	;al>=10
	cmp al, 16
	jl a22 ; al<16
	; al>=16 значит жопа, надо делить
	sub al, 16
	mov bh, 1
	jmp next33
a22: 
	sub al, 10
	add al, 'A' ;закодировано и готово к вписке в строку
	mov bh, 0
	jmp next33

a21:
	add al, 30h
	mov bh, 0
next33:

	mov [si], al
	dec di
	inc si
	loop lep1
	pop si
	jmp ed

qq2:
	jmp qq3

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

	cmp al, 41h
	jl hh111 ; al<A
	add al, 10	;делаю из буквы цифру
	sub al, 'A'
	jmp next111
hh111:
	sub al, 30h ;цифра 
next111:
	add al, bh
	jmp hlp

hlp:
	cmp al, 10
	jl a211 ; al<10
	;al>=10
	cmp al, 16
	jl a221 ; al<16
	; al>=16 значит жопа, надо делить
	sub al, 16
	mov bh, 1
	add al, 30h
	jmp next331

a221: 
	sub al, 10
	add al, 'A' ;закодировано и готово к вписке в строку
	mov bh, 0
	jmp next331

a211:
	add al, 30h
	mov bh, 0
next331:
	mov [di], al
	inc di
	dec si
	loop lep2
	cmp bh, 0
	je sds
	add bh, 30h
	mov [di], bh

sds:
	pop di
	jmp ed

qq3:
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
	push offset res
	push offset str1
	push offset str2
	call calc

	mov dx, offset res
	mov si, dx
	;mov ah, 09h
	;int 21h
	add si, 6
	mov cl, 5
outp:
	mov dl, [si]
	;sub dl, 30h
	mov ah, 02h
	int 21h
	dec si
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