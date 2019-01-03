程式目的

實作出AOE(activity-on-edge)網路。

主要架構

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

nodePointer create(int x, int y);//用 malloc 製造連接 linked-list 的 node

void topSort (hdnodes *graph, int n, int x);//進行topological order的函式，x代表正拓樸(0)&逆拓樸(1)

main():

一開始進行輸入各活動的資料，順便找出開頭點及結尾點，即可得知從哪個開頭點到結尾點。

順便插入至正拓樸跟逆拓樸，正拓樸記錄各起頭點連接了誰，逆拓樸記錄各接收點連接了誰。

再來進行正拓樸及逆拓樸排序，得到各點ee,le值。

其中只有開頭點的ee值為0，如果有其他非開頭點的ee值亦為0的話，則 AOE has no solution。

最後就能得到最早時間e、最晚時間l、餘裕l-e。

時間複雜度 : 時間複雜度為 O(n) ~ O(n^2)(如果某起頭點連接太多點，導致拓樸排序需要從頭跑到尾)