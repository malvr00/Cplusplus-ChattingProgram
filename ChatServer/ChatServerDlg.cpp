
// ChatServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
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


// CChatServerDlg 대화 상자



CChatServerDlg::CChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATSERVER_DIALOG, pParent)
	, m_strIpAddress(_T(""))
	, m_strName(_T("관리자"))
	, m_nPortNo(1234)
	, m_strUserList(_T(""))
	, m_strReceiveData(_T(""))
	, m_strSendData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FORCED_EXIT_BT, m_ctrlForcedBt);
	DDX_Control(pDX, IDC_IP_ADDRESS, m_ctrlIpAddress);
	DDX_Text(pDX, IDC_IP_ADDRESS, m_strIpAddress);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_SERVER_PORT, m_nPortNo);
	DDX_Control(pDX, IDC_SEND_BT, m_ctrlSendBt);
	DDX_Control(pDX, IDC_START_BT, m_ctrlStartBt);
	DDX_Control(pDX, IDC_STOP_BT, m_ctrlStopBt);
	DDX_Control(pDX, IDC_USER_LIST, m_ctrlUserList);
	DDX_LBString(pDX, IDC_USER_LIST, m_strUserList);
	DDX_Control(pDX, IDC_RECEIVE_DATA, m_ctrlReceiveData);
	DDX_Text(pDX, IDC_RECEIVE_DATA, m_strReceiveData);
	DDX_Control(pDX, IDC_SEND_DATA, m_ctrlSendData);
	DDX_Text(pDX, IDC_SEND_DATA, m_strSendData);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BT, &CChatServerDlg::OnClickedStartBt)
	ON_BN_CLICKED(IDC_STOP_BT, &CChatServerDlg::OnClickedStopBt)
	ON_BN_CLICKED(IDC_SEND_BT, &CChatServerDlg::OnClickedSendBt)
	ON_BN_CLICKED(IDC_FORCED_EXIT_BT, &CChatServerDlg::OnClickedForcedExitBt)
	ON_MESSAGE(UM_ACCEPT, &CChatServerDlg::OnAcceptMsg)	// 사용자 Message가 도착하면
	ON_MESSAGE(UM_RECEIVE, &CChatServerDlg::OnReceiveMsg)	// 처리할 함수 지정
	ON_MESSAGE(UM_CLOSE, &CChatServerDlg::OnCloseMsg)
END_MESSAGE_MAP()


// CChatServerDlg 메시지 처리기

BOOL CChatServerDlg::OnInitDialog()
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

	// 나의 IP Address 구하기
	m_strIpAddress = "localhost";
	UpdateData(FALSE);

	//Server Start버튼은 활성화
	m_ctrlStartBt.EnableWindow(TRUE);

	//Server Stop 버튼은 사용 불가능 상태로
	m_ctrlStopBt.EnableWindow(FALSE);

	//강제 퇴장 버튼은 사용 불가능 상태로
	m_ctrlForcedBt.EnableWindow(FALSE);

	// 전송 버튼은 사용 불가능 상태로
	m_ctrlSendBt.EnableWindow(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatServerDlg::OnPaint()
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
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatServerDlg::OnClickedStartBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_ctrlStartBt.EnableWindow(FALSE);
	m_ctrlStartBt.SetWindowText(_T("Server 실행중"));

	// Server Start시 문제 생기면
	if (!m_Server.ServerStart(this, m_nPortNo)) {
		MessageBox(_T("Server Socket 문제 발생"));
		m_ctrlStartBt.EnableWindow(TRUE);
		m_ctrlStartBt.SetWindowText(_T("Server Start"));
		return;
	}
	// 버튼들 활성화
	m_ctrlForcedBt.EnableWindow(TRUE);
	m_ctrlSendBt.EnableWindow(TRUE);
	m_ctrlStopBt.EnableWindow(TRUE);

	// Server 정상적으로 작동되면 화면에 출력.
	m_strReceiveData += "Server 실행 후 대기 중입니다.\r\n";
	UpdateData(FALSE);

	// 보내는 글로 Focus 이동
	m_ctrlSendData.SetFocus();
}


