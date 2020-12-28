#include <stdio.h>

void func(void)
{
	printf("func\n");
}

int dummy_func(int a, int b)
{
	printf("dummy func %d %d\n", a, b);
	return (a + b);
}

int main(int argc, char *argv[])
{
	unsigned long address;
	address = (long)&func; // 関数のアドレスを取得
	printf("0x%ld\n", address);

	printf("\n!function test!\n");
	
	// 直アドレスで関数を呼ぶ(引数なし)
	typedef void (*functype)(void);
	functype func_call = (functype)address;
	func_call();

	// 上の例を1行で記述する場合
	((void (*)())func_call)();

	// 直アドレスで関数を呼ぶ(引数あり)
	address = (long)&dummy_func; // 関数のアドレスを取得
	printf("0x%ld\n", address);

	int ret;
	ret = ((int (*)(int a, int b))address)(1, 2);
	printf("ret=%d\n", ret);

	printf("\n!variable test!\n");
	
	// 直アドレスで変数を読み込み/書き込み
	unsigned int val = 0x12345678;
	address = (long)&val;
	printf("0x%ld %x\n", address, *(unsigned int *)address);

	*(unsigned int *)address = 0x87654321;
	printf("0x%ld %x\n", address, *(unsigned int *)address);
	
	return 0;
}
