#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>

#include <cpputils/utils.h>



FIXTURE(s_strncpy_test)
{
	const static int length = 5;
	char expected[length];
	char from[length];
	char to[length];

	SETUP()
	{
		expected[0] = '1';
		expected[1] = '2';
		expected[2] = '3';
		expected[3] = '4';
		expected[4] = 0;

		from[0] = '1';
		from[1] = '2';
		from[2] = '3';
		from[3] = '4';
		from[4] = 0;

		to[0] = '1';
		to[1] = '2';
		to[2] = '3';
		to[3] = '4';
		to[4] = 0;

	}

	TEST(fromδ����ʱ��strcpy������ַ���������)
	{
		from[3] = 0;
		expected[3] = 0;

		strcpy(to, from);

	    ASSERT_SAME_DATA(expected, to, length);
	}

	TEST(from����ʱ��strncpy��������ַ���������)
	{
		strncpy(to, from, 3);

		ASSERT_SAME_DATA(expected, to, length);
	}

	TEST(from����ʱ��s_strncpyҲ������ַ���������)
	{
		expected[2] = 0;

		s_strncpy(to, from, 3);

		ASSERT_SAME_DATA(expected, to, length);
	}
};



FIXTURE(s_snprintf_test)
{
	const static int length = 5;
	char expected[length];
	char from[length];
	char to[length];

	SETUP()
	{
		expected[0] = '1';
		expected[1] = '2';
		expected[2] = '3';
		expected[3] = '4';
		expected[4] = 0;

		from[0] = '1';
		from[1] = '2';
		from[2] = '3';
		from[3] = '4';
		from[4] = 0;

		to[0] = '1';
		to[1] = '2';
		to[2] = '3';
		to[3] = '4';
		to[4] = 0;

	}

	TEST(s_snprintf�ܴ�������������)
	{
		memset(to, 0, sizeof(to));
		s_snprintf(to, sizeof(to), "12%d%d",3, 4);
		ASSERT_SAME_DATA(expected, to, length);
	}

};


FIXTURE(s_malloc_free_test)
{
	char *p;

	SETUP()
	{
	}

	TEST(malloc���ؿ�ʱ��Ӧ��ִ��execute���) 
	{
		/*MOCKER(malloc)
			.defaults()
			.will(invoke(malloc));

		MOCKER(malloc)
			.expects(once())
			.with(eq(0x7fffffff))
			.will(returnValue((void *)0));*/ // û�취��malloc��׮����Ϊmock�������˺ܶ�new����Ҳ�����malloc

		//s_malloc(char *, p, 0x7fffffff, return);

		//FAIL("should return before here.");
	}

    TEST(����ռ��СΪ0��Ӧ��ִ��execute���) 
	{
		s_malloc(char *, p, 0, return);

		FAIL("should return before here.");
	}

	TEST(����ռ���������Ӧ��ִ��execute���) 
	{
		s_malloc(char *, p, 10, FAIL("should not come here."));
		s_free(p);
	}

	TEST(������λ���β������쳣) 
	{
		s_malloc(char *, p, 10, ;);
		s_free(p);
		s_free(p);
	}
};

FIXTURE(s_new_delete_test)
{
	char *p;

	SETUP()
	{
	}

	TEST(new���ؿ�ʱ��Ӧ��ִ��execute���) // û������
	{
	}

	TEST(new�������Ͷ���Ӧ������) 
	{
		s_new(p, char, FAIL("should not come here."));
		s_delete(p);
	}

	TEST(new�������Ͷ���Ӧ������) 
	{
		s_new(p, char[10], FAIL("should not come here."));
		s_delete_array(p);
	}

	struct Dummy 
	{
		Dummy(int a){}
		Dummy(int a, int b){}
	};

	TEST(new�����һ�����������͵Ķ���Ӧ������) 
	{
		Dummy *p;
		s_new(p, Dummy(1), FAIL("should not come here."));
		s_delete(p);
	}


	TEST(new������������������͵Ķ���Ӧ������) 
	{
		Dummy *p;
		s_new(p, Dummy(1, 2), FAIL("should not come here."));
		s_delete(p);
	}
};

FIXTURE(s_div_mod_test)
{
	int expect, result, a, b;

	SETUP()
	{
		a = 20;
		b = 2;
		expect = 10;
	}

	TEST(s_div��������0��Ӧ����ȷִ��)
	{
		s_div(result, a, b, FAIL("should not come here."));
		ASSERT_EQ(expect, result);
	}

	TEST(s_div������Ϊ0��Ӧ��ִ��execute���)
	{
		b = 0;

		s_div(result, a, b, return);

		FAIL("should not come here.");
	}

	TEST(s_mod��������0��Ӧ����ȷִ��)
	{
		expect = 0;
		s_mod(result, a, b, FAIL("should not come here."));
		ASSERT_EQ(expect, result);
	}

	TEST(s_mod������Ϊ0��Ӧ��ִ��execute���)
	{
		b = 0;

		s_mod(result, a, b, return);

		FAIL("should not come here.");
	}
};

FIXTURE(unref_test)
{
	SETUP()
	{
	}

	int foo(int a)
	{
		UNREF(a);

		return 2;
	}

	TEST(UNREF������Σ�Ӧ���ܱ���ͨ��)
	{
		foo(10);
	}

	TEST(UNREF���ڷ���ֵ��Ӧ���ܱ���ͨ��)
	{
		UNREF(foo(10));
	}
};