void CChatServerDlg::OnClickedStopBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (AfxMessageBox(_T("Server를 종료합니다."), MB_YESNO) == IDYES)
		return;

	CClientSocket* pNode;
	char szSendData[DATA_SIZE] = "QServer가 종료됩니다.";
	POSITION frontPos, pos = m_List.GetHeadPosition();

	// 접속하고 있는 모든 유저 종료 Message 보냄
	while (pos != NULL) {
		frontPos = pos;
		pNode = (CClientSocket *)m_List.GetNext(pos);		// pos위치 가져오고 pos를 다음위치로.
		if (pNode->Send(szSendData, DATA_SIZE) == -1)		// 종료 Message 보냄.
			MessageBox(_T("전송실패"));
		m_List.RemoveAt(frontPos);							// ObList에서 Client 제거
		pNode -> Close();									// Client 닫기
		delete pNode;										// Client 제거
	}

	// 접속자 목록 전부 초기화
	m_ctrlUserList.ResetContent();
	
	// Server 시작 버튼 빼고 전부 비활성화.
	m_ctrlForcedBt.EnableWindow(false);
	m_ctrlSendBt.EnableWindow(false);
	m_ctrlStopBt.EnableWindow(false);
	m_ctrlStartBt.EnableWindow(true);
	m_ctrlStartBt.SetWindowText(_T("Server Start"));

	m_Server.ShutDown();			// Server 종료
	m_Server.Close();			// Server 닫기
	m_strReceiveData += "Server를 종료합니다.\r\n";
	UpdateData(FALSE);
}


void CChatServerDlg::OnClickedSendBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szSendData[DATA_SIZE] = "";
	UpdateData(TRUE);
	if (!m_strSendData.IsEmpty()) { // 보내는 글이 있는 경우에만 처리
		strcpy_s(szSendData + 1, DATA_SIZE - 1, CT2A(m_strSendData));
		szSendData[0] = 'D';			// 관리자 메세지
		BroadCast((void*)szSendData);
		m_strReceiveData += szSendData + 1;
		m_strSendData = "";				// 보내는 글 지우기
		UpdateData(FALSE);
	}
	m_ctrlSendData.SetFocus();
}


void CChatServerDlg::OnClickedForcedExitBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	char szName[10] = "";
	char szSendData[DATA_SIZE] = "";

	CClientSocket* pNode;

	UpdateData(TRUE);
	strcpy_s(szName, 10, CT2A(m_strUserList));				// List에서 User 이름 가져옴
	sprintf_s(szSendData, DATA_SIZE, "F%s", szName);			// F: ForcedeExit ( 강제퇴장 )
	UserList(m_strUserList, 'D');						// User List 에서 삭제

	BroadCast((void*)szSendData);						// 전체 접속자에게 보냄
	m_strReceiveData += szSendData + 1;
	m_strReceiveData += "님이 강제 퇴장 되었습니다.\r\n";
	
	UpdateData(FALSE);
	m_ctrlReceiveData.LineScroll(m_ctrlReceiveData.GetLineCount(), 0);

	POSITION frontPos, pos = m_List.GetHeadPosition();
	while (pos != NULL) {							// Linked List 검색
		frontPos = pos;
		pNode = (CClientSocket*)m_List.GetNext(pos);			// pos 위치 가져오고 pos를 다음위치로
		if (pNode->m_strName == m_strUserList) {
			m_List.RemoveAt(frontPos);				// 이름이 같으면 ObList에서 제거
			pNode->Close();						// Socket 닫기
			delete pNode;						// Socket 제거
			break;
		}
	}
}


LRESULT CChatServerDlg::OnAcceptMsg(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	char szSendData[DATA_SIZE] = "", szReceiveData[DATA_SIZE] = "";
	CClientSocket* pSocket = new CClientSocket;

	if (!m_Server.Accept(*pSocket)) {
		MessageBox(_T("Client 연결 실패"));
		return -1;
	}
	// 접속한 User에게 인산말 전송
	sprintf_s(szSendData, DATA_SIZE, "ISejong Chatting Server입니다. \r\n");
	pSocket->Send((void*)szSendData, DATA_SIZE);

	// Receive Message 보낼 화면 번지보냄
	pSocket->SetMainWindow(this);

	// Link List에 추가
	m_List.AddTail(pSocket);

	return LRESULT();
}


