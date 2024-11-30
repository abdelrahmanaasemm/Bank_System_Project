#include "FileHandling.h"

void FileReadTrData(list *pl) {
    FILE *pf = NULL;
    char fl[200] = "C:\\Users\\user1\\CLionProjects\\FirstProject\\System\\DataBase\\Data\\TransactionData.txt";
    pf = fopen(fl, "r");
    if (pf == NULL) {
        printf("Error file is not opened");
        return;
    }
    List_Entry filedata;
    char TrState[33];
    int x=fscanf(pf, "%25[^;];%19[^;];%5[^;] ;%f;%f;%i; %[^\n]",
                 filedata.transactionData.cardHolderData.cardHolderName,
                 filedata.transactionData.cardHolderData.primaryAccountNumber,
                 filedata.transactionData.cardHolderData.cardExpirationDate,
                 &filedata.transactionData.terminalData.maxTransAmount,
                 &filedata.transactionData.terminalData.transAmount,
                 &filedata.transactionData.transactionSequenceNumber ,
                 TrState);
    while ( x == 7) {
        if (strcmp("APPROVED", TrState)) {
            filedata.transactionData.transState = APPROVED;
        } else if (strcmp("DECLINED_INSUFFECIENT_FUND", TrState)) {
            filedata.transactionData.transState = DECLINED_INSUFFECIENT_FUND;
        } else if (strcmp("FRAUD_CARD", TrState)) {
            filedata.transactionData.transState = FRAUD_CARD;
        } else if (strcmp("INTERNAL_SERVER_ERROR", TrState)) {
            filedata.transactionData.transState = INTERNAL_SERVER_ERROR;
        }
        if (filedata.transactionData.cardHolderData.cardHolderName[0] == '\n') {
            // Shift the characters to the left to remove the newline
            memmove(filedata.transactionData.cardHolderData.cardHolderName, filedata.transactionData.cardHolderData.cardHolderName+ 1, strlen(filedata.transactionData.cardHolderData.cardHolderName));
        }
        InsertList(pl, 0, filedata);
        x=fscanf(pf, "%25[^;];%19[^;];%5[^;] ;%f;%f;%i;%[^\n]",
                 filedata.transactionData.cardHolderData.cardHolderName,
                 filedata.transactionData.cardHolderData.primaryAccountNumber,
                 filedata.transactionData.cardHolderData.cardExpirationDate,
                 &filedata.transactionData.terminalData.maxTransAmount,
                 &filedata.transactionData.terminalData.transAmount,
                 &filedata.transactionData.transactionSequenceNumber ,
                 TrState);
    }
    fclose(pf);
}

void FileWriteTrData(ST_transaction_t *transData) {
    FILE *pf = NULL;
    char fl[200] = "C:\\Users\\user1\\CLionProjects\\FirstProject\\System\\DataBase\\Data\\TransactionData.txt";
    pf = fopen(fl, "a");
    if (pf == NULL) {
        printf("Error file is not opened");
        return;
    }
    char TrState[33];
    if (transData->transState == APPROVED) {
        strcpy(TrState, "APPROVED");
    } else if (transData->transState == DECLINED_INSUFFECIENT_FUND) {
        strcpy(TrState, "DECLINED_INSUFFECIENT_FUND");
    } else if (transData->transState == DECLINED_STOLEN_CARD) {
        strcpy(TrState, "DECLINED_STOLEN_CARD");
    } else if (transData->transState == FRAUD_CARD) {
        strcpy(TrState, "FRAUD_CARD");
    } else if (transData->transState == INTERNAL_SERVER_ERROR) {
        strcpy(TrState, "INTERNAL_SERVER_ERROR");
    }
    fprintf(pf,"%s;%s;%s; %.2f;%.2f;%d;%s\n",
            transData->cardHolderData.cardHolderName,
            transData->cardHolderData.primaryAccountNumber,
            transData->cardHolderData.cardExpirationDate,
            transData->terminalData.maxTransAmount,
            transData->terminalData.transAmount,
            transData->transactionSequenceNumber,
            TrState);

    fclose(pf);

}

void FileReadAccData(list *pl) {
    FILE *pf = NULL;
    char fl[200] = "C:\\Users\\user1\\CLionProjects\\FirstProject\\System\\DataBase\\Data\\AccountData.txt";
    pf = fopen(fl, "r");
    if (pf == NULL) {
        printf("Error file is not opened");
        return;
    }
    List_Entry Node;
    char state[8];
    while (fscanf(pf, "%25[^;];%19[^;];%5[^;];%f; %[^\n]s",
                  Node.accountData.name,
                  Node.accountData.primaryAccountNumber,
                  Node.accountData.ExDate,
                  &Node.accountData.balance, state) == 5) {
        if (strcmp(state, "BLOCKED") == 0) {
            Node.accountData.state = BLOCKED;
        } else {
            Node.accountData.state = RUNNING;
        }
        if (Node.accountData.name[0] == '\n') {
            // Shift the characters to the left to remove the newline
            memmove(Node.accountData.name, Node.accountData.name + 1, strlen(Node.accountData.name));
        }
        InsertList(pl, 0, Node);

    }
    fclose(pf);
}

void FileChangeBalance(ST_terminalData_t *termData, ST_accountsDB_t *accountReference, list *pl,ST_transaction_t *transData) {
    FILE *pf = NULL;
    char fl[200] = "C:\\Users\\user1\\CLionProjects\\FirstProject\\System\\DataBase\\Data\\AccountData.txt";
    pf = fopen(fl, "w");
    if (pf == NULL) {
        printf("Error file not opened");
        return;
    }
    listnode *Node;
    Node = pl->head;
    int Newbalance = 0;
    ST_accountsDB_t acc = Node->info.accountData;
    while (Node != NULL) {
        if (strcmp(accountReference->primaryAccountNumber, acc.primaryAccountNumber) == 0) {
            if(transData->op==1){
            Newbalance = accountReference->balance - termData->transAmount;
            accountReference->balance = Newbalance;
            acc.balance=Newbalance;}
            else{
                Newbalance = accountReference->balance + termData->transAmount;
                accountReference->balance = Newbalance;
                acc.balance=Newbalance;
            }
        }
        char AccState[8];
        if (acc.state == BLOCKED) {
            strcpy(AccState, "BLOCKED");
        } else if (acc.state == RUNNING) {
            strcpy(AccState, "RUNNING");
        }
        fprintf(pf, "%s;%s;%s;%f; %s\n", acc.name,
                acc.primaryAccountNumber,
                acc.ExDate,
                acc.balance ,
                AccState);
        if(Node->next==NULL){
            break;
        }
        Node = Node->next;
        acc = Node->info.accountData;
    }
    fclose(pf);
}