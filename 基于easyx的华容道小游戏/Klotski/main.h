#include <conio.h>
#include "EasyXPng.h"
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

#define WIN_WIDTH  600
#define WIN_HEIGHT  800//窗口的宽高
#define BLOCK 150	   //一个方块的宽度

IMAGE imgs[10+1][2];//存放图片素材，第一行是原图，第二行是被单击后的高亮图

enum {EMPTY , MA_CHAO , CAO_CAO , ZHAO_YUN , HUANG_ZHONG , GUAN_YU , ZHANG_FEI ,
	  SOLDIER_1 , SOLDIER_2 , SOLDIER_3 , SOLDIER_4};
//可在此处修改布局
int Board[5][4]={
	MA_CHAO,	  CAO_CAO,		CAO_CAO,	ZHAO_YUN,
	MA_CHAO,	  CAO_CAO,		CAO_CAO,	ZHAO_YUN,
	HUANG_ZHONG,  GUAN_YU,	    GUAN_YU,	ZHANG_FEI,
	HUANG_ZHONG,  SOLDIER_2,	SOLDIER_3 ,	ZHANG_FEI,
	SOLDIER_1,    EMPTY ,		EMPTY ,		SOLDIER_4
		  	};
/*□□□□
  □□□□
  □□□□
  □□□□
  □□□□
*/
struct direction//横向和竖向每一步的偏移量
{
	int row_off;
	int col_off;
}GO_UP={-1,0},GO_DOWN={1,0},GO_LEFT={0,-1},GO_RIGHT={0,1};

struct position {
	int row;
	int col;
};
