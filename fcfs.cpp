#include <bits/stdc++.h>

using namespace std;

int id = 0;

struct Process{
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int completionTime;
    int turnAroundTime;

    Process(){
        pid = id++;
        arrivalTime = 0;
        burstTime = 0;
        waitingTime = 0;
        completionTime = 0;
        turnAroundTime = 0;
    }

    Process(int at, int bt){
        pid = id++;
        arrivalTime = at;
        burstTime = bt;
        waitingTime = 0;
        completionTime = 0;
        turnAroundTime = 0;
    }

    void showPocess(){
        cout<<"pid: "<<pid<<"\n";
        cout<<"arrivalTime: "<<arrivalTime<<"\n";
        cout<<"burstTime: "<<burstTime<<"\n";
        cout<<"waitingTime: "<<waitingTime<<"\n";
        cout<<"completionTime: "<<completionTime<<"\n";
        cout<<"turnAroundTime: "<<turnAroundTime<<"\n";
        cout<<"-------------------------------\n\n";
    }
};

void fcfs(vector<Process>& pList){
    sort(pList.begin(), pList.end(), [](Process &p1, Process &p2){
        return (p1.arrivalTime<p2.arrivalTime || (p1.arrivalTime==p2.arrivalTime && p1.pid<p2.pid));
    });

    int prevCt = -1;

    for(Process& p : pList){
        int currTime = max(p.arrivalTime, prevCt);
        currTime+=p.burstTime;
        p.completionTime = currTime;
        p.turnAroundTime = p.completionTime-p.arrivalTime;
        p.waitingTime = p.turnAroundTime-p.burstTime;
        prevCt = p.completionTime;
    }

}

struct compareBurstTime{
    bool operator()(Process &p1, Process &p2){
        return (p1.burstTime>p2.burstTime || (p1.burstTime==p2.burstTime && p1.pid<p2.pid));
    }
};

void sjfNP(vector<Process>& pList){

    sort(pList.begin(), pList.end(), [](Process &p1, Process &p2){
        return (p1.arrivalTime<p2.arrivalTime || (p1.arrivalTime==p2.arrivalTime && p1.pid<p2.pid));
    });

    priority_queue<Process, vector<Process>, compareBurstTime> minHeap;

    int currTime = 0;
    vector<Process> schedule;
    minHeap.push(pList[0]);
    int ind = 1;
    int n = pList.size();
    while(!minHeap.empty()){
        Process p = minHeap.top();
        minHeap.pop();
        currTime = max(p.arrivalTime, currTime);
        currTime+=p.burstTime;
        p.completionTime = currTime;
        p.turnAroundTime = p.completionTime-p.arrivalTime;
        p.waitingTime = p.turnAroundTime-p.burstTime;
        schedule.push_back(p);

        while(ind<n && pList[ind].arrivalTime <= currTime){
            minHeap.push(pList[ind++]);
        }

    }

    pList = schedule;

}

void sjfP(vector<Process>& pList){

    sort(pList.begin(), pList.end(), [](Process &p1, Process &p2){
        return (p1.arrivalTime<p2.arrivalTime || (p1.arrivalTime==p2.arrivalTime && p1.pid<p2.pid));
    });

    priority_queue<Process, vector<Process>, compareBurstTime> minHeap;

    int currTime = pList[0].arrivalTime;
    vector<Process> schedule;
    minHeap.push(pList[0]);
    int ind = 1;
    int n = pList.size();

    while(!minHeap.empty()){
        currTime++;

        Process p = minHeap.top();
        minHeap.pop();
        p.burstTime--;
        p.waitingTime--;

        if(p.burstTime > 0) minHeap.push(p);
        else{
            p.completionTime = currTime;
            p.turnAroundTime = p.completionTime-p.arrivalTime;
            p.waitingTime += p.turnAroundTime;
            schedule.push_back(p);
        }
        

        while(ind<n && pList[ind].arrivalTime <= currTime){
            minHeap.push(pList[ind++]);
        }
    }

    pList = schedule;

}

void rr(vector<Process>& pList, int tq){
    sort(pList.begin(), pList.end(), [](Process &p1, Process &p2){
        return (p1.arrivalTime<p2.arrivalTime || (p1.arrivalTime==p2.arrivalTime && p1.pid<p2.pid));
    });

    queue<Process> q;
    vector<Process> schedule;

    for(Process p : pList) q.push(p);

    int currTime = q.front().arrivalTime;
    while(!q.empty()){
        Process currProcess = q.front();
        q.pop();
        currTime = max(currTime, currProcess.arrivalTime);
        if(tq <= currProcess.burstTime){
            currProcess.burstTime-=tq;
            currTime+=tq;
            currProcess.waitingTime-=tq;
        }else{
            currTime+=currProcess.burstTime;
            currProcess.waitingTime-=currProcess.burstTime;
            currProcess.burstTime = 0;
        }

        if(currProcess.burstTime != 0){
            q.push(currProcess);
        }else{
            currProcess.completionTime = currTime;
            currProcess.turnAroundTime = currProcess.completionTime-currProcess.arrivalTime;
            currProcess.waitingTime += currProcess.turnAroundTime;
            schedule.push_back(currProcess);
        }
    }

    pList = schedule;
}

int main(){

    int n;
    cin>>n;

    vector<Process> processes;

    while(n--){
        int at, bt;
        cin>>at>>bt;
        Process p(at, bt);
        processes.push_back(p);
    }

    // fcfs(processes);
    // sjfNP(processes);
    // sjfP(processes);
    rr(processes, 2);

    for(Process p : processes) p.showPocess();
    
    return 0;
}