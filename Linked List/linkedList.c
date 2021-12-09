#include<stdio.h>
#include<stdlib.h>

typedef struct N{
    int val;
    struct N *next;
} node_t;
typedef node_t* Ptr_node;

Ptr_node insert_head(int v, Ptr_node n);
Ptr_node order_list(Ptr_node l);
void print_list(Ptr_node n);
void free_list(Ptr_node n);

int main(){
    Ptr_node head;
    head = NULL;

    /* Inserting values in the list: */
    head = insert_head(1, head);
    head = insert_head(2, head);
    head = insert_head(3, head);
    head = insert_head(4, head);
    
    /* Printing the list content */
    print_list(head);

    /* Printing the list after an Insertion Sort */
    head = order_list(head);
    print_list(head);
    
    /* Cleaning the Heap */
    free_list(head);

    return 0;
}

Ptr_node insert_head(int v, Ptr_node n){
	Ptr_node r;
	r = malloc(sizeof(node_t));
	if(!r){
		return NULL;
	}

	r->val = v;
	r->next = n;
	return r;
}

void print_list(Ptr_node n){
    while(n){
        printf("%d -> ", n->val);
        n=n->next;
    }
    printf("\n");
}

void free_list(Ptr_node n){
    Ptr_node succ;
    while(n){
        succ = n->next;
        free(n);
        n = succ;
    }
}

Ptr_node order_list(Ptr_node n){
	Ptr_node list_ord, tmp, prev_tmp;

	if(n==NULL || n-> next==NULL){
		return n;
	}
	list_ord = order_list(n->next);
	tmp = list_ord;
	while(tmp && tmp->val < n->val){
		prev_tmp = tmp;
		tmp = tmp->next;
	}
	if(tmp == list_ord){  
		n->next = list_ord;
		return n;
	} else{
		n -> next = tmp;
		prev_tmp->next = n;
		return list_ord;
	}

}
