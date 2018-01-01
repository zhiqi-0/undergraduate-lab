include emu8086.inc 

jmp openfile

; general rules for file system emulation:

; 1. the emulator emulates all drive paths in c:\emu8086\vdrive\
;    for example: the real path for "c:\test1" is "c:\emu8086\vdrive\c\test1"

; 2. paths without drive letter are emulated to c:\emu8086\MyBuild\
;    for example: the real path for "myfile.txt" is "c:\emu8086\MyBuild\myfile.txt"

; 3. if compiled file is running outside of the emulator rules 1 and 2 do not apply.

filePath db 'C:\data.txt', 0
buffer db 15 dup(0)             ;read 15 numbers

openfile:
    mov dx, offset filePath
    mov ax, 3d00h               ;read-only mode
    int 21h                     ;open the file, ax now is file handle
    jc exit
    ;loop read and store data
    mov bx, ax                  ;read file handle
    mov cx, 15                  ;loop iterator
    mov si, 0                   ;buffer index buffer[si]
getdata_loop:
    push cx
    mov dl, buffer[si]          ;get current buffer[si]
    push dx                     ;push buffer[si] into stack for later use
    lea dx, buffer[si]          ;get current buffer address
    mov cx, 1                   ;read only 1 byte
    mov ah, 3fh                 
    int 21h                     ;read byte, now in [dx]
    pop ax                      ;get previous buffer[si] 
    cmp buffer[si], 32          ;compare with ' '
    je getdata_update           
    sub buffer[si], 48          ;sub ascii value 48 '0'
    mov dl, 10
    mul dl                      ;al = al * 10
    add al, buffer[si]          ;al = al * 10 + buffer[si]
    mov buffer[si], al
    pop cx
    jmp getdata_loop
getdata_update:
    mov buffer[si], al
    call print_num
    PUTC 32 
    add si, 1
    pop cx
    loop getdata_loop
; for(ax = 0; ax < 15; ax = ax + 1){
;   for(bx = 0; bx < 14 - ax; ++bx){
;       if(buffer[bx] > buffer[bx + 1])
;            swap(buffer[bx],buffer[bx + 1])
;   }
;}
sort:
    PRINTN ' '
    mov cx, 15                  ;loop iterator
outer_loop:
    mov ax, cx                  ;
    sub ax, 1                   ;ax represents 14 - ax
    mov bx, 0
inner_loop:
    cmp bx, ax
    jge outer_update 
    mov dl, buffer[bx]          ;al = buffer[bx]
    add bx, 1                   ;don't need update again later
    mov dh, buffer[bx]          ;ah = buffer[bx + 1]
    cmp dl, dh
    ja swap                     ;unsinged jg
    jmp inner_loop
swap:
    mov buffer[bx], dl
    mov buffer[bx - 1], dh
    cmp bx, ax
    jb inner_loop
outer_update:
    loop outer_loop
    mov cx, 15
    mov bx, 0
    jmp print_res
print_res:
    mov ax, 0
    mov al, buffer[bx]
    call print_num
    PUTC 32
    add bx, 1
    loop print_res
    jmp exit
exit: 
    DEFINE_PRINT_NUM
    DEFINE_PRINT_NUM_UNS
    ret

    