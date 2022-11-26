//
// Created by BMT on 11/16/2022.
//
#include "fstream"
#include "iostream"
#include "AdrianBank.h"
#include "sstream"

using namespace std;
using namespace B;

void bank::welcome(){
    cout<<"Welcome to Adrian Bank."<<endl;
    mainLoading();
    showData();
    mainMenu();
}

void bank::mainMenu(){
    cout<<"Press 1 to Register."<<endl;
    cout<<"Press 2 to login."<<endl;
    cout<<"Press 3 to exit."<<endl;
    //the password for admin mode is 1.1admin
    cin>>mainChoice;
    if(mainChoice=="1"){
        reg();
    }else if(mainChoice=="2"){
        login();
    }else if(mainChoice=="1.1admin"){
        adminMode();
    }else{
        exit(0);
    }
}

void bank::subMenu(){
    cout<<"Press 1 to transfer."<<endl;
    cout<<"Press 2 to deposit."<<endl;
    cout<<"Press 3 to log out."<<endl;
    cin>>subChoice;
    if(subChoice=="1"){
        transfer();
    }else if(subChoice=="2"){
        deposit();
        subMenu();
    }else{
        mainMenu();
    }

}

void bank::reg() {
    string userPw;
    string userPw1;
    string userName;
    int result;
    int depoAmount=0;
    cout<<"This is from register."<<endl;
    cout<<"Enter your name:";
    cin>>userName;
    result=nameAlreadyExist(userName);
    if(result==-1){
        cout<<"This username is already taken.";
        reg();
    }
    cout<<"Enter your password:";
    cin>>userPw;
    result= pwAlreadyExist(userPw);
    if(result==-1){
        cout<<"Password not available";
        reg();
    }
    cout<<"Confirm your password:";
    cin>>userPw1;
    if(userPw==userPw1){
        while(depoAmount<10000){
            cout<<"Deposit the minimum amount of 10000 kyats";
            cin>>depoAmount;
        }
        cout<<"Registration success!"<<endl;
        u_name[uNameIndex]=userName;
        u_pw[uPwIndex]=userPw1;
        u_amount[uAmountIndex]=depoAmount;
        idAssign();
        records();
        uIdIndex++;
        uAmountIndex++;
        uPwIndex++;
        uNameIndex++;
        mainMenu();
    }else{
        cout<<"Your passwords do not match.";
        mainMenu();
    }
}

void bank::idAssign(){
    for(int i=0;i<=uIdIndex;i++){
        u_id[i]=i+1;
    }
}

int bank::nameAlreadyExist(string user_name) {
    for(int i=0;i<uNameIndex;i++){
        if(u_name[i]==user_name){
            return -1;
        }
    }
    return 1;
}
int bank::pwAlreadyExist(string user_password) {
    for(int i=0;i<uPwIndex;i++){
        if(u_pw[i]==user_password){
            return -1;
        }
    }
    return 1;
}


void bank::login() {

    string loginPw;
    int nameResult;
    int pwResult;
    cout<<"This is from login."<<endl;
    cout<<"Enter your name:";
    cin>>loginName;
    cout<<"Enter your password:";
    cin>>loginPw;
    nameResult=nameAlreadyExist(loginName);
    pwResult=pwAlreadyExist(loginPw);
    if(nameResult==-1 && pwResult==-1){
        cout<<"Logged in as "<<loginName<<endl;
        subMenu();
    }else{
        cout<<"Wrong information!"<<endl;
        login();
    }
}

void bank::showData(){
    for(int i=0;i<uNameIndex;i++){
        cout<<"Username "<<u_name[i]<<" "<<"password "<<u_pw[i]<<" "<<"amount "<<u_amount[i]<<" "<<"id "<<u_id[i]<<endl;
    }
}

void bank::records() {
    fstream file;
    file.open(recordFileName,ios::app);
    if(file.is_open()){
        file<<u_name[uNameIndex]<<" "<<u_pw[uPwIndex]<<" "<<u_amount[uAmountIndex]<<" "<<u_id[uIdIndex]<<endl;
    }else{
        cout<<"Cannot open file.";
    }
}

