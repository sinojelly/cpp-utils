

//��ӵı������ڱ���const�ֲ�����ʱ��δ��ʼ����BUG

//���磺
int test_const(int i)
{
const char test[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};
return test[i];
}
/*���������£�
:
addiu	$sp,$sp,-8
addu	$a0,$sp,$a0
lb	$v0,0($a0)
jr	$ra
addiu	$sp,$sp,8
nop
�൱������û�г�ʼ�������ؽ��Ϊ���ֵ�� */

