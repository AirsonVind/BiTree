#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define StackInitSize 100 //初始分配量
#define StackIncrement 10 //分配增量


//定义二叉树的链式存储表示
typedef char TElemType;
typedef int Status;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *Lchild,*Rchild;
    int IsOut;//用于DFS后序遍历（非递归）
}BiTNode,*BiTree;


//定义顺序存储栈
typedef BiTree SElemType;
typedef struct 
{
    SElemType *base; //栈底指针
    SElemType *top; //栈顶指针
    int stacksize; //当前栈的最大容量
}SqStack;

//定义链队列
typedef BiTree QElemType;
typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;
typedef struct 
{
    QueuePtr front;//队头指针
    QueuePtr rear;//队尾指针
}LinkQueue;



//----------------二叉树---------------------------------


//创建二叉树的函数原型
Status CreateBiTree(BiTree *T)
{
    TElemType ch;
    scanf("%c",&ch);
    getchar();
    if (ch == ' ') *T = NULL;
    else{
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!T) exit(OVERFLOW);
        (*T)->data = ch;
        printf("输入%c的左子节点(输入空格则为空)：", ch);
        CreateBiTree(&(*T)->Lchild);
        printf("输入%c的右子节点(输入空格则为空)：", ch);
        CreateBiTree(&(*T)->Rchild);
        (*T)->IsOut = 0;
    }
    return OK;
}



//DFS先序遍历(递归)
Status PreOrderTraverse_Recursion(BiTree *T)
{
    if (*T == NULL) return ERROR;
    printf("%c ",(*T)->data);
    PreOrderTraverse_Recursion(&(*T)->Lchild);
    PreOrderTraverse_Recursion(&(*T)->Rchild);
    return OK;
}
//DFS先序遍历（非递归）
Status PreOrderTraverse_InRecursion(BiTree *T)
{
    BiTree p = *T;
    SqStack S;
    InitStack(&S);
    while (p || !EmptyStack(&S))
    {
        if (p)
        {
            printf("%C ",p->data);
            Push(&S,p);
            p = p->Lchild;
        }else
        {
            Pop(&S,&p);
            p = p->Rchild;
        }
    }
    return OK;
}


//DFS中序遍历（递归）
Status InOrderTraverse_Recursion(BiTree *T)
{
    if (*T == NULL) return ERROR;
    InOrderTraverse_Recursion(&(*T)->Lchild);
    printf("%c ",(*T)->data);
    InOrderTraverse_Recursion(&(*T)->Rchild);
    return OK;
}
//DFS中序遍历（非递归）
Status InOrderTraverse_InRecursion(BiTree *T)
{
    BiTree p = *T;
    SqStack S;
    InitStack(&S);
    while (p || !EmptyStack(&S))
    {
        if (p)
        {
            Push(&S,p);
            p = p->Lchild;
        }else
        {
            Pop(&S,&p);
            printf("%C ",p->data);
            p = p->Rchild;
        }
    }
    return OK;
}




//DFS后序遍历（递归）
Status PostOrderTraverse_Recursion(BiTree *T)
{
    if (*T == NULL) return ERROR;
    PostOrderTraverse_Recursion(&(*T)->Lchild); 
    PostOrderTraverse_Recursion(&(*T)->Rchild);
    printf("%c ",(*T)->data);
    return OK;
}
//DFS后序遍历（非递归）
Status PostOrderTraverse_InRecursion(BiTree *T)
{
    BiTree p = *T;
    SqStack S;
    InitStack(&S);
    while (p || !EmptyStack(&S))
    {
        if (p) 
        {
            if (p->IsOut)//左右子树都已输出
            {
                Pop(&S,&p);
                printf("%c ",p->data);
                if (!EmptyStack(&S))//如果该节点输出后任存在上一级未被输出
                {
                    GetTop(&S,&p);//则得到该节点的父节点
                }else
                {
                    p = NULL;//此时p为空，且栈为空，循环终止
                }
            }else//左右子树尚未输出完毕
            {    
                if ((p->Lchild) && (p->Lchild->IsOut == 1))//左子树存在且已经遍历完毕，则直接走右子树
                {
                    p = p->Rchild;
                }else
                {
                    Push(&S,p);
                    p = p->Lchild;
                }
            }
        }else
        {//此时p为空（已遍历至最左端）
             GetTop(&S,&p);//返回上一级
            if (p->Rchild)
            {
                p = p->Rchild;//当右子树存在时进入右子树
            }else//p既没有左子树也没有右子树
            {
                Pop(&S,&p);//将栈顶元素（此时即为p）弹出
                printf("%c ",p->data);//输出
                p->IsOut = 1;
                
                if (!EmptyStack(&S))
                {
                    GetTop(&S,&p);//返回上一级
                    if (p->Rchild->IsOut == 1)//若上一级的右节点已被输出
                        p->IsOut = 1;//则该节点也可被输出
                }else
                {
                    p = NULL;
                }
            } 
        }
    }
}



