
// bgFaceManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "bgFaceManager.h"
#include "bgFaceManagerDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CbgFaceManagerDlg 对话框



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


// CbgFaceManagerDlg 消息处理程序

BOOL CbgFaceManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_cSex.AddString(_T("男"));
	m_cSex.AddString(_T("女"));
	m_cSex.SetCurSel(0);

	m_cIDType.AddString(_T("身份证"));
	m_cIDType.AddString(_T("军官证"));
	m_cIDType.AddString(_T("士兵证"));
	m_cIDType.AddString(_T("护照"));
	m_cIDType.AddString(_T("驾驶证"));
	m_cIDType.AddString(_T("工作证"));
	m_cIDType.SetCurSel(0);

	m_cPersonList.SetExtendedStyle(m_cPersonList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cPersonList.InsertColumn(0, _T("人员ID"), 0, 60);
	m_cPersonList.InsertColumn(1, _T("姓名"), 0, 100);
	m_cPersonList.InsertColumn(2, _T("性别"), 0, 60);
	m_cPersonList.InsertColumn(3, _T("生日"), 0, 80);
	m_cPersonList.InsertColumn(4, _T("国籍"), 0, 80);
	m_cPersonList.InsertColumn(5, _T("民族"), 0, 80);
	m_cPersonList.InsertColumn(6, _T("证件类型"), 0, 80);
	m_cPersonList.InsertColumn(7, _T("证件号"), 0, 120);
	m_cPersonList.InsertColumn(8, _T("住址"), 0, 350);
	m_cPersonList.InsertColumn(9, _T("联系方式"), 0, 80);
	m_cPersonList.InsertColumn(10, _T("状态"), 0, 60);

	m_cFaceList.SetExtendedStyle(m_cFaceList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cFaceList.InsertColumn(0, _T("人脸ID"), 0, 60);
	m_cFaceList.InsertColumn(1, _T("人脸摘要"), 0, 100);

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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CbgFaceManagerDlg::OnPaint()
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
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CbgFaceManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CbgFaceManagerDlg::OnBnClickedBtnStart()
{
	// 打开摄像头，开始抓取人脸
	CWnd *pcwnd = GetDlgItem(IDC_STATIC_SCREEN);
	HWND hwnd = pcwnd->GetSafeHwnd();

	// 
	device_.Open(0, (void*)hwnd);
}


void CbgFaceManagerDlg::OnBnClickedBtnImageAdd()
{
	//// 获取各个控件的数据
	//CString name;
	//m_cName.GetWindowText(name);
	//if (name.IsEmpty())
	//	MessageBox(_T("姓名不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);

	//int sex_index = m_cSex.GetCurSel();
	//CString sex;
	//if (sex_index == 0)
	//	sex = _T("男");
	//if (sex_index == 1)
	//	sex = _T("女");

	//int id_type_index = m_cIDType.GetCurSel();
	//CString id_type;
	//if (id_type_index == 0)
	//	id_type = _T("身份证");
	//if (id_type_index == 1)
	//	id_type = _T("军官证");
	//if (id_type_index == 2)
	//	id_type = _T("护照");

	//CString id;
	//m_cIDNumber.GetWindowText(id);
	//if (id.IsEmpty())
	//	MessageBox(_T("证件号不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);

	//CString address;
	//m_cAddress.GetWindowText(address);
	//if (address.IsEmpty())
	//	MessageBox(_T("住址不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);

	CFileDialog dlg(TRUE, NULL, NULL, 6UL, _T("jpg File (*.jpg)|*.jpg||"), this);
	INT_PTR ret = dlg.DoModal();

	if (ret != IDOK)
		return;

	// 提取图片文件，塞入接口
	CString path = dlg.GetPathName();

	// 打开图片，提取数据
	USES_CONVERSION;
	FILE *file = nullptr;
	fopen_s(&file, T2A(path.GetBuffer(0)), "rb");
	if (file == nullptr)
		return;

	fseek(file, 0L, SEEK_END);
	int file_size = ftell(file);

	// 回到文件开头
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
	// TODO:  在此添加控件通知处理程序代码
}


void CbgFaceManagerDlg::OnBnClickedBtnAddPerson()
{
	// 获取各个控件的数据
	CString name;
	m_cName.GetWindowText(name);
	if (name.IsEmpty())
	{
		MessageBox(_T("姓名不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	int sex_index = m_cSex.GetCurSel();
	CString sex;
	if (sex_index == 0)
		sex = _T("男");
	if (sex_index == 1)
		sex = _T("女");

	int id_type_index = m_cIDType.GetCurSel();
	CString id_type;
	if (id_type_index == 0)
		id_type = _T("身份证");
	if (id_type_index == 1)
		id_type = _T("军官证");
	if (id_type_index == 2)
		id_type = _T("护照");

	CString id;
	m_cIDNumber.GetWindowText(id);
	if (id.IsEmpty())
	{
		MessageBox(_T("证件号不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString address;
	m_cAddress.GetWindowText(address);
	if (address.IsEmpty())
	{
		MessageBox(_T("住址不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString birthday;
	m_cBirthday.GetWindowText(birthday);
	if (birthday.IsEmpty())
	{
		MessageBox(_T("生日不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString country;
	m_cCountry.GetWindowText(country);
	if (country.IsEmpty())
	{
		MessageBox(_T("国籍不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString nation;
	m_cNation.GetWindowText(nation);
	if (nation.IsEmpty())
	{
		MessageBox(_T("民族不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString contactway;
	m_cContactWay.GetWindowText(contactway);
	if (contactway.IsEmpty())
	{
		MessageBox(_T("联系方式不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}

	BG_PERSON_INFO person_info;

	int errCode = face_.AddPerson(person_info);
	if (errCode == 0)
	{
		MessageBox(_T("添加人员成功"), _T("提示"), MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(_T("添加人员失败"), _T("错误"), MB_OK | MB_ICONERROR);
	}
}
