
// HANOI-TOWERDlg.h: 头文件

#pragma once
#include "afxwin.h"
#include "Hanoi.h"
#include "afxcmn.h"
#include "CNewdlg.h"

// CHANOITOWERDlg 对话框
class CHANOITOWERDlg : public CDialogEx
{
// 构造
public:
	CHANOITOWERDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HANOITOWER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int muiPlateNum; //输入的盘数
	int muiSpeed;
	Hanoi *pHanoi;
	CStatic ctrPicture; //静态控件类
	CDC * GetDC(); //设备环境对象类（上下文
	void MPrint(CString msg);
	CString mPrint;//message
	CSpinButtonCtrl ctrNum,ctrSpeed;
	CNewdlg* newdlg;

	void Delay(DWORD x);
	void HighSpeed();
	bool flag; // 复位
	int Pre; // 源or目标,从哪一根移动
	int model; //模式 1、演示 2、游玩
	int egg; // 彩蛋 
	int Step; // 用了多少步
	bool noRules;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnDeltaposSpinNum(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditNum();
	afx_msg void OnEnChangeEditPrint();
	afx_msg void OnEnChangeEditSpeed();
	afx_msg void OnDeltaposSpinSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonIn();
	CButton BStart;
	CButton BQuick;
	afx_msg void OnBnClickedButtonOut();
	CButton BIn;
	CButton BOut;
	CButton BA;
	CButton BB;
	CButton BC;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CButton BReset;
	afx_msg void OnBnClickedButton2();
	CButton BRules;
};
