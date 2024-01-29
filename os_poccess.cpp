#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct PCB_type{
	int pid; //进程ID 
	int priority; //优先级
	int size; //大小 
	int state; //标志进程状态，0为不在内存，1为在内存，2为挂起 
	char info[10]; 
};

struct PCB_type memory[50];

int pid;  
int num=0; //进程数量 
int suspend=0;//挂起数量 
int flag=0;//标记 
int i,j;

/*********************创建新进程*************************/
void create()
{
	if(num>=50)  printf("\n内存已满，请先换出或结束进程\n");
	else{
		for(i=0;i<50;i++)
		{
			if(memory[i].state==0) 
			{
				break;
			}
		}
		
		printf("\n请输入新建进程的pid值\n");
		scanf("%d",&memory[i].pid);
		
		for(j=0;j<i;j++)//判断之前是否存在相同的进程 
		{
			if(memory[j].pid==memory[i].pid)
			{
				printf("\n该进程已存在于内存中");//不需要再创建一次,ID值重复会让下面的操作无法识别具体是哪个进程 
				return;
			}				
		}
		
		printf("\n请输入新进程的优先级\n");
		scanf("%d",&memory[i].priority);
		
		printf("\n请输入新进程的大小\n");
		scanf("%d",&memory[i].size);
		
		printf("\n请输入新进程的内容\n");
		scanf("%s",&memory[i].info);
			
		memory[i].state=1; /*将进程状态设为1，表示在内存中*/
		num++; /*内存中进程数目加一*/
	}
}

/********************查看当前运行进程**************************/

void run()
{
	printf("运行进程信息如下:\n");
	for(i=0;i<50;i++)
	{
		if(memory[i].state==1)
		{
			printf("pid=%d\n",memory[i].pid);
			printf("priority=%d\n",memory[i].priority);
			printf("size=%d\n",memory[i].size);
			printf("state=%d\n",memory[i].state);
			printf("info=%s\n",memory[i].info);
			printf("\n");
			flag=1;//作为一个判断的标记 
		}
	 } 
	 
	 if(!flag)//如果没有一个标记为1及说明 没有进程在运行 
	 {
	 	printf("\n当前没有运行进程！\n");
	 }
}

/********************换出进程***************************/
void  swap_out()
{
	if(!num)
	{
		printf("当前没有运行进程！\n");
		return;
	 } 
	 
	 printf("\n请输入换出进程的ID值");
	 scanf("%d",&pid);
	 
	 for(i=0;i<50;i++)
	 {
	 	if(pid==memory[i].pid) 
	 	{
	 		if(memory[i].state==1)
	 		{
	 			memory[i].state=2;//把进程的状态设置为2 
	 			suspend++; //挂起数量加1 
	 			printf("\n已经成功换出进程\n");
			 }
			else if(memory[i].state==2) 
			 {
			 	printf("\n要换出的进程已经被挂起\n");
			  } 
			else
			 {
			 	printf("\n进程不存在，不可换出\n");
			 }
			 break;
		 }
	 }
}

/********************杀死进程***************************/
void kill() 
{
	if(!num)
	{
		printf("当前没有运行进程！\n");
		return;
	}
	
	printf("\n请输入要杀死进程的ID值");
	scanf("%d",&pid);
	
	for(i=0;i<50;i++)
	{
		if(pid==memory[i].pid)
		{
			if(memory[i].state==1)
			{
				memory[i].state=0;
				num--;
				printf("\n已经成功杀死进程\n");
			}
			else if(memory[i].state==2) 
			{
				printf("\n要杀死的进程已经被挂起\n");
			}
			else 
			{
				printf("\n要杀死的进程不存在\n");
			}
			break;
	 	 }
	 }	 
}

/********************唤醒进程***************************/
void awaken()
{
	if(!num)
	{
		printf("当前没有运行进程\n");
		return;
	}
	
	printf("\n请输入要唤醒的进程\n");
	scanf("%d",&pid);
	
	for(i=0;i<50;i++)
	{
		if(pid==memory[i].pid)
		{
			if(memory[i].state==2)
			{
				memory[i].state=1;
				suspend--;
				printf("\n成功唤醒进程\n");
			}
			else if(memory[i].state==1)
			{
				printf("\n进程已经在运行中\n");
			}
			else if(memory[i].state==0)
			{
				printf("\n要唤醒的进程不存在\n");
			}
		}
	}
}

int main()
{
	int i,n=1;
	int x;//系统操作的序号数 

	for(i=0;i<50;i++)
	{
		memory[i].state=0;//一开始所有进程都不在内存中
	}	
	
	while(n){
		printf("\n******************************************");
		printf("\n*		进程演示系统	   	 *");
		printf("\n******************************************");
		printf("\n*1.创建新的进程		2.查看运行进程 	 *");
		printf("\n*3.换出某个进程		4.杀死运行进程 	 *");
		printf("\n*5.唤醒某个进程		6.退出系统 	 *");
		printf("\n******************************************");
		printf("\n请选择想要进行的操作:\n");
		scanf("%d",&x);
		
		switch(x)
		{
			case 1: create(); 	break;
			case 2: run(); 		break;
			case 3: swap_out(); break;
			case 4: kill();		break; 
			case 5: awaken();	break;
		}
		flag=0;
	}
	return 0;
}



