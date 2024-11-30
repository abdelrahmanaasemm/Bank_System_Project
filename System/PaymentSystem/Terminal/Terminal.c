#include "Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
    if(termData==NULL){
        printf("Error NULL POINTER");
        return WRONG_TERMINAL;
    }
    time_t current_time = time(NULL);
    strftime(termData->transactionDate, 11, "%d/%m/%Y", localtime(&current_time));
    printf("\t\t\t================================\nThe current date is:%s \n"
           "\t\t\t================================\n", termData->transactionDate);

    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData) {
    if(termData==NULL){
        printf("Error NULL POINTER");
        return WRONG_TERMINAL;
    }
    EN_terminalError_t Error = EXPIRED_CARD;
    int ExMonth = (cardData->cardExpirationDate[0] - '0') * 10 + cardData->cardExpirationDate[1] - '0';
    int ExYear = (cardData->cardExpirationDate[3] - '0') * 10 + cardData->cardExpirationDate[4] - '0' + 2000;
    int TrMonth;
    if (termData->transactionDate[3] - '0' == 0) {
        TrMonth = termData->transactionDate[4] - '0';
    } else {
        TrMonth = (termData->transactionDate[3] - '0') * 10 + termData->transactionDate[4] - '0';
    }
    int TrYear = (termData->transactionDate[6] - '0') * 1000 + (termData->transactionDate[7] - '0') * 100 +
                 (termData->transactionDate[8] - '0') * 10 + termData->transactionDate[9] - '0';
    if (TrYear == ExYear) {
        if (TrMonth > ExMonth) {
            return Error;
        } else {
            Error = TERMINAL_OK;
            return Error;
        }
    } else if (TrYear > ExYear) {
        return Error;
    } else {
        Error = TERMINAL_OK;
        return Error;
    }

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData) {
    if(termData==NULL){
        printf("Error NULL POINTER");
        return WRONG_TERMINAL;
    }
    EN_terminalError_t Error = INVALID_AMOUNT;
    int n = 3;
    while (n--) {

        printf("\t\t\t================================\nPlease Enter The Transaction amount and\nyou should know that Transaction amount\nmust be a positive value not 0 or negative value : ");
        scanf("%f", &termData->transAmount);
        fflush(stdin);
        fflush(stdout);
        if (termData->transAmount <= 0) {
            if (n == 0)
                return Error;
        } else {
            Error = TERMINAL_OK;
            return Error;
        }
    }
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {
    if(termData==NULL){
        printf("Error NULL POINTER");
        return WRONG_TERMINAL;
    }
    EN_terminalError_t Error = EXCEED_MAX_AMOUNT;
    if (termData->transAmount > termData->maxTransAmount) {
        return Error;
    } else {
        Error = TERMINAL_OK;
        return Error;
    }

}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount) {
    if(termData==NULL){
        printf("Error NULL POINTER");
        return WRONG_TERMINAL;
    }
    EN_terminalError_t Error = INVALID_MAX_AMOUNT;

        termData->maxTransAmount = maxAmount;
        if (termData->maxTransAmount <= 0) {
                return Error;
        } else {
            Error = TERMINAL_OK;
            return Error;
        }


}

EN_cardError_t isValidCardPAN(ST_cardData_t *cardData) {
    if(cardData==NULL){
        printf("Error NULL POINTER");
        return WRONG_DATA;
    }
    EN_cardError_t Error = CARD_OK;
    long long sum = 0;
    int flag = 0;
    for (int i = strlen(cardData->primaryAccountNumber )-1; i >= 0; --i) {
        int number = cardData->primaryAccountNumber[i] - '0';
        if (flag) {
            number *= 2;
            if (number > 9) {
                number -= 9;
            }
        }
        sum += number;
        flag = !flag;

    }
    if (sum % 10 == 0) {
    } else {
        Error = WRONG_PAN;
    }

    return Error;

}// Optional
