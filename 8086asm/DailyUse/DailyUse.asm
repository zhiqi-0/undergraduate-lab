; for daily use
; zhiqi lin
; 12/30/2017

jmp test_start

filename db 'C:\data1.txt', 0
test_string db 'Hello World', 0

; print_num procedure
; print 16 bit signed number in ax
print_snum_16 proc near
    ; push used register
    push ax
    push bx
    push cx
    push dx
    test ax, 8000h  ;check signed bit
    jnz print_snum_negative   
print_snum_dowhile_init:
    mov bx, 0       ;for counting bit
    mov cx, 10      
print_snum_do_body:
    xor dx, dx
    div cx          ;ax = ax / cx, dx = ax mod cx
    add dl, 30h
    push dx
    inc bx  
print_snum_while_cond:
    cmp ax, 0
    jne print_snum_do_body
    mov ah, 2
print_snum_print_cond:
    cmp bx, 0
    je print_snum_exit
print_snum_print_body:
    pop dx              ; dx used for output
    int 21h
    sub bx, 1
    jmp print_snum_print_cond
print_snum_exit:
    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_snum_negative:
    neg ax          ;
    mov dx, '-'     
    push ax
    mov ah, 2       ;
    int 21h
    pop ax
    jmp print_snum_dowhile_init 
print_snum_16 endp


; print_num procedure
; print 8 bit signed number in al
print_snum_8 proc near
    push ax
    test al, 80h
    jz print_snum_8_print
    xor ah, ah
    not ah
print_snum_8_print:
    call print_snum_16
    pop ax
    ret 
print_snum_8 endp

; print_unum procedure
; print 16 bit unsigned number in ax
print_unum_16 proc near
    push ax
    push bx
    push cx
    push dx
print_unum_dowhile_init:
    mov bx, 0       ;for counting bit
    mov cx, 10      
print_unum_do_body:
    xor dx, dx
    div cx          ;ax = ax / cx, dx = ax mod cx
    add dl, 30h
    push dx
    inc bx  
print_unum_while_cond:
    cmp ax, 0
    jne print_unum_do_body
    mov ah, 2
print_unum_print_cond:
    cmp bx, 0
    je print_unum_exit
print_unum_print_body:
    pop dx              ; dx used for output
    int 21h
    sub bx, 1
    jmp print_unum_print_cond
print_unum_exit:
    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_unum_16 endp

print_enter proc near
    push ax
    push dx
    mov ah, 2
    mov dx, 13
    int 21h
    mov dx, 10
    int 21h
    pop dx
    pop ax
    ret
print_enter endp

; read a integer( >= 0, 16 bit) from file handle
; this will automatically pass starting space char(s) 
; param: bx: file handle
; return: dx:value, al: last read status (use cmp al, eof to check)
iofile_read_base10 proc near
    push cx          
iofile_read_base10_pass_body:
    mov dx, offset iofile_databuffer
    mov cx, 1
    mov ah, 3fh
    int 21h             ; read one byte, now in [dx]
    mov dl, iofile_databuffer
    cmp al, 00h         ; check whether is at file end
    je iofile_read_base10_end_exit
    cmp dx, ' '         ; check whether is space
    je iofile_read_base10_pass_body
    sub dl, 30h
    push dx             ; get first number into stack
iofile_read_base10_do_body:
    mov dx, offset iofile_databuffer
    mov cx, 1           ; read only one byte
    mov ah, 3fh
    int 21h             ; read a byte, now in [dx]
    mov dx, 0
    mov dl, iofile_databuffer
    cmp dx, 30h         ; check whether dx < '0'
    jl iofile_read_base10_exit
    cmp dx, 39h         ; check whecher dx > '9'
    jg iofile_read_base10_exit          
    pop ax              ; get previous integer 
    sub dx, 30h
    push dx      
    mov cx, 10
    mul cx              ; ax = ax * 10, in dx:ax
    pop dx
    add ax, dx          ; ax = ax * 10 + dx
    push ax
    jmp iofile_read_base10_do_body
iofile_read_base10_exit:
    pop dx
    pop cx
    ret
