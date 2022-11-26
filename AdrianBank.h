//
// Created by BMT on 11/16/2022.
//
#include "iostream"
#include "ctime"
using namespace std;
#ifndef PROJECTS_ADRIANBANK_H
#define PROJECTS_ADRIANBANK_H

namespace B{
    class bank{
    public:
        time_t now= time(0);
        char* dt= ctime(&now);
        int uNameIndex=0;
        int uPwIndex=0;
        int uAmountIndex=0;
        int uIdIndex=0;
        string mainChoice;
        string subChoice;
        string u_name[1000];
        string u_pw[1000];
        int u_amount[1000];
        int u_id[1000];
        string recordFileName="bankRecordFile.txt";
        string transitionRecordFile="transitions.txt";
        string depoRecordFile="deposit.txt";
        string loginName;
        //methods
        void welcome();
        void mainMenu();
        void reg();
        void login();
        int nameAlreadyExist(string user_name);
        int pwAlreadyExist(string user_password);
        void showData();
        void records();
        void recordsWrite();
        void mainLoading();
        void transfer();
        void idAssign();
        void subMenu();
        void deposit();
        void transitionRecord(string recipientName,int transferAmount);
        void depoRecord(int depoAmount);
        void adminMode();
        void changeInfo();
        void specificInfo();
        void infoById();
        void infoByName();
    };
}

#endif //PROJECTS_ADRIANBANK_H
