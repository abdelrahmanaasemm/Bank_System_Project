
#ifndef CARD_H
#define CARD_H
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include <math.h>
#include <ctype.h>
#define CARD_NAME_MIN 20
#define CARD_NAME_MAX 24
#define CARD_EXPIRE 5
#define CARD_PAN_MAX 19
#define CARD_PAN_MIN 16
typedef struct ST_cardData_t
{
    char cardHolderName[25];
    char primaryAccountNumber[20];
    char cardExpirationDate[6];
}ST_cardData_t;
typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN,WRONG_DATA
}EN_cardError_t;
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif //CARD_H
