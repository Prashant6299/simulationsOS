This repository contains 2 programs for the given question statements:

Ques. 8. Sudesh Sharma is a Linux expert who wants to have an online system where he can handle student queries. Since there can be multiple requests at any time he wishes to dedicate a fixed amount of time to every request so that everyone gets a fair share of his time. He will log into the system from 10am to 12am only.  He wants to have separate requests queues for students and faculty. Implement a strategy for the same. The summary at the end of the session should include the total time he spent on handling queries and average query time.

Solution:
I've taken two different queues for faculty and student. Both of them containt their repsective arrival times, burst times, etc. 
As every user must get a fair share of time, I've used Round Robin algorithm for this purpose. But before that we must combine both the faculty and student queries into a single process queue. Faculty queue is given the priorty when merging both the queues. Insertion sort is also used to sort the elements in increasing order of their arrival times to be processed by the Round Robin algorithm.

---------------------------------------------------------------------------------------------------------------------------------

Ques. 19. There are 5 processes and 3 resource types, resource A with 10 instances, B with 5 instances and C with 7 instances. Consider following and write a c code to find whether the system is in safe state or not?

Allocation for:
P0={0,1,0}
P1={2,0,0}
P2={3,0,2}
P3={2,1,1}
P4={0,0,2}

Max for:
P0={7,5,3}
P1={3,2,2}
P2={9,0,2}
P3={2,2,2}
P4={4,3,3}

Available:
A=3
B=3
C=2

Solution: Bankers Algorithm is what I've used here. This algorithm tells us about the safe state and also helps us find the safe sequence. First of all a need matrix is calulated and then the algorithm proceeds further to find the safe sequence.
