#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    char data;
    struct node *lchild;
    struct node *rchild;
}Node,*BiTree;

typedef struct{
    BiTree buf[1000]; //缓冲区，存放类型为指针
    int size;
    void init(){ //初始化
        size=0;
    }
    void push(BiTree x){  //入栈
        buf[size++]=x;
    }
    BiTree pop(){ //出栈
        return buf[--size];
    }
    int empty(){ //判断栈空
        return size==0;
    }
}Stack;


BiTree create(char x){ //创建一个二叉树的结点，结点内容为x，并返回它的指针
    BiTree ret=(BiTree)malloc(sizeof(Node));
    ret->lchild=NULL;
    ret->rchild=NULL;
    ret->data=x;
    return ret;
}


void PreCreate(BiTree &root){ //先序遍历构建一棵二叉树
    char c;
    c=getchar();
    if(c=='#') root=NULL;
    else{
        root=create(c);
        PreCreate(root->lchild);
        PreCreate(root->rchild);
    }
}


void InOrderTraver1(BiTree rt){ //通过递归的方法来中序遍历二叉树
    if(rt==NULL) return ;
    InOrderTraver1(rt->lchild);
    printf("%c",rt->data);
    InOrderTraver1(rt->rchild);
}


void InOrderTraver2(BiTree root){ //通过非递归的方法来中序遍历二叉树并返回叶子节点的数量
    Stack s;
    s.init(); //开一个栈辅助用
    BiTree cur=root;
    while(cur!=NULL||s.empty()==false){
        while(cur&&cur->lchild!=NULL){
            s.push(cur);
            cur=cur->lchild;
        }
        if(cur!=NULL){
            printf("%c",cur->data);
        }
        if(cur->rchild!=NULL){
            cur=cur->rchild;
        }
        else if(s.empty()==false){
            cur=s.pop();
            printf("%c",cur->data);
            cur=cur->rchild;
        }
        else{
            cur=NULL;
        }
    }
}

void PreTraverse(BiTree root){ //先序遍历
    if(root==NULL) return ;
    printf("%c",root->data);
    PreTraverse(root->lchild);
    PreTraverse(root->rchild);
}

BiTree buf[1000];
void LayerTraverse(BiTree root){ //层序遍历
    int head,tail;
    head=tail=0;
    buf[tail++]=root;
    while(tail>head){
        BiTree cur=buf[head++];
        printf("%c",cur->data);
        if(cur->lchild) buf[tail++]=cur->lchild;
        if(cur->rchild) buf[tail++]=cur->rchild;
    }
    puts("");
}

int CheckBST(BiTree root){ //检查root这棵子树是不是二叉排序树
    if(root==NULL) return 1;
    if(root->lchild&&root->lchild->data>root->data) return 0;
    if(root->rchild&&root->rchild->data<root->data) return 0;
    return CheckBST(root->lchild)&&CheckBST(root->rchild);
}
void InsertBST(BiTree &root,char c){  //在二叉搜索树中插入c
    if(root==NULL){
        root=create(c);
        return ;
    }
    if(c==root->data) return ;
    if(c<root->data) InsertBST(root->lchild,c);
    else             InsertBST(root->rchild,c);
}
void DeleteBST(BiTree rt,char c){ //在二叉搜索树中删除c
    BiTree q=rt;
    BiTree p=rt->lchild;
    while(p->data!=c){
        q=p;
        if(c<p->data) p=p->lchild;
        else          p=p->rchild;
    }
    if(p->lchild==NULL&&p->rchild==NULL){
        if(q->lchild==p) q->lchild=NULL;
        else             q->rchild=NULL;
    }
    else if(p->lchild!=NULL&&p->rchild==NULL){
        if(q->lchild==p) q->lchild=p->lchild;
        else             q->rchild=p->lchild;
    }
    else if(p->rchild!=NULL&&p->lchild==NULL){
        if(q->lchild==p) q->lchild=p->rchild;
        else             q->rchild=p->rchild;
    }
    else{
        BiTree pp=p->rchild;
        while(pp->lchild) pp=pp->lchild;
        char cc=pp->data;
        DeleteBST(rt,cc);
        p->data=cc;
    }
}

int main(){
    BiTree root=NULL; //二叉树的根
    BiTree temp=NULL;
    printf("请输入字符序列，通过先序遍历创建二叉树（#表示空）\n");
    PreCreate(root);  //先序遍历构建二叉树
    printf("先序遍历：");
    PreTraverse(root); puts("");
    printf("通过递归的方法中序遍历:");
    InOrderTraver1(root); //采用递归的形式中序遍历二叉链表
    puts(""); //换行
    printf("通过非递归的方法中序遍历:");
    InOrderTraver2(root); //采用非递归的形式中序遍历二叉链表
    puts(""); //换行
    printf("层序遍历：");
    LayerTraverse(root);
    if(CheckBST(root)){
        printf("这棵树是二叉搜索树\n");
        temp=create(127); temp->lchild=root;
        //为了方便删除,增加一个头结点辅助
        while(1){
            printf("请选择操作：0结束/1插入/2删除\n");
            int opt;
            scanf("%d",&opt);
            if(opt==0) break;
            if(opt==1){
                printf("插入：");
                char c; c=getchar();
                while(c=='\n'||c=='\r') c=getchar();
                InsertBST(temp,c);
            }
            if(opt==2){
                printf("删除：");
                char c; c=getchar();
                while(c=='\n'||c=='\r') c=getchar();
                DeleteBST(temp,c);
            }
        }
        printf("中序遍历操作后的二叉搜索树：");
        InOrderTraver1(temp->lchild);
    }
    else{
        printf("这棵树不是二叉搜索树");
    }
    return 0;
}
//ha#d##mk##n##
