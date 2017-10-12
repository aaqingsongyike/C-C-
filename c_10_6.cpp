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

//����һ���ṹ��SqQueue��ʾ���У�����ѭ�����У�
typedef struct{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

//����һ���ն���Q
Status InitQueue(SqQueue *Q){
	Q->base=(QElemType *)malloc(MAXQSIZE *sizeof (QElemType));
	if(!Q->base) return(OVERFLOW);	//�洢����ʧ��
	Q->front=Q->rear=0;
	return OK;
}

//�ж϶����Ƿ�Ϊ�ա����շ���TRUE
Status QueueEmpty(SqQueue Q){
	if(Q.front==Q.rear) return TRUE;
	else return FALSE;
}

//�����Q��Ԫ�ظ����������еĳ���
int QueueLength(SqQueue Q){
	return(Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

//�����в��գ�ȡ����ͷԪ��
Status GetHead(SqQueue Q,QElemType *e){
	if(Q.front==Q.rear) return ERROR;
	*e=Q.base[Q.front];
	return OK;
}

//��ӣ�����Ԫ��eΪ���е��µĶ�βԪ��
Status EnQueue(SqQueue *Q,QElemType e){
	if((Q->rear+1)%MAXQSIZE==Q->front) return ERROR;
	Q->base[Q->rear]=e;
	Q->rear=(Q->rear+1)%MAXQSIZE;
	return OK;
}

//���ӣ������в��գ���ɾ������Q�Ķ�ͷԪ�أ���e������ֵ��������ok
Status DeQueue(SqQueue *Q,QElemType *e){
	if(Q->rear==Q->front) return ERROR;
	*e=Q->base[Q->front];
	Q->front=(Q->front+1)%MAXQSIZE;
	return OK;
}

/*�ж϶����Ƿ���

*/

//��������е�Ԫ��
Status PrintQueue(SqQueue Q){
	int i = Q.front;
	if(QueueEmpty(Q)){
		printf("����Ϊ��!\n");
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
		printf("�ռ����ʧ�ܣ��˳�");
	else{
		printf("\n\t\t��ӭ�����ϻ��Ŷ�ģ��\n");
		printf("****************************\n");
		printf("1.ȡ��	2.��ѯ�Ŷ����	3.�ϻ�����	4.�˳�ϵͳ\n");
		printf("****************************\n");
		while(1){
			printf("������ѡ��1-4:");
			scanf("%d",&choice);
			switch(choice){
			case 1:
				printf("������ѧ��:");
				scanf("%d",&e);
				EnQueue(&Q,e);
				printf("��ǰ�Ŷӵȴ���ѧ��:\n");
				PrintQueue(Q);
				break;
			case 2:
				printf("��ǰ��%d��ѧ���Ⱥ��ϻ�:\n",QueueLength(Q));
				PrintQueue(Q);
				break;
			case 3:
				if (DeQueue(&Q,&e)==ERROR){
					printf("������û��ѧ���Ⱥ�\n");
					break;
				}
				else{
					printf("ѧ��%d��ѧ����ʼ�ϻ�!\n",e);
					if (GetHead(Q,&e)==ERROR) printf("������û��ѧ���Ⱥ�\n");
					else printf("��һ��׼���ϻ���ѧ��Ϊ:%d\n",e);
					break;
				}
			}
			if(choice==4)
				break;
		}
	}
}














