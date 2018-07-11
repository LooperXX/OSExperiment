//
// Created by LooperXX on 2018/6/29.
//

#include <bits/stdc++.h>

#define pss(a, b) pair<state,string>(a,b)
using namespace std;

enum state {
    ready = 1,
    working = 2,
    finish = 3
};

class lab2_PCB {
private:
    string name;
    lab2_PCB *pNext;
    int time;
    int level;
    state s;
    int cpuTime = 0;
    int waitingTime = 0;
    bool started = false;

public:

    int getWaitingTime() const {
        return waitingTime;
    }

    int getCpuTime(){
        return cpuTime;
    }

    void incCpuTime() {
        if(started){
            cpuTime++;
            if(s == ready )
                waitingTime++;
        }
        else{
            waitingTime++;

        }
    }

    lab2_PCB()= default;

    lab2_PCB(string name, lab2_PCB *pNext, int time, int level, state s) {
        this->name = name;
        this->pNext = pNext;
        this->time = time;
        this->level = level;
        this->s = s;
    }

    void run() {
        level--;
        time--;
        started = true;

    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        lab2_PCB::name = name;
    }

    lab2_PCB *getPNext() const {
        return pNext;
    }

    void setPNext(lab2_PCB *pNext) {
        lab2_PCB::pNext = pNext;
    }

    int getTime() const {
        return time;
    }

    void setTime(int time) {
        lab2_PCB::time = time;
    }

    int getLevel() const {
        return level;
    }

    void setLevel(int level) {
        lab2_PCB::level = level;
    }

    state getS() const {
        return s;
    }

    void setS(state s) {
        lab2_PCB::s = s;
    }
};