#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <windows.h>
#include <random>
#include <cstdlib>  // 新增必要头文件
#include <ctime>    // 新增时间相关头文件
using namespace std;

// 控制台颜色配置（修正颜色值）
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 作业结构体（添加默认初始化）
struct Job {
    int id = 0;             
    int arriveTime = 0;     
    int duration = 0;       
    int startTime = -1; 
    int priority = 0;       
    int waitTime = 0;   
    bool completed = false;
};

// 系统事件类型（添加枚举作用域）
enum EventType { JOB_ARRIVE, JOB_FINISH };

// 系统事件结构体（修正比较运算符）
struct SystemEvent {
    int time;
    EventType type;
    int jobId;
    
    bool operator<(const SystemEvent& other) const {
        return time > other.time; // 保持小顶堆特性
    }
};

class Scheduler {
private:
    priority_queue<SystemEvent> eventQueue;
    vector<Job> jobPool;                    
    vector<int> readyQueue;                 
    int currentJob = -1;                    
    int systemTime = 0;                     
    
    void logEvent(const string& msg, int color=15) {
        setColor(color);
        cout << "[" << systemTime << "] " << msg << endl;
        setColor(15);
    }

public:
    void initialize(bool autoGenerate, int jobCount) {
        random_device rd;
        mt19937 gen(rd());
        
        for(int i=0; i<jobCount; i++) {
            Job job;
            job.id = i+1;
            
            if(autoGenerate) {
                // 明确指定模板参数类型
                uniform_int_distribution<int> arriveDist(1, 20);
                uniform_int_distribution<int> durationDist(1, 15);
                job.arriveTime = arriveDist(gen);
                job.duration = durationDist(gen);
            } else {
                cout << "输入作业" << job.id << "的到达时间和运行时长: ";
                cin >> job.arriveTime >> job.duration;
            }
            
            job.priority = job.duration;
            jobPool.push_back(job);
            
            eventQueue.push({job.arriveTime, JOB_ARRIVE, i});
        }
    }

    void run() {
        while(!eventQueue.empty()) {
            SystemEvent e = eventQueue.top();
            eventQueue.pop();
            systemTime = e.time;

            switch(e.type) {
                case JOB_ARRIVE:
                    handleJobArrive(e.jobId);
                    break;
                case JOB_FINISH:
                    handleJobFinish(e.jobId);
                    break;
            }

            if(currentJob == -1 && !readyQueue.empty()) {
                scheduleJob();
            }
        }
    }

private:
    void handleJobArrive(int jobId) {
        Job& job = jobPool[jobId];
        readyQueue.push_back(jobId);
        logEvent("作业" + to_string(job.id) + "到达（初始优先数:" 
               + to_string(job.priority) + "）", 2);  // 绿色
    }

    void handleJobFinish(int jobId) {
        Job& job = jobPool[jobId];
        job.completed = true;
        currentJob = -1;
        logEvent("作业" + to_string(job.id) + "完成，总耗时: " 
               + to_string(systemTime - job.arriveTime), 4); // 红色
    }

    void scheduleJob() {
        int minPriority = INT_MAX;
        int selected = -1;
        
        // 更新所有作业的等待时间和优先数
        for(int& id : readyQueue) {
            Job& job = jobPool[id];
            job.waitTime = systemTime - job.arriveTime;
            job.priority = job.duration - job.waitTime;
        }
        
        // 选择优先数最小的作业
        for(size_t i=0; i<readyQueue.size(); i++) {
            if(jobPool[readyQueue[i]].priority < minPriority) {
                minPriority = jobPool[readyQueue[i]].priority;
                selected = i;
            }
        }

        if(selected != -1) {
            currentJob = readyQueue[selected];
            Job& job = jobPool[currentJob];
            
            job.startTime = systemTime;
            logEvent("开始执行作业" + to_string(job.id) 
                   + "（等待:" + to_string(job.waitTime)
                   + " 当前优先数:" + to_string(job.priority) + "）", 14); // 黄色
            
            // 生成完成事件
            SystemEvent finishEvent;
            finishEvent.time = systemTime + job.duration;
            finishEvent.type = JOB_FINISH;
            finishEvent.jobId = currentJob;
            eventQueue.push(finishEvent);
            
            readyQueue.erase(readyQueue.begin() + selected);
        }
    }
};

int main() {
    setColor(15);
    //system("chcp 65001 > nul");  // 设置控制台编码
    
    cout << "★ 作业调度系统 ★\n"
         << "1. 手动输入作业\n"
         << "2. 自动生成作业\n"
         << "选择模式：";
    
    int mode;
    cin >> mode;
    
    cout << "输入作业数量：";
    int num;
    cin >> num;

    Scheduler scheduler;
    scheduler.initialize(mode == 2, num);
    
    cout << "\n◆◆ 开始调度 ◆◆\n";
    scheduler.run();
    
    cout << "\n◆◆ 所有作业调度完成 ◆◆\n";
    return 0;
}