sseg segment para stack 'stack'
dw 200h
sseg ends
dseg segment para 'data'
val1 db 'COE$'
val2 db '415',10,13,'$'
val3 db 10,13, '1$'
dseg ends
cseg segment para 'code'
main proc far
assume cs:cseg, ds:dseg, ss:sseg
mov ax,dseg
mov ds,ax
mov ax,0003h
int 10h

;blockA
mov ah,09
lea dx,val1
int 21h

;block B
mov ah,09
lea dx,val2
int 21h

;block C
mov ah,02
mov dl,val3
int 21h

mov ah,4ch
int 21h
main endp
cseg ends
end main
