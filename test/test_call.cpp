
#include "gtest/gtest.h"
#include "../include/cffi.h"
extern "C" {
#include <string.h>
#include <dlfcn.h>
}
int testValue1 = 0;
void funWithoutParamsWithoutRvalue() {
    testValue1++;
}

TEST(test_cffi_call_without_params_without_rValue, test_cffi_call) {
    EXPECT_EQ(testValue1, 0);
    cffi_call( (void*)funWithoutParamsWithoutRvalue, 0, nullptr);
    EXPECT_EQ(testValue1, 1);
}


int funWithoutParams () {
    return 1;
}
TEST(test_cffi_call_without_params, test_cffi_call) {
    void* result = cffi_call( (void*)funWithoutParams, 0, nullptr);
    EXPECT_EQ((unsigned long long)result, 1);
}


int funWithTowParams(int arg1, int agr2){
    EXPECT_EQ(arg1,1);
    EXPECT_EQ(agr2,2);
    return arg1 + agr2;
}

TEST(test_cffi_call_with_tow_params, test_cffi_call) {
    void* argv [] = { (void*)1, (void*)2 };
    void* result = cffi_call( (void*)funWithTowParams, 2, argv);
    EXPECT_EQ((unsigned long long)result, 3);
}

int funWithSixParams(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    EXPECT_EQ(arg1,1);
    EXPECT_EQ(arg2,2);
    EXPECT_EQ(arg3,3);
    EXPECT_EQ(arg4,4);
    EXPECT_EQ(arg5,5);
    EXPECT_EQ(arg6,6);
    return arg1 + arg2 + arg3 + arg4 + arg5 + arg6;
}

TEST(test_cffi_call_with_six_params, test_cffi_call) {
    void* argv [] = { (void*)1, (void*)2 , (void*)3, (void*)4 ,(void*)5, (void*)6 };
    void* result = cffi_call( (void*)funWithSixParams, 6, argv);
    EXPECT_EQ((unsigned long long)result, 21);
}


int funWithStringParams (const char * str) {
    return strlen(str);
}

TEST(test_cffi_call_with_string_params, test_cffi_call) {
    void* argv[] = { (void*)"123456" };
    void* result = cffi_call( (void*)funWithStringParams, 1, argv);
    EXPECT_EQ((unsigned long long)result,6);
}


const char* funWithStringRvalue() {
    return  "123456";
}

TEST(test_cffi_call_with_string_rValue, test_cffi_call) {
    void* result = cffi_call( (void*)funWithStringRvalue, 0, nullptr);
    const char* str = reinterpret_cast< const char*>(result);
    EXPECT_STREQ(str, "123456");
}

struct test_struct{
    int property1;
    const char* property2;
};

int funWithPointVar (test_struct* params) {
    EXPECT_EQ(params->property1, 1);
    EXPECT_STREQ(params->property2, "123456");
    int len = strlen(params->property2);
    return len + params->property1;
}

TEST(test_cffi_call_with_point_var, test_cffi_call) {
    test_struct testStruct{1, "123456"};
    void* argv[] = { (void*)&testStruct};
    void* result = cffi_call( (void*)funWithPointVar, 1, argv);
    EXPECT_EQ((unsigned long long)result,7);
}

void funRef (int* params) {
    *params = 1;
}

TEST(test_cffi_call_with_ref_params, test_cffi_call) {
    int var = 0;
    void* argv[] = { (void*)&var};
    cffi_call( (void*)funRef, 1, argv);
    EXPECT_EQ(var, 1);
}


TEST(test_cffi_call_so_lib, test_cffi_call) {
    void* handle = dlopen("./bar.so",  RTLD_LAZY);
    EXPECT_TRUE(!!handle);
    void* add = dlsym( handle, "add" );
    void* argv [] = { (void*)1, (void*)2 };
    void* result = cffi_call( add, 2, argv);
    EXPECT_EQ((unsigned long long)result, 3);
    dlclose(handle);
}