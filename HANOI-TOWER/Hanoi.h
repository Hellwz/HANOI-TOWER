#pragma once
#pragma comment(lib, "winmm.lib ")

#include <WinDef.h>
#include <MMSystem.h> 

#define PEGS_NUM	3
#define MAX_PLATE	10
#define NO_PLATE	-1

#define COLOR_YELLOW	RGB(255, 255, 0)
#define COLOR_ORANGE	RGB(255, 128, 0)
#define COLOR_RED		RGB(255, 0, 0)
#define COLOR_DEEPGREEN	RGB(0, 160, 0)
#define COLOR_MAGENTA	RGB(64, 0, 128)
#define COLOR_GREEN		RGB(0, 255, 0)
#define COLOR_BLUE		RGB(0, 0, 255)
#define COLOR_VIOLET	RGB(128, 0, 255)
#define COLOR_CYAN		RGB(0, 128, 255)
#define COLOR_BLACK		RGB(0, 0, 0)
#define COLOR_WHITE		RGB(255, 255, 255)
#define COLOR_GOLD      RGB(205,127,50)

static COLORREF ColorMenu[MAX_PLATE] = {
	COLOR_RED,
	COLOR_ORANGE,
	COLOR_YELLOW,
	COLOR_GREEN,
	COLOR_DEEPGREEN,
	COLOR_CYAN,
	COLOR_BLUE,
	COLOR_VIOLET,
	COLOR_MAGENTA,
	COLOR_GOLD
	
};

// 参考点
#define DRAWAREA_POR_X	40
#define DRAWAREA_POR_Y	20

#define PEG_BASE_WIDTH			150
#define PEG_BASE_HEIGHT			6
#define PEG_POLE_WIDTH			4
#define PEG_POLE_HEIGHT			260
// Peg 1
#define PEG_BASE1_POINT_TOPLEFT_X	DRAWAREA_POR_X
#define PEG_BASE1_POINT_TOPLEFT_Y	DRAWAREA_POR_Y + 280
#define PEG_POLE1_POINT_TOPLEFT_X	DRAWAREA_POR_X + (PEG_BASE_WIDTH / 2) - (PEG_POLE_WIDTH / 2)
#define PEG_POLE1_POINT_TOPLEFT_Y	PEG_BASE1_POINT_TOPLEFT_Y - PEG_POLE_HEIGHT
// Peg 2
#define PEG_BASE2_POINT_TOPLEFT_X	PEG_BASE1_POINT_TOPLEFT_X + 180
#define PEG_BASE2_POINT_TOPLEFT_Y	PEG_BASE1_POINT_TOPLEFT_Y
#define PEG_POLE2_POINT_TOPLEFT_X	PEG_POLE1_POINT_TOPLEFT_X + 180
#define PEG_POLE2_POINT_TOPLEFT_Y	PEG_POLE1_POINT_TOPLEFT_Y
// Peg 3
#define PEG_BASE3_POINT_TOPLEFT_X	PEG_BASE2_POINT_TOPLEFT_X + 180
#define PEG_BASE3_POINT_TOPLEFT_Y	PEG_BASE2_POINT_TOPLEFT_Y
#define PEG_POLE3_POINT_TOPLEFT_X	PEG_POLE2_POINT_TOPLEFT_X + 180
#define PEG_POLE3_POINT_TOPLEFT_Y	PEG_POLE2_POINT_TOPLEFT_Y

#define PLATE_HEIGHT	20

class Plate
{
public:
	COLORREF color;
	int width;
public:
	Plate(int id);
	int ID;
	int posPeg, posRow; //在哪根柱子，哪一行，越往上行数越大
	void Draw(CDC *pDC, bool b);	//画一个圆盘or去掉一个
	void Move(CDC *pDC, int to, int row);
};
class Hanoi
{
public:
	Hanoi(void *pDlg);
	~Hanoi();
private:
	Plate *pPlate[MAX_PLATE];
	int status[PEGS_NUM][MAX_PLATE+1];  // +1
	void *pDlalog;
	void Run(int from, int use, int to, int platenum);
public:
	void Move(int from, int to);
	int PlateNum;
	int Speed;
	void initPlateStatus(int num,int sp);
	void Begin();
	void DrawPeg(CDC *pDC);
	void DrawPlate(CDC *pDC, int x);
	void DrawFrame(CDC *pDC,int x,bool b); //画边框
	int findTop(int peg);
	void Delay(DWORD x);
};

