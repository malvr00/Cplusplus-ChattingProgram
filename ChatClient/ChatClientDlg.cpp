
// ChatClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
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


// CChatClientDlg 대화 상자



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATCLIENT_DIALOG, pParent)
	, m_strIpAddress(_T("localhost"))
	, m_nPortNo(1234)
	, m_strReceiveData(_T(""))
	, m_strSendData(_T(""))
	, m_strName(_T(""))
	, m_bConnect(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_BT, m_ctrlConnectBt);
	DDX_Control(pDX, IDC_STOP_BT, m_ctrlDisConnectBt);
	DDX_Control(pDX, IDC_SEND_BT, m_ctrlSendBt);
	DDX_Control(pDX, IDC_IP_ADDRESS, m_ctrlIpAddress);
	DDX_Text(pDX, IDC_IP_ADDRESS, m_strIpAddress);
	DDX_Text(pDX, IDC_SERVER_PORT, m_nPortNo);
	DDX_Control(pDX, IDC_RECEIVE_DATA, m_ctrlReceiveData);
	DDX_Text(pDX, IDC_RECEIVE_DATA, m_strReceiveData);
	DDX_Control(pDX, IDC_SEND_DATA, m_ctrlSendData);
	DDX_Text(pDX, IDC_SEND_DATA, m_strSendData);
	DDX_Control(pDX, IDC_NAME, m_ctrlName);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Control(pDX, IDC_USER_LIST, m_ctrlUserList);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_RECEIVE, &CChatClientDlg::OnReceiveMsg)			// 사용자 Message 처리
	ON_BN_CLICKED(IDC_STOP_BT, &CChatClientDlg::OnClickedStopBt)
	ON_BN_CLICKED(IDC_START_BT, &CChatClientDlg::OnClickedStartBt)
	ON_BN_CLICKED(IDC_SEND_BT, &CChatClientDlg::OnClickedSendBt)
END_MESSAGE_MAP()


// CChatClientDlg 메시지 처리기

BOOL CChatClientDlg::OnInitDialog()
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

	// 초기에 자료 전송, 연결해제 버튼은 사용 불가능 상태로 설정
	m_ctrlSendBt.EnableWindow(false);
	m_ctrlDisConnectBt.EnableWindow(false);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatClientDlg::OnPaint()
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
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CChatClientDlg::OnReceiveMsg(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	char szReceiveData[DATA_SIZE] = "";
	CString strName;
	m_Socket.Receive((void*)szReceiveData, DATA_SIZE);
	strName = szReceiveData + 1;
	switch (szReceiveData[0]) {
	case 'I':		// 접속 후 관리자를 List에 추가
		m_strReceiveData += "Server에 접속됨\r\n";
		m_ctrlUserList.AddString(_T("관리자"));
		break;
	case 'U':		// 접속 후 List에 자기 자신 추가
		UserList(strName, 'A');
		break;
	case 'C':		// User가 접속한 경우
		strcat_s(szReceiveData, DATA_SIZE, "님이 접속 하셨습니다.\r\n");
		UserList(strName, 'A');
		break;
	case 'E':		// 다른 User가 나간 경우
		sprintf_s(szReceiveData, "E%s님이 퇴장하셨습니다.\r\n", szReceiveData + 1);
		UserList(strName, 'D');
		break;
	case 'F':
		sprintf_s(szReceiveData, "F%s님이 강제퇴장 되었습니다.\r\n", szReceiveData + 1);
		UserList(strName, 'D');
		break;
	case 'Q':				// Server 종료 메세지가 온 경우
		m_ctrlUserList.ResetContent();
		break;
	}
	m_strReceiveData += szReceiveData + 1;
	UpdateData(FALSE);
	m_ctrlReceiveData.LineScroll(m_ctrlReceiveData.GetLineCount(), 0);		// 받는 글에 최신들이 보이도록 설정
	return LRESULT();
}


