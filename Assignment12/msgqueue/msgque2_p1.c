#include "msgque2.h"

int main()
{
	int mqid,oids,ret;

	//create a message queue
	mqid=msgget(mq_key, IPC_CREAT | 0600);
	if(mqid < 0)
	{
		perror("msgget() failed");
		_exit(1);
	}

	//p1 send message to p2 - msgsnd()
	msgg_t m1;
	m1.id = MSG1_ID;
	printf("p1 : Enter a Message :");
	gets(m1,data);
	ret = msgsnd(mqid,&m1,sizeof(msg_t)-sizeof(long),0);
	if(ret<0)
		perror("p1:msgsnd() failed");
	else
		printf("p1: message sent %s\n",m1.data);
	
	printf("")



 return 0;
}
