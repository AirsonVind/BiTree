#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define StackInitSize 100 //��ʼ������
#define StackIncrement 10 //��������


//�������������ʽ�洢��ʾ
typedef char TElemType;
typedef int Status;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *Lchild,*Rchild;
    int IsOut;//����DFS����������ǵݹ飩
}BiTNode,*BiTree;


//����˳��洢ջ
typedef BiTree SElemType;
typedef struct 
{
    SElemType *base; //ջ��ָ��
    SElemType *top; //ջ��ָ��
    int stacksize; //��ǰջ���������
}SqStack;

//����������
typedef BiTree QElemType;
typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;
typedef struct 
{
    QueuePtr front;//��ͷָ��
    QueuePtr rear;//��βָ��
}LinkQueue;



//----------------������---------------------------------


//�����������ĺ���ԭ��
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
        printf("����%c�����ӽڵ�(����ո���Ϊ��)��", ch);
        CreateBiTree(&(*T)->Lchild);
        printf("����%c�����ӽڵ�(����ո���Ϊ��)��", ch);
        CreateBiTree(&(*T)->Rchild);
        (*T)->IsOut = 0;
    }
    return OK;
}



//DFS�������(�ݹ�)
Status PreOrderTraverse_Recursion(BiTree *T)
{
    if (*T == NULL) return ERROR;
    printf("%c ",(*T)->data);
    PreOrderTraverse_Recursion(&(*T)->Lchild);
    PreOrderTraverse_Recursion(&(*T)->Rchild);
    return OK;
}
//DFS����������ǵݹ飩
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


//DFS����������ݹ飩
Status InOrderTraverse_Recursion(BiTree *T)
{
    if (*T == NULL) return ERROR;
    InOrderTraverse_Recursion(&(*T)->Lchild);
    printf("%c ",(*T)->data);
    InOrderTraverse_Recursion(&(*T)->Rchild);
    return OK;
}
//DFS����������ǵݹ飩
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




//DFS����������ݹ飩
Status PostOrderTraverse_Recursion(BiTree *T)
{
    if (*T == NULL) return ERROR;
    PostOrderTraverse_Recursion(&(*T)->Lchild); 
    PostOrderTraverse_Recursion(&(*T)->Rchild);
    printf("%c ",(*T)->data);
    return OK;
}
//DFS����������ǵݹ飩
Status PostOrderTraverse_InRecursion(BiTree *T)
{
    BiTree p = *T;
    SqStack S;
    InitStack(&S);
    while (p || !EmptyStack(&S))
    {
        if (p) 
        {
            if (p->IsOut)//���������������
            {
                Pop(&S,&p);
                printf("%c ",p->data);
                if (!EmptyStack(&S))//����ýڵ�������δ�����һ��δ�����
                {
                    GetTop(&S,&p);//��õ��ýڵ�ĸ��ڵ�
                }else
                {
                    p = NULL;//��ʱpΪ�գ���ջΪ�գ�ѭ����ֹ
                }
            }else//����������δ������
            {    
                if ((p->Lchild) && (p->Lchild->IsOut == 1))//�������������Ѿ�������ϣ���ֱ����������
                {
                    p = p->Rchild;
                }else
                {
                    Push(&S,p);
                    p = p->Lchild;
                }
            }
        }else
        {//��ʱpΪ�գ��ѱ���������ˣ�
             GetTop(&S,&p);//������һ��
            if (p->Rchild)
            {
                p = p->Rchild;//������������ʱ����������
            }else//p��û��������Ҳû��������
            {
                Pop(&S,&p);//��ջ��Ԫ�أ���ʱ��Ϊp������
                printf("%c ",p->data);//���
                p->IsOut = 1;
                
                if (!EmptyStack(&S))
                {
                    GetTop(&S,&p);//������һ��
                    if (p->Rchild->IsOut == 1)//����һ�����ҽڵ��ѱ����
                        p->IsOut = 1;//��ýڵ�Ҳ�ɱ����
                }else
                {
                    p = NULL;
                }
            } 
        }
    }
}



//BFS�㼶���ȱ���(�ǵݹ�)
Status BFSQueue(BiTree *T)
{
    if(T == NULL)  return ERROR;
    LinkQueue Q;
    InitQueue(&Q);
 
    EnQueue(&Q,T);//���������
 
    QElemType temp;//��������
    while(!EmptyQueue(&Q))//�����в�Ϊ��ʱ
    {
        if(DeQueue(&Q,&temp))
            printf("%c ",temp->data);//�����һ��
        if(temp->Lchild) EnQueue(&Q,&temp->Lchild);//����������ʱ�����������
        if(temp->Rchild) EnQueue(&Q,&temp->Rchild);//����������ʱ�����������
    }
	printf("\n");
    return OK;
}


//-----------------ջ-----------------------



//��ʼ��ջ
Status InitStack(SqStack *S)
{
    S->base = (SElemType * )malloc(sizeof(SqStack)*StackInitSize);
    if (!S->base)exit(0);
    S->top = S->base;
    S->stacksize = StackInitSize;
    return OK;
};

//�ж�ջ�Ƿ�Ϊ��
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


//���ջ��Ԫ��
Status GetTop(SqStack *S,SElemType *e)
{
    if (S->base == S->top)    return ERROR;
    *e = *(S->top-1);
    return OK;
}

//��ջ
Status Push(SqStack *S,SElemType e)
{
    if (S->top-S->base == S->stacksize)
    {
        S->base = (SElemType * )realloc(S->base,sizeof(SqStack)*(S->stacksize+StackIncrement));
        if (!S->base) exit(0);//����ʧ��

        S->top = S->base + S->stacksize;
        S->stacksize += StackIncrement;
    }
    *S->top++ = e;
    return OK;
}

//��ջ
Status Pop(SqStack *S,SElemType *e)
{
    if (S->top == S->base) exit(0);
    *e = *--S->top;
    return OK;
}



//----------------����----------------------

//����ն���
Status InitQueue(LinkQueue *Q)
{
    Q->front = (QueuePtr)malloc(sizeof(QNode));
    Q->rear = Q->front;
    if (!Q->front) exit(OVERFLOW);
    Q->front->next = NULL;
    return OK;
}

//�ж϶����Ƿ�Ϊ��
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

//���
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

//����
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
    printf("��������ڵ��ֵ(�ַ���):");
    CreateBiTree(&T);
    printf("�������Ѵ������!\n");
    printf("DFS����������ݹ飩:");
    PreOrderTraverse_Recursion(&T);
    printf("\n");
    printf("DFS����������ǵݹ飩:");
    PreOrderTraverse_InRecursion(&T);
    printf("\n");  
    printf("DFS����������ݹ飩:");
    InOrderTraverse_Recursion(&T);
    printf("\n");
    printf("DFS����������ǵݹ飩:");
    InOrderTraverse_InRecursion(&T);
    printf("\n");
    printf("DFS����������ݹ飩:");
    PostOrderTraverse_Recursion(&T);
    printf("\n");
    printf("DFS����������ǵݹ飩:");
    PostOrderTraverse_InRecursion(&T);
    printf("\n");
    printf("BFS������ȱ������ǵݹ飩:");
    BFSQueue(&T);      
    return 0;
}