assume cs: code, ds: data

data segment
vara dd 4.0
varb dd 6.0
varc dd 3.0
vard dd 2.0
sum db ?
data ends

code segment
start:	mov ax, data
		mov ds, ax
		mov ax, 0000h
		mov bx, 0000h
		mov al, varb  ;al=b
		mov bl, varc  ;bl=c
		;div cl ; bx=bx/cl bh=bx/cl bl=bx%cl
		fdiv bl  ; ax=ax/bl ah=ax/bl al=ax%bl
		;mov bl, ax
		fadd al, vara
		mov bl, vard
		fmul bx
		fsub al, 4
		;mov sum, ax
		int 21h
		code ends
		end start