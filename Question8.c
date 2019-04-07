#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

//structure for a process
struct process
{
    //process ID
    int pid[5];
    //arrival time
    int atime;
     //burst time
    int btime;
    //completion time
    int ctime;
    //temporary burst time
    int tempbt;

}student[100], faculty[100], complete[100];
//faculty queue, student queue and final queue(combining faculty and student


int n, fcount=0, scount=0, ccount=0, quanta;
//number of process in each queue and time quantum

//insertion sort to sort the process based on their arrival times
void insertionSort()
{
    int i, j;
    //temp variable to store a structure
    struct process key;

    for (i = 1; i < ccount; i++) {
        key = complete[i];
        j = i - 1;
        //if arrival time of any previous process is less than swap the process
        //until the process is at it's correct position
        while (j >= 0 && complete[j].atime > key.atime) {
            complete[j+1] = complete[j];
            j = j - 1;
        }
        complete[j+1] = key;
    }
}

//Round Robin algorithm
void rralgo(){

	//time = complete[0].atime is used for initializing the time with the first arrived process's arrival time
    int time = complete[0].atime, cc=0, i, j, check;

    //while the total time is less than 120 minutes and
    //all the processes are not processes we'll run the loop
	while(time!=120 && cc!=ccount){
    //iterate through the processes
		for(i=0; i<ccount; i++){
		    //when arrival time is less than the starting time
            if(complete[i].atime<=time ){
            //when burst time is grater than time quantum
			if(complete[i].tempbt > quanta){
				time += quanta;
				complete[i].tempbt -= quanta;
			}
            //when burst time is less than time quantum
			else if(complete[i].tempbt <=quanta && complete[i].tempbt!=0){
				time += complete[i].tempbt;
				complete[i].tempbt =0;
				complete[i].ctime = time;
				cc++;
			}
            }
            //if arrival time is greater than the present time
            else{
                check=0;
                for(j=0;j<i;j++)
                {
                    //to check if any process above is yet to be completed
                    //if not then present time is set to arrival time of this process
                    if((complete[j].atime<complete[i].atime) && (complete[j].tempbt!=0))
                    {
                        check++;
                        break;
                    }
                }
                //if no process is present to execute int the current time
                //we increase the present time to the closest process's arrival time
                if(check==0)
                {
                    time=complete[i].atime;
                }
                continue;
            }
		}
	}
	//if  time limit exceeds then issue a warning because Sudesh can run the system
	//from 10am to 12pm only
	if(time>120)
        {
            printf("\nTime limit exceeded! Results will still show.\n");
        }
}

//Printing the details
void display(){
	int i=0, total=0, total_res=0,a, c, ar[100], j=0;
	double average;
	system("cls");
	printf("\n-------------Scheduling Details----------------\n");
	printf("-----------------------------------------------");
	printf("\nA.T. - Arrival Time\nB.T. - Burst Time\nC.T. - Completion Time\nR.T. - Resolving Time\nT.A.T - Turn Around Time\nW.T. - Waiting Time\n");
	printf("-----------------------------------------------");
	printf("\n PID\t| A.T\t| R.T.\t| C.T.\t| T.A.T\t| W.T.");
	printf("\n-----------------------------------------------");
	for(i; i<ccount; i++){
        //if the completion time exceeds 120 minutes then to put in a proper format this is being used
        if(complete[i].ctime>120)
        {
            c=complete[i].ctime-120;
            c+=1200;
            ar[j]=i;
            j++;
        }
        //if the completion time exceeds 60 minutes then to put in a proper format this is being used
        else if(complete[i].ctime>60)
        {
           c=complete[i].ctime-60;
           c+=1100;
        }
        //else simply add to the completion time
        else
        {
            c=complete[i].ctime+1000;
        }

        if(complete[i].atime>120)
        {
            a=complete[i].atime-120;
            a+=1200;
        }
        else if(complete[i].atime>60)
        {
            a=complete[i].atime-60;
            a+=1100;
        }
        else{
            a=complete[i].atime+1000;
        }

		printf("\n %s\t| %d\t| %d\t| %d\t| %d\t| %d",
		complete[i].pid, a, complete[i].btime, c, (complete[i].ctime-complete[i].atime), ((complete[i].ctime-complete[i].atime)- complete[i].btime));
		total_res+= (complete[i].ctime-complete[i].atime);
	}

	//average time spend on a query=sum total of time spent on all queries/Number of queries present
	average = total_res/ccount;
    if(j!=0){
    printf("\n\nProcess_ID");

    //loop to print the processes whose completion time exceeded 1200 hours
	for(i=0;i<j;i++)
    {
        printf(", '%s'", complete[ar[i]].pid);
    }
    printf(" were not able to complete because their time crossed 1200.");
    }
	printf("\n\n-->Total Time spent on handling queries: %d Minutes\n", total_res);
	printf("\n-->Average Query time: %.2f Minutes\n", average);
	printf("\n-----Processes complete-----\n");
}

