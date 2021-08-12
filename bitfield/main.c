#include "stdio.h"

// 共用体は構造体と異なり１つのメモリ領域を使用
// 共用体のサイズは最も大きいメンバのサイズ
// ワードの上位・下位バイトの入れ替え，いくつかのバイトからなるデータを１回でクリアするなどの用途がある
union unionVal {
	long int l;
	int i[2];
	short s[4];
	unsigned char x[8];
};

// ビットフィールドは，一つのワードで複数のフラグを管理に使用することができる
struct bitField {
	unsigned int a : 10;
	unsigned int b : 8;
	unsigned int c : 12;
	unsigned int d : 2;
};

union {
	struct bitField bf;
	unsigned int u;
} val2;

int main (int argc, char *argv[])
{
	printf("--- union start ---\n");
	union unionVal val;
	printf("size = %ld %ld %ld %ld\n", sizeof(long int), sizeof(int), sizeof(short), sizeof(unsigned char));
	val.l = 0;
	val.s[3] = 0xffff;
	printf("%lx\n", val.l);
	val.x[7] = 0x80;
	printf("%lx\n", val.l);
	val.x[0] = 0x01;
	printf("%lx\n", val.l);
	printf("--- union end ---\n");

	printf("--- bit field start ---\n");
	printf("size = %ld %ld\n", sizeof(struct bitField), sizeof(unsigned int));
	val2.u = 0;
	printf("%08x\n", val2.u);
	val2.bf.a = 0x3ff;
	printf("%08x\n", val2.u);
	val2.bf.b = 0xff;
	printf("%08x\n", val2.u);
	val2.bf.c = 0xfff;
	printf("%08x\n", val2.u);
	val2.bf.d = 0x3;
	printf("%08x\n", val2.u);
	printf("--- bit field end ---\n");

	return 0;
}
