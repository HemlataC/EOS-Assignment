#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>


struct in_num{
          int start;
          int end;
};
struct output{
      int add1;
};

void* add(void *param)
{
  int i;
  struct in_num *ip = (struct input *)param;
  struct output *op = (struct output *)malloc(sizeof(struct output));
  
  op->add1 = 0;

  for(i=ip->start;i<=ip->end;i++)
  {
  op->add1 = op->add1 + i;
  }
  

//printf("add:\n %d",op->add1);

  return op;
}


int main()
{
  struct in_num in = { .start=1 , .end=10};
  struct output *op;
  pthread_t th;
 
  int ret = pthread_create(&th,NULL,add,&in);

  if(ret<0)
 {
       printf("Thread is failed..");
 }

 pthread_join(th,(void **)&op);
 printf("Addition is :%d\n",op->add1);
 free(op);
 return 0;
} 
