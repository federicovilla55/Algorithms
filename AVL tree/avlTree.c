#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct AVLNode {
    int key;
    int upDist, downDist;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;    
    *b = temp;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(AVLNode *node) {
    if (node == NULL)
        return 0;
    return (getHeight(node->left) - getHeight(node->right));
}

AVLNode *createAVLNode(int key) {
    AVLNode *node = NULL;
    node = (AVLNode *)malloc(sizeof(AVLNode));

    if(node == NULL){
        printf("Errore\n");
        return NULL;
    }

    node->key = key;
    node->height = 1;
    node->downDist = 0;
    node->upDist = 0;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *tmp = x->right;

    x->right = y;
    y->left = tmp;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *tmp = y->left;

    y->left = x;
    x->right = tmp;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode *curr = NULL;

AVLNode *insert(AVLNode *node, int key) {
    if (node == NULL){
        curr = createAVLNode(key);
        return curr;
    }

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

AVLNode *search(AVLNode *node, int key) {
    if (node == NULL || node->key == key)
        return node;

    if (key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
}

AVLNode *getMinValueNode(AVLNode *node) {
    AVLNode *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

AVLNode *delete(AVLNode *root, int key) {
    if (root == NULL) {
        printf("non demolita\n");
        return root;
    }

    if (key < root->key) {
        root->left = delete(root->left, key);
    } else if (key > root->key) {
        root->right = delete(root->right, key);
    } else {
        if (root->left == NULL) {
            AVLNode* temp = root->right;
            free(root);
            //removeKey(root->key);
            printf("demolita\n");
            return temp;
        } else if (root->right == NULL) {
            AVLNode* temp = root->left;
            //removeKey(root->key);
            free(root);
            printf("demolita\n");
            return temp;
        }

        AVLNode* successor = getMinValueNode(root->right);
        //removeKey(root->key);
        swap(&root->key, &successor->key); //root->key = successor->key; 
        root->downDist = successor->downDist;
        root->upDist = successor->upDist;
        root->right = delete(root->right, successor->key);
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorderTraversal(AVLNode* root, int low, int high, AVLNode*** result, int* index) {
    if (root == NULL) return;

    inorderTraversal(root->left, low, high, result, index);

    if (root->key >= low && root->key <= high) {
        if(result) (*result)[*index] = &root;
        *index = *index + 1;
    }


    inorderTraversal(root->right, low, high, result, index);
}

void postorderTraversal(AVLNode* root, int low, int high, AVLNode*** result, int* index) {
    if (root == NULL) return;

    postorderTraversal(root->right, low, high, result, index);

    if (root->key >= low && root->key <= high) {
        if(result) (*result)[*index] = &root;
        *index = *index + 1;
    }

    postorderTraversal(root->left, low, high, result, index);
}

AVLNode** getElementsInRange(AVLNode* root, int low, int high, int* size) {
    int count = 0;
    inorderTraversal(root, low, high, NULL, &count);

    AVLNode** result = (AVLNode**)malloc(count * sizeof(AVLNode*));
    if(result == NULL){
        printf("error\n");
        return NULL;
    }

    count = 0;
    inorderTraversal(root, low, high, result, &count);

    *size = count;
    return result;
}

AVLNode** getElementsInRangeRev(AVLNode* root, int low, int high, int* size) {
    int count = 0;
    postorderTraversal(root, low, high, NULL, &count);

    AVLNode** result = (AVLNode**)malloc(count * sizeof(AVLNode*));
    if(result == NULL){
        printf("errore\n");
        return NULL;
    }

    count = 0;
    postorderTraversal(root, low, high, result, &count);

    *size = count;
    return result;
}

int binSearch(AVLNode** elementi, int left, int size, int X) {
    int right = size;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (elementi[mid]->key == X)
            return mid;
        
        if (elementi[mid]->key > X)
            left = mid + 1;
        else
            right = mid - 1;
    }

    if (left < size)
        return left;
    else
        return size;
}

int main() {
    AVLNode *root = NULL;
    AVLNode *curr = NULL;

    insert(root, 12);
    insert(root, 9);
    insert(root, 22);
    insert(root, 19);
    insert(root, 17);
}