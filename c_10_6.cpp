#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -1
#define MAXQSIZE 100

typedef int Status;
typedef int QElemType;

//定义一个结构体SqQueue表示队列（采用循环队列）
typedef struct{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

//构造一个空队列Q
Status InitQueue(SqQueue *Q){
	Q->base=(QElemType *)malloc(MAXQSIZE *sizeof (QElemType));
	if(!Q->base) return(OVERFLOW);	//存储分配失败
	Q->front=Q->rear=0;
	return OK;
}

//判断队列是否为空、若空返回TRUE
Status QueueEmpty(SqQueue Q){
	if(Q.front==Q.rear) return TRUE;
	else return FALSE;
}

//求队列Q的元素个数，即队列的长度
int QueueLength(SqQueue Q){
	return(Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

//若队列不空，取出对头元素
Status GetHead(SqQueue Q,QElemType *e){
	if(Q.front==Q.rear) return ERROR;
	*e=Q.base[Q.front];
	return OK;
}

//入队，插入元素e为队列的新的队尾元素
Status EnQueue(SqQueue *Q,QElemType e){
	if((Q->rear+1)%MAXQSIZE==Q->front) return ERROR;
	Q->base[Q->rear]=e;
	Q->rear=(Q->rear+1)%MAXQSIZE;
	return OK;
}

//出队，若队列不空，则删除队列Q的队头元素，用e返回其值，并返回ok
Status DeQueue(SqQueue *Q,QElemType *e){
	if(Q->rear==Q->front) return ERROR;
	*e=Q->base[Q->front];
	Q->front=(Q->front+1)%MAXQSIZE;
	return OK;
}

/*判断队列是否满

*/

//输出队列中的元素
Status PrintQueue(SqQueue Q){
	int i = Q.front;
	if(QueueEmpty(Q)){
		printf("队列为空!\n");
		return ERROR;
	}
	else{
		printf("---------------------------------\n");
		while(i!=Q.rear){
			printf("%d	\n",Q.base[i]);
			i=(i+1)%MAXQSIZE;
		}
		printf("---------------------------------\n");
	}
}

main(){
	int choice,e;
	SqQueue Q;
	if(InitQueue(&Q)==OVERFLOW)
		printf("空间分配失败，退出");
	else{
		printf("\n\t\t欢迎进入上机排队模块\n");
		printf("****************************\n");
		printf("1.取号	2.查询排队情况	3.上机呼叫	4.退出系统\n");
		printf("****************************\n");
		while(1){
			printf("请输入选项1-4:");
			scanf("%d",&choice);
			switch(choice){
			case 1:
				printf("请输入学号:");
				scanf("%d",&e);
				EnQueue(&Q,e);
				printf("当前排队等待的学生:\n");
				PrintQueue(Q);
				break;
			case 2:
				printf("当前有%d名学生等候上机:\n",QueueLength(Q));
				PrintQueue(Q);
				break;
			case 3:
				if (DeQueue(&Q,&e)==ERROR){
					printf("队列中没有学生等候\n");
					break;
				}
				else{
					printf("学号%d的学生开始上机!\n",e);
					if (GetHead(Q,&e)==ERROR) printf("队列中没有学生等候\n");
					else printf("下一个准备上机的学生为:%d\n",e);
					break;
				}
			}
			if(choice==4)
				break;
		}
	}
}














