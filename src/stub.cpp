

// just make a .lib.
void doNothing()
{}

// for lint test
#include <cpputils/utils.h>
#include <cpputils/log.h>
#include <cpputils/decls.h>

__BEGIN_C_DECLS

//lint -u
//lint -e753  Info 753: local struct 'B' (line 98, file stub.cpp) not referenced
//lint -e754  Info 754: local structure member 'B::a' (line 101, file stub.cpp) not referenced

void lint_s_strncpy()
{
    char buffer[5];
    s_strncpy(buffer, "123456", sizeof(buffer));
}

void lint_s_snprintf()
{
    char buffer[5];
    UNREF(s_snprintf(buffer, sizeof(buffer), "123456"));
}

//lint -e438  Warning 438: Last value assigned to variable 'p' not used
void lint_s_malloc()
{
    char *p;
	s_malloc(char *, p, 5, return);	
	s_free(p);
}

void lint_s_new()
{
    char *p;
    s_new(p, char[5], return);
    s_delete_array(p);
}

struct Dummy 
{
    Dummy(){}
	Dummy(int a, int b)
	{
	    UNREF(a);
		UNREF(b);
	}
};

void lint_s_new_dummy()
{
    Dummy *p;
    s_new(p, Dummy(1, 2), return);
    s_delete(p);
}

//lint -e550 Warning 550: Symbol 'r' (line 57) not accessed
void lint_s_devide()
{
    double r,b = 2;
    s_devide(r, 3.0, b, return);
}

void lint_s_devide_2()
{
    double r, b = 0;
    s_devide(r, 3.0, b, return);
}

void lint_s_mode()
{
    int r;
    s_mode(r, 3, 2, return);
}

void lint_s_mode_2()
{
    int r, b = 0;
    s_mode(r, 3, b, return);
}

void lint_array_size()
{
    char a[5] = {1, 2, 3, 4, 5};
	
	for (size_t i = 0; i < array_size(a); i++)
	{
	    if(a[i] == 3)
		{
		    return;
		}
	}
}

int foo(int a)
{
	UNREF(a);

	return 2;
}

void lint_unref()
{
    UNREF(foo(10));
}

#include <cpputils/pack_1>
	struct B
	{
		int a;
		char b;
		short c;
	};
#include <cpputils/unpack>

void lint_assert_s_true()
{
	ASSERT_S(true, return); //lint !e506 !e774  Warning 506: Constant value Boolean
}

void lint_assert_s_false()
{
	ASSERT_S(false, return); //lint !e506 !e774  Info 774: Boolean within 'if' always evaluates to False
}

__END_C_DECLS
