
// HANOI-TOWERDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "HANOI-TOWER.h"
#include "HANOI-TOWERDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHANOITOWERDlg 对话框



CHANOITOWERDlg::CHANOITOWERDlg(CWnd* pParent /*=nullptr*/) //构造函数
	: CDialogEx(IDD_HANOITOWER_DIALOG, pParent)
	, muiPlateNum(0)
	, mPrint(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	newdlg = new CNewdlg();
	newdlg->Create(IDD_DIALOG1, 0);

	pHanoi = NULL;
	muiPlateNum = 3;
	muiSpeed = 3;
}

void CHANOITOWERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_HT, ctrPicture);
	DDX_Text(pDX, IDC_EDIT_NUM, muiPlateNum);
	DDV_MinMaxUInt(pDX, muiPlateNum, 1, MAX_PLATE);
	DDX_Text(pDX, IDC_EDIT_SPEED, muiSpeed);
	DDV_MinMaxUInt(pDX, muiSpeed, 1, 9);
	DDX_Text(pDX, IDC_EDIT_PRINT, mPrint);
	DDX_Control(pDX, IDC_SPIN_NUM, ctrNum);
	DDX_Control(pDX, IDC_SPIN_SPEED, ctrSpeed);
	DDX_Control(pDX, IDC_BUTTON_START, BStart);
	DDX_Control(pDX, IDC_BUTTON1, BQuick);
	DDX_Control(pDX, IDC_BUTTON_IN, BIn);
	DDX_Control(pDX, IDC_BUTTON_OUT, BOut);
	DDX_Control(pDX, IDC_BUTTON3, BA);
	DDX_Control(pDX, IDC_BUTTON4, BB);
	DDX_Control(pDX, IDC_BUTTON5, BC);
	DDX_Control(pDX, IDC_BUTTON_RESET, BReset);
	DDX_Control(pDX, IDC_BUTTON2, BRules);
}

BEGIN_MESSAGE_MAP(CHANOITOWERDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHANOITOWERDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_START, &CHANOITOWERDlg::OnBnClickedButtonStart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NUM, &CHANOITOWERDlg::OnDeltaposSpinNum)
	ON_EN_CHANGE(IDC_EDIT_NUM, &CHANOITOWERDlg::OnEnChangeEditNum)
	ON_EN_CHANGE(IDC_EDIT_PRINT, &CHANOITOWERDlg::OnEnChangeEditPrint)
	ON_EN_CHANGE(IDC_EDIT_SPEED, &CHANOITOWERDlg::OnEnChangeEditSpeed)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SPEED, &CHANOITOWERDlg::OnDeltaposSpinSpeed)
	ON_BN_CLICKED(IDC_BUTTON1, &CHANOITOWERDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CHANOITOWERDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_IN, &CHANOITOWERDlg::OnBnClickedButtonIn)
	ON_BN_CLICKED(IDC_BUTTON_OUT, &CHANOITOWERDlg::OnBnClickedButtonOut)
	ON_BN_CLICKED(IDC_BUTTON3, &CHANOITOWERDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CHANOITOWERDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CHANOITOWERDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CHANOITOWERDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CHANOITOWERDlg 消息处理程序

BOOL CHANOITOWERDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ctrNum.SetRange(1, MAX_PLATE);
	ctrSpeed.SetRange(1, 9);
	pHanoi = new Hanoi((void *)this);

	model = 1;
	BOut.EnableWindow(0);
	BA.EnableWindow(0);
	BB.EnableWindow(0);
	BC.EnableWindow(0);
	BRules.EnableWindow(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHANOITOWERDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHANOITOWERDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		//初始画面
		CDC *pDC = ctrPicture.GetWindowDC();	
		CRect rect;

		GetClientRect(&rect); //获取窗口客户区的大小
		pDC->FillSolidRect(rect, RGB(255, 255, 255));

		pHanoi->DrawPeg(pDC);

		UpdateData(TRUE);
		if ((muiPlateNum != pHanoi->PlateNum) || (muiSpeed != pHanoi->Speed) || (flag == 1))
		{
			mPrint = _T("");
			flag = 0;
			pHanoi->initPlateStatus(muiPlateNum,muiSpeed);
		}
		UpdateData(FALSE);

		for (int i= 0; i < muiPlateNum; i++)
			pHanoi->DrawPlate(pDC, i);
		ctrPicture.ReleaseDC(pDC);
		egg = 0;
		Pre = -1;
		Step = 0;
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHANOITOWERDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHANOITOWERDlg::MPrint(CString Msg)
{
	UpdateData(TRUE);
	mPrint += Msg;
	UpdateData(FALSE);
	CEdit *p = (CEdit*)GetDlgItem(IDC_EDIT_PRINT); //定义一个指向编辑框的句柄的指针
	p->LineScroll(p->GetLineCount());//滚动条置底
	MSG   msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) //神奇的操作,保留画面
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

CDC * CHANOITOWERDlg::GetDC()
{
	return ctrPicture.GetWindowDC();
}

void CHANOITOWERDlg::Delay(DWORD x)
{
	DWORD timeBegin = timeGetTime();
	DWORD timeEnd = 0;
	do
	{
		timeEnd = timeGetTime();
	} while (timeEnd - timeBegin <= x);
}

void CHANOITOWERDlg::HighSpeed()
{
	pHanoi->Speed = 0;
}


void CHANOITOWERDlg::OnBnClickedOk()//没有
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CHANOITOWERDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//SetTimer(1, 1000, NULL); //计时器1
	BStart.EnableWindow(0);
	BReset.EnableWindow(0);
	BIn.EnableWindow(0);
	ctrNum.EnableWindow(0);
	ctrSpeed.EnableWindow(0);
	pHanoi->Begin();
	BReset.EnableWindow(1);
	ctrNum.EnableWindow(1);
	ctrSpeed.EnableWindow(1);
	//KillTimer(1);
}

void CHANOITOWERDlg::OnDeltaposSpinNum(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CHANOITOWERDlg::OnEnChangeEditNum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (model == 1)
	{
		BStart.EnableWindow(1);
		BIn.EnableWindow(1);
	}
	Invalidate();  //重绘
}


void CHANOITOWERDlg::OnEnChangeEditPrint()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CHANOITOWERDlg::OnEnChangeEditSpeed()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//pHanoi->Speed = muiSpeed;
	if (model == 1)
	{
		BStart.EnableWindow(1);
		BIn.EnableWindow(1);
	}
	Invalidate();
}


