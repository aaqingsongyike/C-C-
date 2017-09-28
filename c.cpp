#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>
#define ERROR 0
#define	OK 1
#define FALSE 0
#define TRUE 1
#define OVERFLOW -1
#define LIST_INIT_SIZE 100	/*线性表存储空间的初始分配量定义为100*/
#define LISTINCREMENT 10	/*线性表存储空间的初始分配量定义为10*/
typedef int Status;
//定义一个结构体student表示学生（即线性表中的元素ai）
typedef struct{//13
	int no;
	char name[20];
	char sex[4];
	int age;
	char dorm[10];
}student;//19
typedef student ElemType;
//定义一个结构体SqList表示线性表（采用顺序存储结构）
typedef struct{
	ElemType *elem;	//存储空间基址
	int length;		//线性表长度
	int listsize;	//当前分配的存储容量
}SqList;
//构造空的线性表
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
//在顺序表L的第i个位置之前插入元素e
Status ListInsert(SqList *L,int i,ElemType e){
	ElemType *p,*q;
	ElemType *newbase;
	if (i<1||i>L->length+1) //判空
		return ERROR;
	if(L->length>=L->listsize){		//判满
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
//显示线性表中的学生信息
Status PrintList(SqList L){//59
	int i;
	printf("学号\t姓名\t性别\t年龄\t宿舍好\n");
	for(i=0;i<L.length;i++){//62
		printf("-------------------------------------\n");
		printf("%d\t%s\t%s\t%d\t%s\n",L.elem[i].no,L.elem[i].name,L.elem[i].sex,L.elem[i].age,L.elem[i].dorm);//64
	}
	return OK;
}
//删除学生的信息
Status ListDelete(SqList *L,int i,ElemType *e){	//删除顺序表中第i个元素并用e返回 
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
//显示班级人数
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
	printf("\n\t\t欢迎进入学生基本信息录入模块\n\n");
	printf("******************************************\n");
	printf("1.插入学生信息\t\t	2.输出学生信息\t\n");
	printf("3在末尾插入学生的信息\t	4删除学生信息\t\n");
	printf("5显示班级人数\t\t\t6按序号查询学生的信息\n");
	printf("7按学号查询学生的信息\t\t0退出系统\n");
	printf("******************************************\n");
	while(1){
		printf("请输入数字0-7选择相应操作：");
		scanf("%d",&choice);
		getchar();
		switch(choice){
		case 1:
			printf("请输入要插入学生的学号：\n");
			scanf("%d",&e.no);//83
			printf("请输入要插入学生的姓名：\n");
			scanf("%s",&e.name);
			printf("请输入要插入学生的性别：\n");
			scanf("%s",&e.sex);
			printf("请输入要插入学生的年龄：\n");
			scanf("%d",&e.age);
			printf("请输入要插入学生的宿舍号：\n");
			scanf("%s",&e.dorm);//91
			printf("请输入要插入学生的位置：\n");
			scanf("%d",&i);
			ListInsert(&L,i,e);
			printf("插入成功！\n");
			break;
		case 2:
			if(ListEmpty(L))
				printf("当前没有学生信息:\n");
			else
				PrintList(L);
			break;
		case 3:
			printf("请输入要插入学生的学号：\n");
			scanf("%d",&e.no);//83
			printf("请输入要插入学生的姓名：\n");
			scanf("%s",&e.name);
			printf("请输入要插入学生的性别：\n");
			scanf("%s",&e.sex);
			printf("请输入要插入学生的年龄：\n");
			scanf("%d",&e.age);
			printf("请输入要插入学生的宿舍号：\n");
			scanf("%s",&e.dorm);			
			ListInsert(&L,e.no,e);
			printf("插入成功！\n");
			break;
		case 4:
			printf("请输入要删除学生的学号：\n");
			scanf("%d",&e.no);	
			ListDelete(&L,e.no,&e);	
			break;
		case 5:
			printf("班级人数为：%d\n",ListLength(L));
			break;
		case 6:
			if(ListEmpty(L))
				printf("当前没有学生信息：\n");
			else{
				printf("请输入要查询学生的序号：\n");
				scanf("%d",&i);
				if(!GetElem(L,i,&e))
					printf("参数输入错误\n");
				else{
					printf("学号\t姓名\t性别\t年龄\t宿舍好\n");
					printf("%d\t%s\t%s\t%d\t%s\n",e.no,e.name,e.sex,e.age,e.dorm);
				}
			}
			break;
		case 7:
			if(ListEmpty(L))
				printf("当前没有学生信息：\n");
			else{
				printf("请输入要查询学生的学号：\n");
				scanf("%d",&k);
				i=BinSearch(L,k);
				printf("this%d",i);
				if(i==0)
					printf("查找失败！\n");
				else{
					GetElem(L,i,&e);
					printf("查找成功！该学生的序号为：%d,具体信息为：\n",i);
					printf("学号\t姓名\t性别\t年龄\t宿舍好\n");
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
