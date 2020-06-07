#include <iostream>
#include <cstdio>

using namespace std;
#define N 1000005
char s[N];
int m;
bool checkDigit(char c){
    return c>='0'&&c<='9';
}
typedef struct node{
    int data;
    struct node * next;
}*ListNode,Node;
ListNode head;
void ins(int x){
    ListNode p=head;
    while(p->next!=NULL&&p->next->data<x) p=p->next;
    ListNode q=(ListNode)malloc(sizeof(Node));
    q->next=p->next;
    q->data=x;
    p->next=q;
}
void print(){
    ListNode p=head;
    while(p->next!=NULL){
        p=p->next;
        printf("%d ",p->data);
    }
}
int main(){
    head=(ListNode)malloc(sizeof(Node));
    head->next=NULL;
    int n=0;
    cin>>n;
    for(int i=0;i<n;++i){
        gets(s);
        if(!checkDigit(s[0])){
            --i;
            continue;
        }
        int cur=0; int j=0;
        while(s[j]!='0'){
            if(checkDigit(s[j])){
                cur=cur*10+s[j]-'0';
                if(!checkDigit(s[j+1])){
                    ins(cur);
                    cur=0;
                }
            }
            ++j;
        }
    }
    print();
    return 0;
}

/*
4 
2 4 8
3 4 6
5 8 9 11
1 6 7 10 12

*/
