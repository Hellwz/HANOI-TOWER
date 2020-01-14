#include "stdafx.h"
#include "Hanoi.h"
#include "HANOI-TOWERDlg.h"


Hanoi::Hanoi(void * pDlg)
{
	pDlalog = (CHANOITOWERDlg *)pDlg;
	PlateNum = 0;
	Speed = 300;
	status[0][MAX_PLATE] = NO_PLATE;
	status[1][MAX_PLATE] = NO_PLATE;
	status[2][MAX_PLATE] = NO_PLATE;
	for (int i = 0; i < MAX_PLATE; i++)
		pPlate[i] = new Plate(i);
}

Hanoi::~Hanoi()
{
	for (int i = 0; i < MAX_PLATE; i++)
		delete pPlate[i];
}

Plate::Plate(int id)
{
	ID = id;
	width = 130 - 10 * (9 - ID);
	color = ColorMenu[id];
}

void Plate::Draw(CDC * pDC, bool b)
{

	CRect rect; //画图用的矩形类
	CPoint topLeft, bottomRight;

	topLeft.x = (PEG_BASE1_POINT_TOPLEFT_X + 180 * posPeg) + (PEG_BASE_WIDTH - width) / 2;
	topLeft.y = PEG_BASE1_POINT_TOPLEFT_Y - PLATE_HEIGHT * (posRow + 1);
	bottomRight.x = topLeft.x + width;
	bottomRight.y = topLeft.y + PLATE_HEIGHT;
	rect.SetRect(topLeft, bottomRight);

	if (b==1)
	{
		pDC->FillSolidRect(rect, color);
	}
	else //清空并补充黑色
	{
		pDC->FillSolidRect(rect, COLOR_WHITE);

		topLeft.x = PEG_POLE1_POINT_TOPLEFT_X + (180 * posPeg);
		bottomRight.x = topLeft.x + PEG_POLE_WIDTH;

		rect.SetRect(topLeft, bottomRight);
		pDC->FillSolidRect(rect, COLOR_BLACK);
	}
}

void Hanoi::DrawFrame(CDC * pDC,int id,bool b)
{
	CRect rect; 
	CPoint topLeft, bottomRight;

	topLeft.x = (PEG_BASE1_POINT_TOPLEFT_X + 180 * pPlate[id]->posPeg) + (PEG_BASE_WIDTH - pPlate[id]->width) / 2;
	topLeft.y = PEG_BASE1_POINT_TOPLEFT_Y - PLATE_HEIGHT * (pPlate[id]->posRow + 1);
	bottomRight.x = topLeft.x + pPlate[id]->width;
	bottomRight.y = topLeft.y + PLATE_HEIGHT;
	rect.SetRect(topLeft, bottomRight);

	pDC->FillSolidRect(rect, COLOR_BLACK);
	if (b == 0)
	{
	    topLeft.x= topLeft.x+3;
		topLeft.y= topLeft.y+3;
		bottomRight.x= bottomRight.x-3;
		bottomRight.y= bottomRight.y-3;
		rect.SetRect(topLeft, bottomRight);
	}
	pDC->FillSolidRect(rect, pPlate[id]->color);
}

void Plate::Move(CDC * pDC, int to, int row)
{
	Draw(pDC, 0);
	posPeg = to;
	posRow = row;
	Draw(pDC, 1);
}

void Hanoi::Run(int from, int use, int to, int platenum)
{
	if (platenum == 0) return;
	Run(from, to, use, platenum - 1);
	Delay(Speed);
	Move(from, to);
	Run(use, from, to, platenum - 1);
	return;
}

void Hanoi::Move(int from, int to)
{
	int id;
	int from_row = 0,to_row = 0;
	CString msgPrint;
	CHANOITOWERDlg *p = (CHANOITOWERDlg *)pDlalog;
	CDC *pDC = p->GetDC();

	while (status[from][from_row] != NO_PLATE) //找到最上面的并移动
		from_row++;
	id = status[from][from_row - 1];
	status[from][from_row - 1] = NO_PLATE;

	while (status[to][to_row] != NO_PLATE)
		to_row++;
	status[to][to_row] = id;

	pPlate[id]->Move(pDC, to, to_row);
	msgPrint.Format(_T("(%c, %d) --> (%c, %d)\r\n"), from+'A', from_row-1+1, to+'A', to_row+1);
	p->MPrint(msgPrint);
}

