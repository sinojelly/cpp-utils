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

	TEST(Ĭ��packӦ��Ϊ4)
	{
		ASSERT_EQ(8, sizeof(A)); 
	}

	TEST(ָ��pack 1֮�󣬽ṹ��Ϊ7�ֽ�)
	{
		ASSERT_EQ(7, sizeof(B)); 
	}

	TEST(ָ����pack 1ȡ���󣬽ṹ��Ϊ8�ֽ�)
	{
		ASSERT_EQ(8, sizeof(C)); 
	}
};

