//
// Created by user1 on 8/2/2024.
//

#ifndef SERVER_H
#define SERVER_H
#include "../../DataBase/File_Handling/FileHandling.h"

typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND,
    LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

EN_transState_t recieveTransactionData(struct ST_transaction_t *transData);
EN_serverError_t isValidAccount(list *pl,ST_cardData_t *cardData, ST_accountsDB_t*
accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,
                                   ST_accountsDB_t* accountRefrence);
EN_serverError_t saveTransaction(struct ST_transaction_t *transData,list *PtoTrData);
void listSavedTransactions(ST_transaction_t *transData,char TrState[28]);
#endif //SERVER_H
