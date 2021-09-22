
// FileCopyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FileCopy.h"
#include "FileCopyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CFileCopyDlg 대화 상자



CFileCopyDlg::CFileCopyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILECOPY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileCopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK2, m_enc);
}

BEGIN_MESSAGE_MAP(CFileCopyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFileCopyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFileCopyDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFileCopyDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CFileCopyDlg 메시지 처리기

BOOL CFileCopyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFileCopyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFileCopyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFileCopyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFileCopyDlg::OnBnClickedButton1()
{
	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText(IDC_EDIT1, strPathName);
	}
}


void CFileCopyDlg::OnBnClickedButton2()
{
	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText(IDC_EDIT2, strPathName);
	}
}


void CFileCopyDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HANDLE OriginalFile = INVALID_HANDLE_VALUE;
	HANDLE OriginalFileMap = INVALID_HANDLE_VALUE;
	HANDLE DestFile = INVALID_HANDLE_VALUE;

	ULONGLONG Remaining_size = 0;
	ULONGLONG Ori_File_size = 0;

	DWORD Write_byte = 0;
	DWORD Current_byte = 0;

	LARGE_INTEGER File_size;
	LARGE_INTEGER File_now = { 0 };

	BYTE *pMapFile = NULL;

	SYSTEM_INFO si;
	GetSystemInfo(&si);

	CString ori_str,dst_str;
	GetDlgItemText(IDC_EDIT1, ori_str);
	GetDlgItemText(IDC_EDIT2, dst_str);


	OriginalFile = CreateFile(ori_str, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (OriginalFile == INVALID_HANDLE_VALUE) {
		MessageBox(_T("Could not open File! 1"), NULL, MB_ICONERROR);
	}

	DestFile = CreateFile(dst_str, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (DestFile == INVALID_HANDLE_VALUE) {
		MessageBox(_T("Could not open File! 2"), NULL, MB_ICONERROR);
	}

	OriginalFileMap = CreateFileMapping(OriginalFile, NULL, PAGE_READWRITE, 0, 0, NULL);
	if (OriginalFileMap == INVALID_HANDLE_VALUE) {
		MessageBox(_T("error 3"), NULL, MB_ICONERROR);
	}
	if (!GetFileSizeEx(OriginalFile, &File_size)) {
		MessageBox(_T("error 4"), NULL, MB_ICONERROR);
	}
	Remaining_size = File_size.QuadPart;
	Ori_File_size = File_size.QuadPart;
	BOOL enc_check = m_enc.GetCheck();
	int enc_value = 0;
	if (enc_check == 1) {
		enc_value = GetDlgItemInt(IDC_EDIT3);
	}
		
	while (Remaining_size > 0)
	{
		Current_byte = Remaining_size > si.dwAllocationGranularity ? si.dwAllocationGranularity : Remaining_size;
		pMapFile = (BYTE*)MapViewOfFile(OriginalFileMap, FILE_MAP_ALL_ACCESS, File_now.HighPart, File_now.LowPart, Current_byte);
		if (enc_check == 1) {
			WriteFile(DestFile, pMapFile, Current_byte ^ enc_value, &Write_byte, NULL);
		}
		else {
			WriteFile(DestFile, pMapFile, Current_byte, &Write_byte, NULL);
		}
		UnmapViewOfFile(pMapFile);
		File_now.QuadPart += Current_byte;
		Remaining_size -= Current_byte;
	}
	if (OriginalFileMap != INVALID_HANDLE_VALUE) {
		CloseHandle(OriginalFileMap);
	}
	if (DestFile != INVALID_HANDLE_VALUE) {
		CloseHandle(DestFile);
	}
	if (OriginalFile != INVALID_HANDLE_VALUE) {
		CloseHandle(OriginalFile);
	}
	MessageBox(_T("복사성공"), NULL, MB_ICONINFORMATION);
}
