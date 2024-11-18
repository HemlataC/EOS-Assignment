#ifndef __MSGQUE_H
#define __MSGQUE_H


#include<stdio.h> 
#include<unistd.h>
#include<sys/wait.h>
#include<sys/msg.h>


#define mq_key 0x1234
#define msg1_id   101
#define msg2_id	 102

typedef struct msg{
		
		long id;
		char data[32];
}msg_t;


#endif
