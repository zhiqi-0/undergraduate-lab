; Author: Zhiqi Lin
; Last update time: 6/11/2017
include emu8086.inc     
    array db 36 dup(0)          ;allocate an array with 6*6 size
    mov dx, 1                   ;dx represents the number from 1-36
;store 1-36 into array                    
    mov cx, 36                  ;cx represents loop iterator
    mov bx, 0                   ;bx represents array index
store_loop:
    mov array[bx], dl           ;put number (range from 1-36) into array
    add dx, 1                   ;update number
    add bx, 1                   ;update index
    loop store_loop             ;until cx == 0
;print array
    mov cx, 6                              
    mov ax, 0                   ;visit array by array[ax][bx]
print_outer_loop:  
    mov bx, 0
print_inner_loop:                
    cmp bx, ax                  ;if bx <= ax than go to print array
    jle print_number
    PRINTN ' '                  ;print '\n'
    add ax, 1                   ;update ax, print new line
    loop print_outer_loop
    jmp print_end 
    
print_number:                   ;this function calculate the index of array and print on screen
    push ax                     ;save for later use
    mov dx, 6
    mul dx                      ;cal ax = ax * 6 + bx
    add ax, bx                  
    mov si, ax                  ;index registers only can be bx, si, di, bp
    mov ax, 0
    mov al, array[si]           ;prepare to print
    call print_num
    PUTC 32                     ;print space
    pop ax                      ;fetch ax
    add bx, 1                   ;prepare for next loop
    jmp print_inner_loop   
    
print_end: 
    DEFINE_PRINT_NUM
    DEFINE_PRINT_NUM_UNS
    RET;
END;