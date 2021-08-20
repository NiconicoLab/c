#ifndef __LIBRARY1_H__
#define __LIBRARY1_H__

// CとC++の両方のプログラムにインクルード可能なヘッダーファイルを作成するために
// __cplusplusの定義の有無またはその値に基づいた条件付きコンパイルを使用する

#if defined (__cplusplus)
extern "C" {
#endif

extern int library_func(int i);

#if defined (__cplusplus)
}
#endif

#endif /* __LIBRARY1_H__ */
