
// bgFaceManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bgFaceManager.h"
#include "bgFaceManagerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CbgFaceManagerDlg �Ի���



CbgFaceManagerDlg::CbgFaceManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CbgFaceManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbgFaceManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_cName);
	DDX_Control(pDX, IDC_COMBO_SEX, m_cSex);
	DDX_Control(pDX, IDC_COMBO_ID_TYPE, m_cIDType);
	DDX_Control(pDX, IDC_EDIT_ID_NUMBER, m_cIDNumber);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_cAddress);
	DDX_Control(pDX, IDC_EDIT_RESULT_NAME, m_cResultName);
	DDX_Control(pDX, IDC_EDIT_RESULT_SEX, m_cResultSex);
	DDX_Control(pDX, IDC_EDIT_RESULT_ID_TYPE, m_cResultIDType);
	DDX_Control(pDX, IDC_EDIT_RESULT_IDNUMBER, m_cResultID);
	DDX_Control(pDX, IDC_EDIT_RESULT_ADDRESS, m_cResultAddress);
	DDX_Control(pDX, IDC_LIST_FACES, m_cFaceList);
	DDX_Control(pDX, IDC_LIST_PERSONS, m_cPersonList);
	DDX_Control(pDX, IDC_EDIT_BIRTHDAY, m_cBirthday);
	DDX_Control(pDX, IDC_EDIT_COUNTRY, m_cCountry);
	DDX_Control(pDX, IDC_EDIT_NATION, m_cNation);
	DDX_Control(pDX, IDC_EDIT_CONTACTWAY, m_cContactWay);
}

BEGIN_MESSAGE_MAP(CbgFaceManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CbgFaceManagerDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_IMAGE_ADD, &CbgFaceManagerDlg::OnBnClickedBtnImageAdd)
	ON_BN_CLICKED(IDC_BTN_IMAGE_REGONGNITION, &CbgFaceManagerDlg::OnBnClickedBtnImageRegongnition)
	ON_BN_CLICKED(IDC_BTN_ADD_PERSON, &CbgFaceManagerDlg::OnBnClickedBtnAddPerson)
END_MESSAGE_MAP()


// CbgFaceManagerDlg ��Ϣ�������

