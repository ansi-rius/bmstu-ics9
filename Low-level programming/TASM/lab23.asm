assume cs: code, ds: data

data segment
msg db 0, 0, 0, 0
mas db 52, 22, 70, 38, 29, 10, 21, 40, 50, 60          
len dw $-mas
indexMax db ?   
data ends
code segment

; Найти индекс максимального элемента массива
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

main:	mov ax, data
		mov ds, ax
		lea bx, mas  ;берём в bx адрес первого элемента
		mov cx, len  ;счетчик цикла
		mov ah, 1
		mov al, [bx]            
		mov indexMax, ah
 
Next:   
		cmp al, [bx]  ; сравниваем макс. число с очередным элементом массива
		jg  Max       ;Al>[BX]
		mov al, [bx]
		mov indexMax, ah
Max:
		inc bx  ;переходим к следующему элементу
		inc ah
		loop Next
		
		mov al, indexMax
		call printBite
		;mov sum, al
		mov ah, 4ch
		int 21h
		code ends
		end main