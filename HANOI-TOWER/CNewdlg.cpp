// CNewdlg.cpp: 实现文件
//

#include "stdafx.h"
#include "HANOI-TOWER.h"
#include "CNewdlg.h"
#include "afxdialogex.h"


// CNewdlg 对话框

IMPLEMENT_DYNAMIC(CNewdlg, CDialogEx)

CNewdlg::CNewdlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CNewdlg::~CNewdlg()
{
}

void CNewdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewdlg, CDialogEx)
END_MESSAGE_MAP()


// CNewdlg 消息处理程序
