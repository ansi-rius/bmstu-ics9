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
	mov si, [bp+6] ;str2
	mov di, [bp+8] ;str1
	mov bl, [si+1] ;n2 str2
	mov bh, [di+1] ;n1 str1
	cmp bl, bh
	jge aa   ;n2 >= n1
	mov cl, bh
aa: 
	mov cl, bl

	add si, bl ;индекс последнего эл str2
	add di, bh ;индекс последнего эл str1

	mov 



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

	push ah, 0
	
	push offset str1
	push offset str2
	push offset res
	call calc

	mov ah, 4ch
	int 21h
	code ends
	end start