void CHANOITOWERDlg::OnDeltaposSpinSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CHANOITOWERDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HighSpeed();
}


void CHANOITOWERDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	flag = 1;
	Pre = -1;
	if (model == 1)
	{
		BStart.EnableWindow(1);
		BIn.EnableWindow(1);
	}
	noRules = 0;
	Invalidate();
	if (model == 2)
	{
		CString str;
		BRules.EnableWindow(1);
		str.Format(_T("您仍处于游玩模式！\r\n"));
		MessageBox(str);
		//MPrint(str);
	}
}


void CHANOITOWERDlg::OnBnClickedButtonIn()
{
	// TODO: 在此添加控件通知处理程序代码
	BStart.EnableWindow(0);
	BQuick.EnableWindow(0);
	ctrNum.EnableWindow(0);
	ctrSpeed.EnableWindow(0);
	BIn.EnableWindow(0);
	BOut.EnableWindow(1);
	BA.EnableWindow(1);
	BB.EnableWindow(1);
	BC.EnableWindow(1);
	Pre = -1;
	model = 2;
	noRules = 0;
	CString str;
	BRules.EnableWindow(1);
	str.Format(_T("您已进入游玩模式！\r\n"));
	MPrint(str);
	MessageBox(str);
}


void CHANOITOWERDlg::OnBnClickedButtonOut()
{
	// TODO: 在此添加控件通知处理程序代码
	BStart.EnableWindow(1);
	BQuick.EnableWindow(1);
	ctrNum.EnableWindow(1);
	ctrSpeed.EnableWindow(1);
	BIn.EnableWindow(1);
	BOut.EnableWindow(0);
	BA.EnableWindow(0);
	BB.EnableWindow(0);
	BC.EnableWindow(0);
	flag = 1;
	model = 1;
	BRules.EnableWindow(0);
	Invalidate();
	CString str;
	str.Format(_T("您已退出游玩模式！\r\n"));
	MessageBox(str);
}


