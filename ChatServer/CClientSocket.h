#pragma once

// CClientSocket 명령 대상

#define UM_RECEIVE (WM_USER + 1)
#define UM_CLOSE  (WM_USER + 3)
class CClientSocket : public CSocket
{
private:
	CWnd* m_pWnd;
public:
	CClientSocket();
	virtual ~CClientSocket();

	CString m_strName;				// 대화 명을 저장할 변수.
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void SetMainWindow(CWnd* pWnd);
};


