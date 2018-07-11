//
// Created by LooperXX on 2018/7/5.
//
#include <bits/stdc++.h>
using namespace std;
#define blocklength 128
#define M 4
#define B 10
queue<int> fifo;
int P[M];
bool Block[B];

class pageTable{
private:
    int pageNum;
    int flag;
    int blockNum;
    int changed;
    string pos;
public:
    pageTable(int pageNum, int flag, int blockNum, const string &pos) : pageNum(pageNum), flag(flag),
                                                                        blockNum(blockNum), pos(pos) {
        changed = 0;
    }

    int getChanged() const {
        return changed;
    }

    void setChanged(int changed) {
        pageTable::changed = changed;
    }

    const string &getPos() const {
        return pos;
    }

    void setPos(const string &pos) {
        pageTable::pos = pos;
    }

    int getPageNum() const {
        return pageNum;
    }

    void setPageNum(int pageNum) {
        pageTable::pageNum = pageNum;
    }

    int getFlag() const {
        return flag;
    }

    void setFlag(int flag) {
        pageTable::flag = flag;
    }

    int getBlockNum() const {
        return blockNum;
    }

    void setBlockNum(int blockNum) {
        pageTable::blockNum = blockNum;
    }
};

class order{
private:
    string oname;
    int pagenum;
    string unitNum;
public:
    order(const string &oname, int pagenum, const string &unitNum) : oname(oname), pagenum(pagenum), unitNum(unitNum) {}

    const string &getOname() const {
        return oname;
    }

    void setOname(const string &oname) {
        order::oname = oname;
    }

    int getPagenum() const {
        return pagenum;
    }

    void setPagenum(int pagenum) {
        order::pagenum = pagenum;
    }

    const string &getUnitNum() const {
        return unitNum;
    }

    void setUnitNum(const string &unitNum) {
        order::unitNum = unitNum;
    }

    void printOrder(){
        cout << "------------当前操作------------\n";
        cout << "操作\t" << "页号\t" << "单元号" << endl;
        cout << oname << "\t" << pagenum << "\t" << unitNum << endl;
    }
};

// 找到num对应的index
int findPosInP(int num){
    for(int i = 0; i < M; i++){
        if(num == P[i]){
            num = i;
        }
    }
    return num;
}

// 找到页号对应的页表项
pageTable* findPagePoint(vector<pageTable *> &pt, int curpageNum){
    for (auto &iter : pt) {
        if(iter->getPageNum() == curpageNum){
            return iter;
        }
    }
    return nullptr;
}

string transadd(int blockNum, string b){
    int b_dec = atoi(b.c_str());
    char b_binary[6];
    itoa(b_dec,b_binary,2);
    string b_str = b_binary;
    string res;
    for(int i = 0; i < 7 - b_str.length(); i++){
        res += "0";
    }
    res += b_str;
    char a[10];
    itoa(blockNum,a,2);
    string newA = a;
    return newA + res;
}

void printPageTable(vector<pageTable *> &pt){
    cout << "页号" << "\t" << "标志" << "\t" << "主存块号" << "\t" << "修改标志" << "\t"  << "在磁盘上的位置" << endl;
    for (auto &iter : pt) {
        cout << iter->getPageNum() << "\t" << iter->getFlag() << "\t" ;
        if(iter->getBlockNum() == -1){
            cout << "" << "\t\t" << iter->getChanged();
        }else{
            cout << iter->getBlockNum() << "\t\t" << iter->getChanged();
        }
        cout << "\t\t" << iter->getPos() << endl;
    }
}

void printOrderTable(vector<order *> &orderList){
    for (auto &iter : orderList) {
        cout << iter->getOname() << "\t" << iter->getPagenum() << "\t" << iter->getUnitNum() << endl;
    }
}

int main(){
    vector<pageTable*> pt;
    pt.push_back(new pageTable(0,1,5,"011"));
    pt.push_back(new pageTable(1,1,8,"012"));
    pt.push_back(new pageTable(2,1,9,"013"));
    pt.push_back(new pageTable(3,1,1,"021"));
    pt.push_back(new pageTable(4,0,-1,"022"));
    pt.push_back(new pageTable(5,0,-1,"023"));
    pt.push_back(new pageTable(6,0,-1,"121"));
    printPageTable(pt);
    cout << endl;
    vector <order*> orderList;
    orderList.push_back(new order("+",0,"070"));
    orderList.push_back(new order("+",1,"050"));
    orderList.push_back(new order("*",2,"015"));
    orderList.push_back(new order("存",3,"021"));
    orderList.push_back(new order("取",0,"056"));
    orderList.push_back(new order("-",6,"040"));
    orderList.push_back(new order("移位",4,"053"));
    orderList.push_back(new order("+",5,"023"));
    orderList.push_back(new order("存",1,"037"));
    orderList.push_back(new order("取",2,"078"));
    orderList.push_back(new order("+",4,"001"));
    orderList.push_back(new order("存",6,"084"));
    cout << "操作" << "\t" << "页号" << "\t" << "单元号" << endl;
    printOrderTable(orderList);
    cout << endl;
    for(int i = 0; i < M; i++){
        P[i] = i;
    }
    int K = 0;
    for(auto iter = orderList.begin(); iter != orderList.end(); iter++){
        order* cur = *iter;
        cur->printOrder();
        int curpageNum = cur->getPagenum();
        pageTable* res = findPagePoint(pt,curpageNum);
        // 缺页中断
        if(res->getFlag() == 0){
            cout << "*" << curpageNum << endl;
            if(!fifo.empty()){
                K = findPosInP(fifo.front());
                fifo.pop();
            }
            pageTable* outpoint = findPagePoint(pt,P[K]);
            outpoint->setFlag(0);
            int newBlockNum = outpoint->getBlockNum();
            outpoint->setBlockNum(-1);
            if(outpoint->getChanged() == 1){
                cout << "OUT: " << P[K] << endl;
                outpoint->setChanged(0);
            }
            P[K] = curpageNum;
            pageTable* inpoint = findPagePoint(pt,P[K]);
            inpoint->setFlag(1);
            inpoint->setBlockNum(newBlockNum);
            cout << "IN: " << P[K] << endl;
            K = (K + 1) % M;
            iter--;
        }else{
            if(strcmp("存",cur->getOname().data()) == 0){
                pageTable* point = findPagePoint(pt,curpageNum);
                point->setChanged(1);
            }
            cout << "绝对地址: " << transadd(res->getBlockNum(),cur->getUnitNum()) << endl;
            if(findPagePoint(pt,curpageNum)->getFlag() == 0){
                fifo.push(curpageNum);
            }
        }
        printPageTable(pt);
    }
    for(int p : P){
        cout << p << "\t";
    }
    cout << endl;
    system("pause");
    return 0;
}