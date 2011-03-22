#ifndef __CPP_UTILS_H__
#define __CPP_UTILS_H__
#include <stdio.h> 
#include <stdlib.h> 
  
// safe strncpy, padding a nul at the end of to string, even from is longger than count. Note: strncpy_s was used in MSVC.
#define s_strncpy(to, from, count) {strncpy(to, from, count - 1)[count - 1] = '\0';}

// safe snprintf, just apply the same ui on VC and gnu.
#ifdef _MSC_VER
#define s_snprintf(to, size, from, ...)  sprintf_s(to, size /*- 1*/, from, ##__VA_ARGS__)   // VC����to��size����С��from��ӡ�������ַ�������+1, ���Բ��ܼ�
#else
#define s_snprintf(to, size, from, ...)  snprintf(to, size /*- 1*/, from, ##__VA_ARGS__)  // gnu already reserved one byte for '\0'.
#endif

//lint -emacro(506, s_malloc, s_devide, s_mode)  Warning 506: Constant value Boolean
//lint -emacro(774, s_malloc, s_new, s_devide, s_mode)  Info 774: Boolean within 'if' always evaluates to False
// ��ȫ��malloc���������pΪ�ջ�����γ���<=0����ִ��execute(һ���return)
#define s_malloc(type, p, size, execute) \
{ \
    if ((size) <= 0) { execute; } \
    p = (type)malloc(size); \
    if (p == NULL)  { execute; } \
}

// ��ȫ��free�������ͷź��ָ�븳ֵΪNULL�������ظ��ͷŻ���ʹ�õ�Ұָ�롣��free(0)������ģ�
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
// C++ ����ģ��Ԫ���ʵ�ֱ�������ֵ�����Ͱ�ȫ(�������ų���ָ��������±�����)������Ԫ�ظ�����.
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


