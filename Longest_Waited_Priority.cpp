#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process;

vector<Process *> running_queue;

void print_gantt_chart();
void print_priority(int, vector<Process *>);

enum State
{
    COMPLETED,
    READY,
    NOT_ARRIVED
};

struct Process
{
    int pid;
    string process_name;
    int arrival_time;
    int estimated_run_time;

    int turnaround_time;
    int executed_time = 0;
    int waiting_time = 0;
    float priority = 1;
    State state = NOT_ARRIVED;

    Process(
        string _process_name,
        int _arrival_time,
        int _estimated_run_time) : pid(rand()),
                                   process_name(_process_name),
                                   arrival_time(_arrival_time),
                                   estimated_run_time(_estimated_run_time) {}

    void setPriority()
    {
        priority = 1 + (float)waiting_time / estimated_run_time;
    }

    void run(int curr_time)
    {
        executed_time++;
        running_queue.push_back(this);
        cout << "Process " << process_name << " running..." << endl;
        if (executed_time == estimated_run_time)
        {
            state = COMPLETED;
            turnaround_time = curr_time + 1 - arrival_time;
            cout << "Process " << process_name << " completed..." << endl;
        }
    }

    void wait()
    {
        waiting_time++;
        cout << "Process " << process_name << " waiting..." << endl;
    }
};

void run_process(vector<Process *> processes)
{
    int curr_time = 0;

    queue<Process *> job_queue;
    vector<Process *> ready_queue;

    for (auto proc : processes)
        job_queue.push(proc);

    while (true)
    {
        if (!job_queue.empty())
        {
            Process *p = job_queue.front();
            while (p->arrival_time == curr_time)
            {
                job_queue.pop();
                ready_queue.push_back(p);
                p->state = READY;

                if (job_queue.empty())
                    break;

                p = job_queue.front();
            }
        }

        Process *highest_priority_process = NULL;

        for (auto proc : ready_queue)
        {
            if (highest_priority_process == NULL || proc->priority > highest_priority_process->priority)
                highest_priority_process = proc;
            else if (proc->priority == highest_priority_process->priority && proc->waiting_time < highest_priority_process->waiting_time)
                highest_priority_process = proc;
        }

        bool completed = false;
        auto iter = ready_queue.end();

        print_priority(curr_time, processes);

        for (auto it = ready_queue.begin(); it < ready_queue.end(); it++)
        {
            auto proc = *it;

            if (proc->pid == highest_priority_process->pid)
            {
                proc->run(curr_time);
                completed = (proc->state == COMPLETED);
                iter = it;
            }
            else
            {
                proc->wait();
            }

            proc->setPriority();
        }

        if (completed && iter != ready_queue.end())
            ready_queue.erase(iter);

        curr_time++;

        if (job_queue.empty() && ready_queue.empty())
            break;
    }
}

void print_priority(int curr_time, vector<Process *> processes)
{
    cout << endl
         << "(t = " << curr_time << ")" << endl;
    cout << left << setw(10) << "Process"
         << "| Priority" << endl;
    cout << "----------+---------" << endl;

    for (auto proc : processes)
    {
        if (proc->state == READY)
            cout << left << setw(10) << proc->process_name << "| " << proc->priority << endl;
    }
}

void print_gantt_chart()
{
    cout << endl
         << "Gantt Chart:" << endl;

    for (int i = 0; i < running_queue.size(); i++)
        cout << "+" << string(running_queue[i]->process_name.length() + 2, '-');

    cout << "+" << endl;
    for (auto p : running_queue)
        cout << "| " << p->process_name << " ";

    cout << "|" << endl;
    for (int i = 0; i < running_queue.size(); i++)
        cout << "+" << string(running_queue[i]->process_name.length() + 2, '-');

    cout << "+" << endl;
}

bool cmp(Process *a, Process *b)
{
    if (a->arrival_time < b->arrival_time)
        return true;

    if (a->arrival_time == b->arrival_time && a->estimated_run_time < b->estimated_run_time)
        return true;

    return false;
}

vector<Process *> get_processes()
{
    vector<Process *> processes;

    int num;
    cout << "Enter no. of processes: ";
    cin >> num;

    while (num--)
    {
        string name;
        int arrival_time, estimated_run_time;
        cout << "-----------------------------" << endl;
        cout << "Enter process name: ";
        cin >> name;
        cout << "Enter arrival time: ";
        cin >> arrival_time;
        cout << "Enter estimated run time: ";
        cin >> estimated_run_time;
        processes.push_back(new Process(name, arrival_time, estimated_run_time));
    }
    sort(processes.begin(), processes.end(), cmp);

    return processes;
}

void print_process_table(vector<Process *> processes)
{
    cout << "+-----------+--------------+------------+" << endl;
    cout << "| " << left << setw(10) << "Name" << setw(15) << "| Arrival Time" << setw(15) << "| Burst Time |" << endl;
    cout << "+-----------+--------------+------------+" << endl;
    // Print the table rows
    for (auto p : processes)
    {
        cout << "| " << left << setw(10) << p->process_name << "| " << setw(13) << p->arrival_time << "| " << setw(11) << p->estimated_run_time << "|" << endl;
    }
    cout << "+-----------+--------------+------------+" << endl;
}

void print_waiting_time(vector<Process *> processes)
{
    cout << endl
         << "Waiting Time: " << endl;
    cout << "+-----------+--------------+------------+-----------------+--------------+" << endl;
    cout << "| " << left << setw(10) << "Name" << setw(15) << "| Arrival Time" << setw(13) << "| Burst Time" << setw(18) << "| Turnaround Time" << setw(15) << "| Waiting Time |" << endl;
    cout << "+-----------+--------------+------------+-----------------+--------------+" << endl;
    // Print the table rows
    int total_time_waited = 0;
    for (auto p : processes)
    {
        total_time_waited += p->turnaround_time - p->estimated_run_time;
        cout << "| " << left << setw(10) << p->process_name << "| " << setw(13) << p->arrival_time << "| " << setw(11) << p->estimated_run_time << "| " << setw(16) << p->turnaround_time << "| " << setw(13) << p->turnaround_time - p->estimated_run_time << "|" << endl;
    }
    cout << "+-----------+--------------+------------+-----------------+--------------+" << endl;
    cout << "Avg. Waiting Time: " << float(total_time_waited) / processes.size() << endl;
}

int main(void)
{

    // processes.push_back(new Process("A", 1, 5));
    // processes.push_back(new Process("B", 1, 2));
    // processes.push_back(new Process("C", 8, 2));
    vector<Process *> processes = get_processes();
    if (processes.size() == 0)
    {
        cout << "No processes to Run.";
        return 1;
    }
    print_process_table(processes);
    run_process(processes);
    print_gantt_chart();
    print_waiting_time(processes);
}