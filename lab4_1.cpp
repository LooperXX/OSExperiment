//
// Created by LooperXX on 2018/7/6.
//
#include <bits/stdc++.h>
using namespace std;
#define USERMAX 10
#define SAVEMAX 10
#define OPENMAX 5
// �����ļ�Ŀ¼
struct AFD {
    string fileName;
    int protectCode;
    int read;
    int write;
    AFD(string name, int code) :
            fileName(name), protectCode(code), read(0), write(0) {}
};

// �û��ļ�Ŀ¼
struct UFD{
    string fileName;
    int protectCode;
    int length;
    UFD(string name, int code) : fileName(name),protectCode(code),length(0){}
};

// ��Ŀ¼
struct MFD{
    string userName;
    vector<UFD> UFD;
    MFD(string uName): userName(uName){}
};

void printSaveFileList();

void printOpenFileList();

void createFile();

bool checkFileName(string basic_string);

void deleteFile();

vector<UFD>::iterator getFileIndex(const string &fileName);

void openFile();

void closeFile();

bool checkRunFileName(const string &basic_string);

void writeFile();

vector<AFD>::iterator getRunFileIndex(string basic_string);

void readFile();

vector<MFD> mfd;
vector<AFD> afd;
MFD* userMFD;

void showMenuHead(){
    cout << "+-------------------------------------+" << endl;
    cout << "|               �ļ�ϵͳ               |" << endl;
    cout << "+-------------------------------------+" << endl;
}

void showMenu(){
    showMenuHead();
    cout << "[Input]�����������û���:" << endl;
    string input;
    cin >> input;
    bool find = false;
    for(auto u : mfd){
        if(strcmp(u.userName.data(),input.data()) == 0){
            find = true;
            userMFD = &u;
        }
    }
    if(!find){
        cout << "[Wrong]ϵͳ�޴��û�:<" << endl;
        showMenu();
    }else{
        bool quit = false;
        while(!quit){
            showMenuHead();
            cout << "| 1.�鿴�����ļ�Ŀ¼" << endl;
            cout << "| 2.�鿴���ļ�Ŀ¼" << endl;
            cout << "| 3.�½��ļ�" << endl;
            cout << "| 4.ɾ���ļ�" << endl;
            cout << "| 5.���ļ�" << endl;
            cout << "| 6.�ر��ļ�" << endl;
            cout << "| 7.��ȡ�ļ�" << endl;
            cout << "| 8.д���ļ�" << endl;
            cout << "| 0.�˳�" << endl;
            cout << "+-------------------------------------+" << endl;
            int op;
            cin >> op;
            switch (op){
                case 1:
                    printSaveFileList();
                    break;
                case 2:
                    printOpenFileList();
                    break;
                case 3:
                    createFile();
                    break;
                case 4:
                    deleteFile();
                    break;
                case 5:
                    openFile();
                    break;
                case 6:
                    closeFile();
                    break;
                case 7:
                    readFile();
                    break;
                case 8:
                    writeFile();
                    break;
                case 0:
                    quit = true;
                    break;
                default:
                    cout << "[Wrong]������������!:<" << endl;
                    break;
            }
        }

    }
}

void readFile() {
    string readFileName;
    int len = 0;
    cout << "[Input]�����������ȡ���ļ����Ƽ���ȡ���ȣ�" << endl;
    cin >> readFileName >> len;
    if(!checkRunFileName(readFileName)){
        cout << "[Wrong]��������ļ����������Ѵ��ļ���Ŀ¼��:<" << endl;
        return;
    }
    auto iter = getRunFileIndex(readFileName);
    if(iter->protectCode % 100 != 1){
        cout << "[Wrong]��û�ж�ȡȨ��:<" << endl;
        return;
    }
    auto iterFile = getFileIndex(readFileName);
    iterFile->length += len;
    iter->read = len;
    cout << "[Success]���ѳɹ���ȡ" << readFileName << "����ȡ����: " << len << ":>" << endl;
}

void writeFile() {
    string writeFileName;
    int len = 0;
    cout << "[Input]����������д����ļ����Ƽ�д�볤�ȣ�" << endl;
    cin >> writeFileName >> len;
    if(!checkRunFileName(writeFileName)){
        cout << "[Wrong]��������ļ����������Ѵ��ļ���Ŀ¼��:<" << endl;
        return;
    }
    auto iter = getRunFileIndex(writeFileName);
    if(iter->protectCode %10/10 != 1){
        cout << "[Wrong]��û��д��Ȩ��:<" << endl;
        return;
    }
    auto iterFile = getFileIndex(writeFileName);
    iterFile->length += len;
    iter->write = len;
    cout << "[Success]���ѳɹ�д��" << writeFileName << "�У�д�볤��: " << len << ":>" << endl;
}

void closeFile() {
    if(afd.empty()){
        cout << "[Wrong]����û�д򿪹��ļ�:<" << endl;
        return;
    }
    string closeFileName;
    cout << "[Input]����������رյ��ļ����ƣ�";
    cin >> closeFileName;
    if(!checkRunFileName(closeFileName)){
        cout << "[Wrong]��������ļ����������Ѵ��ļ���Ŀ¼��:<" << endl;
        return;
    }
    afd.erase(getRunFileIndex(closeFileName));
    cout << "[Success]���ѳɹ��ر��ļ�:>" << endl;
}

