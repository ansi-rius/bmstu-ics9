sseg segment para stack 'stack'
   dw 200h
sseg ends
dseg segment para 'data'
   val1 db 'COE $'
   val2 db '415 $'
   val3 db '1'
   dseg ends
   cseg segment para 'code'
   main proc far
     assume cs:cseg,ds:dseg,ss:sseg
     mov ax,dseg
     mov ds,ax
     mov ax,003
     int 10h
     mov ah,4ch
     int 21h
   main endp
   cseg ends
     end main