//BFS层级优先遍历(非递归)
Status BFSQueue(BiTree *T)
{
    if(T == NULL)  return ERROR;
    LinkQueue Q;
    InitQueue(&Q);
 
    EnQueue(&Q,T);//将树入队列
 
    QElemType temp;//创建副本
    while(!EmptyQueue(&Q))//当队列不为空时
    {
        if(DeQueue(&Q,&temp))
            printf("%c ",temp->data);//输出第一层
        if(temp->Lchild) EnQueue(&Q,&temp->Lchild);//存在左子树时将左子树入队
        if(temp->Rchild) EnQueue(&Q,&temp->Rchild);//存在右子树时将右子树入队
    }
	printf("\n");
    return OK;
}


//-----------------栈-----------------------



//初始化栈
Status InitStack(SqStack *S)
{
    S->base = (SElemType * )malloc(sizeof(SqStack)*StackInitSize);
    if (!S->base)exit(0);
    S->top = S->base;
    S->stacksize = StackInitSize;
    return OK;
};

//判断栈是否为空
Status EmptyStack(SqStack *S)
{
    if (S->base == S->top)
    {
        return OK;
    }else
    {
        return ERROR;
    }
}


//获得栈顶元素
Status GetTop(SqStack *S,SElemType *e)
{
    if (S->base == S->top)    return ERROR;
    *e = *(S->top-1);
    return OK;
}

//入栈
Status Push(SqStack *S,SElemType e)
{
    if (S->top-S->base == S->stacksize)
    {
        S->base = (SElemType * )realloc(S->base,sizeof(SqStack)*(S->stacksize+StackIncrement));
        if (!S->base) exit(0);//分配失败

        S->top = S->base + S->stacksize;
        S->stacksize += StackIncrement;
    }
    *S->top++ = e;
    return OK;
}

//出栈
Status Pop(SqStack *S,SElemType *e)
{
    if (S->top == S->base) exit(0);
    *e = *--S->top;
    return OK;
}



//----------------队列----------------------

//构造空队列
Status InitQueue(LinkQueue *Q)
{
    Q->front = (QueuePtr)malloc(sizeof(QNode));
    Q->rear = Q->front;
    if (!Q->front) exit(OVERFLOW);
    Q->front->next = NULL;
    return OK;
}

//判断队列是否为空
Status EmptyQueue(LinkQueue *Q)
{
    if (Q->front == Q->rear)
    {
        return TRUE;
    }else
    {
        return FALSE;
    }  
}

//入队
Status EnQueue(LinkQueue *Q,QElemType *e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) exit(OVERFLOW);
    p->data = *e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

//出队
Status DeQueue(LinkQueue *Q,QElemType *e)
{
    QueuePtr p;
    if (Q->front == Q->rear)  return ERROR;
    p = Q->front->next;
    Q->front->next = p->next;
    if (Q->rear == p)
    {
        Q->rear = Q->front;
    }
    (*e) = p->data;
    free(p);
    return OK;
}





int main()
{
    BiTree T;
    int n = 0,m = 0;
    printf("请输入根节点的值(字符型):");
    CreateBiTree(&T);
    printf("二叉树已创建完成!\n");
    printf("DFS先序遍历（递归）:");
    PreOrderTraverse_Recursion(&T);
    printf("\n");
    printf("DFS先序遍历（非递归）:");
    PreOrderTraverse_InRecursion(&T);
    printf("\n");  
    printf("DFS中序遍历（递归）:");
    InOrderTraverse_Recursion(&T);
    printf("\n");
    printf("DFS中序遍历（非递归）:");
    InOrderTraverse_InRecursion(&T);
    printf("\n");
    printf("DFS后序遍历（递归）:");
    PostOrderTraverse_Recursion(&T);
    printf("\n");
    printf("DFS后序遍历（非递归）:");
    PostOrderTraverse_InRecursion(&T);
    printf("\n");
    printf("BFS层次优先遍历（非递归）:");
    BFSQueue(&T);      
    return 0;
}