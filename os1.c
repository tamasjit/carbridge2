#include<stdio.h>


int waitN[20];
int waitS[20];
int xn,xs;

struct lock{
    int lck;
};
void lock_init(struct lock lok){
    lok.lck = 0;
}
struct bridge{

    int north_waiting;
    int north_crossing;
    int north_consecutive;

    int south_waiting;
    int south_crossing;
    int south_consecutive;

    struct lock lk;
}Osbridge;

void bridge_init(struct bridge os)
{
    os.north_waiting = 0;
    os.north_crossing = 0;
    os.north_consecutive = 0;
    os.south_consecutive = 0;
    os.south_crossing = 0;
    os.south_waiting = 0;

    lock_init(os.lk);
}



//lock acquire
void lock_acquire_north()
{
    Osbridge.lk.lck = 2;
}
void lock_acquire_south()
{
    Osbridge.lk.lck = 1;
}


// empyty wait
void emptywaitN(){

    int z;
    for(z = 0; z < xn; z++)
    {
        printf("Process North %d gets executed :: ",waitN[z]);
    }
    puts("");
    xn = 0;

}

void emptywaitS(){

    int z;
    for(z = 0; z < xs; z++)
    {
        printf("Process south %d gets executed :: ",waitS[z]);
    }
    puts("");
    xs = 0;

}


//check
void bridge_arrive_north(int j)
{
    if(Osbridge.lk.lck == 0 || Osbridge.lk.lck == 2)
            {
                printf("Process North %d executed \n",j);
                lock_acquire_north();
            }
            else
            {
                printf("Process North %d goes to waiting\n",j);
                waitN[xn] = j;
                xn++;
                if(xn >= 5)
                {
                    lock_acquire_north();
                    emptywaitN();
                }
            }
}

void bridge_arrive_south(int k)
{
    if(Osbridge.lk.lck == 0 || Osbridge.lk.lck == 1)
            {
                printf("\tProcess South %d executed \n",k);
                lock_acquire_south();
            }
            else
            {
                printf("Process South %d goes to waiting\n",k);
                waitS[xs] = k;
                xs++; 
                if(xs >= 5)
                {
                    lock_acquire_south();
                    emptywaitS();
                }
            }
}





int north_cars, south_cars;
int main()
{
	int i;
    
    printf("::::::::::::We assume that the cars are inputted acoording to arrival time in ascending order::::::\n\n\n");


    printf("%s","Total Numbers of North Cars : ");
    scanf("%d",&north_cars);
    int north_arival[north_cars];
    for( i = 0; i < north_cars; i++)
    {
    	printf("Arrival Time of %d car : ",i+1);
    	scanf("%d",&north_arival[i]);
	}
	
	printf("%s","Total Numbers of South Cars : ");
    scanf("%d",&south_cars);
    int south_arival[south_cars];
    for( i = 0; i < south_cars; i++)
    {
    	printf("Arrival Time of %d car : ",i+1);
    	scanf("%d",&south_arival[i]);

	}

    printf(":::::::::NOrth Cars:::::::::\n");
    printf("No.\tArrival\tLeave\n");
    for(i = 0; i < north_cars; i++)
    {
        printf("%d\t%d\n",i,north_arival[i]);
    }

    printf(":::::::::SOrth Cars:::::::::\n");
    printf("No.\tArrival\tLeave\n");
    for(i = 0; i < south_cars; i++)
    {
        printf("%d\t%d\n",i,south_arival[i]);
    }

    // Input SetUp done; 
    bridge_init(Osbridge);
    
    i = 0;
    int j = 0;
    int k = 0;
    

    do{
        if(north_arival[j] <= south_arival[k])
        {
            bridge_arrive_north(j);
            j++;
            
        }
        else
        {
            bridge_arrive_south(k);
            k++; 
        }
    }while(j < north_cars && k < south_cars);


    emptywaitS();
    emptywaitN();
    if(j == north_cars)
    {
        for(k; k <south_cars; k++)
        {
            printf("Process South %d executed\n",k);
        }
    }
    else
    {
        for(j; j <north_cars; j++)
        {
            
            printf("Process North %d executed\n",j);
        }
    }
    


}