vector<AFD>::iterator getRunFileIndex(string fileName) {
    for(auto iter = afd.begin(); iter != afd.end(); iter++){
        if(strcmp((*iter).fileName.c_str(),fileName.c_str()) == 0)
            return iter;
    }
}

bool checkRunFileName(const string &fileName) {
    for (const auto &item : afd) {
        if (strcmp(item.fileName.c_str(),fileName.c_str()) == 0)
            return true;
    }
    return false;
}

void openFile() {
    if(afd.size() > OPENMAX){
        cout << "[Wrong]���򿪵��ļ��Ѵﵽ����:<" << endl;
        return;
    }
    string openFileName;
    cout << "[Input]����������򿪵��ļ����ƣ�";
    cin >> openFileName;
    if(!checkFileName(openFileName)){
        cout << "[Wrong]��������ļ������������ļ�Ŀ¼��:<" << endl;
        return;
    }
    // �����������ļ�Ŀ¼
    auto iter = getFileIndex(openFileName);
    afd.emplace_back(iter->fileName, iter->protectCode);
    cout << "[Success]���ѳɹ����ļ�:>" << endl;
}

void deleteFile() {
    string deleteFileName;
    cout << "[Input]����������ɾ�����ļ����ƣ�";
    cin >> deleteFileName;
    if(!checkFileName(deleteFileName)){
        cout << "[Wrong]��������ļ������������ļ�Ŀ¼��:<" << endl;
        return;
    }
    userMFD->UFD.erase(getFileIndex(deleteFileName));
    if(checkRunFileName(deleteFileName)){
        afd.erase(getRunFileIndex(deleteFileName));
    }
    cout << "[Success]���ѳɹ�ɾ���ļ�:>" << endl;
}

vector<UFD>::iterator getFileIndex(const string &fileName) {
    for(auto iter = userMFD->UFD.begin(); iter != userMFD->UFD.end(); iter++){
        if(strcmp((*iter).fileName.c_str(),fileName.c_str()) == 0)
            return iter;
    }
}

void createFile() {
    string newFileName;
    int protectCode;
    if(userMFD->UFD.size() > SAVEMAX){
        cout << "[Wrong]��������ļ��Ѵﵽ����:<" << endl;
        return;
    }
    cout << "[Input]���������ļ����Ƽ�����Ȩ�ޣ�";
    cin >> newFileName >> protectCode;
    if(checkFileName(newFileName)){
        cout << "[Wrong]��������ļ����Ѵ���:<" << endl;
        return;
    }
    (userMFD->UFD).emplace_back(newFileName, protectCode);
    cout << "[Success]���ѳɹ��½��ļ�:>" << endl;
}

bool checkFileName(string newName) {
    for (auto iter = userMFD->UFD.begin(); iter != userMFD->UFD.end(); iter++) {
        if (strcmp((*iter).fileName.c_str(),newName.c_str()) == 0)
            return true;
    }
    return false;
}

void printOpenFileList() {
    showMenuHead();
    cout << "+-------------------------------------+" << endl;
    cout << "|            �Ѵ��ļ�Ŀ¼            |" << endl;
    cout << "+-------------------------------------+" << endl;
    if(afd.empty()){
        cout << "| Ŀ¼Ϊ��" << endl;
        return;
    }
    for(auto &afdItem : afd){
        cout << "| �ļ��� \t|" << afdItem.fileName << endl;
        cout << "| ������ \t|" << afdItem.protectCode << endl;
        cout << "| ��ָ�� \t|" << afdItem.read << endl;
        cout << "| дָ�� \t|" << afdItem.write << endl;
    }
    cout << endl;
}

void printSaveFileList() {
    showMenuHead();
    cout << "+-------------------------------------+" << endl;
    cout << "|            �û������ļ�Ŀ¼           |" << endl;
    cout << "+-------------------------------------+" << endl;
    if (userMFD->UFD.empty()) {
        cout << "| Ŀ¼Ϊ��" << endl;
        return;
    }
    for (auto &ufd : userMFD->UFD) {
        cout << "***********************" << endl;
        cout << "| �ļ�����" << ufd.fileName << "; \t|" << endl;
        cout << "| �����룺" << ufd.protectCode << "; \t|" << endl;
        cout << "| �ļ����ȣ�" << ufd.length << "; \t|" << endl;
        cout << "***********************" << endl;
    }
    cout << endl;
}

void initSys(vector<MFD> &mfd) {
    mfd.emplace_back("user1");
    mfd.emplace_back("user2");
    mfd.emplace_back("user3");
    mfd.emplace_back("user4");
    mfd.emplace_back("user5");
    mfd.emplace_back("user6");
    mfd.emplace_back("user7");
    mfd.emplace_back("user8");
    mfd.emplace_back("user9");
    mfd.emplace_back("user10");
}


int main(){
    initSys(mfd);
    showMenu();
}

