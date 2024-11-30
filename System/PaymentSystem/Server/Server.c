#include "Server.h"

EN_transState_t recieveTransactionData(struct ST_transaction_t *transData) {
    list AccList, TrList;
    CreateList(&TrList);
    CreateList(&AccList);
    FileReadAccData(&AccList);
    EN_serverError_t Error = APPROVED;
    transData->transState = Error;
    FileReadTrData(&TrList);

    ST_accountsDB_t Account;
    EN_serverError_t accError = isValidAccount(&AccList, &transData->cardHolderData, &Account);
    if (accError == ACCOUNT_NOT_FOUND) {
        transData->transState = FRAUD_CARD;
        saveTransaction(transData, &TrList);
        return FRAUD_CARD;
    }
    if (transData->op == 1) {
        if (isAmountAvailable(&transData->terminalData, &Account) == LOW_BALANCE) {
            transData->transState = DECLINED_INSUFFECIENT_FUND;
            saveTransaction(transData, &TrList);
            return DECLINED_INSUFFECIENT_FUND;
        }
    }
    if (isBlockedAccount(&Account) == BLOCKED_ACCOUNT) {
        transData->transState = DECLINED_STOLEN_CARD;
        saveTransaction(transData, &TrList);
        return DECLINED_STOLEN_CARD;
    }

    EN_terminalError_t ExdateError = isCardExpired(&transData->cardHolderData, &transData->terminalData);
    if (ExdateError == EXPIRED_CARD) {
        transData->transState = INTERNAL_SERVER_ERROR;
        saveTransaction(transData, &TrList);
        return INTERNAL_SERVER_ERROR;
    }
    if (transData->transState == APPROVED) {
        saveTransaction(transData, &TrList);
        FileChangeBalance(&transData->terminalData, &Account, &AccList,transData);
    }

}

EN_serverError_t isValidAccount(list *pl, ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence) {
    listnode *p = pl->head;

    while (p != NULL) {
        ST_accountsDB_t GetAccData = p->info.accountData;

        if ((strcmp(cardData->cardHolderName, GetAccData.name) == 0)) {
            int size = strlen(GetAccData.primaryAccountNumber);
            if (!(strncmp(cardData->primaryAccountNumber, GetAccData.primaryAccountNumber, size))) {
                *accountRefrence = GetAccData;
                return SERVER_OK;
            }
        }
        p = p->next;
    }
    accountRefrence = NULL;
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence) {
    if (accountRefrence->state == BLOCKED) {
        return BLOCKED_ACCOUNT;
    } else {
        return SERVER_OK;
    }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence) {
    if (termData->transAmount > accountRefrence->balance) {
        return LOW_BALANCE;
    } else {
        return SERVER_OK;
    }
}

EN_serverError_t saveTransaction(struct ST_transaction_t *transData, list *PtoTrData) {
    listnode *p = PtoTrData->head;
    int SqNumber = 0;
    while (p != NULL) {
        if (strcmp(transData->cardHolderData.primaryAccountNumber,
                   p->info.transactionData.cardHolderData.primaryAccountNumber) == 0) {
            SqNumber = transData->transactionSequenceNumber + 1;
            transData->transactionSequenceNumber = SqNumber;
        }
        p = p->next;
    }

    FileWriteTrData(transData);
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
    listSavedTransactions(transData, TrState);

}

void listSavedTransactions(ST_transaction_t *transData, char TrState[28]) {
    printf("\t\t\t================================\nCardholder Name: %s\n", transData->cardHolderData.cardHolderName);
    printf("Primary Account Number: %s\n", transData->cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date: %5s\n", transData->cardHolderData.cardExpirationDate);
    printf("Transaction Amount: %.2f\n", transData->terminalData.transAmount);
    printf("Max Transaction Amount: %.2f\n", transData->terminalData.maxTransAmount);
    printf("Transaction Date: %s\n", transData->terminalData.transactionDate);
    printf("Transaction State: %s\n", TrState);
    printf("Transaction Sequence Number: %d\n\t\t\t================================", transData->transactionSequenceNumber);
}