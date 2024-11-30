
#ifndef TERMINAL_H
#define TERMINAL_H
#include "../Card/Card.h"
#include <time.h>
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    char transactionDate[11];
}ST_terminalData_t;
typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT,WRONG_TERMINAL
}EN_terminalError_t ;
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t*
termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float
maxAmount);
EN_cardError_t isValidCardPAN(ST_cardData_t *cardData) ;

#endif //TERMINAL_H
