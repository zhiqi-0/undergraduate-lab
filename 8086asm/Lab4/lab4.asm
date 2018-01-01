;Basic Idea: every element perform 'add' operation
;meet paren then save res & sign to stack and calculate data inside paren first
include emu8086.inc
 
temp dw 1 dup(0)

mov bx, 0                   ;bl used for sign flag; bh used for operator flag
mov cx, 0                   ;cx used for result

get_val:
    ;get input data
    mov dx, 0
    mov ah, 1
    int 21h                 ;data now in al
    ;set sign bit, use dl
    cmp al, 43              ;if = '+'
    je set_add
    cmp al, 45              ;if = '-'
    je set_sub
    cmp al, 40              ;if = '('
    je set_leftparen
    cmp al, 41              ;if = ')'
    je set_rightparen
    cmp al, 13              ;if = '\n'
    je print
    jmp set_data            ;if = '0' - '9'            
set_add:
    call update_res
    jmp get_val
set_sub:
    call update_res
    add bl, 1               ;means '-'
    jmp get_val
set_leftparen:
    push cx
    mov bh, 0
    push bx
    mov bx, 0
    mov cx, 0
    mov temp[0], 0
    jmp get_val
set_rightparen:
    call update_res
    pop bx                  ;sign bit before ()
    mov temp[0], cx
    mov cx, 0
    call update_res         ;set () value
    pop dx                  ;result before ()
    add cx, dx              ;cal result
    jmp get_val
set_data:
    mov ah, 0
    sub al, 48              ;get data
    mov si, ax              ;si = data
    mov ax, temp[0]         ;get previous data
    mov dx, 10
    mul dx                  ;dx = ax * 10
    add ax, si              ;update data
    mov temp[0], ax
    mov bh, 0               ;reset operator flag
    jmp get_val
print:
    call update_res
    mov dl, 13
    mov ah, 2
    int 21h
    mov dl, 10
    int 21h
    mov dl, cl              ;check sign
    and dl, 80h
    cmp dl, 80h             ;negative
    je set_negative_out
    mov ch, 0
print_res:
    mov ax, cx
    call print_num
    define_print_num
    define_print_num_uns
    ret
set_negative_out:
    mov ch, 255
    jmp print_res

update_res proc near
    ;used for update cx(results)
    cmp bh, 1               ;bh = 1 means already updated
    je update_res_out
    mov bh, 1
    mov dx, temp[0]         ;dx denotes unsigned data
    and bl, 1
    cmp bl, 1               ;means dx is negative
    je set_negative
update:
    add cl, dl              ;update result
    mov temp[0], 0          ;reset temp data
    mov bl, 0
    ret
set_negative:
    push bx
    mov bx, dx              ;bx = u data
    mov dx, 0               ;dx = 0
    sub dx, bx              ;dx = -data
    pop bx
    jmp update
update_res_out:
    ret
update_res endp