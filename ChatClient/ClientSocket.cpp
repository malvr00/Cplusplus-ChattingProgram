// ClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "ChatClient.h"
#include "ClientSocket.h"


// ClientSocket

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}


// ClientSocket 멤버 함수


void ClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	AfxGetMainWnd()->PostMessage(UM_RECEIVE, 0, (LPARAM)this);		// PreTranslateMessage 사용 위해 Post로 메세지 보냄
	CSocket::OnReceive(nErrorCode);
}
