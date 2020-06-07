#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int id;
    struct Node *next;
}node;

int n; int m;
node *head=NULL;//头指针
node *tail=NULL;//尾指针

void init(){ //创建一个大小为n的循环链表
	node *cur;//当前结点指针
    node *lst=NULL;//cur上一个链表节点
    for(int i=1;i<=n;++i){
        cur=(node *)(malloc(sizeof(node)));//给cur申请空间
        cur->id=i;
     
        if(lst!=NULL) 
			lst->next=cur;
        
        if(head==NULL)
		head=cur;
        tail=cur;
        lst=cur;
    }
    tail->next=head;
}
int nums;
void fun(){ //根据题意模拟
    node *lst=tail;//初始化lst为tail，形成循环链表
	node *cur=head; 
    for(int i=1;i<=n-1;++i){
        for(int j=1;j<=m-1;++j){
            lst=cur;
            cur=cur->next;
        }
        lst->next=cur->next;
        printf("第%d个出去的人:%d \n",++nums,cur->id);
        cur=cur->next;
    }
    printf("最后一个人:%d \n",cur->id);
}

int main(){
	printf("请输入n m:");
    scanf("%d %d",&n,&m);
    init();
    fun();
    return 0;
}
