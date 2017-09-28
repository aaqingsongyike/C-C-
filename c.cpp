#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>
#define ERROR 0
#define	OK 1
#define FALSE 0
#define TRUE 1
#define OVERFLOW -1
#define LIST_INIT_SIZE 100	/*���Ա�洢�ռ�ĳ�ʼ����������Ϊ100*/
#define LISTINCREMENT 10	/*���Ա�洢�ռ�ĳ�ʼ����������Ϊ10*/
typedef int Status;
//����һ���ṹ��student��ʾѧ���������Ա��е�Ԫ��ai��
typedef struct{//13
	int no;
	char name[20];
	char sex[4];
	int age;
	char dorm[10];
}student;//19
typedef student ElemType;
//����һ���ṹ��SqList��ʾ���Ա�����˳��洢�ṹ��
typedef struct{
	ElemType *elem;	//�洢�ռ��ַ
	int length;		//���Ա���
	int listsize;	//��ǰ����Ĵ洢����
}SqList;
//����յ����Ա�
Status InitList(SqList *L){//28
	L->elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L->elem) exit(OVERFLOW);//30
	L->length=0;
	L->listsize=LIST_INIT_SIZE;
	return OK;
}
Status ListEmpty(SqList L){
	if(L.length==0) return TRUE;
	else return FALSE;
}
//��˳���L�ĵ�i��λ��֮ǰ����Ԫ��e
Status ListInsert(SqList *L,int i,ElemType e){
	ElemType *p,*q;
	ElemType *newbase;
	if (i<1||i>L->length+1) //�п�
		return ERROR;
	if(L->length>=L->listsize){		//����
		newbase = (ElemType*) realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
			if(!newbase)exit(OVERFLOW);
			L->elem=newbase;
			L->listsize+=LISTINCREMENT;
	}
	q=&(L->elem[i-1]);
	for(p=&(L->elem[L->length-1]);p>=q;--p)
		*(p+1)=*p;
	*q=e;
	++L->length;
	return OK;
}
//��ʾ���Ա��е�ѧ����Ϣ
Status PrintList(SqList L){//59
	int i;
	printf("ѧ��\t����\t�Ա�\t����\t�����\n");
	for(i=0;i<L.length;i++){//62
		printf("-------------------------------------\n");
		printf("%d\t%s\t%s\t%d\t%s\n",L.elem[i].no,L.elem[i].name,L.elem[i].sex,L.elem[i].age,L.elem[i].dorm);//64
	}
	return OK;
}
//ɾ��ѧ������Ϣ
Status ListDelete(SqList *L,int i,ElemType *e){	//ɾ��˳����е�i��Ԫ�ز���e���� 
	ElemType *p,*q;
	if(i<1||i>L->length) return ERROR;
	p=&(L->elem[i-1]);
	*e=*p;
	q=L->elem+L->length-1;
	for(++p;p<=q;++p)
	*(p-1)=*p;
	--L->length;
	return OK;
} 
//��ʾ�༶����
Status ListLength(SqList L){
	return L.length;
} 

Status GetElem(SqList L,int i,ElemType *e){
	if(i>0&&i<=L.length){
		*e=L.elem[i-1];
		return OK;
	}else{
		return ERROR;
	}
}

Status BinSearch(SqList L,int k){
	int low=0,high=L.length-1,mid;
	while(low<=high){
		mid=(low+high)/2;
		if(L.elem[mid].no==k)
			return mid+1;
		else if(L.elem[mid].no>k)
			high=mid-1;
		else
			low=mid+1;
		
	}
	return 0;
}

int main(){
	student e;
	SqList L;
	int choice,i;
	int k;
	InitList(&L);
	printf("\n\t\t��ӭ����ѧ��������Ϣ¼��ģ��\n\n");
	printf("******************************************\n");
	printf("1.����ѧ����Ϣ\t\t	2.���ѧ����Ϣ\t\n");
	printf("3��ĩβ����ѧ������Ϣ\t	4ɾ��ѧ����Ϣ\t\n");
	printf("5��ʾ�༶����\t\t\t6����Ų�ѯѧ������Ϣ\n");
	printf("7��ѧ�Ų�ѯѧ������Ϣ\t\t0�˳�ϵͳ\n");
	printf("******************************************\n");
	while(1){
		printf("����������0-7ѡ����Ӧ������");
		scanf("%d",&choice);
		getchar();
		switch(choice){
		case 1:
			printf("������Ҫ����ѧ����ѧ�ţ�\n");
			scanf("%d",&e.no);//83
			printf("������Ҫ����ѧ����������\n");
			scanf("%s",&e.name);
			printf("������Ҫ����ѧ�����Ա�\n");
			scanf("%s",&e.sex);
			printf("������Ҫ����ѧ�������䣺\n");
			scanf("%d",&e.age);
			printf("������Ҫ����ѧ��������ţ�\n");
			scanf("%s",&e.dorm);//91
			printf("������Ҫ����ѧ����λ�ã�\n");
			scanf("%d",&i);
			ListInsert(&L,i,e);
			printf("����ɹ���\n");
			break;
		case 2:
			if(ListEmpty(L))
				printf("��ǰû��ѧ����Ϣ:\n");
			else
				PrintList(L);
			break;
		case 3:
			printf("������Ҫ����ѧ����ѧ�ţ�\n");
			scanf("%d",&e.no);//83
			printf("������Ҫ����ѧ����������\n");
			scanf("%s",&e.name);
			printf("������Ҫ����ѧ�����Ա�\n");
			scanf("%s",&e.sex);
			printf("������Ҫ����ѧ�������䣺\n");
			scanf("%d",&e.age);
			printf("������Ҫ����ѧ��������ţ�\n");
			scanf("%s",&e.dorm);			
			ListInsert(&L,e.no,e);
			printf("����ɹ���\n");
			break;
		case 4:
			printf("������Ҫɾ��ѧ����ѧ�ţ�\n");
			scanf("%d",&e.no);	
			ListDelete(&L,e.no,&e);	
			break;
		case 5:
			printf("�༶����Ϊ��%d\n",ListLength(L));
			break;
		case 6:
			if(ListEmpty(L))
				printf("��ǰû��ѧ����Ϣ��\n");
			else{
				printf("������Ҫ��ѯѧ������ţ�\n");
				scanf("%d",&i);
				if(!GetElem(L,i,&e))
					printf("�����������\n");
				else{
					printf("ѧ��\t����\t�Ա�\t����\t�����\n");
					printf("%d\t%s\t%s\t%d\t%s\n",e.no,e.name,e.sex,e.age,e.dorm);
				}
			}
			break;
		case 7:
			if(ListEmpty(L))
				printf("��ǰû��ѧ����Ϣ��\n");
			else{
				printf("������Ҫ��ѯѧ����ѧ�ţ�\n");
				scanf("%d",&k);
				i=BinSearch(L,k);
				printf("this%d",i);
				if(i==0)
					printf("����ʧ�ܣ�\n");
				else{
					GetElem(L,i,&e);
					printf("���ҳɹ�����ѧ�������Ϊ��%d,������ϢΪ��\n",i);
					printf("ѧ��\t����\t�Ա�\t����\t�����\n");
					printf("%d\t%s\t%s\t%d\t%s\n",e.no,e.name,e.sex,e.age,e.dorm);
				}
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
