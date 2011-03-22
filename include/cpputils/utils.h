#ifndef __CPP_UTILS_H__
#define __CPP_UTILS_H__
#include <stdio.h> 
#include <stdlib.h> 
  
// safe strncpy, padding a nul at the end of to string, even from is longger than count. Note: strncpy_s was used in MSVC.
#define s_strncpy(to, from, count) {strncpy(to, from, count - 1)[count - 1] = '\0';}

// safe snprintf, just apply the same ui on VC and gnu.
#ifdef _MSC_VER
#define s_snprintf(to, size, from, ...)  sprintf_s(to, size /*- 1*/, from, ##__VA_ARGS__)   // VC计算to的size不得小于from打印参数后字符串长度+1, 所以不能减
#else
#define s_snprintf(to, size, from, ...)  snprintf(to, size /*- 1*/, from, ##__VA_ARGS__)  // gnu already reserved one byte for '\0'.
#endif

//lint -emacro(506, s_malloc, s_devide, s_mode)  Warning 506: Constant value Boolean
//lint -emacro(774, s_malloc, s_new, s_devide, s_mode)  Info 774: Boolean within 'if' always evaluates to False
// 安全的malloc函数：如果p为空或者入参长度<=0，则执行execute(一般会return)
#define s_malloc(type, p, size, execute) \
{ \
    if ((size) <= 0) { execute; } \
    p = (type)malloc(size); \
    if (p == NULL)  { execute; } \
}

// 安全的free函数：释放后把指针赋值为NULL，避免重复释放或者使用到野指针。（free(0)是允许的）
#define s_free(p) \
{ \
    free(p); \
    p = NULL; \
}

// safe new  
#define s_new(p, type, execute) \
{ \
    p = new type; \
    if (p == NULL) { execute; } \
}

// safe delete , see also: s_delete_array(p)
#define s_delete(p) \
{ \
    delete p; \
    p = NULL; \
}

#define s_delete_array(p) \
{ \
    delete [] p; \
    p = NULL; \
}

#define s_devide(result, a, b, execute) \
{ \
    if ((b) == 0) { execute; } \
    result = a / b; \
}

#define s_mode(result, a, b, execute) \
{ \
    if ((b) == 0) { execute; } \
    result = a % b; \
}
 

#ifndef __cplusplus
#define array_size(a)      (sizeof(a)/sizeof(a[0]))
#else
// C++ 下用模板元编程实现编译期求值且类型安全(编译期排除了指针和重载下标的情况)的数组元素个数宏.
template<int N>
struct array_size_struct
{
    char c[N];
};
template<class T, int N>
array_size_struct<N> static_array_size_fn(T(&)[N]);
#define array_size(a)   sizeof(static_array_size_fn(a).c)
#endif
 
#ifdef _MSC_VER
#define UNREF(x)   (void)##x    
#else
// gnu: no '##' after '(' or ')'.
#define UNREF(x)   (void)x    
#endif

#define XSTR(x)    #x 
#define STR(x)     XSTR(x)
 


#endif


