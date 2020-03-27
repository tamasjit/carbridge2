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
}os_bridge;
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
void lock_acquire_north()
{
    os_bridge.lk.lck = 2;
}
void lock_acquire_south()
{
    os_bridge.lk.lck = 1;
}
void emptywait_north(){
    int z;
    for(z = 0; z < xn; z++)
    {
        printf("North car %d gets released :: ",waitN[z]);
    }
    puts("");
    xn = 0;
}
void emptywaitS(){

    int z;
    for(z = 0; z < xs; z++)
    {
        printf("South car %d gets released :: ",waitS[z]);
    }
    puts("");
    xs = 0;
}
//check
void bridge_arrive_north(int j)
{
    if(os_bridge.lk.lck == 0 || os_bridge.lk.lck == 2)
            {
                printf("North car %d released \n",j);
                lock_acquire_north();
            }
            else
            {
                printf("North car %d goes to wait\n",j);
                waitN[xn] = j;
                xn++;
                if(xn >= 5)
                {
                    lock_acquire_north();
                    emptywait_north();
                }
            }
}
void bridge_arrive_south(int k)
{
    if(os_bridge.lk.lck == 0 || os_bridge.lk.lck == 1)
            {
                printf("\tSouth car %d released \n",k);
                lock_acquire_south();
            }
            else
            {
                printf("South car %d goes to wait\n",k);
                waitS[xs] = k;
                xs++;
                if(xs >= 5)
                {
                    lock_acquire_south();
                    emptywaitS();
                }
            }
}
int partition(int a[], int low, int high);
void sort_arival(int a[], int low, int high)

{
	if (low < high)
    {
    	
        int pi=partition(a, low, high);
	    sort_arival(a, low, pi - 1);  
        sort_arival(a, pi + 1, high); 
    }
}
 int partition (int a[], int low, int high)
{
    int pivot = a[high];  
    int i = (low-1);  
    int j;
    for ( j = low; j <= high-1; j++)
    {

        if (a[j] <= pivot)
        {
            i++;   
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    int t = a[i + 1];
    a[i+1] = a[high];
    a[high] = t;
    return (i + 1);
}
int north_cars, south_cars;

int main()
{
    int i;    
    printf("%s","Total Numbers of North Cars : ");
    scanf("%d",&north_cars);
    int north_arival[north_cars];
    for( i = 0; i < north_cars; i++)
    {
    	printf("Arrival Time of %d car : ",i+1);
    	scanf("%d",&north_arival[i]);
	}
	sort_arival(north_arival,0,north_cars-1);
	printf("%s","Total Numbers of South Cars : ");
    	scanf("%d",&south_cars);
    	int south_arival[south_cars];
    	for( i = 0; i < south_cars; i++)
    {
    	printf("Arrival Time of %d car : ",i+1);
    	scanf("%d",&south_arival[i]);

	}
	sort_arival(south_arival,0,south_cars-1);

    printf("----------------North Cars----------------\n");
    printf("No.\tArrival\tLeave\n");
    for(i = 0; i < north_cars; i++)
    {
        printf("%d\t%d\n",i,north_arival[i]);
    }

    printf("----------------South Cars----------------\n");
    printf("No.\tArrival\tLeave\n");
    for(i = 0; i < south_cars; i++)
    {
        printf("%d\t%d\n",i,south_arival[i]);
    }
    bridge_init(os_bridge);    
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
    emptywait_north();
    if(j == north_cars)
    {
        for(k; k <south_cars; k++)
        {
            printf("South car %d executed\n ",j);
        }
    }
    else
    {
        for(j; j <north_cars; j++)
        {
            
            printf("North car %d executed\n ",j);
        }
    }   
}