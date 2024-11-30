#include "Card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
    if(cardData==NULL){
        printf("Error NULL POINTER");
        return WRONG_DATA;
    }
    int n = 3;
    while (n--) {
        EN_cardError_t Error = WRONG_NAME;
        printf("\t\t\t================================"
               "\nPlease Enter Your Card Name and you should know that\nyour name must be at least 20 alphabet and max 24  : ");
        scanf("%[^\n]s", cardData->cardHolderName);
        fflush(stdin);
        fflush(stdout);
        if (strlen(cardData->cardHolderName) < CARD_NAME_MIN || strlen(cardData->cardHolderName) > CARD_NAME_MAX) {
            printf("\n!!!!!!!!!!!!!!!!!!Invalid Name!!!!!!!!!\n");
            if (n == 0)
                return Error;
            continue;
        } else {
            return CARD_OK;
        }
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
    if(cardData==NULL){
        printf("Error NULL POINTER");
        return WRONG_DATA;
    }
    int n = 3;
    EN_cardError_t Error = WRONG_EXP_DATE;
    while (n--) {
        printf("\t\t\t================================\nPlease Enter Your Card Expire Date in this format\nMM/YY MM is month and YY is year and slash is very important : ");
        scanf("%[^\n]s", cardData->cardExpirationDate);
        fflush(stdin);
        fflush(stdout);
        int month = (cardData->cardExpirationDate[0] - '0') * 10 + cardData->cardExpirationDate[1] - '0';
        int year = (cardData->cardExpirationDate[3] - '0') * 10 + cardData->cardExpirationDate[4] - '0';
        if (cardData->cardExpirationDate[2] != '/' || strlen(cardData->cardExpirationDate) > CARD_EXPIRE ||
            strlen(cardData->cardExpirationDate) < CARD_EXPIRE || month > 12 || month < 1 || year < 0 || year > 99) {
            printf("!!!!!!!!!you should know that month must not exceed 12 and\nyear must not exceed 99!!!!!!!!!\n");
            if (n == 0)
                return Error;
            continue;
        } else {
            for (int i = 0; i < 5; ++i) {
                if (i == 2) {
                    continue;
                }
                if (0 != isdigit(cardData->cardExpirationDate[i])) {
                } else {
                    if (n == 0)
                        return Error;
                    break;
                }
                if(i==n-1){
                    Error = CARD_OK;
                    return Error;
                }
            }

        }
    }

}

EN_cardError_t getCardPAN(ST_cardData_t *cardData) {
    if(cardData==NULL){
        printf("Error NULL POINTER");
        return WRONG_DATA;
    }
    int n=3;
    EN_cardError_t Error = WRONG_PAN;
    for (int i = 0; i < 20; ++i) {
        cardData->primaryAccountNumber[i]='\0';
    }
    while (n--) {
        printf("\t\t\t================================\nPlease Enter Your Card Primary Account Number(PAN) and you should know \nthat your PAN must be at least 16 alphabet and max 19 : ");
        scanf("%[^\n]s", cardData->primaryAccountNumber);
        fflush(stdin);
        fflush(stdout);
        if (strlen(cardData->primaryAccountNumber) < CARD_PAN_MIN ||
            strlen(cardData->primaryAccountNumber) > CARD_PAN_MAX) {

        } else {
            for (int i = 0; i < strlen(cardData->primaryAccountNumber); ++i) {
                if (0 != isdigit(cardData->primaryAccountNumber[i])) {
                    if (i == strlen(cardData->primaryAccountNumber) - 1) {
                        return CARD_OK;
                    }
                } else {
                    break;
                }

            }

        }
    }
    return Error;

}

