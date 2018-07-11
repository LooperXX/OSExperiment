#include <bits/stdc++.h>
#include "lab2_PCB.cpp"
#define pii(a,b) pair<int,int>(a,b)
int CPUTIME = 0;
int MAXLEVEl;
map<state, string> res_state;
map<int,int> sortMap;
void sortInit(lab2_PCB *list, lab2_PCB &head);

void show(lab2_PCB *list);

void pSatrt(lab2_PCB *list, lab2_PCB &head);

using namespace std;

int main() {

    res_state.insert(pss(ready, "ready"));
    res_state.insert(pss(working, "working"));
    res_state.insert(pss(finish, "finish"));
//    // 随机生成优先数与要求运行时间
//    int level[5] = {};
//    int time[5] = {};
//    for (int i = 0; i < 5; i++) {
//        int randnum = rand() % 5 + 1;
//        MAXLEVEl = max(MAXLEVEl,randnum);
//        level[i] = randnum;
//        time[i] = (randnum + 3) % 3 + 1;
//
//    }

    //test
    int level[5] = {1,5,3,4,2};
    int time[5] = {2,3,1,2,4};
    MAXLEVEl = 5;

    lab2_PCB list[5];
    lab2_PCB p1("P1", nullptr, time[0], level[0], ready);
    list[0] = p1;
    lab2_PCB p2("P2", nullptr, time[1], level[1], ready);
    list[1] = p2;
    lab2_PCB p3("P3", nullptr, time[2], level[2], ready);
    list[2] = p3;
    lab2_PCB p4("P4", nullptr, time[3], level[3], ready);
    list[3] = p4;
    lab2_PCB p5("P5", nullptr, time[4], level[4], ready);
    list[4] = p5;
    lab2_PCB head;
    cout << "INPUT NAME, NEEDTIME AND PRIORITY" << endl;
    cout << p1.getName() << "\t" << time[0] << "\t" << p1.getLevel() << "\t" << endl;
    cout << p2.getName() << "\t" << time[1] << "\t" << p2.getLevel() << "\t" << endl;
    cout << p3.getName() << "\t" << time[2] << "\t" << p3.getLevel() << "\t" << endl;
    cout << p4.getName() << "\t" << time[3] << "\t" << p4.getLevel() << "\t" << endl;
    cout << p5.getName() << "\t" << time[4] << "\t" << p5.getLevel() << "\t" << endl;
    sortInit(list, head);
    cout << "OUTPUT  OF  PRIORITY:" << endl;
    cout << "CPUTIME:" << CPUTIME << endl;
    cout << "NAME" << "\t\t" << "CPUTIME" << "\t\t" << "NEEDTIME" << "\t" << "PRIORITY" << "\t" << "STATE" << "\t" << endl;
    show(list);
    pSatrt(list, head);
    cout << "NAME" << "\t\t" << "RoundTime" << "\t" << "WaitingTime" << "\t\t" << endl;
    for(int i = 0; i < 5; i++){
        cout << list[i].getName() << "\t\t" << list[i].getWaitingTime() + time[i] << "\t\t" << list[i].getWaitingTime() << "\t\t" << endl;
    }
    system("pause");
}

void pSatrt(lab2_PCB *list, lab2_PCB &head) {
    while (true) {
        CPUTIME++;// 更新全局CPUTIME
        head.getPNext()->run();// 触发进程运转事件
        head.getPNext()->setS(working); // 更新当前进程状态
        for(int i = 0; i < 5; i++){
            if(list[i].getS() != finish)
                list[i].incCpuTime();// 更新进程的各种时间参数
        }
        if (head.getPNext()->getTime() == 0) { // 进程是否结束
            head.getPNext()->setS(finish);
        }

        // 打印进程状态
        cout << "CPUTIME:" << CPUTIME << endl;
        show(list);

        if(head.getPNext()->getTime() != 0){ // 还原当前进程状态
            head.getPNext()->setS(ready);
        }
        //进程切换
        if (head.getPNext()->getTime() == 0) { // 是否删除进程
            head.setPNext(head.getPNext()->getPNext());
            if( head.getPNext() == nullptr){ // 是否已经没有进程
                break;
            }
        }else{ // 不删除进程时
            lab2_PCB* temp = head.getPNext();
            head.setPNext(head.getPNext()->getPNext());
            lab2_PCB* start = &head;
            lab2_PCB* change = nullptr;
            // 找到当前进程的插入点并连接
            for(int i = 0;start->getPNext() != nullptr;i++){
                if(start->getPNext()->getLevel() >= temp->getLevel()){
                    change = start;
                }
                start = start->getPNext();
            }
            if(change == nullptr) // 队列中只有当前进程时
                head.setPNext(temp);
            else{
                temp->setPNext(change->getPNext()->getPNext());
                change->getPNext()->setPNext(temp);
            }

        }
    }
}

void show(lab2_PCB *list) {
    for(int i = 0; i < 5; i++) {
        cout << list[i].getName() << "\t\t" << list[i].getCpuTime() << "\t\t" << list[i].getTime() << "\t\t"
             << list[i].getLevel() << "\t\t" << res_state[list[i].getS()] << "\t\t" << endl;
    }
}

void sortInit(lab2_PCB *list, lab2_PCB &head) {
    int temp = MAXLEVEl;
    int headIndex = 0;
    // 找出队首并让进程头对象的pNext指针指向队首
    for (int i = 0; i < 5; i++) {
        if (list[i].getLevel() == temp) {
            head.setPNext(&list[i]);
            headIndex = i;
            temp--;
            sortMap.insert(pii(headIndex,1));
            break;
        }
    }
    // 自队首开始，依次寻找更低优先级的进程并连接在一起
    int left = headIndex;
    bool flag;
    for (int j = 0; j < 4; j++) {
        flag = false;
        for (int i = 0; i < 5; i++) {
            if (list[i].getLevel() == temp && sortMap.count(i)== 0) {
                list[left].setPNext(&list[i]);
                left = i;
                flag = true;
                sortMap.insert(pii(i,1));
                break;
            }
        }
        if(!flag){
            temp--;
            j--;
        }
    }
    list[left].setPNext(0);// 最后一个进程的pNext指针指向0
}
