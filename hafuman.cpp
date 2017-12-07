#include <stdio.h> 
#include <stdlib.h> 
#define MaxSize 50 
typedef struct{ 
    char c;                       //代码; 
    int w;                       //代码权值; 
    char code[MaxSize];           //代码的Huffman编码; 
    }HuffCode[MaxSize]; 
typedef struct{ 
    int Weight;                   //权值; 
    int LChild,RChild,Parent; 
    }HTNode,HuffTree[MaxSize]; 
//================================================================================ 
void HuffmanTree(HuffTree HT,int length,HuffCode hc);        //生成Huffman树; 
void SelectHTNode(HuffTree HT,int n,int *min1,int *min2);    //查找最小和次小序号; 
void HuffmanCode(HuffTree HT,int len,HuffCode hc);            //生成Huffman编码; 
//================================================================================ 
int main(void) 
{ 
    HuffTree HT;       //Huffman树; 
    HuffCode HC;       //Huffman编码; 
    int i,len; 
    printf("<<<<  Huffman编码生成程序  >>>>\t\tby Haroldi.\n\n  请帮助评价一下思路及改善意见!\t多谢了:-)...\n\n\n\n"); 
    printf("\n输入代码数量：");    scanf("%d",&len); system("cls");printf("代码数量：%2d\n\n",len); 
    printf("输入代码及权值(e.g.:  \"a16[回车]\" )：\n"); 
    for(i=1;i <= len;i++) 
    { 
        while(getchar() != '\n')    NULL; 
        printf("No.%2d：  ",i); 
        HC[i].c = getchar(); 
        scanf("%d",&HC[i].w); 
    } 
    HuffmanTree(HT,len,HC); 
    HuffmanCode(HT,len,HC); 

    printf("\n输出Huffman编码：\n"); 
    for(i = 1;i<=len;i++) 
    { 
        printf("\n %c :",HC[i].c); 
        puts(HC[i].code); 
    } 
//测试Huffman树结构; 
    printf("\n\n输出Huffman树结构：");system("pause"); 
    printf("\nHT[i]:\t权值\t双亲\t左孩子\t右孩子\n"); 
    for(i = 1;i<2*len;i++) 
    { 
        if(i <= len)    printf("(%c)",HC[i].c); 
        printf("%2d:\t %2d;\t%2d,\t %2d,\t %2d.\n", 
            i,HT[i].Weight,HT[i].Parent,HT[i].LChild,HT[i].RChild); 
    } 
    return 0; 
} 
//================================================================================ 
void HuffmanTree(HuffTree HT,int length,HuffCode hc)       //Huffman树初始化; 
{ 
    int i,min1,min2; 
    HT[0].Weight = 65535; 
    for(i = 1;i <= length;i++) 
    { 
        HT[i].Weight = hc[i].w; 
        HT[i].LChild = HT[i].RChild = HT[i].Parent = -1; 
    } 
    for(;i < 2*length;i++)            //i初值 = length+1; 
    { 
        HT[i].LChild = HT[i].RChild = HT[i].Parent = -1; 
    } 

    for(i = length+1;i < 2*length;i++) 
    { 
        SelectHTNode(HT,i,&min1,&min2); 
        HT[min1].Parent = i; 
        HT[min2].Parent = i; 
        HT[i].LChild = min1; 
        HT[i].RChild = min2; 
        HT[i].Weight = HT[min1].Weight + HT[min2].Weight; 
    } 
} 
//================================================================================ 
void SelectHTNode(HuffTree HT,int n,int *min1,int *min2)    //查找最小和次小序号; 
{ 
    int i; 
    *min1 = *min2 = 0; 
    for(i = 1;i < n;i++) 
    { 
        if(HT[i].Parent == -1) 
        { 
            if(HT[*min1].Weight >= HT[i].Weight) 
            { 
                *min2 = *min1; 
                *min1 = i; 
            } 
            else if(HT[*min2].Weight > HT[i].Weight)    *min2 = i; 
        } 
    } 
} 
//================================================================================ 
void HuffmanCode(HuffTree HT,int len,HuffCode hc)         //生成Huffman编码; 
{ 
    int i,j,tc,Stack[MaxSize],top = -1; 
    char flag[MaxSize]; 
    HTNode th; 
    for(i = 1;i <= len;i++) 
    { 
        top = -1;                        //栈初始化; 
        j = 0;                            //hc[i].code串首位置偏移; 
        th = HT[i];                        //当前结点th; 
        tc = i;                            //当前结点标记tc; 
        while(th.Parent != -1) 
        {            //当前结点th双亲P入栈,由P的孩子是th,确定flag;确定下次结点标记tc; 
            Stack[++top] = th.Parent; 
            if(HT[th.Parent].LChild == tc)    {flag[top] = 'L'; tc = th.Parent;} 
            if(HT[th.Parent].RChild == tc)    {flag[top] = 'R'; tc = th.Parent;} 
            th = HT[Stack[top]];        //下一结点; 
        }                                
        while(top != -1) 
        { 
            if(flag[top] == 'L')    hc[i].code[j++] ='0'; 
            else                    hc[i].code[j++] ='1'; 
            Stack[top--];                //出栈; 
        } 
        hc[i].code[j] ='\0';            //当前串结束; 
    }          
}