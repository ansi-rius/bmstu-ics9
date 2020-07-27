CODE    SEGMENT PUBLIC 'CODE'
        ASSUME CS:CODE,DS:DATA
 
START:
        mov AX,DATA
        mov DS,AX
 
        mov cx,len
        lea SI,X
        mov     bx,[si]         ;bx - максимальный элемент
        mov     dl,0            ;индекс текущего элемента
        dec     cx              ;рассматривать будем со 2-го элемента
        add     si,2
        inc     dl
h:
        cmp bx,[si]
        jge Max
        mov bx,[si]
        mov indexMax,dl
Max:
        add si,2
        inc dl
        loop    h
ENDLESS:
        JMP ENDLESS
CODE    ENDS
 
DATA    SEGMENT PUBLIC PARA 'DATA'
X DW 5,6,7,2,3,4,15,1,2,8
len=($-X)/2
indexMax DB ?
DATA    ENDS
 
STACKSEG SEGMENT PARA STACK 'STACK'
        db 100h dup(?)
STACKSEG ENDS
        END START
