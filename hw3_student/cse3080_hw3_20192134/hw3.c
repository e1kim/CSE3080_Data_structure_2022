#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAX_NUM 20
#define MAXWORD 30
#define MAX_ELEMENTS 50000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
#define MAX_VERTEX 10001 //vertex 최대

int parent[MAX_VERTEX];

int simpleFind(int i) {
    int root, trail, lead;

    for (; parent[i] >= 0; i = parent[i])
        ;
   /* for (trail = i; trail != root; trail = lead) {
        lead = parent[trail];
        parent[trail] = root;
    }*/
    return i;
}

void weightedUnion(int i, int j) {
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j]) {
        parent[i] = j;
        parent[j] = temp;
    }
    else {
        parent[j] = i;
        parent[i] = temp;
    }
}
typedef struct {
	int key;
    int v1;
    int v2;
} element;


element *min_heap;

int m = 0; //min
clock_t start, finish;
//element heap[MAX_ELEMENTS]; //출력하기 위한 힙
void insert_min_heap(element item, int* n);
element delete_min_heap(int* m);


int main(int argc, char* argv[])
{
    FILE* ifp, * ofp;
    start = clock();

    //input파일이 1개가 아니면 에러 처리
    if (argc != 2)
    {
        printf("usage: ./hw3 input_filename\n");
        return 1;
    }//input 파일 받아오기
    ifp = fopen(argv[1], "r");
    if (ifp == NULL) {   //파일이 존재하지 않으면 에러처리
        printf("input file does not exist.\n");
        return 1;
    }
    //output file 쓰기
    ofp = fopen("hw3_result.txt", "w");
    if (ofp == NULL) {
        printf("output file open error!\n");
        return 1;
    }
    int vertex_num, edge_num;
    int res,vertex1, vertex2, weight;
    element item;
    res = fscanf(ifp, "%d", &vertex_num);
    for (int i = 0; i < vertex_num; i++) parent[i] = -1;
    
    res = fscanf(ifp, "%d", &edge_num);
    min_heap = (element*)malloc(sizeof(element) * edge_num);

    //printf("%d %d\n", vertex_num, edge_num);

    //파일에 있는 정보 입력받아 min heap에 저장한다.
    for (int i = 0; i < edge_num; ++i)
    {
        res = fscanf(ifp, "%d%d%d", &vertex1, &vertex2, &weight);
        //printf("%d %d %d\n", vertex1, vertex2,weight);
        item.key = weight;
        item.v1 = vertex1;
        item.v2 = vertex2;
        
        insert_min_heap(item, &m);
        //printf("m: %d\n",m);
    }
    int T = 1;
    int sum = 0;
    //kruskal's algorithm

    while (T < vertex_num && m)
    {
        
        item = delete_min_heap(&m);
        
        if (T == 0) {
            weightedUnion(item.v1, item.v2);
        }
        //printf("%d %d\n",simpleFind(item.v1),simpleFind(item.v2));
       

        if (simpleFind(item.v1) != simpleFind(item.v2) || (parent[item.v1] < -1) || (parent[item.v2] < -1)) {
            //printf("선택: %d %d %d\n", item.v1, item.v2, item.key);
            fprintf(ofp, "%d %d %d\n", item.v1, item.v2, item.key);
            T++;
            sum += item.key;
            weightedUnion(simpleFind(item.v1), simpleFind(item.v2));
        }
        else //root가 같을 때, 즉 사이클이 생성될 때
        {
            ;
        }
        
    }
    fprintf(ofp, "%d\n", sum);
    //connect?
    if (T < vertex_num - 1) fputs("DISCONNECTED\n", ofp);
    else fputs("CONNECTED", ofp);
    //output 출력
    printf("output written to hw3_result.txt\n");
    finish = clock();
    double du_time = (double)(finish - start) / CLOCKS_PER_SEC; // CLOCK_PER_SEC;
    //time 출력
    printf("running time: %f seconds\n", du_time);
    //메모리 해제
    free(min_heap);
    fclose(ofp);
    fclose(ifp);
    return 0;
}



void insert_min_heap(element item, int* m) {
    /* insert item into a max heap of current size *m */
    int i;
    i = ++(*m);
    if (HEAP_FULL(*m)) {
        fprintf(stderr, "The heap is full.\n");
        exit(1);
    }

    while ((i != 1) && (item.key < min_heap[i / 2].key)) {
        min_heap[i] = min_heap[i / 2];
        i /= 2;
    }
    min_heap[i] = item;
}

element delete_min_heap(int* m)
{
    element item, temp;
    int child, parent;
    if (HEAP_EMPTY(*m))
    {
        item.key = 0;
    }
    else
    {
        item = min_heap[1];
        temp = min_heap[(*m)--];
        child = 2;
        parent = 1;
        while (child <= *m)
        {
            if (child < *m && min_heap[child].key > min_heap[child + 1].key) child++;
            if (temp.key < min_heap[child].key) break;
            min_heap[parent] = min_heap[child];
            parent = child;
            child *= 2;
        }
        min_heap[parent] = temp;


    }
    return item;
}