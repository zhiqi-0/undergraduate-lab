define i32 @fib(i32 %n) {
    %1 = alloca i32, align 4
    store i32 %n, i32* %1, align 4
    %fib_cmp1 = icmp eq i32 %n, 0
    br i1 %fib_cmp1, label %func_out, label %check_1

check_1:                                 
    %cmp_res1 = icmp eq i32 %n, 1
    br i1 %cmp_res1, label %func_out, label %cal_recursive

cal_recursive:                                   
    %cal1 = sub nsw i32 %n, 1
    %res1 = call i32 @fib(i32 %cal1)
    %cal2 = sub nsw i32 %n, 2
    %res2 = call i32 @fib(i32 %cal2)
    %res = add nsw i32 %res1, %res2
    store i32 %res, i32* %1, align 4
    br label %func_out

func_out:                                     
    %out = load i32, i32* %1, align 4
    ret i32 %out
}

define i32 @main() {
    %1 = alloca i32, align 4
    %2 = alloca i32, align 4          ;represent x
    %3 = alloca i32, align 4          ;represent i
    store i32 0, i32* %1, align 4
    store i32 0, i32* %2, align 4
    store i32 0, i32* %3, align 4
    br label %loop.control

loop.control:                                     
    %control.i = load i32, i32* %3, align 4
    %cmp_res2 = icmp slt i32 %control.i, 10
    br i1 %cmp_res2, label %loop.content, label %func_out

loop.content:                                      
    %pre.i = load i32, i32* %3, align 4
    %res1 = call i32 @fib(i32 %pre.i)
    %pre.x = load i32, i32* %2, align 4
    %new.x = add nsw i32 %res1, %pre.x
    store i32 %new.x, i32* %2, align 4
    %new.i = add nsw i32 %pre.i, 1
    store i32 %new.i, i32* %3, align 4
    br label %loop.control

func_out:                                     
    %out = load i32, i32* %2, align 4
    ret i32 %out
}
