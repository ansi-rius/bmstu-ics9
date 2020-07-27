INCLUDE io.h

Cr EQU 0ah
Lf EQU 0dh


data SEGMENT
p_str1 DB Cr, Lf, 'Enter the string: ',0
p_str2 DB Cr, Lf, 'The copied string is: ',0
str1 DB 100 DUP (?)
str2 DB 100 DUP (?)
data ENDS



code SEGMENT
	ASSUME cs:code, ds:data
start:	mov ax, data
	mov ds, ax
		;input str1
	output p_str1
	inputs str1, 100
		;initalize
	lea si, str1
	lea di, str2	
		;copy str1 to str2
cpy_nxt:mov bl, [si];copy source to destination
	mov [di], bl
	inc si;increment source and destination
	inc di	
	dec cx;decrement count
	jnz cpy_nxt;if not zero goto next bit
		;output str2
	output p_str2
	output str2

quit:	mov al, 00h
	mov ah, 4ch
	int 21h
code ENDS
END start