void CChatClientDlg::OnClickedStopBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (AfxMessageBox(_T("Server와의 연결을 끓을까요?"), MB_YESNO) == IDYES) {
		m_ctrlConnectBt.EnableWindow(TRUE);
		m_ctrlConnectBt.SetWindowText(_T("Server와 연결"));
		m_ctrlSendBt.EnableWindow(FALSE);					// 자료전송 버튼은 사용불가로
		m_ctrlDisConnectBt.EnableWindow(FALSE);
		m_ctrlIpAddress.SetFocus();
		m_Socket.Close();
		m_bConnect = FALSE;									// 접속 종료 표시
		m_ctrlUserList.ResetContent();
		m_strReceiveData = "";
		UpdateData(FALSE);
	}
}


void CChatClientDlg::OnClickedStartBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_strName.IsEmpty()) {
		MessageBox(_T("대화명을 입력하세요."));
		return;
	}
	m_Socket.Create();
	if (!m_Socket.Connect(m_strIpAddress, m_nPortNo)) {
		MessageBox(_T("Server에 접속하지 못했습니다."));
		m_Socket.Close();
		return;
	}
	char szSendData[DATA_SIZE] = "";
	char szName[20];
	strcpy_s(szName, 20, CT2A(m_strName));
	sprintf_s(szSendData, "N%s", szName);					// N : 대화명
	m_Socket.Send(szSendData, DATA_SIZE);					// 대화명 전송

	m_ctrlConnectBt.EnableWindow(FALSE);					// 연결버튼 사용 불능으로
	m_ctrlConnectBt.SetWindowText(_T("Server 연결중"));		// 버튼의 문자 변경
	m_ctrlSendBt.EnableWindow(TRUE);						// 자료전송버튼 활성화
	m_ctrlDisConnectBt.EnableWindow(TRUE);					// 연결 해제 버튼 활성화
	m_ctrlSendData.SetFocus();								// 보내는 글로 Focus 이동
	m_bConnect = true;										// 현재 접속 중임을 알림
}


BOOL CChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)		// esc키가 눌렸을 때 종료하지 말 것
		return TRUE;	
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)		// Enter 키를 누른 경우
	{
		if (m_bConnect)				// 접속 중일 때는 자료 전송
			OnClickedSendBt();
		else                        // 접속하기 전일 때는 Server 접속
			OnClickedStartBt();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CChatClientDlg::OnClickedSendBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szSendData[DATA_SIZE] = "";
	UpdateData(TRUE);
	if (!m_strSendData.IsEmpty())		// 보내는 글이 있는 경우만 처리
	{
		strcpy_s(szSendData + 1, DATA_SIZE - 1, CT2A(m_strSendData));
		szSendData[0] = 'D';										// D : 일반 Data (채팅)
		if (m_Socket.Send((void*)szSendData, DATA_SIZE) == -1)		// 전송 실패 -1 성공은 보낸 Byte 수
			MessageBox(_T("전송실패"));
		m_strSendData = "";
		UpdateData(FALSE);
	}
	m_ctrlSendData.SetFocus();
}


int CChatClientDlg::UserList(CString strUser, char nFlag)
{
	// TODO: 여기에 구현 코드 추가.
	int n, loc;
	if (nFlag == 'D') {
		n = m_ctrlUserList.FindString(-1, strUser);	// 접속자 ListControl에서 해당 이름의 위치 찾기
		m_ctrlUserList.DeleteString(n);				// 접속자 ListControl에서 해다 이름 제거
	}
	else if (nFlag == 'A') {
		m_ctrlUserList.AddString(strUser);			// List에 추가
	}
	loc = m_ctrlUserList.GetCount();				// List Control에 입력된 개수 구하기
	m_ctrlUserList.SetAnchorIndex(loc - 1);			// List Control아래 부분 나타내기
	m_ctrlUserList.SetCurSel(loc - 1);				// List Control 선택
	return 0;
}
