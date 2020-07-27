macro print
{
	mov si, offset res
    mov cl, 8
    add si, 2
lopa:
    mov dl, [si]
    mov ah, 02h
    int 21h
    inc si
    loop lopa
}

macro input
{	
	mov dx, offset string
    mov si, dx
    mov ax, 0
    mov ah, 0Ah
    int 21h

    mov dx, offset ln
    mov ah, 09h
    int 21h
            
    mov dx, offset old_char
    mov si, dx
    mov ah, 0Ah
    int 21h

    mov dx, offset ln
    mov ah, 09h
    int 21h

    mov dx, offset new_char
    mov si, dx
    mov ah, 0Ah
    int 21h

    mov dx, offset ln
    mov ah, 09h
    int 21h
}