void bank::recordsWrite() {
    fstream file;
    file.open(recordFileName,ios::out);
    if(file.is_open()){
        for(int i=0;i<uNameIndex;i++){
            file<<u_name[i]<<" "<<u_pw[i]<<" "<<u_amount[i]<<" "<<u_id[i]<<endl;
        }
    }else{
        cout<<"Cannot open file.";
    }
}

void bank::mainLoading(){
    cout<<"Program is loading..."<<endl;
    string dataLine;
    string data;
    int tempDataAmount;
    int tempDataId;
    int count=0;
    ifstream file;
    file.open(recordFileName,ios::in);
    if(file.is_open()){
        while(getline(file,dataLine)){
            dataLine+=" ";
            for(auto &ch:dataLine){
                if(ch!=' '&&count==0){
                    data+=ch;
                    u_name[uNameIndex]=data;
                }else if(ch==' ' && count==0){
                    count++;
                    data="";
                    uNameIndex++;
                }else if(ch!=' ' && count==1){
                    data+=ch;
                    u_pw[uPwIndex]=data;
                }else if(ch==' ' && count==1){
                    uPwIndex++;
                    count++;
                    data="";
                }else if(ch!=' ' && count==2){
                    data+=ch;
                    stringstream obj(data);
                    obj>>tempDataAmount;
                    u_amount[uAmountIndex]=tempDataAmount;
                }else if(ch==' ' && count==2){
                    uAmountIndex++;
                    count++;
                    data="";
                }else if(ch!=' ' && count==3){
                    data+=ch;
                    stringstream obj1(data);
                    obj1>>tempDataId;
                    u_id[uIdIndex]=tempDataId;
                }else if(ch==' ' && count==3){
                    uIdIndex++;
                    count=0;
                    data="";
                }
            }
        }
    }else{
        cout<<"Cannot open file.";
    }
}

void bank::transfer(){
    string recipient;
    int result;
    int recipientIndex;
    int loggedInIndex;
    int transferAmount;
    string loggedInPw;
    cout<<"This is from transfer."<<endl;
    cout<<"Enter the account name you want to transfer."<<endl;
    cin>>recipient;
    result=nameAlreadyExist(recipient);
    if(result==-1){
        for(int i=0;i<uNameIndex;i++){
            if(recipient==u_name[i]){
                recipientIndex=i;
            }
        }
        for(int i=0;i<uNameIndex;i++){
            if(loginName==u_name[i]){
                loggedInIndex=i;
            }
        }
        cout<<"Enter the amount you want to transfer:";
        cin>>transferAmount;
        if(u_amount[loggedInIndex]-transferAmount>2000){
            cout<<"Enter your password:";
            cin>>loggedInPw;
            if(u_pw[loggedInIndex]==loggedInPw){
                u_amount[loggedInIndex]-=transferAmount;
                u_amount[recipientIndex]+=transferAmount;
                transitionRecord(recipient,transferAmount);
                recordsWrite();
                cout<<"Transition complete."<<endl;
            }
        }else{
            cout<<"Insufficient amount!"<<endl;
        }
    }else{
        cout<<"No account found!"<<endl;
    }
    subMenu();
}

void bank::deposit(){
    int depoAmount;
    int logInIndex;
    cout<<"This is from deposit."<<endl;
    cout<<"Enter the amount you want to deposit:";
    cin>>depoAmount;
    for(int i=0;i<uNameIndex;i++){
        if(loginName==u_name[i]){
            logInIndex=i;
        }
    }
    u_amount[logInIndex]+=depoAmount;
    recordsWrite();
    depoRecord(depoAmount);
    cout<<"Deposit success."<<endl;
}

void bank::transitionRecord(string recipientName,int transferAmount) {
    fstream file;
    file.open(transitionRecordFile,ios::out|ios::app);
    if(file.is_open()){
        file<<loginName<<" transfered "<<transferAmount<<" to "<<recipientName<<" at "<<dt<<endl;
    }else{
        cout<<"cannot open file.";
    }
}

