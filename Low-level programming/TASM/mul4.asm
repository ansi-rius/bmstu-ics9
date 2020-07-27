assume cs: code, ds: data

data segment
str1 db 10, 9 dup (0)
str2 db 10, 9 dup (0)
ennd db 0dh,0ah, '$'
res db 10, 9 dup (0)
res2 db 10, 9 dup (0)

fin db 10, 9 dup (0)
data ends

code segment

mult proc
	push bp
	mov bp, sp
	mov al, 0
	mov ah, 0
	mov bl, 0
	mov bh, 0
	mov cl, 0
	mov ch,0
	mov dl, 0
	mov dh,0


	mov si, [bp+4] ; str1
	mov di, [bp+6] ; цифра

	mov al, [si+1] ;n1
	mov bl, [di+1] ;n2

	cmp al, bl
	jge iter   ;n1 >= n2
	mov cl, bl
	jmp setIter
iter: 
	mov cl, al
setIter:
	mov dl, [si] ;конец массива
	mov ah, 0

	add si, ax
	add di, bx

	add si, 1 ;последний элемент str2
	add di, 1 ;последний элемент str1

	mov bh, 0

	mov dh, 0

lep1part: ;внутренний цикл
	mov al, [si]
	mov bl, [di]

	sub al, 30h
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
	inc bl ;кладу цифру в массив = увеличиваю n
	mov [si+1], bl
	add si, dx
	add al, 30h
	mov [si], al
	dec dl

	pop si

	dec si
	loop lep1part

	cmp bh, 0
	je eds; bh=0
	;bh>0
	push si
	mov si, [bp+8] ;res
	mov al, [si+1]
	inc al
	mov [si+1], al
	add si, dx
	dec dl
	add bh, 30h
	mov [si], bh

	pop si
eds:
;отладочная печать, сколько раз работает ф-ия
;и что она ваще выводит

;	mov si, [bp+8]
	;mov ah, 09h
	;int 21h
;	add si, 2
;	mov cl, 9
;outp:
;	mov dl, [si]
	;add dl, 30h
;	mov ah, 02h
;	int 21h
;	inc si
;	loop outp

;конец отладки
	mov al, 0
	mov ah, 0
	mov bl, 0
	mov bh, 0
	mov cl, 0
	mov ch,0
	mov dl, 0
	mov dh,0

	pop bp

	ret
mult endp

start:
	mov ax, data
	mov ds, ax

	mov si, offset res
	mov di, offset fin
	mov cl, [si]
	sub cl, 2
	add si, 2
	add di, 2
	mov al, 30h
pep:
	mov [si], al
	mov [di], al
	inc si
	inc di
	loop pep

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

	mov si, offset str1
	mov di, offset str2
	mov al, [si+1]
	mov ah, [di+1]

	cmp al, ah
	jl we ;al<ah
	push offset fin
	push offset str2
	push offset str1
	jmp wex
we:
	push offset fin
	push offset str1
	push offset str2
wex:
	call mult

	mov si, offset str1
	mov di, offset str2
	mov al, [si+1]
	mov ah, [di+1]

	cmp al, ah
	jl wes ;al<ah
	mov si, offset str1
	mov di, offset str2
	jmp wess
wes:
	mov di, offset str1
	mov si, offset str2
wess:
	mov al, [si+1]
	mov ah, [di+1]

	cmp al, 1
	je exit1
	;al!=1
	cmp ah, 1
	je exit1
	;ah!=1

	pop si
	pop si
	pop si
	mov bl, 1 ;счетчик внешнего цикла + сдвиг
	mov di, offset str2
	mov dh, [di+1]
q:
; пододвигаю цифру второй строки	
	push bx
	push dx
	mov si, offset str2
	mov cl, [si+1]
	add si, cx
	dec cl
	inc si
tr:
	mov al, [si-1]
	mov [si], al
	dec si
	loop tr
; конец сдвига

	;mov si, offset str2
	;add si, 2
	;mov al, [si]
	;inc si
	;mov al, [si]
	mov si, offset str1
	mov di, offset str2
	mov al, [si+1]
	mov ah, [di+1]

	cmp al, ah
	jl we1 ;al<ah
	push offset res
	push offset str2
	push offset str1
	jmp wex1
we1:
	push offset res
	push offset str1
	push offset str2
wex1:
	call mult
	pop si
	pop si
	pop si
	jmp oo
exit1:
	jmp exit2

oo:
; надо сложить с результатом + сдвиг
	pop dx
	pop bx
	mov si, offset res
	mov di, offset fin
	mov cl, [si] ;10
	;dec cl ;9
	add si, cx ; в конце строки (9)
	add di, cx ;в конце стркоки (9)
	dec cl	;8
	sub di, bx ;(8)
	sub cl, bl ;7
	jmp sumres
	afr:
	jmp q
sumres:
	mov al, [di]
	sub al, 30h
	mov ah, [si]
	sub ah, 30h

	cmp dl, 0
	je non ;dl = 0
	;dl !=0
	add al, dl
non:
	add al, ah
	cmp al, 10
	jl hep ; al<10

	;al>=10
	sub al, 10
	mov dl, 1
	jmp edd
hep:
	mov dl, 0
edd:
	add al, 30h
	mov [di], al
	dec si
	dec di
	dec cl
	cmp cl, 0
	je xd ;cl=0
	;cl!=0
	jmp sumres
xd:
	inc bl
	cmp bl, dh
	jl afr ;bl < bh

finale:
	mov si, offset fin
	;mov ah, 09h
	;int 21h
	add si, 2
	mov cl, 9
outp1:
	mov dl, [si]
	;add dl, 30h
	mov ah, 02h
	int 21h
	inc si
	loop outp1
	jmp rew

exit2:
	mov si, offset fin
	;mov ah, 09h
	;int 21h
	add si, 2
	mov cl, 9
outp2:
	mov dl, [si]
	;add dl, 30h
	mov ah, 02h
	int 21h
	inc si
	loop outp2

rew:
	mov ah, 4ch
	int 21h
	code ends
	end start