//
// Created by LooperXX on 2018/7/6.
//
#include <bits/stdc++.h>
using namespace std;
#define USERMAX 10
#define SAVEMAX 10
#define OPENMAX 5
// 运行文件目录
struct AFD {
    string fileName;
    int protectCode;
    int read;
    int write;
    AFD(string name, int code) :
            fileName(name), protectCode(code), read(0), write(0) {}
};

// 用户文件目录
struct UFD{
    string fileName;
    int protectCode;
    int length;
    UFD(string name, int code) : fileName(name),protectCode(code),length(0){}
};

// 主目录
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
    cout << "|               文件系统               |" << endl;
    cout << "+-------------------------------------+" << endl;
}

void showMenu(){
    showMenuHead();
    cout << "[Input]请输入您的用户名:" << endl;
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
        cout << "[Wrong]系统无此用户:<" << endl;
        showMenu();
    }else{
        bool quit = false;
        while(!quit){
            showMenuHead();
            cout << "| 1.查看保存文件目录" << endl;
            cout << "| 2.查看打开文件目录" << endl;
            cout << "| 3.新建文件" << endl;
            cout << "| 4.删除文件" << endl;
            cout << "| 5.打开文件" << endl;
            cout << "| 6.关闭文件" << endl;
            cout << "| 7.读取文件" << endl;
            cout << "| 8.写入文件" << endl;
            cout << "| 0.退出" << endl;
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
                    cout << "[Wrong]您的输入有误!:<" << endl;
                    break;
            }
        }

    }
}

void readFile() {
    string readFileName;
    int len = 0;
    cout << "[Input]请输入您想读取的文件名称及读取长度：" << endl;
    cin >> readFileName >> len;
    if(!checkRunFileName(readFileName)){
        cout << "[Wrong]您输入的文件名不在您已打开文件的目录中:<" << endl;
        return;
    }
    auto iter = getRunFileIndex(readFileName);
    if(iter->protectCode % 100 != 1){
        cout << "[Wrong]您没有读取权限:<" << endl;
        return;
    }
    auto iterFile = getFileIndex(readFileName);
    iterFile->length += len;
    iter->read = len;
    cout << "[Success]您已成功读取" << readFileName << "，读取长度: " << len << ":>" << endl;
}

void writeFile() {
    string writeFileName;
    int len = 0;
    cout << "[Input]请输入您想写入的文件名称及写入长度：" << endl;
    cin >> writeFileName >> len;
    if(!checkRunFileName(writeFileName)){
        cout << "[Wrong]您输入的文件名不在您已打开文件的目录中:<" << endl;
        return;
    }
    auto iter = getRunFileIndex(writeFileName);
    if(iter->protectCode %10/10 != 1){
        cout << "[Wrong]您没有写入权限:<" << endl;
        return;
    }
    auto iterFile = getFileIndex(writeFileName);
    iterFile->length += len;
    iter->write = len;
    cout << "[Success]您已成功写入" << writeFileName << "中，写入长度: " << len << ":>" << endl;
}

void closeFile() {
    if(afd.empty()){
        cout << "[Wrong]您并没有打开过文件:<" << endl;
        return;
    }
    string closeFileName;
    cout << "[Input]请输入您想关闭的文件名称：";
    cin >> closeFileName;
    if(!checkRunFileName(closeFileName)){
        cout << "[Wrong]您输入的文件名不在您已打开文件的目录中:<" << endl;
        return;
    }
    afd.erase(getRunFileIndex(closeFileName));
    cout << "[Success]您已成功关闭文件:>" << endl;
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
        cout << "[Wrong]您打开的文件已达到上限:<" << endl;
        return;
    }
    string openFileName;
    cout << "[Input]请输入您想打开的文件名称：";
    cin >> openFileName;
    if(!checkFileName(openFileName)){
        cout << "[Wrong]您输入的文件名不在您的文件目录中:<" << endl;
        return;
    }
    // 更新已运行文件目录
    auto iter = getFileIndex(openFileName);
    afd.emplace_back(iter->fileName, iter->protectCode);
    cout << "[Success]您已成功打开文件:>" << endl;
}

void deleteFile() {
    string deleteFileName;
    cout << "[Input]请输入您想删除的文件名称：";
    cin >> deleteFileName;
    if(!checkFileName(deleteFileName)){
        cout << "[Wrong]您输入的文件名不在您的文件目录中:<" << endl;
        return;
    }
    userMFD->UFD.erase(getFileIndex(deleteFileName));
    if(checkRunFileName(deleteFileName)){
        afd.erase(getRunFileIndex(deleteFileName));
    }
    cout << "[Success]您已成功删除文件:>" << endl;
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
        cout << "[Wrong]您保存的文件已达到上限:<" << endl;
        return;
    }
    cout << "[Input]请输入新文件名称及其与权限：";
    cin >> newFileName >> protectCode;
    if(checkFileName(newFileName)){
        cout << "[Wrong]您输入的文件名已存在:<" << endl;
        return;
    }
    (userMFD->UFD).emplace_back(newFileName, protectCode);
    cout << "[Success]您已成功新建文件:>" << endl;
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
    cout << "|            已打开文件目录            |" << endl;
    cout << "+-------------------------------------+" << endl;
    if(afd.empty()){
        cout << "| 目录为空" << endl;
        return;
    }
    for(auto &afdItem : afd){
        cout << "| 文件名 \t|" << afdItem.fileName << endl;
        cout << "| 保护码 \t|" << afdItem.protectCode << endl;
        cout << "| 读指针 \t|" << afdItem.read << endl;
        cout << "| 写指针 \t|" << afdItem.write << endl;
    }
    cout << endl;
}

void printSaveFileList() {
    showMenuHead();
    cout << "+-------------------------------------+" << endl;
    cout << "|            用户保存文件目录           |" << endl;
    cout << "+-------------------------------------+" << endl;
    if (userMFD->UFD.empty()) {
        cout << "| 目录为空" << endl;
        return;
    }
    for (auto &ufd : userMFD->UFD) {
        cout << "***********************" << endl;
        cout << "| 文件名：" << ufd.fileName << "; \t|" << endl;
        cout << "| 保护码：" << ufd.protectCode << "; \t|" << endl;
        cout << "| 文件长度：" << ufd.length << "; \t|" << endl;
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

