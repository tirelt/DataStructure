#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node *insertAfter(struct Node* prev_node, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->prev = prev_node;
    new_node->next = NULL;
    if(prev_node){
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }
    return new_node; 
}

struct Node *findBegin(struct Node* head) {
    if(!head)
        return NULL;
    if(!head->prev)
        return head;
    return findBegin(head->prev);
}

struct Node *findEnd(struct Node* head) {
    if(!head)
        return NULL;
    if(!head->next)
        return head;
    return findEnd(head->next);
}

void dealloc(struct Node* node) {
    if(!node)
        return;
    struct Node* end = findEnd(node);
    while(end->prev){
        end = end->prev;
        free(end->next);
    }
    free(end);
}

struct Node *findNode(struct Node* begin, struct Node* end, int data) {
    if(!begin||!end)
        return NULL;
    if (begin->data == data)
        return begin;
    if (begin == end)
        return NULL; 
    return findNode(begin->next, end, data);
}
int main(){
    struct Node* head = NULL;
    head = insertAfter(head, 69);
    head = insertAfter(head, 42);
    head = insertAfter(head, 15);
    head = insertAfter(head, 100);
    struct Node* begin = findBegin(head);
    printf("Front: %d\n", begin->next->data);
    struct Node* end = findEnd(head);
    printf("Back: %d\n", end->data);
    if(findNode(begin, end, 42))
        printf("Found 42\n");
    else
        printf("42 not found\n");
    dealloc(head);
    return 0;
}