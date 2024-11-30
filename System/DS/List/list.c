#include "list.h"


void CreateList(list *pl) {
    pl->size = 0;
    pl->head = NULL;
}

int ListEmpty(list *pl) {
    return !pl->size;
}

int ListFull(list *pl) {
    return 0;
}

int ListSize(list *pl) {
    return pl->size;
}

void Destroy(list *pl) {
    listnode *pn = NULL;
    while ((pl->head)) {
        pn = pl->head->next;
        free(pl->head);
        pl->head = pn;
    }
    pl->size = 0;
}

void TraverseList(list *pl, void(*pf)(List_Entry)) {
    listnode *pn = pl->head;
    while (pn) {
        (pf)(pn->info);
        pn = pn->next;
    }
}

int InsertList(list *pl, int pos, List_Entry e) {
    listnode *p = NULL, *q = NULL;
    if (p = (listnode *) malloc(sizeof(listnode))) {

        p->info = e;
        p->next = NULL;
        if (pos == 0) {
            p->next = pl->head;
            pl->head = p;
        } else {
            q = pl->head;
            for (int i = 0; i < pos - 1; i++) {
                q = q->next;
            }
            p->next = q->next;
            q->next = p;

        }

        pl->size++;
        return 1;
    }
    return 0;
}

void RetrieveList(list *pl, int pos, List_Entry *pe) {
    listnode *q = NULL;
    q = pl->head;
    for (int i = 0; i < pos; ++i) {
        q = q->next;
    }
    *pe = q->info;

}

void DeleteList(list *pl, int pos, List_Entry *pe) {
    listnode *q = NULL, *temp = NULL;
    if (pos == 0) {
        *pe = pl->head->info;
        temp = pl->head->next;
        free(pl->head);
        pl->head = temp;
    } else {
        q = pl->head;
        for (int i = 0; i < pos - 1; ++i) {
            q = q->next;
        }
        *pe = q->next->info;
        temp = q->next->next;
        free(q->next);
        q->next = temp;
    }
    pl->size--;
}

void ReplaceList(list *pl, int pos, List_Entry e) {
    listnode *q = NULL;
    q = pl->head;
    for (int i = 0; i < pos; ++i) {
        q = q->next;
    }
    q->info = e;
}

void DisplayList(List_Entry element) {
    printf("the element is %d\n", element);
}



void ReverseList(list *pl) {
    listnode *cur = NULL, *prev = pl->head;

    if (pl->head != NULL) {
        prev = pl->head;
        cur = pl->head->next;
        pl->head = pl->head->next;
        prev->next = NULL;
    }
    while (pl->head != NULL) {
        pl->head = pl->head->next;
        cur->next = prev;
        prev = cur;
        cur = pl->head;
    }

    pl->head = prev;

}
List_Entry ListMiddle(list *pl){
    listnode *q=NULL;
    q=pl->head;
    if(ListSize(pl)==1){
        return pl->head->info;
    }else{
    for (int i = 0; i < ListSize(pl)/2; ++i) {
        q=q->next;
    }
        return q->info;
}
}
