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
        responseTime = 0;
    }

    Process(int at, int bt1, int io, int bt2){
        pid = id++;
        arrivalTime = at;
        reEntryTime = 0;
        burstTime1 = bt1;
        ioTime = io;
        burstTime2 = bt2;
        waitingTime = 0;
        completionTime = 0;
        turnAroundTime = 0;
        bt = bt1+io+bt2;
        responseTime = 0;

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

struct compareBurstTime{
    bool operator()(Process &p1, Process &p2){
        int p1bt = p1.burstTime1+p1.burstTime2;
        int p2bt = p2.burstTime1+p2.burstTime2;
        return (p1bt>p2bt || (p1bt==p2bt && p1.pid>p2.pid));
    }
};

vector<Process> sjfNp(vector<Process> newProcesses){

    sort(newProcesses.begin(), newProcesses.end(), [](Process &p1, Process &p2){
        return (p1.arrivalTime<p2.arrivalTime || (p1.arrivalTime==p2.arrivalTime && p1.pid>p2.pid));
    });

    priority_queue<Process, vector<Process>, compareBurstTime> readyQueue;
    priority_queue<Process, vector<Process>, compareReEntryTime> waitingQueue;

    vector<Process> schedule;
    unordered_map<int, int> m;

    int timer = 0;
    int ind  = 0;
    int n = newProcesses.size();

    while(true){
        
        while(ind<n && newProcesses[ind].arrivalTime <= timer){
            readyQueue.push(newProcesses[ind++]);
        }

        if(!readyQueue.empty()){
            Process currProcess = readyQueue.top();
            readyQueue.pop();

            if(!currProcess.bt1Over){
                if(m.find(currProcess.pid) == m.end()){
                    m[currProcess.pid] == 1;
                    currProcess.responseTime = timer-currProcess.arrivalTime;
                }
                timer+=currProcess.burstTime1;
                currProcess.bt1Over = true;
                currProcess.bt-=currProcess.burstTime1;
                if(!currProcess.ioOver){
                    currProcess.reEntryTime = timer+currProcess.ioTime;
                    waitingQueue.push(currProcess);
                }
            }

            else if(currProcess.bt1Over && currProcess.ioOver && !currProcess.bt2Over){
                timer+=currProcess.burstTime2;
                currProcess.bt-=currProcess.burstTime2;
                currProcess.bt2Over = true;
            }

            if(currProcess.bt1Over && currProcess.ioOver && currProcess.bt2Over){
                currProcess.completionTime = timer;
                currProcess.turnAroundTime = currProcess.completionTime - currProcess.arrivalTime;
                currProcess.waitingTime = currProcess.turnAroundTime - (currProcess.burstTime1 + currProcess.burstTime2);
                schedule.push_back(currProcess);
            }
        }

        while(!waitingQueue.empty() && waitingQueue.top().reEntryTime <= timer){
            Process reEntryProcess = waitingQueue.top();
            reEntryProcess.ioOver = true;
            reEntryProcess.bt-=reEntryProcess.ioTime;
            waitingQueue.pop();
            readyQueue.push(reEntryProcess);
        }

        if(readyQueue.empty() && !waitingQueue.empty()){
            timer = waitingQueue.top().reEntryTime;
        }

        if(readyQueue.empty() && waitingQueue.empty() && ind<n) timer = newProcesses[ind].arrivalTime;

        if(readyQueue.empty() && waitingQueue.empty() && ind>=n) break;
        
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

    vector<Process> schedule = sjfNp(processes);

    for(Process p : schedule) p.showPocess();
    
    return 0;
}