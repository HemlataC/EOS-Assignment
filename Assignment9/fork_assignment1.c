#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
	int count=1,i,s,pid1,s1,pid2,s2,pid3,s3,pid4,s4,pid5,s5;
	pid1=fork();
	if(pid1==0)
	{
		for(i=1;i<=5;i++)
		{
		printf("child1=%d\n",i);
		sleep(1);
		}
		_exit(1);
	}

	pid2=fork();
	if(pid2==0)
	{
		for(i=1;i<5;i++)
		{
		printf("child2=%d\n",i);
		sleep(1);
		}
		_exit(2);
	}

	pid3=fork();
	if(pid3==0)
	{
		for(i=1;i<=5;i++)
		{
		printf("child3=%d\n",i);
		sleep(1);
		}
		_exit(3);
	}

	pid4=fork();
	if(pid4==0)
	{
		for(i=1;i<=5;i++)
		{
		printf("child4=%d\n",i);
		sleep(1);
		}
		_exit(4);
	}
	
	pid5=fork();
	if(pid5==0)
	{
		for(i=1;i<=5;i++)
		{
		printf("child5=%d\n",i);
		sleep(1);
		}
		_exit(5);
	}
   
	//parent process
	for(i=1;i<=5;i++)
	{
		printf("count=%d\n",count);
		count++;
		printf("parent=%d\n",i);
		sleep(1);
	}
//ek ek karke child ke zombie exit krega
//waitpid(pid1,&s1,0);
//waitpid(pid2,&s2,0);
//waitpid(pid3,&s3,0);
//etc
while(waitpid(-1,&s,0)>0) //ek sath sare child ke zombie bhi exit krta hai
printf("child exit status=%d\n",WEXITSTATUS(s));
return 0;
}



