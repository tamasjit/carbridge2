#include <stdio.h>
#include <stdbool.h>

int processCount;
int resourcesCount;
char ret;
char prsVals[4] = "ABCD";

#define ANSI_BG_BLUE "\x1b[44;1m"
#define ANSI_BG_RED "\x1b[41;1m"
#define ANSI_BG_GREEN "\x1b[43;1m"
#define ANSI_BG_BLACK "\x1b[40;1m"

// print title
int printTitle()
{
    // clear the previous outputs
    system("clear");
    // print title
    printf(ANSI_BG_BLUE "\n\n                            \n");
    printf("     Banker's Algorithm     \n");
    printf("                            \n" ANSI_BG_BLACK);
}

// take input
int takeInput()
{
    printTitle();
    printf("\nEnter the number process: ");
    scanf("%d", &processCount);
    printf("Enter the number resources: ");
    scanf("%d", &resourcesCount);

    // check for valid input
    if (processCount > 6 || processCount < 3)
    {
        printf("\nProcess must be in between 3 and 6!\n\n");
        return 0;
    }
    // check for valid input
    else if (resourcesCount > 4 || resourcesCount < 3)
    {
        printf("\nResources must be in between 3 and 4!\n\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

// calculate the need of all the process
void calculateNeed(int need[processCount][resourcesCount], int max[processCount][resourcesCount],
                   int alloc[processCount][resourcesCount])
{
    for (int i = 0; i < processCount; i++)
        for (int j = 0; j < resourcesCount; j++)
            // need = max - allocation
            need[i][j] = max[i][j] - alloc[i][j];
}

int checkSafe(
    int alloc[processCount][resourcesCount],
    int max[processCount][resourcesCount],
    int avvail[resourcesCount])
{

    int need[processCount][resourcesCount];
    calculateNeed(need, max, alloc);
    bool finish[processCount];
    int work[resourcesCount];
    int sequence[processCount];
    int finishCount = 0;

    for (int i = 0; i < resourcesCount; i++)
        work[i] = avvail[i];

    while (finishCount < processCount)
    {
        int found = 0;
        for (int p = 0; p < processCount; p++)
        {

            if (finish[p] == 0)
            {
                int j;
                int temp = 1;
                for (j = 0; j < resourcesCount; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == resourcesCount)
                {
                    for (int k = 0; k < resourcesCount; k++)
                        work[k] += alloc[p][k];

                    sequence[finishCount++] = p;

                    finish[p] = 1;

                    found = true;
                }
            }
        }

        if (found == false)
        {
            return false;
        }
    }
    // // printTitle();
    // for (int i = 0; i < processCount; i++)
    //     printf("%d ", sequence[i]);
    return true;
}

int main()
{
    if (!takeInput())
    {
        return 0;
    }

    int allocArray[processCount][resourcesCount];
    int maxArray[processCount][resourcesCount];
    int avvArray[resourcesCount];

    for (int a = 0; a < processCount; a++)
    {
        printTitle();
        printf(ANSI_BG_RED "                            \n");
        printf("          Allocation        \n");
        printf("                            \n" ANSI_BG_BLACK);
        printf("\nEnter Process %d (P%d) Values  \n\n", a, a);
        for (int b = 0; b < resourcesCount; b++)
        {
            printf("%c: ", prsVals[b]);
            scanf("%d", &allocArray[a][b]);
        }
    }

    for (int a = 0; a < processCount; a++)
    {
        printTitle();
        printf(ANSI_BG_RED "                            \n");
        printf("             MAX            \n");
        printf("                            \n" ANSI_BG_BLACK);
        printf("\nEnter Process %d (P%d) Values  \n\n", a, a);
        for (int b = 0; b < resourcesCount; b++)
        {
            printf("%c: ", prsVals[b]);
            scanf("%d", &maxArray[a][b]);
        }
    }

    printTitle();
    printf(ANSI_BG_RED "                            \n");
    printf("          Available         \n");
    printf("                            \n\n" ANSI_BG_BLACK);

    for (int b = 0; b < resourcesCount; b++)
    {
        printf("%c: ", prsVals[b]);
        scanf("%d", &avvArray[b]);
    }

    if (checkSafe(allocArray, maxArray, avvArray))
    {
        printTitle();
        printf("\n");
        printf(ANSI_BG_GREEN "                            \n");
        printf("       System is safe!      \n");
        printf("                            \n");
        printf(ANSI_BG_BLACK "\n");
    }
    else
    {
        printTitle();
        printf(ANSI_BG_RED "                            \n");
        printf(ANSI_BG_RED "     System is not safe!    \n");
        printf("                            \n");
        printf(ANSI_BG_BLACK "\n");
    }
}