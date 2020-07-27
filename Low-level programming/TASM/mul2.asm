assume cs: code, ds: data

data segment
str1 db 10, 9 dup (0)
str2 db 10, 9 dup (0)
ennd db 0dh,0ah, '$'
res db 10, 9 dup (0)
fin db 10, 9 dup (0)
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

	pop bp

	ret
mult endp

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

	push offset res
	push offset str2
	push offset str1
	call mult


	mov dx, offset res
	mov si, dx
	;mov ah, 09h
	;int 21h
	add si, 2
	mov cl, 9
outp:
	mov dl, [si]
	;sub dl, 30h
	mov ah, 02h
	int 21h
	inc si
	loop outp
	
	

	mov ah, 4ch
	int 21h
	code ends
	end start