LRESULT CChatServerDlg::OnReceiveMsg(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	char szSendData[DATA_SIZE] = "", szReceiveData[DATA_SIZE] = "";
	CString strName;
	char szName[20];

	CClientSocket* pSocket = (CClientSocket *)lParam;
	pSocket->Receive((void*)szReceiveData, DATA_SIZE);

	switch (szReceiveData[0]) {
	case 'N':
		// UserList 전송
		szSendData[0] = 'U';
		for (int i = 0; i < m_ctrlUserList.GetCount(); i++) {		// 접속한 유저 수 만큼 반복
			m_ctrlUserList.GetText(i, strName);						// ListBox에서 접속 User 닉네임 엏어옴
			strcpy_s(szName, 20, CT2A(strName));
			sprintf_s(szSendData, DATA_SIZE, "U%s", szName);		// User 닉네임 szSendData에 저장
			pSocket->Send((void*)szSendData, DATA_SIZE);			// User 닉네임 차례로 전송
		}
		pSocket->m_strName = szReceiveData + 1;						// 대화명 저장.

		// C = 접속 : 대화명만 보냄.
		sprintf_s(szSendData, DATA_SIZE, "C%s", szReceiveData + 1); 
		BroadCast((void*)szSendData);

		// User List에 추가
		UserList(pSocket->m_strName, 'A');							

		// 접속한 User Server 화면에 나타내기
		m_strReceiveData += szReceiveData + 1;
		m_strReceiveData += "님이 접속하셨습니다.\r\n";
		break;
	default:
		strcpy_s(szName, 20, CT2A(pSocket->m_strName));				// 소캣에서 이름 가져옴
		sprintf_s(szSendData, "D%s : %s \r\n", szName, szReceiveData + 1);
		BroadCast((void*)szSendData);								// 전체 접속자에게 전송
		m_strReceiveData += szSendData + 1;							// 접속한 User Server 화면에 나타내기
	}
	UpdateData(FALSE);
	m_ctrlReceiveData.LineScroll(m_ctrlReceiveData.GetLineCount(), 0);

	return LRESULT();
}


bool CChatServerDlg::BroadCast(void* pStr)
{
	// TODO: 여기에 구현 코드 추가.
	CClientSocket* pNode;

	// Linked List의 모든 접속자에게 전송
	for (POSITION pos = m_List.GetHeadPosition(); pos != NULL;) {
		pNode = (CClientSocket*)m_List.GetNext(pos);
		if (pNode->Send(pStr, DATA_SIZE) == -1)
			MessageBox(_T("전송실패"));
	}
	return false;
}


LRESULT CChatServerDlg::OnCloseMsg(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.
	char szName[20] = "";
	char szSendData[DATA_SIZE] = "";

	CClientSocket* pSocket = (CClientSocket*)lParam;		// 전달되어온 번지를 Pointer 변수에 대입
	strcpy_s(szName, 10, CT2A(pSocket->m_strName));			// Socket에서 이름 가져옴
	sprintf_s(szSendData, DATA_SIZE, "E%s", szName);		// E: Exit Data

	UserList(pSocket->m_strName, 'D');						// User List에서 제거

	BroadCast((void*)szSendData);							// 전체 접속자에게 전송
	m_strReceiveData += szSendData + 1;
	m_strReceiveData += "님이 퇴장하셨습니다.\r\n";
	UpdateData(FALSE);
	m_ctrlReceiveData.LineScroll(m_ctrlReceiveData.GetLineCount(), 0);

	CClientSocket* pNode;
	POSITION frontPos, pos = m_List.GetHeadPosition();
	while (pos != NULL) {
		frontPos = pos;
		pNode = (CClientSocket*)m_List.GetNext(pos);		// Linked List 검색
		if (pSocket == pNode) {								// Linked List와 전달되어온 번지가 같으면
			m_List.RemoveAt(frontPos);						// ObList에서 제거
			pSocket->Close();								// Socket 닫기
			delete pSocket;									// Socket 제거
			break;
		}
	}
	return LRESULT();
}


void CChatServerDlg::UserList(CString str, char nFlag)
{
	// TODO: 여기에 구현 코드 추가.
	int n, loc;
	if (nFlag == 'D') {
		n = m_ctrlUserList.FindString(-1, str);
		m_ctrlUserList.DeleteString(n);
	}
	else if (nFlag == 'A') {
		m_ctrlUserList.AddString(str);
	}
	loc = m_ctrlUserList.GetCount();
	m_ctrlUserList.SetAnchorIndex(loc - 1);
	m_ctrlUserList.SetCurSel(loc - 1);
}