void Hanoi::initPlateStatus(int num,int sp) //初始化状态
{
	PlateNum = num;
	Speed = sp*100;
	for (int i = 0; i < PEGS_NUM; i++)
		for (int j = 0;  j < MAX_PLATE; j++)
			status[i][j] = NO_PLATE;
	for (int i = 0; i < MAX_PLATE; i++) 
	{
		pPlate[i]->posPeg = 0;		
		if (i < num)
		{
			pPlate[i]->posRow = num - i - 1; //第0个在最上面
			status[0][pPlate[i]->posRow] = i;
		}
		else pPlate[i]->posRow = 0;		
	}
}

void Hanoi::Begin()
{
	Run(0, 1, 2, PlateNum);
	return;
}

void Hanoi::DrawPeg(CDC * pDC)
{
	CRect rect;
	COLORREF color;
	CPoint topLeft, bottomRight;

	// 显示第一个底座
	topLeft.x = PEG_BASE1_POINT_TOPLEFT_X;
	topLeft.y = PEG_BASE1_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_BASE1_POINT_TOPLEFT_X + PEG_BASE_WIDTH;
	bottomRight.y = PEG_BASE1_POINT_TOPLEFT_Y + PEG_BASE_HEIGHT;
	color = COLOR_BLACK;
    rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);
	// 显示第一根杆
	topLeft.x = PEG_POLE1_POINT_TOPLEFT_X;
	topLeft.y = PEG_POLE1_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_POLE1_POINT_TOPLEFT_X + PEG_POLE_WIDTH;
	bottomRight.y = PEG_POLE1_POINT_TOPLEFT_Y + PEG_POLE_HEIGHT;
    rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);
	// Base 2
	topLeft.x = PEG_BASE2_POINT_TOPLEFT_X;
	topLeft.y = PEG_BASE2_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_BASE2_POINT_TOPLEFT_X + PEG_BASE_WIDTH;
	bottomRight.y = PEG_BASE2_POINT_TOPLEFT_Y + PEG_BASE_HEIGHT;
	color = COLOR_BLACK;
    rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);
	// Pole 2
	topLeft.x = PEG_POLE2_POINT_TOPLEFT_X;
	topLeft.y = PEG_POLE2_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_POLE2_POINT_TOPLEFT_X + PEG_POLE_WIDTH;
	bottomRight.y = PEG_POLE2_POINT_TOPLEFT_Y + PEG_POLE_HEIGHT;
    rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);
	// Base 3
	topLeft.x = PEG_BASE3_POINT_TOPLEFT_X;
	topLeft.y = PEG_BASE3_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_BASE3_POINT_TOPLEFT_X + PEG_BASE_WIDTH;
	bottomRight.y = PEG_BASE3_POINT_TOPLEFT_Y + PEG_BASE_HEIGHT;
	color = COLOR_BLACK;
    rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);
	// Pole 3
	topLeft.x = PEG_POLE3_POINT_TOPLEFT_X;
	topLeft.y = PEG_POLE3_POINT_TOPLEFT_Y;
	bottomRight.x = PEG_POLE3_POINT_TOPLEFT_X + PEG_POLE_WIDTH;
	bottomRight.y = PEG_POLE3_POINT_TOPLEFT_Y + PEG_POLE_HEIGHT;
    rect.SetRect(topLeft, bottomRight);
	pDC->FillSolidRect(rect, color);
}

void Hanoi::DrawPlate(CDC * pDC, int x)
{
	pPlate[x]->Draw(pDC, 1);
}


int Hanoi::findTop(int peg) //最上面存在的盘的id
{
	int ret = 0;
	while (status[peg][ret+1] != NO_PLATE)
		ret++;
	return status[peg][ret];
}

void Hanoi::Delay(DWORD x)
{
	DWORD timeBegin = timeGetTime();
	DWORD timeEnd = 0;
	do
	{
		timeEnd = timeGetTime();
	} while (timeEnd - timeBegin <= x);
}

