#include<stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int pid1,s1,pid2,s2,pid3,s3,i;
	pid1=fork();
	if(pid1==0)
	{
		pid2=fork();
		if(pid2==0)
		{
			pid3=fork();
			if(pid3==0)
			{
				for(i=1;i<=3;i++)
				{
					printf("child3=%d\n",i);
					sleep(1);
				}	
					_exit(0);
				
			}
			else
			{
				for(i=1;i<=3;i++)
				{
					printf("child2=%d\n",i);
					sleep(1);
				}
				waitpid(pid3,&s3,0);
				_exit(0);

			}
		} 
		else
		{
			for(i=1;i<=3;i++)
			{
				printf("child1=%d\n",i);
				sleep(1);
			}
			waitpid(pid2,&s2,0);
			_exit(0);

		}   
	}
	else
	{
		for(i=1;i<=3;i++)
		{
			printf("parent=%d\n",i);
			sleep(1);
		}	
		waitpid(pid1,&s1,0);
        _exit(0);
	}	
	return 0;
}


