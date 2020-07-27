assume cs: code, ds: data

data segment
msg db 0, 0, 0, 0
vara db 04h
varb db 06h
varc db 03h
vard db 02h
data ends
code segment

printBite proc
		mov es, ax 
		mov ds, ax
		xor di, di ;искл или обнуление

		std
		lea di, msg+2 ;для получения адреса msg
		mov msg[3], '$'
		mov bl, 10
		mov cx, 3 ;итерации цикла
		mov ah, 0

 goto: div bl ;делим на 10 чтобы забрать остаток
		xchg al, ah ;в ah нужная нам цифра, а запись в al
		add al, 30h ;получаем символьный код цифры
		stosb ;сохраняет содержимое байта в регистре al
		mov al, ah
		mov ah, 0
	loop goto

	mov ah, 9
	mov dx, offset msg
	int 21h
	ret
printBite endp

start:	mov ax, data
		mov ds, ax
		mov ax, 0000h
		mov bx, 0000h
		mov al, varb  ;al=b
		mov bl, varc  ;bl=c
		;div cl ; bx=bx/cl bh=bx/cl bl=bx%cl
		div bl  ; ax=ax/bl ah=ax/bl al=ax%bl
		;mov bl, ax
		add al, vara
		mov bl, vard
		mul bx
		sub al, 4

		call printBite
		;mov sum, al
		mov ah, 4ch
		int 21h
		code ends
		end start