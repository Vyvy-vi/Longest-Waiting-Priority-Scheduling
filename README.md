# CSE - 316 (Operating System) Assignment - 2

**Question 2** - Consider a scheduling approach which is pre-emptive similar to shortest remaining time first in nature. The priority of each job is dependent on its estimated run time, and also the amount of time it has spent waiting. Jobs gain higher priority the longer they wait, which prevents indefinite postponement. The jobs that have spent a long time waiting compete against those estimated to have short run times.

The priority can be computed as : `Priority = 1 + Waiting time / Estimated run time`

Write a program to implement such an algorithm. Ensure -
1. The input is given dynamically at run time by the user
2. The priority of each process is visible after each unit of time
3. The gantt chart is shown as an output
4. Calculate individual waiting time and average waiting time


# Outputs

## Output - 1

3 Processes A, B and C with the following arrival times and estimated run times were dynamically inputted -

| Name | Arrival Time| Estimated Run Time |
| :-: | :-: | :-: |
| A  | 1  | 2 |
| B  | 1  | 5 |
| C  | 3  | 3 |


![](https://i.imgur.com/ma4HW27.png)
![](https://i.imgur.com/YxcDpux.png)
![](https://i.imgur.com/8zog12r.png)

## Output - 2

2 Processes A and B and C with the following arrival times and estimated run times were dynamically inputted -

| Name | Arrival Time| Estimated Run Time |
| :-: | :-: | :-: |
| A  | 0  | 1 |
| B  | 0  | 2 |

![](https://i.imgur.com/MydUPIc.png)
![](https://i.imgur.com/0ehvIiO.png)
