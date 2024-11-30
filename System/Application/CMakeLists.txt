cmake_minimum_required(VERSION 3.24)
project(Application C)

set(CMAKE_C_STANDARD 11)

add_executable(Application main.c  ../PaymentSystem/Card/Card.c ../PaymentSystem/Terminal/Terminal.c  ../PaymentSystem/Card/Card.h  ../PaymentSystem/Server/Server.h ../PaymentSystem/Server/Server.c ../PaymentSystem/Terminal/Terminal.h ../PaymentSystem/Server/Server.h ../DS/List/list.h ../DS/List/list.c ../DataBase/File_Handling/FileHandling.c ../DataBase/File_Handling/FileHandling.h ../PaymentSystem/Server/Server.h ../DataBase/Data/AccountData.txt ../DataBase/Data/TransactionData.txt ../PaymentSystem/Server/Server.h ../PaymentSystem/Server/Server.h ../PaymentSystem/Server/Server.h ../PaymentSystem/Card/Card.h ../PaymentSystem/Terminal/Terminal.h ../PaymentSystem/Terminal/Terminal.h ../PaymentSystem/Terminal/Terminal.h ../DS/List/list.h ../PaymentSystem/Server/Server.h ../PaymentSystem/Card/Card.h ../PaymentSystem/Terminal/Terminal.h)
