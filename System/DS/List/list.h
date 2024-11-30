#include <stdio.h>
#include <stdlib.h>
#include "../../PaymentSystem/Terminal/Terminal.h"
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD,FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    int transactionSequenceNumber;
    int op;
}ST_transaction_t;


typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;


typedef struct ST_accountsDB_t
{    char name[25];
    char primaryAccountNumber[20];
    char ExDate[6];
    float balance;
    EN_accountState_t state;
}ST_accountsDB_t;


typedef union data {
        ST_transaction_t transactionData;
        ST_accountsDB_t accountData;
} data;

typedef data List_Entry;
typedef struct listnode{
    List_Entry info;
    struct listnode *next;
}listnode;
typedef struct list{
    int size;
    listnode *head;
}list;

 void CreateList(list*pl);
 int ListEmpty(list*pl);
 int ListFull(list*pl);
 int ListSize(list *pl);
 void Destroy(list*pl);
 void TraverseList(list *pl,void(*pf)(List_Entry));
 int InsertList(list*pl,int pos,List_Entry e);
void RetrieveList(list *pl,int pos,List_Entry *pe);
void DeleteList(list *pl,int pos,List_Entry *pe);
void ReplaceList(list*pl,int pos,List_Entry e);
void DisplayList(List_Entry element);
long long ListSum(list *pl);
void ReverseList(list *pl);
List_Entry ListMiddle(list *pl);

