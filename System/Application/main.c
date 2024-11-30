#include <stdio.h>
#include "../PaymentSystem/Server/Server.h"

int main() {

    ST_cardData_t Card;
    EN_cardError_t CError;
    CError = getCardHolderName(&Card);
    if (CError != CARD_OK) {
        printf("Error your name is not valid");
        return 0;
    }
    CError = getCardPAN(&Card);
    if (CError != CARD_OK) {
        printf("Error your PAN is not valid");
        return 0;
    }
    EN_terminalError_t VPan = isValidCardPAN(&Card);
    if (VPan == WRONG_PAN) {
        printf("\n!!!!!!!!!!!!!!!!!!Your PAN is not valid!!!!!!!!!!!!!!!!!!\n");
        return 0;
    }
    CError = getCardExpiryDate(&Card);
    if (CError != CARD_OK) {
        printf("\n!!!!!!!!!!!!!!!!!!Error your PAN is not valid!!!!!!!!!!!!!!!!!!\n");
        return 0;
    }
    ST_terminalData_t Terminal;
    getTransactionDate(&Terminal);
    EN_terminalError_t ExDateError = isCardExpired(&Card, &Terminal);
    if (ExDateError == EXPIRED_CARD) {
        printf("Declined Expired Card");
        return 0;
    }
    getTransactionAmount(&Terminal);

        EN_terminalError_t mxError =setMaxAmount(&Terminal, 100000.000000);

    if(Terminal.transAmount>Terminal.maxTransAmount){
        printf("\n!!!!!!!!!!!!!!!!!!Declined Amount Exceeding limit!!!!!!!!!!!!!!!!!!\n");
        return 0;
    }
    int operation;
    int n=3;
    while (n--) {
        printf("\t\t\t================================\nPlease Enter the operation\nif you want withdrawal enter 1\nif you want deposit enter 2 : ");
        scanf("%d",&operation );
        if(operation!=1&&operation!=2){
            printf("\nThis is not available\n");
        }else{
            break;
        }
        if(n==0&&operation!=1&&operation!=2){
            printf("\n!!!!!!!!!!!!!!!!!!Invalid operation!!!!!!!!!!!!!!!!!!\n");
        }
        }

    EN_terminalError_t isbelowmax = isBelowMaxAmount(&Terminal);
    if (isbelowmax == EXCEED_MAX_AMOUNT) {
        printf("\n!!!!!!!!!!!!!!!!!!Declined Amount Exceeding Limit!!!!!!!!!!!!!!!!!!\n");
        return 0;
    }
    ST_transaction_t transData;
    transData.cardHolderData = Card;
    transData.terminalData = Terminal;
    transData.op=operation;
    recieveTransactionData(&transData);

}

