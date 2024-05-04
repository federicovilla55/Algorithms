#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RED   0
#define BLACK 1

typedef struct RBNode {
    int key;
    int color;
    int max;
    struct RBNode *parent, *left, *right;
} RBNode;

RBNode *createRBNode(int key) {
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));
    if(node == NULL){
        printf("Errore\n");
        return NULL;
    }
    node->key = key;
    node->max = 0;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;

    if (x->right != NULL)
        x->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->left;
    x->left = y->right;

    if (x->left != NULL)
        x->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

void fixViolation(RBNode **root, RBNode *x) {
    RBNode *parent = NULL;
    RBNode *grandparent = NULL;

    if(*root == NULL) return;

    while ((x != *root) && (x->color != BLACK) && (x->parent->color == RED)) {
        parent = x->parent;
        grandparent = x->parent->parent;

        if (parent == grandparent->left) {
            RBNode *uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent;
            } else {
                if (x == parent->right) {
                    leftRotate(root, parent);
                    x = parent;
                    parent = x->parent;
                }

                rightRotate(root, grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                x = parent;
            }
        } else {
            RBNode *uncle = grandparent->left;

            if ((uncle != NULL) && (uncle->color == RED)) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent;
            } else {
                if (x == parent->left) {
                    rightRotate(root, parent);
                    x = parent;
                    parent = x->parent;
                }

                leftRotate(root, grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                x = parent;
            }
        }
    }

    (*root)->color = BLACK;
}

RBNode *search(RBNode *root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

RBNode *minimumNode(RBNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

RBNode *successorNode(RBNode *node) {
    if (node->right != NULL) {
        return minimumNode(node->right);
    }

    RBNode *parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

void delete(RBNode **root, int key) {
    RBNode *nodeToDelete = search(*root, key);
    if (nodeToDelete == NULL) {
        printf("non demolita\n");
        return;
    }

    RBNode *nodeToFix = NULL;
    RBNode *child = NULL;

    if (nodeToDelete->left == NULL || nodeToDelete->right == NULL) {
        nodeToFix = nodeToDelete;
    } else {
        nodeToFix = successorNode(nodeToDelete);
    }

    if (nodeToFix->left != NULL) {
        child = nodeToFix->left;
    } else {
        child = nodeToFix->right;
    }

    if (child != NULL) {
        child->parent = nodeToFix->parent;
    }

    if (nodeToFix->parent == NULL) {
        *root = child;
    } else if (nodeToFix == nodeToFix->parent->left) {
        nodeToFix->parent->left = child;
    } else {
        nodeToFix->parent->right = child;
    }

    if (nodeToFix != nodeToDelete) {
        nodeToDelete->key = nodeToFix->key;
        nodeToDelete->max = nodeToFix->max;
    }

    if (nodeToFix->color == BLACK) {
        if (child != NULL) {
            child->color = BLACK;
        } else {
            RBNode *parent = nodeToFix->parent;
            fixViolation(root, parent);
        }
    }
    free(nodeToFix);
}

void insertNode(RBNode **root, int key) {
    RBNode *node = createRBNode(key);
    RBNode *y = NULL;
    RBNode *x = *root;

    while (x != NULL) {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;

    if (y == NULL)
        *root = node;
    else if (node->key < y->key)
        y->left = node;
    else
        y->right = node;

    fixViolation(root, node);
}

void inorderTraversal(RBNode* root, int low, int high, RBNode*** result, int* index) {
    if (root == NULL) return;

    inorderTraversal(root->left, low, high, result, index);

    if (root->key >= low && root->key <= high) {
        if(result) (*result)[*index] = root;
        *index = *index + 1;
    }

    inorderTraversal(root->right, low, high, result, index);
}

void postorderTraversal(RBNode* root, int low, int high, RBNode*** result, int* index) {
    if (root == NULL) return;

    postorderTraversal(root->right, low, high, result, index);

    if (root->key >= low && root->key <= high) {
        if(result) (*result)[*index] = root;
        *index = *index + 1;
    }

    postorderTraversal(root->left, low, high, result, index);
}

RBNode** getElementsInRange(RBNode* root, int low, int high, int* size) {
    int count = 0;
    inorderTraversal(root, low, high, NULL, &count);

    RBNode** result = (RBNode**)malloc(count * sizeof(RBNode*));
    if(result == NULL){
        printf("error\n");
        return NULL;
    }

    count = 0;
    inorderTraversal(root, low, high, &result, &count);

    *size = count;
    return result;
}

RBNode** getElementsInRangeRev(RBNode* root, int low, int high, int* size) {
    int count = 0;
    postorderTraversal(root, low, high, NULL, &count);
    // Rimuovendolo presenta: "Execution killed (could be triggered by violating memory limits)""

    RBNode** result = (RBNode**)malloc(count * sizeof(RBNode*));
    if(result == NULL){
        printf("error\n");
        return NULL;
    }

    count = 0;
    postorderTraversal(root, low, high, &result, &count);

    *size = count;
    return result;
}

int main() {
    RBNode *root = NULL;

    insertNode(&root, 12);
    insertNode(&root, 9);
    insertNode(&root, 22);
    insertNode(&root, 19);
    insertNode(&root, 17);
}