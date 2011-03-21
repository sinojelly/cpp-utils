#ifndef __CPP_UTILS_LOG_H__
#define __CPP_UTILS_LOG_H__

#include <string.h>

#include <iostream> 

using namespace std;


// TODO: ������
inline const char *file_name(const char *file)
{
    for (int i = strlen(file) - 1; i >= 0; i--)
	{
	    if ((file[i] == '\\') || (file[i] == '/'))
		{
		    return (file + i + 1);
		}
	}
	
	return file;
}

//lint -emacro(1702, ASSERT_S)
//lint -emacro(534, ASSERT_S)
#if _MSC_VER > 1200
#define ASSERT_S(test, execute, ...)        \
{ \
    if (!(test)) \
    { /*TODO: __VA_ARGS__ ��������?*/\
        cerr << "(" << file_name(__FILE__) <<", "<<__LINE__<<")" << " Assert: [TEST] " << #test << ". " __VA_ARGS__ << endl; /*lint !e1702*/ \
        /*system("pause"); DevC++����仰��֤ͣ��*/\
        execute; \
    } \
}
#else
#define ASSERT_S(test, execute)        \
{ \
    if (!(test)) \
    { \
        cerr << "(" << file_name(__FILE__) <<", "<<__LINE__<<")" << " Assert: [TEST] " << #test << ". " << endl; /*lint !e1702*/\
        /*system("pause"); DevC++����仰��֤ͣ��*/\
        execute; \
    } \
}
#endif


#endif


