#if defined(__cplusplus)
extern "C" {
#endif
#include "../include/cffi.h"
extern void* cffi_call_platform(int params_count,void** params,int stack_size, void* fun);

void* cffi_call(void* fun, int params_count , void** params){

    // 最大支持6个参数
    if(params_count > 6) {
        return 0;
    }

    // 计算 cffi_call_platform 函数需要分配的堆栈大小
    // 在这里全部使用64位寄存器作为参数传递。
    // 堆栈大小以16字节对齐。
    int stack_size = 0;
    // 获取最小公倍数
    double result = (params_count + 2.0) * 8 /16;
    if (result != (int)result) {
        stack_size = (int)(result + 1) * 16;
    } else {
        stack_size = (int)result * 16;
    }

    return cffi_call_platform(params_count,params, stack_size, fun);
}

#if defined(__cplusplus)
}
#endif