void CHANOITOWERDlg::OnBnClickedButton3() //Button A
{
	// TODO: 在此添加控件通知处理程序代码
	int Top = pHanoi->findTop(0);
	if (Top == -1 && Pre == -1)
	{
		CString str;
		str.Format(_T("A上没有圆盘\r\n"));
		MPrint(str);
	}
	else {
		if (Pre == -1)
		{
			//CString str;
			//str.Format(_T("A上有圆盘\r\n"));
			//MPrint(str);
			pHanoi->DrawFrame(GetDC(), Top, 0);
			Pre = 0;
		}
		else
		{
			if (pHanoi->findTop(Pre) > Top && Top != -1 && (noRules == 0))
			{
				CString str;
				str.Format(_T("违反规则了哟\r\n"));
				MPrint(str);
				pHanoi->DrawFrame(GetDC(), pHanoi->findTop(Pre), 1);
				Pre = -1;
			}
			else
			{
				pHanoi->Move(Pre, 0);
				Step++;
				Pre = -1;
			}
		}
	}
}


void CHANOITOWERDlg::OnBnClickedButton4() //Button B
{
	// TODO: 在此添加控件通知处理程序代码
	int Top = pHanoi->findTop(1);
	if (Top == -1 && Pre == -1)
	{
		CString str;
		str.Format(_T("B上没有圆盘\r\n"));
		MPrint(str);
	}
	else {
		if (Pre == -1)
		{
			//CString str;
			//str.Format(_T("A上有圆盘\r\n"));
			//MPrint(str);
			pHanoi->DrawFrame(GetDC(), Top, 0);
			Pre = 1;
		}
		else
		{
			if (pHanoi->findTop(Pre) > Top && Top != -1 && (noRules == 0))
			{
				CString str;
				str.Format(_T("违反规则了哟\r\n"));
				MPrint(str);
				pHanoi->DrawFrame(GetDC(), pHanoi->findTop(Pre), 1);
				Pre = -1;
			}
			else
			{
				pHanoi->Move(Pre, 1); 
				Step++;
				Pre = -1;
			}
		}
	}
}


void CHANOITOWERDlg::OnBnClickedButton5() //Button C
{
	// TODO: 在此添加控件通知处理程序代码
	int Top = pHanoi->findTop(2);
	if (Top == -1 && Pre == -1)
	{
		CString str;
		str.Format(_T("C上没有圆盘\r\n"));
		MPrint(str);
	}
	else {
		if (Pre == -1)
		{
			//CString str;
			//str.Format(_T("A上有圆盘\r\n"));
			//MPrint(str);
			pHanoi->DrawFrame(GetDC(), Top, 0);
			Pre = 2;
		}
		else
		{
			if (pHanoi->findTop(Pre) > Top && Top != -1 && (noRules == 0))
			{
				CString str;
				str.Format(_T("违反规则了哟\r\n"));
				MPrint(str);
				pHanoi->DrawFrame(GetDC(), pHanoi->findTop(Pre), 1);
				Pre = -1;
			}
			else
			{
				pHanoi->Move(Pre, 2);
				Step++;
				Pre = -1;
				if (pHanoi->findTop(0) == -1 && pHanoi->findTop(1) == -1) {
					CString str;
					str.Format(_T("恭喜你完成了！\r\n"));
					MPrint(str);
					str.Format(_T("你完成%d重塔使用了%d步！\r\n"), muiPlateNum, Step);
					//MPrint(str);
					MessageBox(str);
					egg++;
					if (egg == 3)
					{
						str.Format(_T("恭喜你触发了彩蛋！\r\n"));
						//MPrint(str);
						MessageBox(str);
					}
					/*if (noRules == 1 || pHanoi->PlateNum == 10) //没有规则或有10个盘子，完成后立即复位
						              //使用"无视规则"将无法触发彩蛋
					{                 // Bug已解决
						flag = 1;
						Pre = -1;
						/*if (model == 1)
						{
							BStart.EnableWindow(1);
							BIn.EnableWindow(1);
						}*/
						/*noRules = 0;
						BRules.EnableWindow(1);
						Invalidate();
					}*/
				}
			}
		}
	}
}


void CHANOITOWERDlg::OnBnClickedButton2() //无视规则
{
	// TODO: 在此添加控件通知处理程序代码
	newdlg->ShowWindow(SW_SHOWNORMAL); //展示新对话框
	noRules = 1;
	BRules.EnableWindow(0);
}
