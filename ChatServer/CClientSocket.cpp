// CClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "CClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pWnd->SendMessage(UM_RECEIVE, 0, (LPARAM)this);
	CSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pWnd->SendMessage(UM_CLOSE, 0, (LPARAM)this);
	CSocket::OnClose(nErrorCode);
}


void CClientSocket::SetMainWindow(CWnd* pWnd)
{
	// TODO: 여기에 구현 코드 추가.
	m_pWnd = pWnd;
}
