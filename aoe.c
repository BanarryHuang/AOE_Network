#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTICES 100
typedef struct {//�s�J�Ҧ��䬡��
    int number;
    int event1;
    int event2;
} edge;
typedef struct node *nodePointer;
typedef struct node {//�䬡�ʬ���
    int vertex;
    int duration;
    nodePointer link;
};
typedef struct {//�P�I�۱��� linked-list
    int count;
    nodePointer link;
} hdnodes;

int ee[MAX_VERTICES],le[MAX_VERTICES];

nodePointer create(int x, int y){//�� malloc �s�y�s�� linked-list �� node
    nodePointer temp;
    temp=(nodePointer)malloc(sizeof(nodePointer));
    temp->vertex=x;
    temp->duration=y;
    temp->link=NULL;
    return temp;
}

void topSort (hdnodes *graph, int n, int x){//�i��topological order���禡�Ax�N��@�}�l���ݾ�(0)&�f�ݾ�(1)
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

    P=malloc(MAX_VERTICES*sizeof(hdnodes));//�@�}�l���ݾ�
    S=malloc(MAX_VERTICES*sizeof(hdnodes));//�f�ݾ�
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

            /*��X�Y���`�I*/
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
            /*���J�ܤ@�}�l���ݾ�(��ee��)*/
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
            /*���J�ܰf�ݾ�(��le��)*/
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

        topSort(P,tail-head+1,0);//�i��ݾ�Ƨ�

        for(i=0;i<tail-head+1;i++){
            if(ee[i]==0&&i!=0){
                printf("No solution\n");
                n=1;
                break;
            }
            le[i]=ee[tail];
        }

        if(n==1) continue;//No solution

        topSort(S,tail-head+1,1);//�i��ݾ�Ƨ�

        printf("%d\n",edge_num);
        for(i=0;i<edge_num;i++){
            a=ee[edge_set[i].event1];//�̦��ɶ�e
            b=le[edge_set[i].event2]-edge_set[i].number;//�̱߮ɶ�l
            printf("%d %d %d ",a,b,b-a);
            if(b-a==0)//�l��l-e
                printf("y\n");
            else
                printf("n\n");
        }
    }
    return 0;
}
