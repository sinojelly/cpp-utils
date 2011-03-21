

//风河的编译器在编译const局部数组时有未初始化的BUG

//比如：
int test_const(int i)
{
const char test[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};
return test[i];
}
/*编译结果如下：
:
addiu	$sp,$sp,-8
addu	$a0,$sp,$a0
lb	$v0,0($a0)
jr	$ra
addiu	$sp,$sp,8
nop
相当于数组没有初始化，返回结果为随机值。 */

