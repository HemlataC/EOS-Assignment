#include "msgque2.h"


int main()
{
	int mqid,s,ret;
	//p2 get the message queue

	mqid=msgget(mq_key,0);
	if(mqid<0){
		perror("msgget() failed..");
		_exit(1);
	}
	// p2 receive message from p1
	msg_t m2;
	printf("p2: waiting for p1 message...\n");
	ret=msgrcv(mqid,&m2,sizeof(msg_t)-sizeof(long),msg1_id,0);
  	if(ret<0)
		perror("msgrcv() failed..");

		else
		printf("process 2: received :%s\n",m2.data);
	
	// p2 send message to p1

	msg_t m5;
	m5.id = msg2_id;
	printf("Enter the message...");
	scanf("%s",m5.data);
	ret=msgsnd(mqid , &m5, sizeof(msg_t)-sizeof(long),0);
	if(ret<0)
		perror("msgsnd() failed...");
	else
	    printf("process 2: message sent %s\n",m5.data);


		



	return 0;
}
