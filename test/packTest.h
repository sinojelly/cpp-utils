#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>




FIXTURE(pack_test)
{
	struct A 
	{
		int a;
		char b;
		short c;
	};
#include <cpputils/pack_1>
	struct B
	{
		int a;
		char b;
		short c;
	};
#include <cpputils/unpack>
	struct C
	{
		int a;
		char b;
		short c;
	};

	SETUP()
	{
	}

	TEST(默认pack应该为4)
	{
		ASSERT_EQ(8, sizeof(A)); 
	}

	TEST(指定pack 1之后，结构体为7字节)
	{
		ASSERT_EQ(7, sizeof(B)); 
	}

	TEST(指定的pack 1取消后，结构体为8字节)
	{
		ASSERT_EQ(8, sizeof(C)); 
	}
};

