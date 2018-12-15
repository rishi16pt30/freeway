#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<time.h>
#include"adsproject.cpp"
#include"adspackage.cpp"
using namespace std;
class Flight
{
    public:
        int start_hr,start_min,start_sec;
        int end_hr,end_min,end_sec;
        int flight_color;
        string flight_number;
        int time;
        int runway_number;
        int index;
        Flight()
        {
            this->runway_number=0;
        }
        void print()
        {
        cout<<start_hr<<"  "<<start_min<<"  "<<start_sec<<"  "<<end_hr<<"  "<<end_min<<"  "<<end_sec<<"  ";
        }

};
bool isEdge(int starthr1,int startmin1,int startsec1,int endhr1,int endmin1,int endsec1,int starthr2,int startmin2,int startsec2)
{
    if((starthr2>=starthr1 && starthr2<=endhr1) && (startmin2>=startmin1 && startmin2<=endmin1) && (startsec2>=startsec1 && startsec2<=endsec1))
    {
        return true;
    }
    else
    {
        return false;
    }
}
int timeout ( int seconds )
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}
    return  1;
}


int main()
{
    int tot_no_flights;
    int hour,minutes,seconds;
    int tot_duration;
    int tot_runways;
    int day,month,year;
    int temp;

    cout<<"\n*********************************************************************************************************************"<<endl;
    cout<<"\n*****************WELCOME TO THE PACKAGE   (AIR TRAFFIC CONTROL USING VERTEX COLOURING AND HEAP)***********************";
    cout<<endl<<endl;
    cout<<"**********************************************************************************************************************"<<endl;


    cout<<"ENTER  TODAY'S  DATE......."<<endl;
    scanf("%d/%d/%d",&day,&month,&year);

    if((day >31 || day<0) || (month >12 || month<0) || (year>2018))
    {
        cout<<"ERROR..!!";
        cout<<"Date set to default";
        day=12;
        month=12;
        year=2012;
    }

    cout<<"ENTER THE TOTAL NUMBER OF FLIGHTS / AEROPLANES "<<endl;
    cin>>tot_no_flights;

    cout<<"ENTER THE TOTAL NUMBER OF RUNWAYS  :"<<endl;
    cin>>tot_runways;

    Flight flight[tot_no_flights];


    for(int i=0;i<tot_no_flights;i++)
    {
        system("cls");
        cout<<"ENTER THE FLIGHT TIMINGS IN HH : MM : SS - (24- HOUR FORMAT)"<<" DATE : "<<day<<" / "<<month<<" / "<<year<<endl;
        cout<<"ENTER THE FLIGHT TIMINGS IN HH:MM:SS "<<"FOR FLIGHT "<<i+1<<endl;

        cout<<"ENTER THE START TIMING :"<<endl;
        scanf("%d:%d:%d",&flight[i].start_hr,&flight[i].start_min,&flight[i].start_sec);
        if((flight[i].start_hr>24 || flight[i].start_hr<0) || (flight[i].start_min>60 || flight[i].start_min<0) ||((flight[i].start_sec>60 || flight[i].start_sec<0)))
        {
            cout<<"ERROR..!!";
            cout<<"Time set to default";
            flight[i].start_hr=10;
            flight[i].start_min=10;
            flight[i].start_sec=0;
        }
        temp=flight[i].start_hr*10000+flight[i].start_min*100+flight[i].start_sec;
        flight[i].time=temp;

        cout<<"ENTER THE END   TIMING :"<<endl;
        scanf("%d:%d:%d",&flight[i].end_hr,&flight[i].end_min,&flight[i].end_sec);
        if((flight[i].end_hr>24 || flight[i].end_hr<0) || (flight[i].end_min>60 || flight[i].end_min<0) ||((flight[i].end_sec>60 || flight[i].end_sec<0)))
        {
            cout<<"ERROR..!!";
            cout<<"Time set to default";
            flight[i].end_hr=10;
            flight[i].end_min=30;
            flight[i].end_sec=0;
        }

        cout<<"ENTER THE FLIGHT NUMBER :"<<endl;
        cin>>flight[i].flight_number;

    }


    Graph flight_graph(tot_no_flights);
    //flight_graph.printGraph();

    for(int i=0;i<tot_no_flights;i++)
    {
        cout<<endl;
        for(int j=i+1;j<tot_no_flights;j++)
        {
            if(isEdge(flight[i].start_hr,flight[i].start_min,flight[i].start_sec,flight[i].end_hr,flight[i].end_min,flight[i].end_sec,flight[j].start_hr,flight[j].start_min,flight[j].start_sec)==true)
            {
                flight_graph.addEdge(i,j);
            }
        }

    }

    //flight_graph.printGraph();

    int k=flight_graph.mincolor();
    k=3;

    int different_flight_colour[k];

    string temp_flight_no[k];


    if(k >tot_runways)
    {
        cout<<"ERROR.......!!!!!!....TOTAL NUMBER OF RUNWAYS IS VERY LESS...!!"<<"WE NEED ATLEAST "<<k<<" RUNWAYS"<<endl;
        cout<<"YOU HAVE TO CHANGE SOME FLIGHT TIMING....!!!!!";
        exit(0);
    }
    else
    {
        cout<<"WE HAVE SUFFICIENT RUNWAYS TO ACCOMODATE THE FLIGHTS";
        cout<<endl;
        cout<<"WE NEED "<<k<<" RUNWAYS"<<endl;
    }
    if(timeout(5)==1)
    {
        system("cls");
    }
    for(int i=0;i<tot_no_flights;i++)
    {
        flight[i].runway_number=assign_color[i];
    }
    for(int i=0;i<tot_no_flights;i++)
        cout<<flight[i].runway_number<<endl;

    MinHeap Heap(tot_no_flights);

    for(int i=0;i<tot_no_flights;i++)
    {
        Heap.InsertKey(flight[i].time);
    }

    cout<<endl;

    int minimum;
    system("cls");
    for(int i=0;i<tot_no_flights;i++)
    {
            //system("cls");
            minimum=Heap.ExtractMin();
            for(int j=0 ; j<tot_no_flights; j++)
            {
                if(minimum==flight[j].time)
                {
                    cout<<endl;
                    cout<<"FLIGHT NUMBER                        :"<<"   "<<flight[j].flight_number<<endl;
                    cout<<"READY TO TAKE OFF AT RUNWAY NUMBER   :"<<"   "<<flight[j].runway_number<<endl;
                    cout<<"DEPARTURE TIME                       :"<<"   "<<flight[j].end_hr<<" : "<<flight[j].end_min<<" : "<<flight[j].start_sec<<endl;
                    cout<<endl;
                }
            }
    }


}


