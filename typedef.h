// typedef.h
/*----------------------------------------------------------------------+
|		typedef											 				|
|       Author:     DuanYanSong  2011/05/30								|
|            Ver 1.0													|
|            Ver 1.0													|
|       Copyright (c)2011, WHU RSGIS DPGrid Group						|
|	         All rights reserved.                                       |
|		ysduan@whu.edu.cn; ysduan@sohu.com              				|
+----------------------------------------------------------------------*/
#ifndef TYPEDEF_H_DUANYANSONG_2011_06_30_19_32_2435769809876543
#define TYPEDEF_H_DUANYANSONG_2011_06_30_19_32_2435769809876543

#ifdef WIN32
#include <windows.h>
#else

typedef 	unsigned int	HANDLE		;
typedef 	int				BOOL		;
typedef 	const char*     LPCSTR		;
typedef		char*			LPSTR		;
typedef 	unsigned char	BYTE		;
typedef 	unsigned int	RGBQUAD		;
typedef 	unsigned short	WORD		;
typedef 	unsigned int	DWORD		;
typedef 	unsigned int	UINT		;
typedef 	unsigned long	LONGLONG	;

#endif

#define MB					1024*1024
#define TRUE				1
#define FALSE				0
#define NULL				0



#endif

