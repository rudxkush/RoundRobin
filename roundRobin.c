# RoundRobin
#include <stdio.h>

struct Process
{
    int Process_no;
    int burst_time;
    int arrival_time;
    int completion_time;
    int io_burst;
    int priority;
    int Turn_Around_time;
    int waiting_time;
    int timeQuantum;
};

int main()
{
    struct Process process[3];
    for(int i = 0; i < 3; i++)
    {
        printf("Enter process id: ");
        scanf("%d", &process[i].Process_no);
        printf("Enter process burst time: ");
        scanf("%d", &process[i].burst_time);
        printf("Enter process arrival time: ");
        scanf("%d", &process[i].arrival_time);
        printf("Enter process completion time: ");
        scanf("%d", &process[i].completion_time);
        printf("Enter process I/O burst time: ");
        scanf("%d", &process[i].io_burst);
        printf("Enter process priority: ");
        scanf("%d", &process[i].priority);
        process[i].completion_time = 0;
        process[i].waiting_time = 0;
        process[i].Turn_Around_time = 0;
        process[i].timeQuantum = 2;
    }

    // Sort processes by arrival time
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2 - i; j++)
        {
            if (process[j].arrival_time > process[j+1].arrival_time)
            {
                struct Process temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }

    // Run round-robin scheduling
    int time = process[0].arrival_time;
    int remaining_time[3];
    for (int i = 0; i < 3; i++)
    {
        remaining_time[i] = process[i].burst_time;
    }

    int count = 0;
    while (count < 3)
    {
        for (int i = 0; i < 3; i++)
        {
            if (process[i].arrival_time <= time && remaining_time[i] > 0)
            {
                if (remaining_time[i] <= process[i].timeQuantum)
                {
                    time += remaining_time[i];
                    process[i].completion_time = time;
                    process[i].Turn_Around_time = process[i].completion_time - process[i].arrival_time;
                    process[i].waiting_time = process[i].Turn_Around_time - process[i].burst_time;
                    remaining_time[i] = 0;
                    count++;
                }
                else
                {
                    time += process[i].timeQuantum;
                    remaining_time[i] -= process[i].timeQuantum;
                }
            }
        }
    }
    // Output results
    printf("Process No.\tBurst Time\tArrival Time\tCompletion Time\tI/O Burst Time\tPriority\tTA Time\t\tWaiting Time\n");
    for (int i = 0; i < 3; i++)
       {
        process[i].Turn_Around_time = process[i].burst_time + process[i].waiting_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process[i].Process_no, process[i].burst_time, process[i].arrival_time,
               process[i].completion_time, process[i].io_burst, process[i].priority, process[i].Turn_Around_time, process[i].waiting_time);
       }
     return 0;
}
