assume cs: code, ds: data

data segment
str1 db 10, 9 dup (0)
str2 db 10, 9 dup (0)
str3 db 10, 9 dup (0)
str4 db 10, 9 dup (0)
ennd db 0dh,0ah, '$'
res db 10, 9 dup (0)
res2 db 10, 9 dup (0)
str0 db 10, 9 dup (0)
fin db 10, 9 dup (0)
data ends

code segment

perev proc
    push bp
    mov bp, sp
   
    mov bl, 0
    mov si, [bp+4]
    mov di, [bp+6]
    mov bl, 10
    mov [di], bl
    mov al, [di]
    mov bl, 0
    add si, 2
point:
    mov al, [si]
    sub al, '0'
    cmp al, 0
    jne ded
    add bl, 1
    add si, 1
    jmp point
ded:
    add di, 1
    mov cl, 10
    sub cl, bl
    sub cl, 2
    ;add al, '0'
    mov [di], cl
lop:
    add di, 1
    mov dh, [si]
    ;add dh, '0'
    mov [di], dh
    ;mov dl, 0
    ;mov [si], dl
    cmp cl, 0
    je vixod
    dec cl
    add si, 1
    jmp lop
vixod:
   
    mov di, [bp+6]
    mov al, [di]
    inc di
    mov al, [di]
    inc di
    mov al, [di]
    inc di
    mov al, [di]
    inc di
    mov al, [di]

	mov si, offset str0
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
   
   
    pop bp
    ret
perev endp

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

	mov si, [bp+8]
	;mov ah, 09h
	;int 21h
	add si, 2
	mov cl, 9
outp:
	mov dl, [si]
	;add dl, 30h
	mov ah, 02h
	int 21h
	inc si
	loop outp

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

	mov al, [di+2]
	cmp al, 31h
	jne rr ;al!=1
	mov si, offset str1
	;mov ah, 09h
	;int 21h
	mov cl, [si+1]
	add si, 2
outp6:
	mov dl, [si]
	;add dl, 30h
	mov ah, 02h
	int 21h
	inc si
	loop outp6
	jmp exit1
rr:
	cmp al, 30h
	jne tt
	mov dl, 31h
	mov ah, 02h
	int 21h
	jmp exit1
tt:
	mov al, 0
	mov ah, 0
	mov bl, 0
	mov bh, 0
	mov cl, 0
	mov ch,0
	mov dl, 0
	mov dh,0

	mov si, offset str2
	mov di, offset str3
	mov al, [si]
	mov [di], al
	mov al, [si+1]
	mov [di+1], al
	mov al, [si+2]
	mov [di+2], al

	mov si, offset str1
	mov di, offset str2
	mov cl, 4
lk3:
	mov al, [si]
	mov [di], al
	inc si
	inc di
	dec cl
	cmp cl, 0
	je oee3
	jmp lk3
oee3:
	mov si, offset str1
	mov di, offset str4
	mov cl, 4
lk4:
	mov al, [si]
	mov [di], al
	inc si
	inc di
	dec cl
	cmp cl, 0
	je oee4
	jmp lk4
oee4:

	mov si, offset str2
	;mov ah, 09h
	;int 21h
	mov cl, [si+1]
	add si, 2
outp5:
	mov dl, [si]
	;add dl, 30h
	mov ah, 02h
	int 21h
	inc si
	loop outp5
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	push offset fin
	push offset str1
	push offset str2
qwe1:
	mov si, offset res
	mov di, offset fin
	mov cl, [si]
	sub cl, 2
	add si, 2
	add di, 2
	mov al, 30h
pep1:
	mov [si], al
	mov [di], al
	inc si
	inc di
	loop pep1
		
	call mult

	mov si, offset str1
	mov di, offset str2
	
	mov al, [si+1]
	mov ah, [di+1]

	cmp al, 1
	je y
	;al!=1
	cmp ah, 1
	je y
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
	push offset res
	push offset str2
	push offset str1
	
	call mult
	pop si
	pop si
	pop si
	jmp oo
exit1:
	jmp exit2
y:
	jmp y1
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
	mov bl, 0
	mov dh, 0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
y1:	mov di, offset str3
	mov cl, [di+2]
	sub cl, 30h
	mov ch, 0
	dec cl
	add cl, 30h
	mov [di+2], cl
	sub cl, 30h
	cmp cl, 1
	jle finale ;cl=<1

	mov al, 0
	mov ah, 0
	mov bl, 0
	mov bh, 0
	mov cl, 0
	mov ch, 0
	mov dl, 0
	mov dh, 0
	push offset str0
	push offset fin
	call perev
	pop si
	pop si

	mov si, offset str0
	mov al, [si+1]
	inc al
	;add al, 30h
	mov [si+1], al

	jmp oee1
finale:
	jmp finale2
oee1:
	mov si, offset str4
	mov di, offset str2

	mov cl, [si]
lk5:
	mov al, [si]
	mov [di], al
	inc si
	inc di
	dec cl
	cmp cl, 0
	je oee5
	jmp lk5
oee5:
	mov si, offset str2
	;mov ah, 09h
	;int 21h
	add si, 2
	mov cl, 9
outp3:
	mov dl, [si]
	;add dl, 30h
	mov ah, 02h
	int 21h
	inc si
	loop outp3

	mov si, offset str0
	mov di, offset str1

	mov cl, [si]
lk1:
	mov al, [si]
	mov [di], al
	inc si
	inc di
	dec cl
	cmp cl, 0
	je oee2
	jmp lk1
oee2:
	mov si, offset str1
	;mov ah, 09h
	;int 21h
	add si, 2
	mov cl, 9
outp4:
	mov dl, [si]
	;add dl, 30h
	mov ah, 02h
	int 21h
	inc si
	loop outp4

	push offset fin
	push offset str2
	push offset str1
 	jmp qwe1

finale2:
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
rew:
	mov ah, 4ch
	int 21h
	code ends
	end start