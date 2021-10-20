#include <stdio.h>
#include <stdbool.h>

/*
do~while(0)は2点の使い方がある
 1.複数行のマクロはdo while(0)で囲む
   ->PRE10-C. 複数の文からなるマクロは do-while ループで包む
 2.評価式が複数ある場合，途中でbreakで抜けることができる
   ->main文の中身で説明
*/

// 違反コード
// ->代入する場所によりうまく展開されない．(例えばif文で括弧で囲まない場合など)
#define SWAP(x, y) \
	tmp = x; \
	x = y; \
	y = tmp

// 適合コード
#define SWAP2(x, y) \
	do { \
		tmp = (x); \
		(x) = (y); \
		(y) = tmp; } \
	while (0)

bool func(bool i)
{
	return i;
}

int main(int argc, char *argv[])
{
	// do while
	do {
		if (!func(false))
			break;
		if (!func(false))
			break;
		if (!func(false))
			break;
		printf("debug1\n");
	} while(0);

	do {
		if (!func(true))
			break;
		if (!func(true))
			break;
		if (!func(true))
			break;
		printf("debug2\n");
	} while(0);

	// if文で同じことを行うためには，
	if((func(true)) && (func(true)) && (func(true)))
	{
		printf("debug3\n");
	}
	if(func(true))
	{
		if(func(true))
		{
			if(func(true))
			{
				printf("debug4\n");
			}
		}
	}
	
	return 0;
}
