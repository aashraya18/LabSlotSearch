#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<ctime>
#include<stdio.h>
#include<iomanip>
#include<stdlib.h>
using namespace std;
struct BookingRequest
{
    int numberOfUser;
    char name[20];
    bool isConfirmed;
};
struct timeslot
{
    float start;
    float finish;
    int request_count;
    BookingRequest req[1];
};
struct day
{
    char dname[10];
    struct timeslot ts[6];
};
struct lab
{
    char labname[10];
    struct day d[5];
};
struct building
{
    char bname[10];
    struct lab l[4];
}b[2];
void import()
{
    char line[80],ch;
    int i=0;
    ifstream fin;
    fin.open("data.txt",ios::in);
    fin.seekg(0);
    for(i=0;i<2;i++)
    {
        fin.getline(line,80);// change line variable
        strcpy(b[i].bname,line);
        for(int j=0;j<4;j++)
        {
            fin.getline(line,80);
            strcpy(b[i].l[j].labname,line);
            for(int k=0;k<5;k++)
            {
                fin.getline(line,80);
                strcpy(b[i].l[j].d[k].dname,line);
                for(int m=0;m<6;m++)
                {
                    fin.getline(line,80);
                    b[i].l[j].d[k].ts[m].start=atof(line);

                    fin.getline(line,80);
                    b[i].l[j].d[k].ts[m].finish=atof(line);

                    fin.getline(line,80);
                    int request_count=atoi(line);
                    b[i].l[j].d[k].ts[m].request_count=request_count;
                    for(int p=0;p<request_count;p++)
                    {
                        fin.getline(line,80);
                        b[i].l[j].d[k].ts[m].req[p].numberOfUser=atoi(line);
                        fin.getline(line,80);
                        strcpy(b[i].l[j].d[k].ts[m].req[p].name,line);
                        fin.getline(line,80);
                        b[i].l[j].d[k].ts[m].req[p].isConfirmed=atoi(line);
                    }
                }
            }
        }
    }
    fin.close();
}
void export_data()
{
    int i;
    ofstream fout;
    fout.open("data.txt",ios::out);
    for(i=0;i<2;i++)
    {
        fout<<b[i].bname<<endl;
        for(int j=0;j<4;j++)
        {
            fout<<b[i].l[j].labname<<endl;
            for(int k=0;k<5;k++)
            {
                fout<<b[i].l[j].d[k].dname<<endl;
                for(int m=0;m<6;m++)
                {
                    fout<<b[i].l[j].d[k].ts[m].start<<endl;
                    fout<<b[i].l[j].d[k].ts[m].finish<<endl;
                    fout<<b[i].l[j].d[k].ts[m].request_count<<endl;
                    for(int p=0;p<b[i].l[j].d[k].ts[m].request_count;p++)
                    {

                        fout<<b[i].l[j].d[k].ts[m].req[p].numberOfUser<<endl;
                        fout<<b[i].l[j].d[k].ts[m].req[p].name<<endl;
                        fout<<b[i].l[j].d[k].ts[m].req[p].isConfirmed<<endl;
                    }
                }
            }
        }
    }
    fout.close();
}
int get_day()
{
   time_t now = time(0);
   tm *ltm = localtime(&now);
   int a=(int)(ltm->tm_wday)-1;
    return a;
}
int get_time()
{
   time_t now = time(0);
   tm *ltm = localtime(&now);
   return (int)(ltm->tm_hour);
}
void export_new()
{
    int i;
    ofstream fout;
    fout.open("data.txt",ios::out);
    for(i=0;i<2;i++)
    {
        fout<<b[i].bname<<endl;
        for(int j=0;j<4;j++)
        {
            fout<<b[i].l[j].labname<<endl;
            for(int k=0;k<5;k++)
            {
                fout<<b[i].l[j].d[k].dname<<endl;
                for(int m=0;m<6;m++)
                {
                    fout<<b[i].l[j].d[k].ts[m].start<<endl;
                    fout<<b[i].l[j].d[k].ts[m].finish<<endl;
                    b[i].l[j].d[k].ts[m].request_count=0;
                    fout<<b[i].l[j].d[k].ts[m].request_count<<endl;
                }
            }
        }
    }
    fout.close();
}
void confirm()
{
    int day;
    if((int)get_day()==-1)
    {
        day=0;
    }
    else
        day=(int)get_day()+1;
    for(int i=0;i<2;i++)
    {
         for(int j=0;j<4;j++)
        {
            for(int k=0;k<5;k++)
            {
                for(int m=0;m<6;m++)
                {
                    if(k==day)
                    {
                        if((b[i].l[j].d[day].ts[m].request_count)!=0)
                        {

                            b[i].l[j].d[day].ts[m].req[0].isConfirmed=1;
                        }
                    }
                }
            }
        }
    }
}

