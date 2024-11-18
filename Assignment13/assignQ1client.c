#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

#define FIFO_IN "fifo_in"
#define FIFO_OUT "fifo_out"

int main()
{
 int fd_in,fd_out;
 int num1,num2,sum;
 
 mkfifo(FIFO_IN, 0600);
 mkfifo(FIFO_OUT, 0600);

 printf("Enter two no");
 scanf("%d%d",&num1,&num2);

 fd_in = open(FIFO_IN,O_WRONLY);
 if(fd_in == -1)
{
   perror("open () failed for writing");
   _exit(1);
}
  int number[]={num1,num2};
  write(fd_in,number,sizeof(number));
  fd_out = open(FIFO_OUT,O_RDONLY);
  if(fd_out == -1)
{
    perror("open () failed for reading");
   _exit(1);
}

 read(fd_out,&sum,sizeof(sum));

 printf("the sum of two num:%d %d\n",num1,num2,sum);

 close(fd_in);
 close(fd_out);

return 0;

}
