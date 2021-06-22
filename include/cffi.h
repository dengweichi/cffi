//
// Created by CF on 2021/6/22.


#ifndef UNTITLED2_CFFI_H
#define UNTITLED2_CFFI_H

/**
 * 如果环境为c++编译环境，使用扩展c语言的规则去处理
 */
#if defined(__cplusplus)
extern "C" {
#endif

void *cffi_call(void *fun, int params_count, void **params);

#if defined(__cplusplus)
    }
#endif

#endif
