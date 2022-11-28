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

vector<Process> mlfq(vector<Process> newProcesses){
    sort(newProcesses.begin(), newProcesses.end(), [](Process &p1, Process &p2){
        return (p1.arrivalTime<p2.arrivalTime || (p1.arrivalTime==p2.arrivalTime && p1.pid>p2.pid));
    });

    unordered_map<int, int> m;
    unordered_map<int, int> pushed;
    unordered_map<int, int> responseTime;

    vector<Process> schedule;
    priority_queue<Process, vector<Process>, compareArrivalTime> readyQueue1;
    priority_queue<Process, vector<Process>, compareArrivalTime> readyQueue2;
    priority_queue<Process, vector<Process>, compareArrivalTime> readyQueue3;
    priority_queue<Process, vector<Process>, compareReEntryTime> waitingQueue;

    int timer = 0;
    int ind = 0;
    int n = newProcesses.size();
    int tq1 = 2;
    int tq2 = 5;

    while(true){

        while(ind<n && newProcesses[ind].arrivalTime <= timer){
            readyQueue1.push(newProcesses[ind++]);
        }

        while(!waitingQueue.empty() && waitingQueue.top().reEntryTime <= timer){
            Process reEntryProcess = waitingQueue.top();
            waitingQueue.pop();
            reEntryProcess.bt -= reEntryProcess.ioTime;
            reEntryProcess.ioOver = true;
            readyQueue1.push(reEntryProcess);
        }

        if(!readyQueue1.empty()){
            Process currProcess = readyQueue1.top();
            readyQueue1.pop();

            if(responseTime.find(currProcess.pid) == responseTime.end()){
                responseTime[currProcess.pid] = timer;
            }

            if(!currProcess.bt1Over){
                int remainingBt = currProcess.bt - (currProcess.ioTime + currProcess.burstTime2);
                if(tq1 <= remainingBt){
                    currProcess.bt-=tq1;
                    timer+=tq1;
                }else{
                    timer+=remainingBt;
                    currProcess.bt -= remainingBt;
                }
                
                if(currProcess.bt == currProcess.ioTime + currProcess.burstTime2){
                    currProcess.bt1Over = true;
                    if(!currProcess.ioOver){
                        currProcess.reEntryTime = timer+currProcess.ioTime;
                        waitingQueue.push(currProcess);
                    }
                    
                }else if(!currProcess.bt1Over && currProcess.bt > currProcess.ioTime + currProcess.burstTime2){
                    currProcess.usedArrTime = timer;
                    readyQueue2.push(currProcess);
                }

            }

            else if(currProcess.bt1Over && currProcess.ioOver && !currProcess.bt2Over){
                if(tq1 <= currProcess.burstTime2){
                    currProcess.bt-=tq1;
                    timer+=tq1;
                }else{
                    timer+=currProcess.burstTime2;
                    currProcess.bt -= currProcess.burstTime2;
                }

                if(currProcess.bt == 0){
                    currProcess.bt2Over = true;
                }else{
                    currProcess.usedArrTime = timer;
                    readyQueue2.push(currProcess);
                }
            }

            if(currProcess.bt1Over && currProcess.ioOver && currProcess.bt2Over){
                currProcess.completionTime = timer;
                currProcess.turnAroundTime = currProcess.completionTime - currProcess.arrivalTime;
                currProcess.waitingTime = currProcess.turnAroundTime - (currProcess.burstTime1 + currProcess.burstTime2 );
                schedule.push_back(currProcess);
            }
            
        }

        else if(readyQueue1.empty() && !readyQueue2.empty()){
            Process currProcess = readyQueue2.top();
            readyQueue2.pop();

            if(!currProcess.bt1Over){
                int remainingBt = currProcess.bt - (currProcess.ioTime + currProcess.burstTime2);
                if(tq2 <= remainingBt){
                    currProcess.bt-=tq2;
                    timer+=tq2;
                }else{
                    timer+=remainingBt;
                    currProcess.bt -= remainingBt;
                }

                if(currProcess.bt == currProcess.ioTime + currProcess.burstTime2){
                    currProcess.bt1Over = true;
                    if(!currProcess.ioOver){
                        currProcess.reEntryTime = timer+currProcess.ioTime;
                        waitingQueue.push(currProcess);
                    }
                }else if(!currProcess.bt1Over && currProcess.bt > currProcess.ioTime + currProcess.burstTime2){
                    currProcess.usedArrTime = timer;
                    readyQueue3.push(currProcess);
                }

            }
            else if(currProcess.bt1Over && currProcess.ioOver && !currProcess.bt2Over){
                if(tq2 <= currProcess.burstTime2){
                    currProcess.bt-=tq2;
                    timer+=tq2;
                }else{
                    timer+=currProcess.burstTime2;
                    currProcess.bt -= currProcess.burstTime2;
                }

                if(currProcess.bt == 0){
                    currProcess.bt2Over = true;
                }else{
                    currProcess.usedArrTime = timer;
                    readyQueue3.push(currProcess);
                }
            }

            if(currProcess.bt1Over && currProcess.ioOver && currProcess.bt2Over){
                currProcess.completionTime = timer;
                currProcess.turnAroundTime = currProcess.completionTime - currProcess.arrivalTime;
                currProcess.waitingTime = currProcess.turnAroundTime - (currProcess.burstTime1 + currProcess.burstTime2 );
                schedule.push_back(currProcess);
            }
        }

        else if(readyQueue1.empty() && readyQueue2.empty() && !readyQueue3.empty()){
            Process currProcess = readyQueue3.top();
            readyQueue3.pop();

            if(!currProcess.bt1Over){
                timer+=(currProcess.bt - (currProcess.ioTime + currProcess.burstTime2));
                currProcess.bt = currProcess.ioTime + currProcess.burstTime2;
                currProcess.bt1Over = true;
                if(!currProcess.ioOver){
                    currProcess.reEntryTime = timer+currProcess.ioTime;
                    waitingQueue.push(currProcess);
                }
            }else if(currProcess.bt1Over && currProcess.ioOver && !currProcess.bt2Over){
                timer+=currProcess.bt;
                currProcess.bt = 0;
                currProcess.bt2Over = true;
            }

            if(currProcess.bt1Over && currProcess.ioOver && currProcess.bt2Over){
                currProcess.completionTime = timer;
                currProcess.turnAroundTime = currProcess.completionTime - currProcess.arrivalTime;
                currProcess.waitingTime = currProcess.turnAroundTime - (currProcess.burstTime1 + currProcess.burstTime2 );
                schedule.push_back(currProcess);
            }
        }

        if(readyQueue1.empty() && readyQueue2.empty() && readyQueue3.empty() && waitingQueue.empty()){
            break;
        }

        if(readyQueue1.empty() && readyQueue2.empty() && readyQueue3.empty() && waitingQueue.empty() && ind<n) timer++;

        if(!waitingQueue.empty() && readyQueue1.empty() && readyQueue2.empty() && readyQueue3.empty()) timer++;

    }

    int sn = schedule.size();
    for(int i=0; i<sn; i++) {
        schedule[i].responseTime = responseTime[schedule[i].pid];
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

    vector<Process> schedule = mlfq(processes);

    for(Process p : schedule) p.showPocess();

    return 0;
}