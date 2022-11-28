#include <bits/stdc++.h>

using namespace std;

int id = 1;

struct Process{
    int pid;
    int arrivalTime;
    int reEntryTime;
    int burstTime1;
    int ioTime;
    int burstTime2;
    int waitingTime;
    int completionTime;
    int turnAroundTime;
    int priority;
    int responseTime;
    int bt;

    bool bt1Over = true;
    bool ioOver = true;
    bool bt2Over = true;

    Process(){
        pid = id++;
        arrivalTime = 0;
        reEntryTime = 0;
        ioTime = 0;
        burstTime2 = 0;
        waitingTime = 0;
        completionTime = 0;
        turnAroundTime = 0;
        priority = 0;
        responseTime = 0;
        bt = 0;
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
        priority = 0;
        bt = bt1 + io + bt2;
        responseTime = 0;

        if(bt1 > 0) bt1Over = false;
        if(io > 0) ioOver = false;
        if(bt2 > 0) bt2Over = false;
    }

    Process(int at, int bt1, int io, int bt2, int pt){
        pid = id++;
        arrivalTime = at;
        reEntryTime = 0;
        burstTime1 = bt1;
        ioTime = io;
        burstTime2 = bt2;
        waitingTime = 0;
        completionTime = 0;
        turnAroundTime = 0;
        priority = pt;
        bt = bt1 + io + bt2;
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
        cout<<"priority: "<<priority<<"\n";
        cout<<"-------------------------------\n\n";
    }
};

struct compareReEntryTime{
    bool operator()(Process &p1, Process &p2){
        return (p1.reEntryTime>p2.reEntryTime || (p1.reEntryTime==p2.reEntryTime && p1.priority>p2.priority) ||  (p1.arrivalTime==p2.arrivalTime && p1.priority==p2.priority && p1.pid>p2.pid));
    }
};



struct comparePriority{
    bool operator()(Process &p1, Process &p2){
        return ((p1.priority>p2.priority) ||  (p1.priority==p2.priority && p1.pid>p2.pid));
    }
};

vector<Process> priorityP(vector<Process> newProcesses){
    sort(newProcesses.begin(), newProcesses.end(), [](Process &p1, Process &p2){
        return (p1.arrivalTime<p2.arrivalTime || (p1.arrivalTime==p2.arrivalTime && p1.priority>p2.priority) || (p1.arrivalTime==p2.arrivalTime && p1.priority==p2.priority && p1.pid>p2.pid));
    });

    priority_queue<Process, vector<Process>, comparePriority> readyQueue;
    priority_queue<Process, vector<Process>, compareReEntryTime> waitingQueue;

    vector<Process> schedule;
    unordered_map<int, int> m;

    int timer = newProcesses[0].arrivalTime;
    int ind = 1;
    int size = newProcesses.size();

    readyQueue.push(newProcesses[0]);


    while(true){
        if(size > ind && newProcesses[ind].arrivalTime==timer)
            readyQueue.push(newProcesses[ind++]);

        if(!readyQueue.empty()){
            Process currProcess = readyQueue.top();
            readyQueue.pop();

            //executing in cpu
            if(currProcess.arrivalTime>timer){
                timer++;
                readyQueue.push(currProcess);
                
            }
            else if(!currProcess.bt1Over) {
                timer++;
                if(m.find(currProcess.pid) == m.end()){
                    m[currProcess.pid] = 1;
                    currProcess.responseTime = timer-currProcess.arrivalTime;
                }

                currProcess.burstTime1--;
                currProcess.waitingTime--;

                if(currProcess.burstTime1==0){
                    currProcess.bt1Over = true;
                    currProcess.reEntryTime = timer+currProcess.ioTime;
                    waitingQueue.push(currProcess);
                }
                else
                    readyQueue.push(currProcess);
            }

            else if(currProcess.bt1Over && currProcess.ioOver && !currProcess.bt2Over){
                timer++;
                currProcess.burstTime2--;
                currProcess.waitingTime--;

                if(currProcess.burstTime2==0){
                    currProcess.bt2Over = true;
                    currProcess.completionTime = timer;
                    currProcess.turnAroundTime = currProcess.completionTime - currProcess.arrivalTime;
                    currProcess.waitingTime += currProcess.turnAroundTime;
                    schedule.push_back(currProcess);
                }
                else{
                    readyQueue.push(currProcess);
                }
            }
            else if(currProcess.bt1Over && currProcess.ioOver && currProcess.bt2Over){
                currProcess.completionTime = timer;
                currProcess.turnAroundTime = currProcess.completionTime - currProcess.arrivalTime;
                currProcess.waitingTime += currProcess.turnAroundTime;
                schedule.push_back(currProcess);
            }

        }
        else if(readyQueue.empty() && !waitingQueue.empty()) timer++;

        //ioprocess execution
        while(!waitingQueue.empty() && waitingQueue.top().reEntryTime <= timer){
            Process ioCurrProcess = waitingQueue.top();
            waitingQueue.pop();
            ioCurrProcess.ioOver = true;
            readyQueue.push(ioCurrProcess);
        }
        

        if(readyQueue.empty() && waitingQueue.empty() && ind>=size) break;

        if(readyQueue.empty() && waitingQueue.empty() && ind<size) timer++;

    }

    return schedule;

}




vector<Process> get_processes()
{

	// File pointer
	fstream fin;

	// Open an existing file
    vector<Process> Input_process;
	fin.open("processes.csv", ios::in);


	string line, word;

	while (getline(fin, line)) {
        vector<int> cur_process;
		stringstream s(line);

		while (getline(s, word, ',')) {
            cur_process.push_back(stoi(word));
		}
        Process p(cur_process[0], cur_process[1], cur_process[2], cur_process[3],cur_process[4]);
        Input_process.push_back(p);

	}
    return Input_process;

   
}


int main(){



    vector<Process> processes;

    processes = get_processes();

    vector<Process> schedule = priorityP(processes);

    for(Process p : schedule) p.showPocess();
    
    return 0;
}