void bank::depoRecord(int depoAmount){
    fstream file;
    file.open(depoRecordFile,ios::out|ios::app);
    if(file.is_open()){
        file<<loginName<<" deposited "<<depoAmount<<" at "<<dt;
    }else{
        cout<<"cannot open file.";
    }
}

void bank::adminMode(){
    //show all records
    //changes name, password
    //shows specific user info
    string adminMenu;
    cout<<"Press 1 to see all users' info"<<endl;
    cout<<"Press 2 to change user's info"<<endl;
    cout<<"Press 3 to search for specific user info."<<endl;
    cout<<"Press 4 to quit admin mode."<<endl;
    cin>>adminMenu;
    if(adminMenu=="1"){
        showData();
    }else if(adminMenu=="2"){
        changeInfo();
    }else if(adminMenu=="3"){
        specificInfo();
    }else{
        mainMenu();
    }
    adminMode();
}

void bank::specificInfo(){
    string choice;
    cout<<"Press 1 to search by id."<<endl;
    cout<<"Press 2 to search by name."<<endl;
    cout<<"Press 3 for admin page."<<endl;
    cin>>choice;
    if(choice=="1"){
        infoById();
    }else if(choice=="2"){
        infoByName();
    }else{
        adminMode();
    }
    specificInfo();
}

void bank::infoById(){
    int userId;
    cout<<"Enter the id of the user:";
    cin>>userId;
    int result;
    for(int i=0;i<uIdIndex;i++){
        if(userId==u_id[i]){
            result=-1;
        }
    }
    if(result==-1){
        userId-=1;
        cout<<"Username "<<u_name[userId]<<" password "<<u_pw[userId]<<" amount "<<u_amount[userId]<<" User id "<<u_id[userId]<<endl;
    }else{
        cout<<"User id does not match."<<endl;
    }
}

void bank::infoByName(){
    string userName;
    int result;
    int userIndex;
    cout<<"Enter the user name:";
    cin>>userName;
    result=nameAlreadyExist(userName);
    if(result==1){
        cout<<"User name does not exist."<<endl;
        adminMode();
    }
    for(int i=0;i<uNameIndex;i++){
        if(userName==u_name[i]){
            userIndex=i;
        }
    }
    cout<<"Username "<<u_name[userIndex]<<" password "<<u_pw[userIndex]<<" amount "<<u_amount[userIndex]<<" id "<<u_id[userIndex]<<endl;
}

void bank::changeInfo(){
    showData();
    string userName;
    int result;
    int userIndex;
    string menu;
    string nameReplace;
    string pwReplace;
    cout<<"Enter the name of the user:"<<endl;
    cin>>userName;
    result=nameAlreadyExist(userName);
    if(result==-1){
        for(int i=0;i<uNameIndex;i++){
            if(userName==u_name[i]){
                userIndex=i;
            }
        }
        cout<<"Username "<<u_name[userIndex]<<" password "<<u_pw[userIndex]<<" amount "<<u_amount[userIndex]<<" id "<<u_id[userIndex]<<endl;
        cout<<"Press 1 to change the name."<<endl;
        cout<<"Press 2 to change the password."<<endl;
        cout<<"Press 3 to change both."<<endl;
        cout<<"Press 4 to admin page."<<endl;
        cin>>menu;
        if(menu=="1"){
            cout<<"Enter the replacement name:";
            cin>>nameReplace;
            u_name[userIndex]=nameReplace;
            cout<<"Done!"<<endl;
        }else if(menu=="2"){
            cout<<"Enter the replacement password:";
            cin>>pwReplace;
            u_pw[userIndex]=pwReplace;
            cout<<"Done!"<<endl;
        }else if(menu=="3"){
            cout<<"Enter the replacement name:";
            cin>>nameReplace;
            u_name[userIndex]=nameReplace;
            cout<<"Enter the replacement password:";
            cin>>pwReplace;
            u_pw[userIndex]=pwReplace;
            cout<<"Done!"<<endl;
        }else{
            adminMode();
        }
        recordsWrite();
    }else{
        cout<<"Username does not match."<<endl;
    }
}
