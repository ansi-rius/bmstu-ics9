assume cs: code, ds: data

data segment
mas db 52, 22, 70, 38, 29, 90, 21, 40, 50, 60          
len dw $-mas
indexMax db ?   
strMax      DB 13,10,"Max value: ","$"
strMaxIndex DB 13,10,"Index of Max value: ","$"
data ends
code segment

; Найти индекс максимального элемента массива

start:	mov ax, data
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
 
		;вывод(начало) 
  		push ax
  		; Ввод множимого
  		lea dx, strMax ; в DX - адрес строки
  		mov ah, 9
  		int 21h ; вывод строки
  		pop ax
 
 
;ДАННЫЕ В al хранятся       
		aam     
		add ax, 3030h   
		mov bx, ax      
		mov ah, 02       
		mov dl, bh       
		int 21h          
		mov dl, bl       
		int 21h
 
; Ввод множимого
  		lea dx,strMaxIndex ; в DX - адрес строки
  		mov ah,9
  		int 21h ; вывод строки
 
  		mov al, indexMax
 
;теперь номер максимального в al
		aam     
		add ax, 3030h   
		mov bx, ax      
		mov ah, 02       
		mov dl, bh       
		int 21h          
		mov dl, bl       
		int 21h
 
		mov ax, 4c00h    
		int 21h  
		code ends
		end start