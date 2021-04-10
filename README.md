# This is Chatting program using socket
 
> V/C++

## Socket Chatting Server Program.
 유저관리. & 기능. & Message 구분.

###  Chatting Program Server [[코드참조]](https://github.com/malvr00/Cplusplus-ChattingProgram/tree/main/ChatServer)
* Chtting Server에서 유저관리 방법으로 Linked List 복습할 겸 사용.
* Server의 기능으론 현재 User 강제퇴장 기능. 접속한 User 목록표시 ( 향후 추가 할 계획 Maybe)
* User가 접속하면 접속한 User정보들 보내고 User 접속자 목록에 표시.
* Message 구분은 코드의 OnReceiveMsg [[부분참조]](https://github.com/malvr00/Cplusplus-ChattingProgram/blob/main/ChatServer/ChatServerDlg.cpp)
>  'N' : 최초접속( 대화명 전송 ), 'C' : 유저접속 ( ~가 입장하셨습니다. ), 'A' : 리스트 접속자 업데이트, 'D' : 리스트 접속자 삭제

   <img src="https://user-images.githubusercontent.com/77275513/114269239-cb0ad000-9a40-11eb-85b5-6377f6e73279.PNG" width="450px" height="300px" title="100px" alt="RubberDuck"></img><br/>


### Chatting Program Client [[코드참조]](https://github.com/malvr00/Cplusplus-ChattingProgram/tree/main/ChatClient)
* Chatting Server에 접속 및 접속한 User List 표시.
* Message 구분은 코드 OnReceiveMsg [[부분참조]](https://github.com/malvr00/Cplusplus-ChattingProgram/blob/main/ChatClient/ChatClientDlg.cpp)
> 'I' : 서버접속시 인삿말, 'U' : 접속한 유저 리스트업데이트, 'C' : 유저접속 ( ~가 입장하셨습니다.), 'E' : 유저퇴장( ~가 퇴장하셨습니다.),
> 'F' : 강제퇴장, 'Q' : Server 종료, 'D' : 일반 채팅

   <img src="https://user-images.githubusercontent.com/77275513/114269452-212c4300-9a42-11eb-9ca1-0dfebaa240f4.PNG" width="600px" height="300px" title="100px" alt="RubberDuck"></img><br/>
