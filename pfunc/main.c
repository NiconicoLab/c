#include <stdio.h>

int add(int a, int b)
{
	return (a+b);
}

int minus(int a, int b)
{
	return (a-b);
}

typedef int(* FP_FUNC)(int, int);

int main(void)
{
	int (*pfunc)(int, int);
	printf("%d\n", add(1, 10));

	pfunc = add;
	printf("%d\n", pfunc(1, 10));

	printf("%d\n", minus(6, 3));

	pfunc = minus;
	printf("%d\n", minus(6, 3));

	printf("--- typedef test ---\n");
    FP_FUNC pfunc2 = NULL;
	pfunc2 = add;
	printf("%d\n", pfunc2(1, 10));

	return 0;
}

#if 0

関数ポインタは，「関数」を参照している「ポインタ」
// 関数ポインタの変数定義
long (* pfunc)(int , char);

  pfunc     : 変数につけるラベル名((自由に付与)
  *         : データの型，関数ポインタは「ポインタ型」のため「＊」を指定
  long      : 関数ポインタが参照する関数が定義する「戻り値のデータ型」
  (int char): 関数ポインタが参照する関数が定義する「引数のデータ型」

①typedef前
void test_func(long(* pfunc)(int, short), int num)
{
    return;
}
    // 関数ポインタ
    long (*pfunc)(int, short) = NULL;

    // 関数ポインタを引数で関数に渡す
    test_func(pfunc, 100);

②
// 関数ポインタ型を別名でtypedefする
typedef long(* FP_FUNC)(int, short);
void test_func(FP_FUNC pfunc, int num)
{
    return;
}
    // 関数ポインタ
    FP_FUNC pfunc = NULL;
    test_func(pfunc, 100);

#endif