//function to make the final request queue that merges student and faculty based on
//arrival times, and faculty is give priority if arrival time is same
void all_processes()
{
    //temporary student and faculty count
    int tempsc=0, tempfc= 0, min, flag;

    //if both the queues are not empty
	if( fcount!=0  && scount!=0){

        //loop till all the processes are not completed
		while(tempsc<scount && tempfc<fcount){
            //if arrival time of student and faculty is same then
            //faculty is given the higher priority
			if(faculty[tempfc].atime == student[tempsc].atime){
				complete[ccount] = faculty[tempfc];
				ccount++;
				tempfc++;
				complete[ccount]= student[tempsc];
				ccount++;
				tempsc++;
			}

            //else the process with less arrival time is added to the final queue
			else if(faculty[tempfc].atime < student[tempsc].atime){
				complete[ccount]= faculty[tempfc];
				ccount++;
				tempfc++;
			}

			else if(faculty[tempfc].atime > student[tempsc].atime){
				complete[ccount]= student[tempsc];
				ccount++;
				tempsc++;
			}
		}
        //check the count of queries in final and add remaining queries to final queue
		if(ccount != (fcount+scount)){
			if(fcount!=tempfc){
				while(tempfc!=fcount){
					complete[ccount]= faculty[tempfc];
					ccount++;
					tempfc++;
				}
			}
			else if(scount!=tempsc){
				while(tempsc!=scount){
					complete[ccount]= student[tempsc];
					ccount++;
					tempsc++;
				}
			}
		}
	}

	//if no faculty query is there simply add all students to final queue
	//this will lead to less time consumption
	else if(fcount==0){
		while(tempsc!=scount){
			complete[ccount]= student[tempsc];
			ccount++;
			tempsc++;
		}
	}
	//if no student query is there simply add all faculty to final queue
	else if(scount==0){
		while(tempfc!=fcount){
			complete[ccount]= faculty[tempfc];
			ccount++;
			tempfc++;
		}
	}
	//if no processes are there
	else {
		printf("\n No Processes are available\n");
	}
}

void input()
{
    int type, i=0, time=0;
    scount=0, fcount=0, ccount=0;
    //ask the user for the total number of processes
    printf("\nEnter total number of processes: ");
    scanf("%d", &n);

    //if user enters 0 no process available and exit
	if(n==0){
         printf("\n No processes\n");
         exit(0);
          }

	else{

        //ask user to enter time quantum
		printf("\nEnter time quantum for each Process: ");
		scanf("%d", &quanta);

        //ask whether the process is faculty or a student
		printf("\nEnter 1 for Faculty and 2 for Student\n");
		for(i=0; i<n; i++){

			printf("\nProcess Type (Enter 1 or 2): ");
			scanf("%d", &type);

			//FOR FACULTY
			if(type==1){
				printf("Process Id: ");
				scanf("%s", faculty[fcount].pid);;

				printf("Arrival Time: ");
				scanf("%d", &time);

                //if user enter wrong time, exit the program
				if(time<1000 || time>1200){
                    system("cls");
					printf("\nEnter Correct time");
					printf("Program closed");
					exit(0);
				}

				else{
                        //convert the time from the format to simple minutes
                        if(time>=1100 && time<=1160)
                        {
                            faculty[fcount].atime=(time-1100)+60;
                        }
                        else if(time>=1000 && time<=1060)
                        {
                            faculty[fcount].atime=time-1000;
                        }
                        else{
                            system("cls");
                            printf("Do no enter minutes part greater than 60");
                            printf("Program closed");
                            exit(0);
                        }
                }

				printf("Burst Time: ");
				scanf("%d", &faculty[fcount].btime);
				//also copy burst time in one more variable
				faculty[fcount].tempbt=faculty[fcount].btime;
				fcount++;

			}

            //FOR STUDENT
            else{

				printf("Process Id: ");
				scanf("%s", student[scount].pid);

				printf("Arrival Time: ");
				scanf("%d", &time);

				if(time<1000 || time>1200){
                    system("cls");
					printf("\nEnter Correct time\n");
					printf("Program closed");
					exit(0);
				}

				else {
                        if(time>=1100 && time<=1160)
                        {
                           student[scount].atime=(time-1100)+60;
                        }
                        else if(time>=1000 && time<=1060)
                        {
                            student[scount].atime=time-1000;
                        }
                        else{
                            system("cls");
                            printf("Do no enter minutes part greater than 60");
                            printf("Program closed");
                            exit(0);
                        }
                }

				printf("Burst Time: ");
				scanf("%d", &student[scount].btime);

				student[scount].tempbt=student[scount].btime;
				scount++;
			}
		}
	}
}

int main()
{
    //instruction
    printf("Instructions:\n-Time format is HHMM (First two digit are for hours next two for minutes)\n Example: 10:30 would be written as 1030.\n-Make sure time is between 1000 and 1200 and minute part shouldn't exceed 60.\n-Time units used: Minutes.\n-Faculty type queries are given priority. Enter 1 for Faculty and 2 for Student in process type.\n-Process ID can be a string of length less than 5.\n-Wrong input will lead to program termination!\n\n");
    //function to input data
    input();
    //function used to combine the faculty process queue and student process queue into a single queue
    all_processes();
    //function to sort all the processes in ascending order of their arrival times
    insertionSort();
    //Round robin algorithm performed on the final queue that is obtained

    rralgo();
    display();

    return 0;
}
