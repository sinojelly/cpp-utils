#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>

#include <cpputils/log.h>



FIXTURE(log_test)
{

	SETUP()
	{
	}

	TEST(条件为真，不应该执行execute语句)
	{
		ASSERT_S(true, FAIL("should not come here.")); 
	}

	TEST(条件为假，应该执行execute语句)
	{
		ASSERT_S(false, return); 

		FAIL("should not come here.");
	}

	TEST(条件为假，ASSERT_S能够正确打印文件名行号)
	{
		ASSERT_S(false, ;);  // 观察屏幕吧
	}

};

