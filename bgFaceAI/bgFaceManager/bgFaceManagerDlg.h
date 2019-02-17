
// bgFaceManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "../bgDataAcquisition/bgDevice.h"
#include "../bgFaceAI/bgFaceAI.h"


// CbgFaceManagerDlg �Ի���
class CbgFaceManagerDlg : public CDialogEx
{
// ����
public:
	CbgFaceManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BGFACEMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cName;
	CComboBox m_cSex;
	CComboBox m_cIDType;
	CEdit m_cIDNumber;
	CEdit m_cAddress;
	CEdit m_cResultName;
	CEdit m_cResultSex;
	CEdit m_cResultIDType;
	CEdit m_cResultID;
	CEdit m_cResultAddress;
	CEdit m_cBirthday;
	CEdit m_cCountry;
	CEdit m_cNation;
	CEdit m_cContactWay;

public:
	CListCtrl m_cFaceList;
	CListCtrl m_cPersonList;

public:
	bgMedia device_;
	bgFaceAI face_;

public:
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnImageAdd();
	afx_msg void OnBnClickedBtnImageRegongnition();
	
	afx_msg void OnBnClickedBtnAddPerson();
};
