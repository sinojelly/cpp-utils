#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>

#include <cpputils/log.h>



FIXTURE(log_test)
{

	SETUP()
	{
	}

	TEST(����Ϊ�棬��Ӧ��ִ��execute���)
	{
		ASSERT_S(true, FAIL("should not come here.")); 
	}

	TEST(����Ϊ�٣�Ӧ��ִ��execute���)
	{
		ASSERT_S(false, return); 

		FAIL("should not come here.");
	}

	TEST(����Ϊ�٣�ASSERT_S�ܹ���ȷ��ӡ�ļ����к�)
	{
		ASSERT_S(false, ;);  // �۲���Ļ��
	}

};

