sseg segment para stack 'stack'
dw 200h
sseg ends

dseg segment para 'data'



dseg ends

cseg segment para 'code'

main proc far
assume cs:cseg, ds:dseg, ss:sseg
mov ax, dseg
mov ds, ax
mov es, ax



mov ah, 4ch
int 21h
main endp

cseg ends
end main
