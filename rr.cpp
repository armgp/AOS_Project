#include <bits/stdc++.h>

using namespace std;

int id = 1;

struct Process{
    int pid;
    int arrivalTime;
    int reEntryTime;
    int bt;
    int burstTime1;
    int ioTime;
    int burstTime2;
    int waitingTime;
    int completionTime;
    int turnAroundTime;
    int usedArrTime;
    int responseTime;

    bool bt1Over = true;
    bool ioOver = true;
    bool bt2Over = true;

    Process(){
        pid = id++;
        arrivalTime = 0;
        reEntryTime = 0;
        ioTime = 0;
        bt = 0;
        burstTime2 = 0;
        waitingTime = 0;
        completionTime = 0;
        turnAroundTime = 0;
        usedArrTime = 0;
        responseTime = 0;
    }

    Process(int at, int bt1, int io, int bt2){
        pid = id++;
        arrivalTime = at;
        usedArrTime = at;
        reEntryTime = 0;
        burstTime1 = bt1;
        ioTime = io;
        burstTime2 = bt2;
        waitingTime = 0;
        completionTime = 0;
        turnAroundTime = 0;
        responseTime = 0;
        bt = bt1+io+bt2;

        if(bt1 > 0) bt1Over = false;
        if(io > 0) ioOver = false;
        if(bt2 > 0) bt2Over = false;
    }

    void showPocess(){
        cout<<"pid: "<<pid<<"\n";
        cout<<"arrivalTime: "<<arrivalTime<<"\n";
        cout<<"burstTime1: "<<burstTime1<<"\n";
        cout<<"ioTime: "<<ioTime<<"\n";
        cout<<"burstTime2: "<<burstTime2<<"\n";
        cout<<"waitingTime: "<<waitingTime<<"\n";
        cout<<"completionTime: "<<completionTime<<"\n";
        cout<<"turnAroundTime: "<<turnAroundTime<<"\n";
        cout<<"responseTime: "<<responseTime<<"\n";
        cout<<"-------------------------------\n\n";
    }
};

struct compareReEntryTime{
    bool operator()(Process &p1, Process &p2){
        return (p1.reEntryTime>p2.reEntryTime || (p1.reEntryTime==p2.reEntryTime && p1.pid>p2.pid));
    }
};

struct compareArrivalTime{
    bool operator()(Process &p1, Process &p2){
        return (p1.usedArrTime>p2.usedArrTime || (p1.usedArrTime==p2.usedArrTime && p1.pid>p2.pid));
    }
};

vector<Process> rr(vector<Process> newProcesses, int tq){

    sort(newProcesses.begin(), newProcesses.end(), [](Process &p1, Process &p2){
        return (p1.arrivalTime<p2.arrivalTime || (p1.arrivalTime==p2.arrivalTime && p1.pid>p2.pid));
    });

    priority_queue<Process, vector<Process>, compareArrivalTime> readyQueue;
    priority_queue<Process, vector<Process>, compareReEntryTime> waitingQueue;

    vector<Process> schedule;
    unordered_map<int, int> m;
    unordered_map<int, int> pushed;

    int timer = 0;
    int ind = 0;
    int n = newProcesses.size();

    while(true){

        while(ind<n && newProcesses[ind].arrivalTime <= timer){
            readyQueue.push(newProcesses[ind++]);
        }

        if(!readyQueue.empty()){
            Process currProcess = readyQueue.top();
            readyQueue.pop();

            //executing in cpu
            if(!currProcess.bt1Over) {
                if(m.find(currProcess.pid) == m.end()){
                    m[currProcess.pid] == 1;
                    currProcess.responseTime = timer-currProcess.arrivalTime;
                }
                
                int bt1remaining = currProcess.bt-(currProcess.ioTime + currProcess.burstTime2);
                if(tq <= bt1remaining){
                    currProcess.bt-=tq;
                    timer+=tq;
                }else{
                    currProcess.bt-=bt1remaining;
                    timer+=bt1remaining;
                }
                
                if(currProcess.bt == currProcess.ioTime+currProcess.burstTime2){
                    currProcess.bt1Over = true;
                    if(!currProcess.ioOver){
                        currProcess.reEntryTime = timer+currProcess.ioTime;
                        waitingQueue.push(currProcess);
                    }
                }else{
                    currProcess.usedArrTime = timer;
                    readyQueue.push(currProcess);
                }

            }

            else if(currProcess.bt1Over && currProcess.ioOver && !currProcess.bt2Over){
                if(tq <= currProcess.bt){
                    currProcess.bt-=tq;
                    timer+=tq;
                }else{
                    timer+=currProcess.bt;
                    currProcess.bt=0;
                }

                if(currProcess.bt == 0){
                    currProcess.bt2Over = true;
                    currProcess.completionTime = timer;
                    currProcess.turnAroundTime = currProcess.completionTime - currProcess.arrivalTime;
                    currProcess.waitingTime = currProcess.turnAroundTime - (currProcess.burstTime1 + currProcess.burstTime2);
                    schedule.push_back(currProcess);
                    pushed[currProcess.pid] = 1;
                }else{
                    currProcess.usedArrTime = timer;
                    readyQueue.push(currProcess);
                }
            }

            if(currProcess.bt1Over && currProcess.ioOver && currProcess.bt2Over && pushed.find(currProcess.pid)==pushed.end()){
                currProcess.completionTime = timer;
                currProcess.turnAroundTime = currProcess.completionTime - currProcess.arrivalTime;
                currProcess.waitingTime = currProcess.turnAroundTime - (currProcess.burstTime1 + currProcess.burstTime2 );
                schedule.push_back(currProcess);
                pushed[currProcess.pid] = 1;
            }

        }

        else if(readyQueue.empty() && !waitingQueue.empty()) timer++;

        //ioprocess execution
        while(!waitingQueue.empty() && waitingQueue.top().reEntryTime <= timer){
            Process ioCurrProcess = waitingQueue.top();
            waitingQueue.pop();
            ioCurrProcess.ioOver = true;
            ioCurrProcess.usedArrTime = ioCurrProcess.reEntryTime;
            ioCurrProcess.bt-=ioCurrProcess.ioTime;
            readyQueue.push(ioCurrProcess);
        }

        if(readyQueue.empty() && waitingQueue.empty() && ind<n) timer = newProcesses[ind].arrivalTime;

        if(readyQueue.empty() && waitingQueue.empty()) break;

    }

    return schedule;

}

int main(){

    int n;
    cin>>n;

    vector<Process> processes;

    while(n--){
        int at, bt1, io, bt2;
        cin>>at>>bt1>>io>>bt2;
        Process p(at, bt1, io, bt2);
        processes.push_back(p);
    }

    vector<Process> schedule = rr(processes, 2);

    for(Process p : schedule) p.showPocess();
    
    return 0;
}