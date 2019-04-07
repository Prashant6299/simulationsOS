#include<stdio.h>
#include<stdbool.h>

// constant integer for number of resources present
const int Resource = 3;

// constant integer for number of processes
const int Process = 5;

// Calculating need matrix
void calNeedMatrix(int needMatrix[Process][Resource], int maximum[Process][Resource], int allot[Process][Resource])
{
    // Calculating Need of each process
    int i, j;
    for (i = 0 ; i < Process ; i++)
        for (j = 0 ; j < Resource ; j++){
            // Need  = maximum  - allocated
            needMatrix[i][j] = maximum[i][j] - allot[i][j];}
}

// Function to find the system is in safe state or not
bool safeState(int processes[], int Maximum[][Resource],
            int allot[][Resource], int avail[])
{
    int needMatrix[Process][Resource];

    // Function to calculate need matrix
    calNeedMatrix(needMatrix, Maximum, allot);

    // marking the completed processes as true
    bool completed[] = {false, false, false, false, false};

    //safe sequence
    int SSeq[Process];

    // copy of available resources
    int tempAvail[Resource];
    int i;
    for (i = 0; i < Resource ; i++)
        tempAvail[i] = avail[i];

    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < Process)
    {
        bool check = false;
        int p;
        for (p = 0; p < Process; p++)
        {
            // check if the corresponding process has completed or not
            if (completed[p] == false)
            {
                // check the need of the processes
                int j;
                for (j = 0; j < Resource; j++)
                    if (needMatrix[p][j] > tempAvail[j])
                        break;

                // If all needs of p were satisfied.
                if (j == Resource)
                {
                    // all the allocated resources are added
                    // to available resources for that process
                    int k;
                    for (k = 0 ; k < Resource ; k++)
                        tempAvail[k] += allot[p][k];

                    // Add this process to safe sequence.
                    SSeq[count++] = p;

                    // Mark this p as finished
                    completed[p] = true;

                    check = true;
                }
            }
        }

        // if no process can be processed further
        if (check == false)
        {
            printf("System is not in safe state");
            return false;
        }
    }

    // Safe Sequence
    printf("\nSystem is in safe state.\n\nSafe sequence is: ");
    for (i = 0; i < Process ; i++)
        printf("P0%d\t", SSeq[i] );
    printf("\n\n");
    return true;
}

int main()
{
    //process name/ID
    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int available[] = {3, 3, 2};

    // Maximum resources that can be alloted to
    int maximum[5][3] =  {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};

    // Resources allocated to processes
    int allot[5][3] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1},
                      {0, 0, 2}};

    // Check system is in safe state or not
    safeState(processes, maximum, allot, available);

    return 0;
}
