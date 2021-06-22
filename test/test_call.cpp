
#include "gtest/gtest.h"
#include "../include/cffi.h"
#include <iostream>

int addWithoutParams () {
    return 1;
}

TEST(test_cffi_call_without_param, test_cffi_call) {
    void* result = cffi_call( (void*)addWithoutParams, 0, nullptr);
    EXPECT_EQ((unsigned long long)result, 1);
}


int addWithTowParams(int arg1, int agr2){
    return arg1 + agr2;
}

TEST(test_cffi_call_with_tow_param, test_cffi_call) {
    void* argv [] = { (void*)1, (void*)2 };
    void* result = cffi_call( (void*)addWithTowParams, 2, argv);
    EXPECT_EQ((unsigned long long)result, 3);
}

int addWithSixParams(int arg1, int agr2, int arg3, int agr4, int arg5, int agr6) {
    return arg1 + agr2 + arg3 + agr4 + arg5 + agr6;
}

TEST(test_cffi_call_with_six_param, test_cffi_call) {
    void* argv [] = { (void*)1, (void*)2 , (void*)3, (void*)4 ,(void*)5, (void*)6 };
    void* result = cffi_call( (void*)addWithSixParams, 6, argv);
    EXPECT_EQ((unsigned long long)result, 21);
}