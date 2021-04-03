#pragma once

// CServerSocket 명령 대상

#define UM_ACCEPT (WM_USER + 2)

class CServerSocket : public CSocket
{
private:
	CWnd* m_pWnd;		// MainWindow를 가르키기 위한 Pointer.
public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
	bool ServerStart(CWnd* pWnd, int nPortNo);
};


