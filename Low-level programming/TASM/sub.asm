assume cs: code, ds: data

data segment
str1 db 10, 9 dup (0)
str2 db 10, 9 dup (0)
ennd db 0dh,0ah, '$'
res db 10, 9 dup (0)
data ends

code segment

subt proc
	push bp
	mov bp, sp
	mov di, [bp+4] ;str2
	mov si, [bp+6] ;str1

	mov al, [si+1] ;n1
	mov bl, [di+1] ;n2

	cmp al, bl
	jl sgn1 ;n1<n2

	;n1>=n2
	cmp al, bl
	je sgn2 ;n1=n2

	;n1>n2
sg:	mov dh, 0
	mov dl, "+"
	mov ah, 02h
	int 21h
	jmp signSet

sgn1:
	mov dh, 1
	mov dl, "-"
	mov ah, 02h
	int 21h
	jmp signSet

sgn2:
	mov cl, al
	add si, 2
	add di, 2

lepSgn:
	mov al, [si]
	mov ah, [di]
	cmp al, ah
	jl sgn3 ;al<ah

	;al>=ah
	cmp al, ah
	je sgn4 ;al=ah

	;al>ah
	jmp sg
sgn3:
	jmp sgn1
sgn4:
	inc si
	inc di
	loop lepSgn  ;rabotaet, gospodi
	mov dh, 0
	mov dl, "+"
	mov ah, 02h
	int 21h

signSet:
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
	mov ah, 0
	add si, ax
	add di, bx

	add si, 1 ;последний элемент str2
	add di, 1 ;последний элемент str1

	mov dl, 0
	mov bl, 2
	mov bh, 0

part1lopa:
	cmp dh, 1
	je mark ; dh=1

	;dh=0
	mov al, [si]
	sub al, 30h
	mov ah, [di]
	sub ah, 30h
	jmp markSet

mark:
	mov ah, [si]
	sub ah, 30h
	mov al, [di]
	sub al, 30h

markSet:
	cmp al, ah
	jl presub1 ;al<ah

	;al>=ah
	sub al, ah
	sub al, dl
	mov dl, 0
	jmp recordRes

presub1:
	add al, 10
	sub al, dl
	sub al, ah
	mov dl, 1
	jmp recordRes

;;;;;;;;
recordRes:
	push si
	mov si, [bp+8] ;res
	add si, bx
	add al, 30h
	mov [si], al
	inc bl

	pop si

	dec si
	dec di
	loop part1lopa
;---------------------
	mov di, [bp+4] ;str2
	mov si, [bp+6] ;str1
	mov al, [si+1] ;n1
	mov bl, [di+1] ;n2

	cmp al, bl
	jl qq1 ;n1<n2
	cmp al, bl
	je qq2

	;n1>n2
	jmp next3
qq1:
	push di
	mov di, si
	pop si
	push ax
	mov ax, bx
	pop bx

next3:
	push di ;n1> пушим короткую, она не нужна
	mov di, [bp+8]
	mov ch, 0
	mov cl, [si+1]
	sub cl, bl ;из большей вычитаю длину 2го слагаемого
	add si, 1
	add di, 2 ;res
	mov bh, 0
	add di, bx ;
	add si, cx ;

part2lopa:
	mov al, [si]
	sub al, 30h
	mov ah, dl

	cmp al, ah
	jl presub2 ;al<ah

	;al>=ah
	sub al, ah
	mov dl, 0
	jmp recordRes1

presub2:
	add al, 10
	mov dl, 1
	sub al, ah
	jmp recordRes1

;;;;;;;;
recordRes1:
	add al, 30h
	mov [di], al

	dec si
	inc di
	loop part2lopa
	pop si


;----------------
qq2:
	pop bp

	ret
subt endp

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
	call subt

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