iofile_read_base10_end_exit:
    pop cx
    ret
iofile_databuffer db 0

iofile_read_base10 endp


; read a integer( >= 0, 16 bit, base 16) from file handle
; this will automatically pass starting space char(s) 
; param: bx: file handle
; return: dx:value, al: last read status (use cmp al, 00h to check)
iofile_read_base16 proc near
    push cx
    mov dx, 0
    push dx          
iofile_read_base16_pass_body:
    mov dx, offset iofile_base16_databuffer
    mov cx, 1
    mov ah, 3fh
    int 21h             ; read one byte, now in [dx]
    mov dl, iofile_base16_databuffer
    mov dh, 0
    cmp al, 00h         ; check whether is at file end
    je iofile_read_base16_exit
    cmp dx, ' '         ; check whether is space
    je iofile_read_base16_pass_body
    jmp iofile_read_base16_getnum
iofile_read_base16_update:
    pop ax
    shl ax, 4
    add al, dl          
    push ax
    mov dx, offset iofile_base16_databuffer
    mov cx, 1
    mov ah, 3fh
    int 21h             ; read one byte, now in [dx]
    mov dl, iofile_base16_databuffer
    mov dh, 0
    cmp al, 00h
    je iofile_read_base16_exit 
iofile_read_base16_getnum:
    ;check in 'a' - 'z'
    cmp dx, 'a'
    jl iofile_read_base16_bletter
    cmp dx, 'z'
    jg iofile_read_base16_exit
    sub dx, 87
    jmp iofile_read_base16_update
iofile_read_base16_bletter:
    cmp dx, 'A'
    jl iofile_read_base16_num
    cmp dx, 'Z'
    jg iofile_read_base16_exit
    sub dx, 55
    jmp iofile_read_base16_update
iofile_read_base16_num:
    cmp dx, '0'
    jl iofile_read_base16_exit
    cmp dx, '9'
    jg iofile_read_base16_exit
    sub dx, 30h
    jmp iofile_read_base16_update
iofile_read_base16_exit:
    pop dx
    pop cx
    ret
iofile_base16_databuffer db 0   
iofile_read_base16 endp

;read unsigned integer (16bit, base10) from keyboard
;return: ax
iokeyboard_uint_16 proc near
    push cx
    push dx
    mov cx, 0
iokeyboard_uint_cond:
    mov ah, 1
    int 21h
    cmp al, 13      ;check whether is enter
    je iokeyboard_exit
iokeyboard_uint_body:
    mov ah, 0
    sub al, 30h     ;digit number
    push ax
    mov ax, cx      ;ax = previous number
    mov cx, 10
    mul cx          ;ax = ax * 10, in dx:ax
    pop cx
    add cx, ax      ;cx = ax * 10 + cx
    jmp iokeyboard_uint_cond
iokeyboard_exit:
    call print_enter
    mov ax, cx
    pop dx
    pop cx
    ret
iokeyboard_uint_16 endp


;print string, end with ascii = 0
;param: si: offset of start addr
print_string proc near
    push dx
    push ax
    push si
print_string_cond:
    mov dx, [si]
    mov dh, 0
    cmp dx, 0
    je print_string_exit
print_string_body:
    mov ah, 2
    int 21h
    inc si
    jmp print_string_cond
print_string_exit:
    pop si
    pop ax
    pop dx
    ret
print_string endp
    
    
    
    
      
; test
test_start:
    mov dx, offset filename
    mov ax, 3d00h
    int 21h                     ;open file, read-only mode
    mov bx, ax
read_cond:
    cmp al, 00h
    je keyboard_test
read_body:
    call iofile_read_base16
    push ax
    mov ax, dx
    call print_unum_16
    call print_enter
    pop ax
    jmp read_cond
keyboard_test:
    call iokeyboard_uint_16
    call print_unum_16
    call print_enter
    call iokeyboard_uint_16
    call print_unum_16
    call print_enter
    lea si, test_string
    call print_string
exit:
    mov ah, 42                  ; back to system   
    int 21h
    
     
    