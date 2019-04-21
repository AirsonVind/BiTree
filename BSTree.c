#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;
typedef struct BiTNode
{
    int data;
    struct BiTNode *Lchild, *Rchild;
} BiTNode, *BiTree;


Status CreateBiTree(BiTree *T)//�������Ĵ���
{
    int c;
    scanf("%d",&c);
    getchar();
    if (c == ' ') *T = NULL;
    else{
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!T) exit(OVERFLOW);
        (*T)->data = c;
        printf("����%c�����ӽڵ�(����ո���Ϊ��)��", c);
        CreateBiTree(&(*T)->Lchild);
        printf("����%c�����ӽڵ�(����ո���Ϊ��)��", c);
        CreateBiTree(&(*T)->Rchild);
    }
    return OK;
}



Status Search(BiTree *T,int n,BiTree *f,BiTree *p)//p����ָ�����һ��Ҷ�ӽ��
{
    if (!(*T)){
        *p = *f;
        return ERROR;//δ�ҵ�
    }else if (n == (*T)->data)
    {
        *p = *f;
        return OK;//�ҵ�
    }else if (n < (*T)->data)
    {
        return Search(&((*T)->Lchild),n,&(*T),&(*p));//��������������
    }else
    {
        return Search(&((*T)->Rchild),n,&(*T),&(*p));//��������������
    }
}



Status Insert(BiTree *T,int n)
{
    BiTree p = NULL;
    BiTree f = NULL;//f��Ϊ�ݴ����һ��Ҷ�ӽڵ��ָ��
    //������Ҳ��ɹ��������������
    if (!Search(&(*T),n,&f,&p)) {
        //��ʼ��������
        BiTree s = (BiTree)malloc(sizeof(BiTree));
        s->data = n;
        s->Lchild = s->Rchild = NULL;
        //��� p ΪNULL��˵���ö���������Ϊ��������ʱ����Ľ��Ϊ�������ĸ����
        if (!p) {
            *T = s;
        }
        //��� p ��Ϊ NULL����s����(p ָ���Ϊ����ʧ�ܵ����һ��Ҷ�ӽ��)
        else if(n < p->data){
            p->Lchild=s;
        }else{
            p->Rchild=s;
        }
        return TRUE;
    }
    //������ҳɹ�������Ҫ���������������ʧ��
    return FALSE;
}


int DeleteBST(BiTree *T, int n)
{
    if( !(*T)){
        return FALSE;
    }
    else
    {
        if( n == (*T)->data ){
            Delete(T);
            return TRUE;
        }
        else if( n < (*T)->data){
            //�ݹ�
            return DeleteBST(&(*T)->Lchild, n);
        }
        else{
            return DeleteBST(&(*T)->Rchild, n);
        }
    }
}




int main()
{
    BiTree T = NULL;
    int i = 0,temp;
    int s = -1;
    int n[MAXSIZE],length;
    printf("���������������ֵ:(����-1ʱֹͣ)\n");
    do
    {
        printf("�������%d��ֵ��",i+1);
        scanf("%d",&n[i]);
    } while (n[i++] > 0);
    length = i - 1;
    for(i = 0;i < length;i++){
        Insert(&T,n[i]);
    }
    printf("�����������ѽ���,");
    while (1)
    {
        printf("��ѡ����һ������:\n");
        printf("1. ����\n");
        printf("2. ����\n");
        printf("3. ɾ��\n");
        printf("4. �˳�\n");
        scanf("%d",&s);
    
        switch (s)
        {
        case 1:
            printf("������Ҫ���������:");
            scanf("%d",&temp);
            if (Insert(&T,temp))
            {
                printf("��������ɣ�");
            }else
            {
                printf("����ʧ�ܣ�");
            }
            
            break;
        case 2:
            printf("������Ҫ���ҵ�����:");
            scanf("%d",&temp);
            BiTree p = NULL;
            BiTree f = NULL;
            if (Search(&T,temp,&f,&p))
            {
                printf("���ڸ����֣�");
            }else
            {
                printf("�����ڸ����֣�");
            }
        case 3:
            printf("������Ҫɾ��������:");
            scanf("%d",&temp);
            if (DeleteBST(&T,temp))
            {
                printf("ɾ���ɹ���");
            }else
            {
                printf("ɾ��ʧ�ܣ�");
            }
        case 4:
            exit(-1);
        default:
            break;
        }
    }
    
    return 0;
}