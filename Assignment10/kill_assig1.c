#include<stdio.h>
#include <signal.h>
int main()
{
	int k,a,b;
	printf("enter the pid:\n");
	scanf("%d",&a);
	printf("enter the signal:\n");
	scanf("%d",&b);

	k=kill(a,b);
	if(k<0)
	perror("not kill\n");
	else
	printf("kill the process\n");
	return 0;
}	

