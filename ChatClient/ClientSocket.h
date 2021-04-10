#pragma once

// ClientSocket 명령 대상
#define UM_RECEIVE (WM_USER + 1)
class ClientSocket : public CSocket
{
public:
	ClientSocket();
	virtual ~ClientSocket();

	virtual void OnReceive(int nErrorCode);
};


