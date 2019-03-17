#include "utility.h"
int main(){
	struct sockaddr_in serverAddr;
	serverAddr.sin_family=PF_INET;
	serverAddr.sin_port=htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr=inet_addr(SERVER_IP);

	int listener=socket(PF_INET,SOCK_STREAM,0);
	if(listener<0){
		perror("socket error");
		exit(-1);	
	}
	printf("socket created\n");
	if(bind(listener,(struct sockaddr *)& serverAddr,sizeof(serverAddr))<0){
		perror("bind error");
		exit(-1);	
	}
	int ret=listen(listener,5);
	if(ret<0){
		perror("listen error");
		exit(-1);
	}
	printf("start to listen: %s\n",SERVER_IP);
	int epfd=epoll_create(EPOLL_SIZE);
	if(epfd<0){
		perror("epoll_create error");
		exit(-1);
	}
	printf("epoll created,epollfd=%d\n",epfd);
	static struct epoll_event events[EPOLL_SIZE];
	addfd(epfd,listener,true);
	while(1){
		int epoll_events_count=epoll_wait(epfd,events,EPOLL_SIZE,-1);
		if(epoll_events_count<0){
			perror("epoll error");
			break;
		}
		printf("epoll_events_count=%d\n",epoll_events_count);
		for(int i=0;i<epoll_events_count;i++){
			int sockfd=events[i].data.fd;
			if(sockfd==listener){
				struct sockaddr_in client_address;
				socklen_t client_addrLength=sizeof(struct sockaddr_in);
				int clientfd=accept(listener,(struct sockaddr *)&client_address,&client_addrLength);
				printf("client connection from:%s : %d (IP:port),clientfd=%d\n",inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port),clientfd);
				//cout<<"which chat room: "<<endl;
				//cin>>MchatId;
				char message[BUF_SIZE];	
				bzero(message,BUF_SIZE);	
				sprintf(message,"welcome %d\n which chat room? ",clientfd);
				int ret=send(clientfd,message,BUF_SIZE,0);	
				if(ret<0){
					perror("send error");
					exit(-1);
				}
				//recv(clientfd,buf,BUF_SIZE,0);
				char Mnums[1];
				/*ret=recv(clientfd,Mnums,sizeof(Mnums),0);
				if(ret<0){
					perror("choose error");
					exit(-1);
				}
				int MchatId=Mnums[0]-'0';*/
				int MchatId=0;
				cout<<"MchatId: "<<MchatId<<endl;
				MUsers * uu=new MUsers(clientfd);
				uu->chatId=MchatId;
				clients_list.push_back(*uu);
				printf("Add new clientfd=%d to epoll\n",clientfd);
				printf("Now there are %d clients in the chatroom\n",(int)clients_list.size());
				printf("welcome message\n");
				addfd(epfd,clientfd,true);
			}else{
			        int ret=sendBroadcastmessage(sockfd);
				if(ret<0){	
					perror("sendBroad error");
					exit(-1);
				}
			}
		}
	}
	close(listener);
	close(epfd);
	return 0;
}
