�{���ت�

��@�XAOE(activity-on-edge)�����C

�D�n�[�c

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

nodePointer create(int x, int y);//�� malloc �s�y�s�� linked-list �� node

void topSort (hdnodes *graph, int n, int x);//�i��topological order���禡�Ax�N���ݾ�(0)&�f�ݾ�(1)

main():

�@�}�l�i���J�U���ʪ���ơA���K��X�}�Y�I�ε����I�A�Y�i�o���q���Ӷ}�Y�I�쵲���I�C

���K���J�ܥ��ݾ��f�ݾ�A���ݾ�O���U�_�Y�I�s���F�֡A�f�ݾ�O���U�����I�s���F�֡C

�A�Ӷi�楿�ݾ�ΰf�ݾ�ƧǡA�o��U�Iee,le�ȡC

�䤤�u���}�Y�I��ee�Ȭ�0�A�p�G����L�D�}�Y�I��ee�ȥ笰0���ܡA�h AOE has no solution�C

�̫�N��o��̦��ɶ�e�B�̱߮ɶ�l�B�l��l-e�C

�ɶ������� : �ɶ������׬� O(n) ~ O(n^2)(�p�G�Y�_�Y�I�s���Ӧh�I�A�ɭP�ݾ�Ƨǻݭn�q�Y�]���)