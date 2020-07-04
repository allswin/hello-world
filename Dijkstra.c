#include <stdio.h>
#include <stdlib.h>
#define MaxSize 500005
/*
采用带头结点的单链表
*/
typedef struct node{
    int adjvex;
    int weight;
    struct node *next;
}*ListNode,Node;
/*
 定义图结构
 */
typedef struct{
    int vertex; //最大点下标
    ListNode head[MaxSize];  //邻接链表
}*Graph,GraphStruct;
/*
 创建一个单链表的结点,返回其指针
 */
ListNode Create(){
    ListNode head=(ListNode)malloc(sizeof(Node));
    head->next=NULL;
    return head;
}
/*
 在以head为头结点的单链表中插入一个data为x的结点,O(1)
 */
void Ins(ListNode head,int adjvex,int weight){ //
    ListNode q=(ListNode)malloc(sizeof(Node));
    q->adjvex=adjvex;
    q->weight=weight;
    q->next=head->next;
    head->next=q;
}
/*
 初始化一个图,并返回指针
 */
Graph InitGraph(){
    Graph g=(Graph)malloc(sizeof(GraphStruct));
    g->vertex=0; //最大点下标初始化为0
    for(int i=0;i<MaxSize;++i) g->head[i]=Create(); //初始化每个点对应的单链表
    return g;
}
/*
 定义Dijkstra过程中活结点结构
 */
typedef struct{
    int id;
    int dis;
}DijNode;
/*
 定义堆的类型
 */
#define HeapType DijNode
typedef struct{
    int size;
    HeapType buf[MaxSize];
}*Heap,HeapStruct;
/*
 初始化一个堆,并返回指针
 */
Heap InitHeap(){
    Heap hp=(Heap)malloc(sizeof(HeapStruct));
    hp->size=0;
    return hp;
}
/*
 往堆内插入一个元素
 */
void HeapIns(Heap hp,HeapType x,int(*cmp)(HeapType,HeapType)){
    hp->buf[++hp->size]=x;
    int pos=hp->size;
    while(pos/2>=1){
        int nex=pos/2;
        if(cmp(hp->buf[nex],x)) break;
        hp->buf[pos]=hp->buf[nex];
        pos=nex;
    }
    hp->buf[pos]=x;
}
/*
 弹出堆顶
 */
void HeapPop(Heap hp,int(*cmp)(HeapType,HeapType)){
    hp->buf[1]=hp->buf[hp->size];
    --hp->size;
    if(hp->size==0) return ;
    int pos=1;
    HeapType x=hp->buf[pos];
    while(2*pos<=hp->size){
        int nex=2*pos;
        if(nex+1<=hp->size&&cmp(hp->buf[nex+1],hp->buf[nex])) ++nex;
        if(cmp(hp->buf[nex],x)==0) break;
        hp->buf[pos]=hp->buf[nex];
        pos=nex;
    }
    hp->buf[pos]=x;
}
/*
 获得堆顶
 */
HeapType HeapTop(Heap hp){
    return hp->buf[1];
}
/*
 判断堆是否为空
 */
int HeapEmpty(Heap hp){
    return hp->size==0;
}
/*
 比较两个堆结点谁更适合当堆顶
 */
int cmp(HeapType x,HeapType y){
    return x.dis<y.dis;
}
/*
 从文件读入信息创建图
 */
int s;
void CreateGrapth(Graph g){
    FILE *fp;
    if((fp=fopen("/Users/zdw/Downloads/test.txt", "r"))==NULL){
        printf("fail to open the file!\n");
        exit(0);
    }
    while(!feof(fp)){
        int u; int v; int w;
        fscanf(fp, "%d %d %d",&u,&v,&w);
        if(u>g->vertex) g->vertex=u;
        if(v>g->vertex) g->vertex=v;
        Ins(g->head[u], v, w);
    }
    fclose(fp);
}
/*
 通过Dijkstra求出在图g中,s为起点的单源最短路
 */
#define inf 0x3f3f3f3f
int dist[MaxSize]; //记录从s到i的最短路径长度
int pre[MaxSize];  //记录从s到i的最短路径中i的前驱,记录路径用
void Dijkstra(Graph g,int s){
    int n=g->vertex;//点数取出来
    for(int i=1;i<=n;++i) dist[i]=inf; //初始化距离无穷大
    for(int i=1;i<=n;++i) pre[i]=-1;   //初始化-1
    dist[s]=0; //将起点s的dist设为s
    Heap hp=InitHeap(); //创建一个堆
    HeapIns(hp, (DijNode){s,dist[s]}, cmp);
    while (HeapEmpty(hp)==0) {
        DijNode tmp=HeapTop(hp);
        HeapPop(hp, cmp); //取出小根堆的堆顶
        int u=tmp.id;
        int d=tmp.dis;
        if(d!=dist[u]) continue;  //剪枝
        ListNode p=g->head[u];
        while(p->next!=NULL){   //遍历邻接链表
            p=p->next;
            int v=p->adjvex; //取出邻接点
            int w=p->weight; //取出这条边的权值
            if(dist[u]+w<dist[v]){  //dist[u]+w<dist[v],刷新dist[v]并更新pre[v]
                dist[v]=dist[u]+w;
                pre[v]=u;
                HeapIns(hp,(DijNode){v,dist[v]}, cmp); //活结点放入堆中
            }
        }
    }
}
/*
 定义栈的数据结构
 */
#define StackType int
typedef struct{
    StackType buf[MaxSize];
    int size;
}*Stack,StackStruct;
/*
 初始化一个栈,并返回指针
 */
Stack InitStack(){
    Stack stk=(Stack)malloc(sizeof(StackStruct));
    stk->size=0;
    return stk;
}
/*
 入栈
 */
void StackPush(Stack stk,StackType x){
    stk->buf[stk->size++]=x;
}
/*
 出栈
 */
StackType StackPop(Stack stk){
    return stk->buf[--stk->size];
}
/*
 判断栈空
 */
int StackEmpty(Stack stk){
    return stk->size==0;
}

/*
 主函数
 */
int main(){
    Graph g=InitGraph(); //初始化一个图
    CreateGrapth(g);  //读入文件信息创建一个图
    printf("please input s and t!\n"); //提示输入
    int s; int t; scanf("%d %d",&s,&t);
    Dijkstra(g, s); //以s为起点跑单源最短路
    if(dist[t]==inf) printf("can't go to t from s!\n");
    else{
        int cur=t;
        Stack stk=InitStack();
        while(cur!=s){
            StackPush(stk, cur);
            cur=pre[cur];
        }
        StackPush(stk, s);
        printf("%d",StackPop(stk));
        while(StackEmpty(stk)==0) printf("-> %d",StackPop(stk));
        printf("\n");
        printf("MinCost:%d\n",dist[t]);
    }
    return 0;
}










