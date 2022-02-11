#include<stdio.h>
#include<stdlib.h>

typedef struct N{
    int val;
    struct N* prev;
    struct N* next;
}queue_node;

typedef queue_node* Ptr_queue;

Ptr_queue enqueue(Ptr_queue rear, Ptr_queue* front, int val){
    Ptr_queue tmp;
    tmp = NULL;
    tmp = malloc(sizeof(queue_node));

    if(tmp){
        tmp->next = rear;
        tmp->prev = NULL;
        tmp->val = val;

        if(rear == NULL){
            rear = tmp;
            *front = tmp;
        }else{
            rear->prev = tmp;
            rear = rear->prev;
        }
    }

    return rear;
}

Ptr_queue dequeue(Ptr_queue front){
    Ptr_queue prec;
    if(front->prev){
        prec = front->prev;
        prec->next = NULL;
        free(front);
    }
    return prec;
}

void printAll(Ptr_queue rear){
    while(rear){
        printf(" -> %d ", rear->val);
        rear = rear->next;
    }
    printf("\n");
}

int main(){
    Ptr_queue rear, front;
    rear = NULL;
    front = NULL;

    rear = enqueue(rear, &front, 12);
    rear = enqueue(rear, &front, 9);
    rear = enqueue(rear, &front, 45);
    rear = enqueue(rear, &front, 2);
    front = dequeue(front);

    printAll(rear);

    return 0;
}