#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTICES 100
typedef struct {//存入所有邊活動
    int number;
    int event1;
    int event2;
} edge;
typedef struct node *nodePointer;
typedef struct node {//邊活動紀錄
    int vertex;
    int duration;
    nodePointer link;
};
typedef struct {//與點相接的 linked-list
    int count;
    nodePointer link;
} hdnodes;

int ee[MAX_VERTICES],le[MAX_VERTICES];

nodePointer create(int x, int y){//用 malloc 製造連接 linked-list 的 node
    nodePointer temp;
    temp=(nodePointer)malloc(sizeof(nodePointer));
    temp->vertex=x;
    temp->duration=y;
    temp->link=NULL;
    return temp;
}

void topSort (hdnodes *graph, int n, int x){//進行topological order的函式，x代表一開始的拓樸(0)&逆拓樸(1)
    int i, j, k, top;
    nodePointer ptr;
    top = -1;
    for (i = 0; i < n; i++)
        if (!graph[i].count) {
            graph[i].count = top;
            top = i;
        }
    for (i = 0; i < n; i++){
        j = top;
        top = graph[top].count;
        for (ptr = graph[j].link ; ptr ; ptr = ptr->link ){
            k = ptr->vertex;
            if(x==0){
                if(ee[k]<(ee[j]+ptr->duration))
                    ee[k]=ee[j]+ptr->duration;
	    }
            else if(x==1){
                if(le[k]>(le[j]-ptr->duration))
                    le[k]=le[j]-ptr->duration;
	    }
            graph[k].count--;
            if (!graph[k].count) {
                graph[k].count = top;
                top = k;
            }
        }
    }
}

int main(){

    int i,j,a,b;
    int edge_num;
    int head,tail;
    hdnodes *S,*P;
    nodePointer x,node;
    edge *edge_set;

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    P=malloc(MAX_VERTICES*sizeof(hdnodes));//一開始的拓樸
    S=malloc(MAX_VERTICES*sizeof(hdnodes));//逆拓樸
    edge_set=malloc(150*sizeof(edge));

    while(scanf("%d",&edge_num)!=EOF){
        int n=0;
        for(i=0;i<MAX_VERTICES;i++){
            P[i].count=0;
            P[i].link=NULL;
            S[i].count=0;
            S[i].link=NULL;
        }
        for(i=0;i<edge_num;i++){
            scanf("%d%d%d", &a, &b, &j);
            edge_set[i].event1=a;
            edge_set[i].event2=b;
            edge_set[i].number=j;

            /*找出頭尾節點*/
            if(i==0){
                head=edge_set[i].event1;
                tail=edge_set[i].event2;
            }
            else{
                if(head>edge_set[i].event1)
                    head=edge_set[i].event1;
                if(tail<edge_set[i].event2)
                    tail=edge_set[i].event2;
            }
            /*插入至一開始的拓樸(找ee值)*/
            node=create(edge_set[i].event2, edge_set[i].number);
            x=P[edge_set[i].event1].link;
            if(x==NULL)
                P[edge_set[i].event1].link=node;
            else{
                for(;;x=x->link)
                    if(x->link==NULL){
                        x->link=node;
                        break;
                    }
            }
            /*插入至逆拓樸(找le值)*/
            node=create(edge_set[i].event1, edge_set[i].number);
            x=S[edge_set[i].event2].link;
            if(x==NULL)
                S[edge_set[i].event2].link=node;
            else{
                for(;;x=x->link)
                    if(x->link==NULL){
                        x->link=node;
                        break;
                    }
            }
            P[edge_set[i].event2].count++;
            S[edge_set[i].event1].count++;
        }

        for(i=0;i<tail-head+1;i++)
            ee[i]=0;

        topSort(P,tail-head+1,0);//進行拓樸排序

        for(i=0;i<tail-head+1;i++){
            if(ee[i]==0&&i!=0){
                printf("No solution\n");
                n=1;
                break;
            }
            le[i]=ee[tail];
        }

        if(n==1) continue;//No solution

        topSort(S,tail-head+1,1);//進行拓樸排序

        printf("%d\n",edge_num);
        for(i=0;i<edge_num;i++){
            a=ee[edge_set[i].event1];//最早時間e
            b=le[edge_set[i].event2]-edge_set[i].number;//最晚時間l
            printf("%d %d %d ",a,b,b-a);
            if(b-a==0)//餘裕l-e
                printf("y\n");
            else
                printf("n\n");
        }
    }
    return 0;
}
