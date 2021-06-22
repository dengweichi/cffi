#params1:int params_count rdi
#params2: void** params rsi
#params3: int stack_size rdx
#params4: void* fun rcx
.text
	.globl	cffi_call_platform
	.type	cffi_call_platform, @function
    cffi_call_platform:
        pushq	%rbp
        movq	%rsp, %rbp# 初始化堆栈空间
       	subq	%rdx, %rsp#分配局部变量的堆栈
        movq	%rdi, -8(%rbp)#保存参数数量
        movq	%rcx, -16(%rbp)#保存调用的函数指针
        pushq %rbx #需要恢复改寄存器
        movq %rsi, %rbx# 多参数数字的引用
params_in_stack:
        cmpq $1,-8(%rbp)
        jl fun_call_params #参数小于1
        movq 0(%rbx), %rax
        movq %rax, -24(%rbp)

        cmpq $2,-8(%rbp)
        jl fun_call_params #参数小于2
        movq 8(%rbx), %rax
        movq %rax, -32(%rbp)

        cmpq $3,-8(%rbp)
        jl fun_call_params #参数小于3
        movq 16(%rbx), %rax
        movq %rax, -40(%rbp)

        cmpq $4,-8(%rbp)
        jl fun_call_params #参数小于4
        movq 24(%rbx), %rax
        movq %rax, -48(%rbp)

        cmpq $5,-8(%rbp)
        jl fun_call_params #参数小于5
        movq 32(%rbx), %rax
        movq %rax, -56(%rbp)

        cmpq $6,-8(%rbp)
        jl fun_call_params #参数小于5
        movq 40(%rbx), %rax
        movq %rax, -64(%rbp)
# 把参数转配到指定的寄存器
fun_call_params:
        cmpq $1,-8(%rbp)
        jl fun_call #参数小于1
        movq -24(%rbp), %rax
        movq %rax, %rdi

        cmpq $2,-8(%rbp)
        jl fun_call #参数小于2
        movq -32(%rbp), %rax
        movq %rax, %rsi

        cmpq $3,-8(%rbp)
        jl fun_call #参数小于3
        movq -40(%rbp), %rax
        movq %rax, %rdx

        cmpq $3,-8(%rbp)
        jl fun_call #参数小于4
        movq -48(%rbp), %rax
        movq %rax, %rcx

        cmpq $3,-8(%rbp)
        jl fun_call #参数小于5
        movq -56(%rbp), %rax
        movq %rax, %r8

        cmpq $3,-8(%rbp)
        jl fun_call #参数小于6
        movq -64(%rbp), %rax
        movq %rax, %r9
fun_call:
        call *-16(%rbp)
        popq %rbx
        leave
        ret