BOOL CbgFaceManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_cSex.AddString(_T("��"));
	m_cSex.AddString(_T("Ů"));
	m_cSex.SetCurSel(0);

	m_cIDType.AddString(_T("���֤"));
	m_cIDType.AddString(_T("����֤"));
	m_cIDType.AddString(_T("ʿ��֤"));
	m_cIDType.AddString(_T("����"));
	m_cIDType.AddString(_T("��ʻ֤"));
	m_cIDType.AddString(_T("����֤"));
	m_cIDType.SetCurSel(0);

	m_cPersonList.SetExtendedStyle(m_cPersonList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cPersonList.InsertColumn(0, _T("��ԱID"), 0, 60);
	m_cPersonList.InsertColumn(1, _T("����"), 0, 100);
	m_cPersonList.InsertColumn(2, _T("�Ա�"), 0, 60);
	m_cPersonList.InsertColumn(3, _T("����"), 0, 80);
	m_cPersonList.InsertColumn(4, _T("����"), 0, 80);
	m_cPersonList.InsertColumn(5, _T("����"), 0, 80);
	m_cPersonList.InsertColumn(6, _T("֤������"), 0, 80);
	m_cPersonList.InsertColumn(7, _T("֤����"), 0, 120);
	m_cPersonList.InsertColumn(8, _T("סַ"), 0, 350);
	m_cPersonList.InsertColumn(9, _T("��ϵ��ʽ"), 0, 80);
	m_cPersonList.InsertColumn(10, _T("״̬"), 0, 60);

	m_cFaceList.SetExtendedStyle(m_cFaceList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cFaceList.InsertColumn(0, _T("����ID"), 0, 60);
	m_cFaceList.InsertColumn(1, _T("����ժҪ"), 0, 100);

	device_.Initialize(MEDIATYPE_CAMERA);
	face_.Initialize(DATABASE_TYPE_SQLite3, "E:\\opensource\\bgFaceAI\\Data\\bgPeopleInfo.db", 0, nullptr, nullptr, nullptr);

	USES_CONVERSION;
	face_.QueryPersonBegin();
	for (;;)
	{
		int count = m_cFaceList.GetItemCount();

		BG_PERSON_INFO person_info;
		face_.QueryNextPerson(person_info);

		CString person_no;
		person_no.Format(_T("%d"), person_info.person_number);
		m_cPersonList.InsertItem(count, person_no.GetString());

		m_cPersonList.SetItemText(count, 1, A2T(person_info.person_name.c_str()));
		m_cPersonList.SetItemText(count, 2, A2T(person_info.person_sex.c_str()));
		m_cPersonList.SetItemText(count, 3, A2T(person_info.person_birthday.c_str()));
		m_cPersonList.SetItemText(count, 4, A2T(person_info.person_country.c_str()));
		m_cPersonList.SetItemText(count, 5, A2T(person_info.person_nation.c_str()));
		m_cPersonList.SetItemText(count, 6, A2T(person_info.person_id_type.c_str()));
		m_cPersonList.SetItemText(count, 7, A2T(person_info.person_id_number.c_str()));
		m_cPersonList.SetItemText(count, 8, A2T(person_info.person_address.c_str()));
		m_cPersonList.SetItemText(count, 9, A2T(person_info.person_contact_way.c_str()));

		CString person_state;
		person_state.Format(_T("%d"), person_info.person_state);
		m_cPersonList.SetItemText(count, 10, person_state);
	}
	face_.QueryPersonEnd();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CbgFaceManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CbgFaceManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CbgFaceManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CbgFaceManagerDlg::OnBnClickedBtnStart()
{
	// ������ͷ����ʼץȡ����
	CWnd *pcwnd = GetDlgItem(IDC_STATIC_SCREEN);
	HWND hwnd = pcwnd->GetSafeHwnd();

	// 
	device_.Open(0, (void*)hwnd);
}


void CbgFaceManagerDlg::OnBnClickedBtnImageAdd()
{
	//// ��ȡ�����ؼ�������
	//CString name;
	//m_cName.GetWindowText(name);
	//if (name.IsEmpty())
	//	MessageBox(_T("��������Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);

	//int sex_index = m_cSex.GetCurSel();
	//CString sex;
	//if (sex_index == 0)
	//	sex = _T("��");
	//if (sex_index == 1)
	//	sex = _T("Ů");

	//int id_type_index = m_cIDType.GetCurSel();
	//CString id_type;
	//if (id_type_index == 0)
	//	id_type = _T("���֤");
	//if (id_type_index == 1)
	//	id_type = _T("����֤");
	//if (id_type_index == 2)
	//	id_type = _T("����");

	//CString id;
	//m_cIDNumber.GetWindowText(id);
	//if (id.IsEmpty())
	//	MessageBox(_T("֤���Ų���Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);

	//CString address;
	//m_cAddress.GetWindowText(address);
	//if (address.IsEmpty())
	//	MessageBox(_T("סַ����Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);

	CFileDialog dlg(TRUE, NULL, NULL, 6UL, _T("jpg File (*.jpg)|*.jpg||"), this);
	INT_PTR ret = dlg.DoModal();

	if (ret != IDOK)
		return;

	// ��ȡͼƬ�ļ�������ӿ�
	CString path = dlg.GetPathName();

	// ��ͼƬ����ȡ����
	USES_CONVERSION;
	FILE *file = nullptr;
	fopen_s(&file, T2A(path.GetBuffer(0)), "rb");
	if (file == nullptr)
		return;

	fseek(file, 0L, SEEK_END);
	int file_size = ftell(file);

	// �ص��ļ���ͷ
	fseek(file, 0L, SEEK_SET);

// 	BG_PERSON_INFO person_info;
// 	person_info.person_id_ = 0;
// 	person_info.person_name_ = T2A(name.GetBuffer(0));
// 	person_info.person_sex_ = T2A(sex.GetBuffer(0));
// 	person_info.person_id_type_ = T2A(id_type.GetBuffer(0));
// 	person_info.person_id_number_ = T2A(id.GetBuffer(0));
// 	person_info.person_address_ = T2A(address.GetBuffer(0));
// 	person_info.person_face_info_[0].face_id_ = 0;
// 	person_info.person_face_info_[0].face_data_ = new unsigned char[file_size];
// 	fread(person_info.person_face_info_[0].face_data_, file_size, 1, file);
// 	person_info.person_face_info_[0].face_data_len_ = file_size;
// 	person_info.face_count_ = 1;

	fclose(file);

	//face_.AddPersonWithFace(&person_info);
}


void CbgFaceManagerDlg::OnBnClickedBtnImageRegongnition()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CbgFaceManagerDlg::OnBnClickedBtnAddPerson()
{
	// ��ȡ�����ؼ�������
	CString name;
	m_cName.GetWindowText(name);
	if (name.IsEmpty())
	{
		MessageBox(_T("��������Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}

	int sex_index = m_cSex.GetCurSel();
	CString sex;
	if (sex_index == 0)
		sex = _T("��");
	if (sex_index == 1)
		sex = _T("Ů");

	int id_type_index = m_cIDType.GetCurSel();
	CString id_type;
	if (id_type_index == 0)
		id_type = _T("���֤");
	if (id_type_index == 1)
		id_type = _T("����֤");
	if (id_type_index == 2)
		id_type = _T("����");

	CString id;
	m_cIDNumber.GetWindowText(id);
	if (id.IsEmpty())
	{
		MessageBox(_T("֤���Ų���Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString address;
	m_cAddress.GetWindowText(address);
	if (address.IsEmpty())
	{
		MessageBox(_T("סַ����Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString birthday;
	m_cBirthday.GetWindowText(birthday);
	if (birthday.IsEmpty())
	{
		MessageBox(_T("���ղ���Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString country;
	m_cCountry.GetWindowText(country);
	if (country.IsEmpty())
	{
		MessageBox(_T("��������Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString nation;
	m_cNation.GetWindowText(nation);
	if (nation.IsEmpty())
	{
		MessageBox(_T("���岻��Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString contactway;
	m_cContactWay.GetWindowText(contactway);
	if (contactway.IsEmpty())
	{
		MessageBox(_T("��ϵ��ʽ����Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}

	BG_PERSON_INFO person_info;

	int errCode = face_.AddPerson(person_info);
	if (errCode == 0)
	{
		MessageBox(_T("�����Ա�ɹ�"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(_T("�����Աʧ��"), _T("����"), MB_OK | MB_ICONERROR);
	}
}
