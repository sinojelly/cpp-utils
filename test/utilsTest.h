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

	TEST(from未超长时，strcpy会添加字符串结束符)
	{
		from[3] = 0;
		expected[3] = 0;

		strcpy(to, from);

	    ASSERT_SAME_DATA(expected, to, length);
	}

	TEST(from超长时，strncpy不会添加字符串结束符)
	{
		strncpy(to, from, 3);

		ASSERT_SAME_DATA(expected, to, length);
	}

	TEST(from超长时，s_strncpy也会添加字符串结束符)
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

	TEST(如果给的长度参数未预留1个字节，snprintf会导致写结束符时越界) // can not test because of uncaughtable exception
	{
		expected[3] = 0;

		//sprintf_s(to, 3, from);  // vc: exception
		//snprintf(to, 3, from);  

		//ASSERT_SAME_DATA(expected, to, length);
	}

	TEST(无须人为预留1个字节，s_snprintf都不会导致越界) // can not test because of uncaughtable exception
	{
		expected[2] = 0;

		//s_snprintf(to, 3, from);  // VC下只要to空间不够，都会抛出异常，无法测试

		//ASSERT_SAME_DATA(expected, to, length);
	}

	TEST(s_snprintf能处理带参数的情况)
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

	TEST(malloc返回空时，应该执行execute语句) 
	{
		/*MOCKER(malloc)
			.defaults()
			.will(invoke(malloc));

		MOCKER(malloc)
			.expects(once())
			.with(eq(0x7fffffff))
			.will(returnValue((void *)0));*/ // 没办法对malloc打桩，因为mock本身用了很多new，它也会调用malloc

		//s_malloc(char *, p, 0x7fffffff, return);

		//FAIL("should return before here.");
	}

    TEST(分配空间大小为0，应该执行execute语句) 
	{
		s_malloc(char *, p, 0, return);

		FAIL("should return before here.");
	}

	TEST(分配空间正常，则不应该执行execute语句) 
	{
		s_malloc(char *, p, 10, FAIL("should not come here."));
		s_free(p);
	}

	TEST(连续复位两次不会有异常) 
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

	TEST(new返回空时，应该执行execute语句) // 没法测试
	{
	}

	TEST(new基本类型对象，应该正常) 
	{
		s_new(p, char, FAIL("should not come here."));
		s_delete(p);
	}

	TEST(new数组类型对象，应该正常) 
	{
		s_new(p, char[10], FAIL("should not come here."));
		s_delete_array(p);
	}

	struct Dummy 
	{
		Dummy(int a){}
		Dummy(int a, int b){}
	};

	TEST(new构造带一个参数的类型的对象，应该正常) 
	{
		Dummy *p;
		s_new(p, Dummy(1), FAIL("should not come here."));
		s_delete(p);
	}


	TEST(new构造带两个参数的类型的对象，应该正常) 
	{
		Dummy *p;
		s_new(p, Dummy(1, 2), FAIL("should not come here."));
		s_delete(p);
	}
};

FIXTURE(s_devide_mode_test)
{
	int expect, result, a, b;

	SETUP()
	{
		a = 20;
		b = 2;
		expect = 10;
	}

	TEST(s_devide被除数非0，应该正确执行)
	{
		s_devide(result, a, b, FAIL("should not come here."));
		ASSERT_EQ(expect, result);
	}

	TEST(s_devide被除数为0，应该执行execute语句)
	{
		b = 0;

		s_devide(result, a, b, return);

		FAIL("should not come here.");
	}

	TEST(s_mode被除数非0，应该正确执行)
	{
		expect = 0;
		s_mode(result, a, b, FAIL("should not come here."));
		ASSERT_EQ(expect, result);
	}

	TEST(s_mode被除数为0，应该执行execute语句)
	{
		b = 0;

		s_mode(result, a, b, return);

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

	TEST(UNREF用于入参，应该能编译通过)
	{
		foo(10);
	}

	TEST(UNREF用于返回值，应该能编译通过)
	{
		UNREF(foo(10));
	}
};