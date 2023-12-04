#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
typedef struct __node_t {
    int         key;
    struct __node_t     *next;
    pthread_mutex_t lock;
} node_t;

typedef struct __list_t {
    node_t      *head;
} list_t;

void List_Init(list_t *L) {
    L->head = NULL;
}

void List_Insert(list_t *L, int key) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) { perror("malloc"); return; }
    new->key  = key;    
    pthread_mutex_init(&new->lock, NULL);
    pthread_mutex_lock(&new->lock);
    new->next = L->head;
    if (L->head != NULL) {
        pthread_mutex_lock(&L->head->lock);
    }
    node_t *prev = L->head;
    L->head = new;
    if (prev!= NULL) {
        pthread_mutex_unlock(&new->next->lock);
    }
    pthread_mutex_unlock(&new->lock);
}

int List_Lookup(list_t *L, int key) {
    node_t *tmp = L->head;
    int flag = 0;
    if (tmp != NULL) {
        pthread_mutex_lock(&tmp->lock);
    }
    while (tmp) {
        if (tmp->key == key) 
        {
            pthread_mutex_unlock(&tmp->lock);
            flag = 1;
            return flag;
        }
        node_t *next = tmp->next;
        if (next != NULL) 
        {
            pthread_mutex_lock(&next->lock);
        }
        pthread_mutex_unlock(&tmp->lock);
        tmp = next;
    }
    return flag;
}

void List_Print(list_t *L) {
    node_t *tmp = L->head;
    if (tmp != NULL) 
    {
        pthread_mutex_lock(&tmp->lock);
    }
    while (tmp) 
    {
        printf("%d ", tmp->key);
        node_t *next = tmp->next;
        if (next != NULL) 
        {
            pthread_mutex_lock(&next->lock);
        }
        pthread_mutex_unlock(&tmp->lock);
        tmp = next;
    }
    printf("\n");
}

typedef struct __threadArguments {
    list_t *list;
    int start;
    int end;
} threadArguments;

void *insert_in_linked_list(void *args) {
    threadArguments *targuments = (threadArguments *)args;
    int st = targuments->start;
    int en = targuments->end;
    for (int i = st; i <= en; i++) 
    {
        List_Insert(targuments->list, i);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc != 5)
    {
        perror("incorrect input\n");
    }
    int n, k, l, r;
    n = atoi(argv[1]);
    k = atoi(argv[2]);
    l = atoi(argv[3]);
    r = atoi(argv[4]);
    list_t list;
    List_Init(&list);

    pthread_t threads[k];
    threadArguments targuments[k];

    for (int i = 0; i < k; i++) 
    {
        targuments[i].list = &list;
        targuments[i].start = 1 + n*i;
        targuments[i].end = n*(i+1);
        pthread_create(&threads[i], NULL, insert_in_linked_list, &targuments[i]);
    }

    for (int i = 0; i < k; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    //uncomment the next line to print the list.
    // List_Print(&list);

    int count = 0;
    node_t *curr = list.head;
    if (curr != NULL) {
        pthread_mutex_lock(&curr->lock);
    }
    while (curr) {
        if (curr->key >= l && curr->key <= r) 
        {
            count++;
        }
        node_t *next = curr->next;
        if (next != NULL) 
        {
            pthread_mutex_lock(&next->lock);
        }
        pthread_mutex_unlock(&curr->lock);
        curr = next;
    }
    printf("the number of elements in the range [l = %d, r = %d] is equal to %d.\n", l, r, count);
    return 0;
}

