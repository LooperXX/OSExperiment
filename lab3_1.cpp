//
// Created by LooperXX on 2018/7/4.
//
#include <bits/stdc++.h>
using namespace std;
#define pip(a,b) pair<int,pageTable*>(a,b)
#define pio(a,b) pair<int,order*>(a,b)
#define blocklength 128

class pageTable{
private:
    int pageNum;
    int flag;
    int blockNum;
    string pos;
public:
    pageTable(int pageNum, int flag, int blockNum, const string &pos) : pageNum(pageNum), flag(flag),
                                                                        blockNum(blockNum), pos(pos) {}

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
        cout << "------------��ǰ����------------\n";
        cout << "����\t" << "ҳ��\t" << "��Ԫ��" << endl;
        cout << oname << "\t" << pagenum << "\t" << unitNum << endl;
    }
};

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

int findPage(vector<pageTable *> pt, int pageNum) {
    for(auto iter = pt.begin();iter != pt.end(); iter++){
        if((*iter)->getPageNum() == pageNum){
            return (*iter)->getBlockNum();
        }
    }
    return -1;
}

void printPageTable(vector<pageTable *> pt){
    for(auto iter = pt.begin();iter != pt.end(); iter++){
        cout <<(*iter)->getPageNum() << "\t" << (*iter)->getFlag() << "\t" ;
        if((*iter)->getBlockNum() == -1){
            cout << "" << "\t\t" << (*iter)->getPos() << endl;
        }else{
            cout << (*iter)->getBlockNum() << "\t\t" << (*iter)->getPos() << endl;
        }
    }
}
void printOrderTable(vector<order *> orderList){
    for(auto iter = orderList.begin();iter != orderList.end(); iter++){
        cout << "����\t" << (*iter)->getOname() << "\tҳ��\t" << (*iter)->getPagenum() << "\t��Ԫ��\t" << (*iter)->getUnitNum() << endl;
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
    cout << "ҳ��" << "\t" << "��־" << "\t" << "������" << "\t" << "�ڴ����ϵ�λ��" << endl;
    printPageTable(pt);
    cout << endl;
    vector <order*> orderList;
    orderList.push_back(new order("+",0,"070"));
    orderList.push_back(new order("+",1,"050"));
    orderList.push_back(new order("*",2,"015"));
    orderList.push_back(new order("��",3,"021"));
    orderList.push_back(new order("ȡ",0,"056"));
    orderList.push_back(new order("-",6,"040"));
    orderList.push_back(new order("��λ",4,"053"));
    orderList.push_back(new order("+",5,"023"));
    orderList.push_back(new order("��",1,"037"));
    orderList.push_back(new order("ȡ",2,"078"));
    orderList.push_back(new order("+",4,"001"));
    orderList.push_back(new order("��",6,"084"));
    cout << "����" << "\t" << "ҳ��" << "\t" << "��Ԫ��" << endl;
    printOrderTable(orderList);
    cout << endl;
    for(auto iter = orderList.begin(); iter != orderList.end(); iter++){
        order* cur = *iter;
        cur->printOrder();
        int curpageNum = cur->getPagenum();
        int res = findPage(pt, curpageNum);
        if(res == -1){
            cout << "*" << curpageNum << endl;
        }else{
            cout << "���Ե�ַ: " << transadd(res,cur->getUnitNum()) << endl;
        }
    }
    system("pause");
    return 0;
}



