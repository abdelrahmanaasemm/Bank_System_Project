
#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include "../../DS/List/list.h"

void FileReadTrData(list *pl);
void FileWriteTrData(ST_transaction_t *transData);
void FileReadAccData(list *pl);
void FileChangeBalance(ST_terminalData_t *termData, ST_accountsDB_t *accountReference, list *pl,ST_transaction_t *transData) ;
#endif //FILEHANDLING_H