void booking()
{
    char person_name[100];
    int slot,strength,building,lab_name,day_name;
    cout<<"***************Welcome TO Booking System*****************"<<endl<<endl;
    cout<<"Please enter building \n 0.SJT\t 1.TT"<<endl;
    cin>>building;
    if(building==0)
    {
    cout<<"Please choose lab Number :"<<endl;
    cout<<"0. Lab315"<<endl;
    cout<<"1. Lab316"<<endl;
    cout<<"2. Lab317"<<endl;
    cout<<"3. Lab318"<<endl;
    cin>>lab_name;
    }
    else if(building==1)
    {
    cout<<"Please choose lab Number :"<<endl;
    cout<<"0. Lab215"<<endl;
    cout<<"1. Lab216"<<endl;
    cout<<"2. Lab217"<<endl;
    cout<<"3. Lab218"<<endl;
    cin>>lab_name;
    }
    cout<<"Please enter day :"<<endl;
    int check=0;
    while(check!=1)
    {
        check=0;
        cout<<"0 monday\n1 tuesday \n2 wednesday\n3 thursday\n4 friday\n15 exit"<<endl;
        cin>>day_name;
        if(day_name==15)
        {
            exit(0);
        }
        if((int)get_time()<19)
        {
        if((int)get_day()<day_name||((int)get_day()==-1 && (int)get_time()>=10))
        {
            check=1;
        }
        else if((int)get_day()==5 || (int)get_day()==4)
        {
            cout<<"You can't book now\n Bookings will start after Sunday 10.00"<<endl;
        }
        else if((int)get_day()>=day_name || ((int)get_day()==-1 && (int)get_time()<10))
        {
            cout<<"You can't book now\n Bookings will start after Sunday 10.00"<<endl;
        }
        }
        else
        {
            cout<<"Bookings are closed Please try for next day"<<endl;
        }
    }
    cout<<"Please choose time"<<endl;
    cout<<"0. 8.00  to 9.30"<<endl;
    cout<<"1. 10.00 to 11.30"<<endl;
    cout<<"2. 11.30 to 13.00"<<endl;
    cout<<"3. 14.00 to 15.30"<<endl;
    cout<<"4. 16.00 to 17.30"<<endl;
    cout<<"5. 17.30 to 19.00"<<endl;
    cin>>slot;
    b[building].l[lab_name].d[day_name].ts[slot].request_count+=1;
    cout<<"Enter no of users";
    int  req_no=b[building].l[lab_name].d[day_name].ts[slot].request_count;
    if(req_no==1)
    {
        cin>>b[building].l[lab_name].d[day_name].ts[slot].req[0].numberOfUser;
        cout<<"Please enter your Name :"<<endl;
        cin>>b[building].l[lab_name].d[day_name].ts[slot].req[0].name;
        b[building].l[lab_name].d[day_name].ts[slot].req[0].isConfirmed=0;
    }
    if(req_no>1)
    {
        int strength;
        char name[100];
        cin>>strength;
        if(strength>b[building].l[lab_name].d[day_name].ts[slot].req[0].numberOfUser)
        {
            b[building].l[lab_name].d[day_name].ts[slot].req[0].numberOfUser=strength;
            cout<<"Please enter your Name :"<<endl;
            cin>>name;
            strcpy(b[building].l[lab_name].d[day_name].ts[slot].req[0].name,name);
            cout<<"Request accepted ,please check your confirmation ater 7 pm"<<endl;
        }
        else
        {
            cout<<"Sorry! Someone's request is already there with more number of users"<<endl;
        }
    }
    b[building].l[lab_name].d[day_name].ts[slot].request_count=1;
    export_data();

}
int slotcheck(float t)
{
    if(t>=8 && t<10)
        return 0;
    if(t>=10 && t<11.3)
        return 1;
    if(t>=11.3 && t<14)
        return 2;
    if(t>=14 && t<16)
        return 3;
    if(t>=16 && t<17.3)
        return 4;
    if(t>=17.3 && t<=19)
        return 5;
}
void checkday()
{
    char s[100];
    cout<<"please enter day :"<<endl;
    cin>>s;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"BUILDING NAME"<<"\t"<<"LAB NAME"<<"\t"<<"start time"<<"\t"<<"finish time"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<4;j++)
        {   int k=0;
            for(int k=0;k<5;k++)
            {
                if(strcmpi(b[i].l[j].d[k].dname,s)==0)
                {   int m=0;
                    for(int m=0;m<6;m++)
                    {
                        if((b[i].l[j].d[k].ts[m].start)!=0 && (b[i].l[j].d[k].ts[m].finish)!=0)
                        {
                                cout<<b[i].bname<<"\t\t"<<b[i].l[j].labname<<"\t\t"<<fixed<<setprecision(2)<<b[i].l[j].d[k].ts[m].start<<"\t\t"<<fixed<<setprecision(2)<<b[i].l[j].d[k].ts[m].finish<<"\t\t"<<endl;
                        }
                    }
                }
            }
        }
        cout<<endl;
    }
    cout<<"------------------------------------------------------------------------"<<endl;
}
void checktime()
{
    float time;
    cout<<"enter time in 24 hour format: "<<endl;
    cin>>time;
    int m=slotcheck(time);
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"BUILDING NAME"<<"\t"<<"LAB NAME"<<"\t"<<"start time"<<"\t"<<"finish time"<<"\t"<<"DAY NAME"<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<4;j++)
        {
            int k=0;
            for(int k=0;k<5;k++)
            {
            if((b[i].l[j].d[k].ts[m].start)!=0 && (b[i].l[j].d[k].ts[m].finish)!=0)
            {

                cout<<b[i].bname<<"\t\t"<<b[i].l[j].labname<<"\t\t"<<fixed<<setprecision(2)<<b[i].l[j].d[k].ts[m].start<<"\t\t"<<fixed<<setprecision(2)<<b[i].l[j].d[k].ts[m].finish<<"\t\t"<<b[i].l[j].d[k].dname<<"\t\t"<<endl;

            }
            }
        }
        cout<<endl;
    }
    cout<<"------------------------------------------------------------------------"<<endl;

}
void checklab()
{
    int i,j,check=0;
    char lab_name[10];
    cout<<"Enter lab name:"<<endl;
    cin>>lab_name;
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"BUILDING NAME"<<"\t"<<"start time"<<"\t"<<"finish time"<<"\t"<<"DAY NAME"<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;
    for(i=0;i<2;i++)
    {
        for(j=0;j<4;j++)
        {
            if(strcmpi(b[i].l[j].labname,lab_name)==0)
            {
                check=1;
                break;
            }
        }
        if(check==1)
            break;

    }
    for(int k=0;k<5;k++)
    {
        for(int m=0;m<6;m++)
        {
            if((b[i].l[j].d[k].ts[m].start)!=0 && (b[i].l[j].d[k].ts[m].finish)!=0)
            {
                cout<<b[i].bname<<"\t\t"<<fixed<<setprecision(2)<<b[i].l[j].d[k].ts[m].start<<"\t\t"<<fixed<<setprecision(2)<<b[i].l[j].d[k].ts[m].finish<<"\t\t"<<b[i].l[j].d[k].dname<<endl;
            }
        }
    }
    cout<<"------------------------------------------------------------------------"<<endl;

}
void checkstatus()
{
    int d=0;
    if((int)get_time()>19)
        d=(int)get_day()+1;
    cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"BUILDING NAME"<<"\t"<<"LAB NAME"<<"\t"<<"FREE SLOT START TIME"<<"\t"<<"FREE SLOT FINISH TIME"<<"\t"<<"STATUS"<<"\t"<<"DAY NAME"<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
    for(int i=0;i<2;i++)
    {
         for(int j=0;j<4;j++)
        {
            for(int k=d;k<5;k++)
            {
                for(int m=0;m<6;m++)
                {
                    if((b[i].l[j].d[k].ts[m].start)!=0 &&(b[i].l[j].d[k].ts[m].finish)!=0)
                    {
                        if(b[i].l[j].d[k].ts[m].request_count==1)
                        {
                         cout<<b[i].bname<<"\t\t"<<b[i].l[j].labname<<"\t\t\t"<<b[i].l[j].d[k].ts[m].start<<"\t\t\t"<<b[i].l[j].d[k].ts[m].finish<<"\t\t"<<b[i].l[j].d[k].dname<<endl<<endl;
                         cout<<"\t\t\t"<<b[i].l[j].d[k].ts[m].req[0].numberOfUser<<"\t\t"<<b[i].l[j].d[k].ts[m].req[0].name<<"\t\t"<<b[i].l[j].d[k].ts[m].req[0].isConfirmed<<endl;
                        }
                    }
                }

            }cout<<endl;

        }
    }
    cout<<"------------------------------------------------------------------------"<<endl;

}
int findslot(char a[],char b[])
{
    if(strcmp(a,"8.00")==0 && strcmp(b,"9.30")==0)
        return 0;
    else if(strcmp(a,"10.00")==0 && strcmp(b,"11.30")==0 )
        return 1;
    else if(strcmp(a,"11.30")==0 && strcmp(b,"13.00")==0)
        return 2;
    else if(strcmp(a,"14.00")==0 && strcmp(b,"15.30")==0)
        return 3;
    else if(strcmp(a,"16.00")==0 && strcmp(b,"17.30")==0)
        return 4;
    else if(strcmp(a,"17.30")==0 && strcmp(b,"19.00")==0)
        return 5;
}
void update()
{

    int i,dayname,choice=0,bld,slot;
    char s[100],start_time[10],finish_time[10];
    cout<<"1. insert\n2. delete"<<endl;
    cin>>choice;
    cout<<"0 SJT\n1 TT"<<endl;//do the same thing for building as in line213-219
    cin>>bld;
    cout<<"enter lab name"<<endl;
    cin>>s;
    for(i=0;i<4;i++)
    {
        if(strcmp(b[bld].l[i].labname,s)==0)
        {
            break;
        }
    }
    cout<<"0 monday\n1 tuesday \n2 wednesday\n3 thursday\n4 friday"<<endl;
    cin>>dayname;
    cout<<"enter starttime and finishtime"<<endl;
    cin>>start_time;
    cin>>finish_time;
    slot=findslot(start_time,finish_time);
    switch(choice)
    {
        case 1:
            b[bld].l[i].d[dayname].ts[slot].start=atof(start_time);
            b[bld].l[i].d[dayname].ts[slot].finish=atof(finish_time);
            break;
        case 2:
            b[bld].l[i].d[dayname].ts[slot].start=0;
            b[bld].l[i].d[dayname].ts[slot].finish=0;
            break;
        default:
            cout<<"please enter valid input";
            break;
    }
    export_data();
}
void read()
{
                cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
                cout<<"BUILDING NAME"<<"\t"<<"LAB NAME"<<"\t"<<"FREE SLOT START TIME"<<"\t"<<"FREE SLOT FINISH TIME"<<"\t"<<"STATUS"<<"\t"<<"DAY NAME"<<endl;
                cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
    for(int i=0;i<2;i++)
    {
         for(int j=0;j<4;j++)
        {
            for(int k=0;k<5;k++)
            {
                for(int m=0;m<6;m++)
                {
                    if((b[i].l[j].d[k].ts[m].start)!=0 &&(b[i].l[j].d[k].ts[m].finish)!=0)
                    {
                        cout<<b[i].bname<<"\t\t"<<b[i].l[j].labname<<"\t\t\t"<<b[i].l[j].d[k].ts[m].start<<"\t\t\t"<<b[i].l[j].d[k].ts[m].finish<<"\t\t"<<b[i].l[j].d[k].dname<<endl;

                    }
                }

            }cout<<endl;

        }
    }
    cout<<"------------------------------------------------------------------------"<<endl;
}
void admin()
{
    int choice=0;
    cout<<"******************************Welcome Admin****************************************"<<endl;
    while(choice!=3)
    {
        cout<<"1.Update     2.Read\t3.Exit\nSelect your choice"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            update();
            break;
        case 2:
            read();
            break;
        case 3:
            break;
        default:
            cout<<"please enter valid choice"<<endl;
            break;
        }
    }
}
void user()
{
    int choice=0;
    char s[100];
    cout<<"-----Please enter your name----"<<endl<<endl;
    cin>>s;
    cout<<endl<<"*****Welcome "<<s<<"******"<<endl<<endl;
    while(choice!=5)
    {
        int n;
        cout<<"1.Check Free Lab  on a particular day"<<endl;
        cout<<"2.Check Free Lab  at a particular time"<<endl;
        cout<<"3.Check Free Time of a particular lab"<<endl;
        cout<<"4.Check your booking status"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"Please enter your choice"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            checkday();
            cout<<"\nWant to book lab\n1. yes\t2. no";
            cin>>n;
            if(n==1)
                booking();
            break;
        case 2:
            checktime();
            cout<<"\nWant to book lab\n1. yes\t2. no";
            cin>>n;
            if(n==1)
                booking();
            break;
        case 3:
            checklab();
            cout<<"\nWant to book lab\n1. yes\t2. no";
            cin>>n;
            if(n==1)
                booking();
            break;
        case 4:
            checkstatus();
            break;
        case 5:
            break;
        default:
            printf("please enter valid choice: ");
            break;

        }
    }
}
int main()
{
    import();
    if((int)get_time()>=19 && (int)get_day()!=4 &&(int)get_day()!=5)
        confirm();
    if((int)get_day()==-1 && ((int)get_time()>=9&&(int)get_time()<=10))
    {
            export_new();
    }
    int choice=0;
    cout<<endl<<"**************************************WELCOME TO THE LAB BOOKING SYSTEM***********************************"<<endl<<endl;
    while(choice!=3)
    {
        cout<<"1.Admin"<<"\t\t"<<"2.User"<<"\t\t"<<"3.Exit"<<endl;
        cout<<endl<<"Please enter your choice: "<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            char password[20];
            cout<<"Enter password :"<<endl;
            cin>>password;
            if(strcmp("2019@dsa",password)==0)
                admin();
            else
                cout<<"You entered wrong password"<<endl;
            break;
        case 2:
            user();
            break;
        case 3:
            break;
        default:
            cout<<"Please enter valid choice"<<endl;
            break;
        }
    }
}
