assume cs: code, ds: data

data segment
string db 10, 99 dup (0)
old_char db 10,9 dup (0)
new_char db 10,9 dup (0)
r db 0, '$'
res db 10, 99 dup (0)
ln db 0dh,0ah, '$'
data ends

code segment

include macro.asm

change proc
    push bp
    mov bp, sp
    mov si, [bp+4] ;str
    mov bx, [bp+6] ;old_char
    mov ah, bl
    mov bx, [bp+8] ;new_char
    mov al, bl
    mov di, [bp+10] ;res

    mov cl, [si]
    sub cl, 2
    mov bl, [si]
    mov [di], bl
    mov bl, [si+1]
    mov [di], bl
    add si, 2
    add di, 2

lep:
    mov bl, [si]
    cmp bl, ah
    je chg ;bl=old_char
    jmp ed
chg:
    mov [di], al
    jmp skp
ed: 
    mov [di], bl 
skp:
    inc si
    inc di
    loop lep

    pop bp
    ret

change endp

start:
    mov ax, data
    mov ds, ax
    input string 
   
    push offset res
    mov al, new_char[2]
    mov ah, 0
    push ax
    mov al, old_char[2]
    mov ah, 0
    push ax
    push offset string
    call change
    pop si
    pop si
    pop si
    pop si
    print string
   ; add si, 2
    ;mov dx, si
    ;mov ah, 09h
    ;int 21h

    mov ah, 4ch
    int 21h
    code ends
    end start
