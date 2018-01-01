include emu8086.inc

jmp get_val

res db 20 dup(0)
tmp db 20 dup(0)

get_val:
    mov dx, 0
    mov ah, 1
    int 21h
    sub al, 48
    mov dl, al
    int 21h
    cmp al, 13
    je start
    mov dh, dl
    sub al, 48
    mov dl, al
start:
    ;mov dx, 0109h         ;dh,dl 
    mov res[0], 1       ;set initial val
for_cond:
    cmp dh, 1           
    jne for_single
for_double:
    mov si, 0
    ;copy tmp
    for_tmp_cond:
        cmp si, 19
        je for_single
    for_tmp_body:       ;tmp = res * 10
        mov bl, res[si]
        mov tmp[si + 1], bl     ;tmp[si + 1] = res[si]
        add si, 1
        jmp for_tmp_cond             
for_single:             ;dh = 0, don't need tmp
    mov cl, 0           ;cl for carry
    mov si, 0
    for_mul_cond:
        cmp si, 20
        je whether_add
    for_mul_body:
        mov ax, 0       ;clear ax
        mov al, res[si]
        mul dl          ;al = res[si] * dl
        add al, cl      ;al = res[si] * dl + cl
        mov bl, 10      ;al = ax / 10, ah = ax % 10
        div bl
        mov res[si], ah ;store res
        mov cl, al      ;update cl
        add si, 1       ;update si
        jmp for_mul_cond
whether_add:
    cmp dh, 1
    jne update_dx
    ;add tmp + res
    mov cx, 0
    mov si, 0
    for_add_cond:
        cmp si, 20
        je update_dx
    for_add_body:
        mov ax, 0
        mov al, res[si]
        add al, tmp[si]
        add al, cl          ;al = res[si] + tmp[si] + cl
        mov bl, 10
        div bl              ;al = ax / 10; ah = ax % 10
        mov res[si], ah
        mov cl, al
        ;update si
        add si, 1
        jmp for_add_cond
update_dx:
    cmp dl, 0
    je decrease_dh
    sub dl, 1
    cmp dx, 0               ; check whether 00
    je print_res
    jmp for_cond
decrease_dh:
    sub dh, 1
    mov dl, 9
    jmp for_cond
print_res:
    putc 10
    putc 13
    mov si, 19
de_0:
    cmp res[si], 0
    je de_update
    jmp print_cond
de_update:
    sub si, 1
    jmp de_0
print_cond:
    cmp si, 0
    js exit
print_body:
     mov al, res[si]
     call print_num
     sub si, 1
     jmp print_cond
exit:
    define_print_num
    define_print_num_uns
    ret    