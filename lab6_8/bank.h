#ifndef _BANK_H_
#define _BANK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
     

#define STR_SIZE 256
#define SUCCESS 1
#define NOT_MEMORY -1
#define NOT_ENOUGH_MONEY -2
#define NOT_CLIENT -3
#define RECEIVER_NOT_CLIENT -4

typedef int32_t ID;

typedef struct _msg {
    ID client;
    int sum;
    int action;
    ID receiverClient;
    void *requester;
    char message[STR_SIZE];
    char fileName[STR_SIZE];
} MsgData;

typedef struct _client {
    ID client;
    int sum;
} *Client;

typedef struct _clientDB {
    Client clients;
    uint32_t size;
    uint32_t freespace;
} *ClientDB;

ClientDB ClientDBCreate(void);
void ClientAdd(ClientDB cDB, ID client);
void ClientDBPrint(ClientDB cDB);
Client ClientFind(ClientDB cDB, int clientint);
void ClientDBDestroy(ClientDB *cDB);

void ClientDBSave(ClientDB cDB, char *fileName);
void ClientDBLoad(ClientDB cDB, char *fileName);

void ClientAccIncrease(Client cl, int sum);
void ClientAccDecrease(Client cl, int sum);
int ClientHasEnoughMoney(Client cl, int sum);
void MoneyPut(int Clientint, int sum, ClientDB cDB);
int MoneyGet(int Clientint, int sum, ClientDB cDB);
int MoneySend(ID clientSender, ID clientReceiver, int sum, ClientDB cDB);
int CheckAccount(ID client, ClientDB cDB);

#endif
