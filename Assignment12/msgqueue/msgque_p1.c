#include "msgque2.h"

int main()
{

	int mqid,pid,s,ret;

	//create msg queue

	mqid=msgget(mq_key, IPC_CREAT | 0600);

	if(mqid<0)
	{
		perror("Msgget() failed..");
		_exit(1);
	}
	
	msg_t m1;
	m1.id = msg1_id;
	printf("Process 1 :Enter message:");
	gets(m1.data);
	ret=msgsnd(mqid,&m1, sizeof(msg_t)-sizeof(long),0);
	if(ret<0)
		perror("msgsnd() failed...");
	else
		printf("Process 1 : Message sent : %s\n",m1.data);
	
	printf("Process 1 : waiting for process 2 message..\n");

	msg_t m4;	
	ret= msgrcv( mqid,&m4,sizeof(msg_t)-sizeof(long),msg1_id,0);
	if(ret<0)
		 perror("msgrcv() failed");
	else	
		 printf("Process 1 : received: %s\n",m4.data);
	

    msgctl(mqid,IPC_RMID,NULL);
	return 0;
}
