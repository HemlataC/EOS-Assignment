#ifndef __MSGQUE_H
#define __MSGQUE_H


#include<stdio.h> 
#include<unistd.h>
#include<sys/wait.h>
#include<sys/msg.h>
	

#define mq_key 0x1235
#define msg1_id  103
#define msg2_id	 104

typedef struct msg{
		
		long id;
		 int num1;
		 int num2;
		 int add;
}msg_t;


#endif
