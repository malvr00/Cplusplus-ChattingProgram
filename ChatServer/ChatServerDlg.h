
// ChatServerDlg.h: 헤더 파일
//

#pragma once

#include "afxcoll.h"			// CObList 용
#include "CClientSocket.h"		// 내가만든 Client Socket 
#include "CServerSocket.h"		// 내가만든 Server Socket

#define DATA_SIZE 100			// 전송 DATA크기

// CChatServerDlg 대화 상자
class CChatServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
		
	CServerSocket m_Server;						// Server Socket
	CObList m_List;							// 접속자 User 저장할 LinkdeList
public:
	// Dlg 변수연결
	CButton m_ctrlForcedBt;
	CEdit m_ctrlIpAddress;
	CString m_strIpAddress;
	CString m_strName;
	int m_nPortNo;
	CButton m_ctrlSendBt;
	CButton m_ctrlStartBt;
	CButton m_ctrlStopBt;
	CListBox m_ctrlUserList;
	CString m_strUserList;
	CEdit m_ctrlReceiveData;
	CString m_strReceiveData;
	CEdit m_ctrlSendData;
	CString m_strSendData;
	afx_msg void OnClickedStartBt();
	afx_msg void OnClickedStopBt();
	afx_msg void OnClickedSendBt();
	afx_msg void OnClickedForcedExitBt();

	afx_msg LRESULT OnAcceptMsg(WPARAM wParam, LPARAM lParam);		// Accept Message 처리 함수
	afx_msg LRESULT OnReceiveMsg(WPARAM wParam, LPARAM lParam);		// Receive Message 처리 함수
	afx_msg LRESULT OnCloseMsg(WPARAM wParam, LPARAM lParam);		// Close Message 처리 함수

	bool BroadCast(void* pStr);				// 접속한 모든 User에게 Message 전송
	void UserList(CString str, char nFlag);			// User ListBox 관리 함수
};
