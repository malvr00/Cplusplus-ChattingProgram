
// ChatClientDlg.h: 헤더 파일
//

#pragma once

#include "ClientSocket.h"
#define DATA_SIZE 100

// CChatClientDlg 대화 상자
class CChatClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATCLIENT_DIALOG };
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
public :
	ClientSocket m_Socket;					// Client User Socket
	bool m_bConnect;						// 사용자 접속 상태 표시

	// Control과 연결 변수들과 메세지 처리함수 추가
	CButton m_ctrlConnectBt;
	CButton m_ctrlDisConnectBt;
	CButton m_ctrlSendBt;
	CEdit m_ctrlIpAddress;
	CString m_strIpAddress;
	int m_nPortNo;
	CEdit m_ctrlReceiveData;
	CString m_strReceiveData;
	CEdit m_ctrlSendData;
	CString m_strSendData;
	CEdit m_ctrlName;
	CString m_strName;
	CListBox m_ctrlUserList;

	afx_msg LRESULT OnReceiveMsg(WPARAM wParam, LPARAM lParam);		// 사용자 Message 처리 함수 (Receive)
	afx_msg void OnClickedStopBt();

	afx_msg void OnClickedStartBt();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickedSendBt();
	int UserList(CString strUser, char nFlag);
};
