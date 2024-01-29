#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct PCB_type{
	int pid; //����ID 
	int priority; //���ȼ�
	int size; //��С 
	int state; //��־����״̬��0Ϊ�����ڴ棬1Ϊ���ڴ棬2Ϊ���� 
	char info[10]; 
};

struct PCB_type memory[50];

int pid;  
int num=0; //�������� 
int suspend=0;//�������� 
int flag=0;//��� 
int i,j;

/*********************�����½���*************************/
void create()
{
	if(num>=50)  printf("\n�ڴ����������Ȼ������������\n");
	else{
		for(i=0;i<50;i++)
		{
			if(memory[i].state==0) 
			{
				break;
			}
		}
		
		printf("\n�������½����̵�pidֵ\n");
		scanf("%d",&memory[i].pid);
		
		for(j=0;j<i;j++)//�ж�֮ǰ�Ƿ������ͬ�Ľ��� 
		{
			if(memory[j].pid==memory[i].pid)
			{
				printf("\n�ý����Ѵ������ڴ���");//����Ҫ�ٴ���һ��,IDֵ�ظ���������Ĳ����޷�ʶ��������ĸ����� 
				return;
			}				
		}
		
		printf("\n�������½��̵����ȼ�\n");
		scanf("%d",&memory[i].priority);
		
		printf("\n�������½��̵Ĵ�С\n");
		scanf("%d",&memory[i].size);
		
		printf("\n�������½��̵�����\n");
		scanf("%s",&memory[i].info);
			
		memory[i].state=1; /*������״̬��Ϊ1����ʾ���ڴ���*/
		num++; /*�ڴ��н�����Ŀ��һ*/
	}
}

/********************�鿴��ǰ���н���**************************/

void run()
{
	printf("���н�����Ϣ����:\n");
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
			flag=1;//��Ϊһ���жϵı�� 
		}
	 } 
	 
	 if(!flag)//���û��һ�����Ϊ1��˵�� û�н��������� 
	 {
	 	printf("\n��ǰû�����н��̣�\n");
	 }
}

/********************��������***************************/
void  swap_out()
{
	if(!num)
	{
		printf("��ǰû�����н��̣�\n");
		return;
	 } 
	 
	 printf("\n�����뻻�����̵�IDֵ");
	 scanf("%d",&pid);
	 
	 for(i=0;i<50;i++)
	 {
	 	if(pid==memory[i].pid) 
	 	{
	 		if(memory[i].state==1)
	 		{
	 			memory[i].state=2;//�ѽ��̵�״̬����Ϊ2 
	 			suspend++; //����������1 
	 			printf("\n�Ѿ��ɹ���������\n");
			 }
			else if(memory[i].state==2) 
			 {
			 	printf("\nҪ�����Ľ����Ѿ�������\n");
			  } 
			else
			 {
			 	printf("\n���̲����ڣ����ɻ���\n");
			 }
			 break;
		 }
	 }
}

/********************ɱ������***************************/
void kill() 
{
	if(!num)
	{
		printf("��ǰû�����н��̣�\n");
		return;
	}
	
	printf("\n������Ҫɱ�����̵�IDֵ");
	scanf("%d",&pid);
	
	for(i=0;i<50;i++)
	{
		if(pid==memory[i].pid)
		{
			if(memory[i].state==1)
			{
				memory[i].state=0;
				num--;
				printf("\n�Ѿ��ɹ�ɱ������\n");
			}
			else if(memory[i].state==2) 
			{
				printf("\nҪɱ���Ľ����Ѿ�������\n");
			}
			else 
			{
				printf("\nҪɱ���Ľ��̲�����\n");
			}
			break;
	 	 }
	 }	 
}

/********************���ѽ���***************************/
void awaken()
{
	if(!num)
	{
		printf("��ǰû�����н���\n");
		return;
	}
	
	printf("\n������Ҫ���ѵĽ���\n");
	scanf("%d",&pid);
	
	for(i=0;i<50;i++)
	{
		if(pid==memory[i].pid)
		{
			if(memory[i].state==2)
			{
				memory[i].state=1;
				suspend--;
				printf("\n�ɹ����ѽ���\n");
			}
			else if(memory[i].state==1)
			{
				printf("\n�����Ѿ���������\n");
			}
			else if(memory[i].state==0)
			{
				printf("\nҪ���ѵĽ��̲�����\n");
			}
		}
	}
}

int main()
{
	int i,n=1;
	int x;//ϵͳ����������� 

	for(i=0;i<50;i++)
	{
		memory[i].state=0;//һ��ʼ���н��̶������ڴ���
	}	
	
	while(n){
		printf("\n******************************************");
		printf("\n*		������ʾϵͳ	   	 *");
		printf("\n******************************************");
		printf("\n*1.�����µĽ���		2.�鿴���н��� 	 *");
		printf("\n*3.����ĳ������		4.ɱ�����н��� 	 *");
		printf("\n*5.����ĳ������		6.�˳�ϵͳ 	 *");
		printf("\n******************************************");
		printf("\n��ѡ����Ҫ���еĲ���:\n");
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



