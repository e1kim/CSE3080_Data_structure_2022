#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAX_NUM 20
#define MAXWORD 30
#define MAX_ELEMENTS 1000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
  int key;
} element;

element max_heap[MAX_ELEMENTS]; //저장하기 위한 힙
element min_heap[MAX_ELEMENTS];
int n = 0; //max
int m = 0; //min
clock_t start,finish;

element heap[MAX_ELEMENTS]; //출력하기 위한 힙
void insert_max_heap(element item, int *n);
void insert_min_heap(element item, int *n);
element delete_max_heap(int *n);
element delete_min_heap(int *m);

int main(int argc, char *argv[]){
    
    FILE *ifp,*ofp;
    start = clock();

    //input파일이 1개가 아니면 에러 처리
    if (argc !=2 )
    {
        printf("usage: ./hw2 input_filename\n");
        return 1;
    }//input 파일 받아오기
    ifp = fopen(argv[1],"r");
    if(ifp == NULL) {   //파일이 존재하지 않으면 에러처리
        printf("input file does not exist.\n");
        return 1;
    }

    ofp = fopen("hw2_result.txt","w");
    if(ofp == NULL) {
        printf("output file open error!\n");
        return 1;
    }
    //heap 구현하기
    int i, rn;
    element item;    
    char *line; 
    line = (char *)malloc(MAXWORD * sizeof(char));
    
    while(1)
    {
        if (fgets(line,MAXWORD,ifp) == NULL) // 파일의 끝 또는에러
        {
            //printf("file done\n");
            break;
        }
        if (line[0] == 'I')
        {
            char *ptr= line;
            int i=0;
            char buffer[MAX_NUM]={0,};
            while(*ptr != '\0')
            {   
                if (*ptr <= '9' && *ptr >= '0')
                {
                    buffer[i++]= *ptr;                
                }ptr++;          

            }
            int temp = atoi(buffer);
            
//            printf("insert %d\n",temp);
            item.key = temp;
            insert_max_heap(item,&n);
            insert_min_heap(item,&m);
        }
        else if (line[0] == 'A')
        {
      //      printf("a\n");
            memcpy(&heap,&min_heap,sizeof(element)*MAX_ELEMENTS);
            int temp=m;
            while(m)
            {
                item=delete_min_heap(&m);
    //            printf("ascend: %d\n",item.key);
                fprintf(ofp,"%d ",item.key);
            }fputs("\n",ofp);
            m=temp;

        }
        else if (line[0] == 'D') //숫자가큰!순서대로->max_heap delete 함수 활용
        {
  //          printf("d\n");
            
            memcpy(&heap,&max_heap,sizeof(element)*MAX_ELEMENTS);
            int temp=n;
            while(n)
            {
                item = delete_max_heap(&n);
//                printf("delete: %d\n",item.key);
                fprintf(ofp,"%d ",item.key);
            }fputs("\n",ofp);
            n=temp;
        }
    }
    printf("output written to hw2_result.txt\n");
    finish = clock();
    double du_time = (double)(finish - start)/CLOCKS_PER_SEC; // CLOCK_PER_SEC;
    printf("running time: %f seconds\n",du_time);
    free(line);
    fclose(ofp);
    fclose(ifp);
    return 0;
}




void insert_max_heap(element item, int *n) {
  /* insert item into a max heap of current size *n */
  int i;
  if(HEAP_FULL(*n)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
  i = ++(*n);
  while((i != 1) && (item.key > max_heap[i/2].key)) {
    max_heap[i] = max_heap[i/2];
    i /= 2;
  }
  max_heap[i] = item;
}


void insert_min_heap(element item, int *m) {
  /* insert item into a max heap of current size *m */
  int i;
  i=++(*m);
  if(HEAP_FULL(*m)) {
    fprintf(stderr, "The heap is full.\n");
    exit(1);
  }
 
  while((i != 1) && (item.key < min_heap[i/2].key)) {
    min_heap[i] = min_heap[i/2];
    i /= 2;
  }
  min_heap[i] = item;
}


element delete_max_heap(int *n) {
  /* delete element with the highest key from the heap */
  
  int parent, child;
  element item, temp;
  if(HEAP_EMPTY(*n)) {
    fprintf(stderr, "The heap is empty");
    exit(1);
  }
  /* save value of the element with the largest key */
  item = heap[1];
  /* use the last element in the heap to adjust heap */
  temp = heap[(*n)--];
  parent = 1;
  child = 2;
  while(child <= *n) {
    /* find the larger child of the current parent */
    if((child < *n) && (heap[child].key < heap[child+1].key)) child++;
    if(temp.key >= heap[child].key) break;
    /* move to the next lower level */
    heap[parent] = heap[child];
    parent = child;
    child *= 2;
  }
  heap[parent] = temp;
  return item;
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
        item = heap[1];
        temp = heap[(*m)--];
        child = 2;
        parent = 1;
        while (child <= *m)
        {
            if (child < *m && heap[child].key > heap[child + 1].key) child++;
            if (temp.key < heap[child].key) break;
            heap[parent] = heap[child];
            parent = child;
            child *= 2;
        }
        heap[parent] = temp;

            
    }
    return item;
}
