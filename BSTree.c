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


Status CreateBiTree(BiTree *T)//二叉树的创建
{
    int c;
    scanf("%d",&c);
    getchar();
    if (c == ' ') *T = NULL;
    else{
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!T) exit(OVERFLOW);
        (*T)->data = c;
        printf("输入%c的左子节点(输入空格则为空)：", c);
        CreateBiTree(&(*T)->Lchild);
        printf("输入%c的右子节点(输入空格则为空)：", c);
        CreateBiTree(&(*T)->Rchild);
    }
    return OK;
}



Status Search(BiTree *T,int n,BiTree *f,BiTree *p)//p用于指向最后一个叶子结点
{
    if (!(*T)){
        *p = *f;
        return ERROR;//未找到
    }else if (n == (*T)->data)
    {
        *p = *f;
        return OK;//找到
    }else if (n < (*T)->data)
    {
        return Search(&((*T)->Lchild),n,&(*T),&(*p));//进入左子树搜索
    }else
    {
        return Search(&((*T)->Rchild),n,&(*T),&(*p));//进入右子树搜索
    }
}



Status Insert(BiTree *T,int n)
{
    BiTree p = NULL;
    BiTree f = NULL;//f作为暂存最后一个叶子节点的指针
    //如果查找不成功，需做插入操作
    if (!Search(&(*T),n,&f,&p)) {
        //初始化插入结点
        BiTree s = (BiTree)malloc(sizeof(BiTree));
        s->data = n;
        s->Lchild = s->Rchild = NULL;
        //如果 p 为NULL，说明该二叉搜索树为空树，此时插入的结点为整棵树的根结点
        if (!p) {
            *T = s;
        }
        //如果 p 不为 NULL，将s插入(p 指向的为查找失败的最后一个叶子结点)
        else if(n < p->data){
            p->Lchild=s;
        }else{
            p->Rchild=s;
        }
        return TRUE;
    }
    //如果查找成功，不需要做插入操作，插入失败
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
            //递归
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
    printf("请依次输入各结点的值:(输入-1时停止)\n");
    do
    {
        printf("请输入第%d个值：",i+1);
        scanf("%d",&n[i]);
    } while (n[i++] > 0);
    length = i - 1;
    for(i = 0;i < length;i++){
        Insert(&T,n[i]);
    }
    printf("二叉搜索树已建立,");
    while (1)
    {
        printf("请选择下一步操作:\n");
        printf("1. 插入\n");
        printf("2. 查找\n");
        printf("3. 删除\n");
        printf("4. 退出\n");
        scanf("%d",&s);
    
        switch (s)
        {
        case 1:
            printf("请输入要插入的数字:");
            scanf("%d",&temp);
            if (Insert(&T,temp))
            {
                printf("插入已完成！");
            }else
            {
                printf("插入失败！");
            }
            
            break;
        case 2:
            printf("请输入要查找的数字:");
            scanf("%d",&temp);
            BiTree p = NULL;
            BiTree f = NULL;
            if (Search(&T,temp,&f,&p))
            {
                printf("存在该数字！");
            }else
            {
                printf("不存在该数字！");
            }
        case 3:
            printf("请输入要删除的数字:");
            scanf("%d",&temp);
            if (DeleteBST(&T,temp))
            {
                printf("删除成功！");
            }else
            {
                printf("删除失败！");
            }
        case 4:
            exit(-1);
        default:
            break;
        }
    }
    
    return 0;
}