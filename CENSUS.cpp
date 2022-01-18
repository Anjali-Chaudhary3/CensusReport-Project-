/HEADER FILES USED IN PROJECT.

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//CLASS USED IN PROJECT.

class CENSUS
{
  int r;
  char sut[30];
  double pop;
  float dg;
  double rp;
  double up;
  double a;
  long d;
  int sr;

public:
	void total();
	void getdata();

	void putdata()
{
	cout<<"\nNAME: ";
	puts(sut);
	cout<<"POPULATION: "<<pop;
	cout<<"\nDECADAL GROWTH: "<<dg;
	cout<<"\nRURAL POPULATION: "<<rp;
	cout<<"\nURBAN POPULATION: "<<up;
	cout<<"\nAREA: "<<a;
	cout<<"\nDENSITY: "<<d;
	cout<<"\nSEX RATIO: "<<sr;
}

int compare1(char ch[30])
	{
	if(strcmp(sut,ch)==0)
	{return 1;}

	else return(0);
	}

int compare2(char ch[30])
	{
	if(strcmp(sut,ch)!=0)
	return 1;

	else return(0);
	}
}s;

//FUNCTION FOR INPUTTING DATA.

void CENSUS::getdata()
{
	cout<<"\nEnter the RANK: ";
	cin>>r;
	cout<<"Enter name of the STATE OR UNION TERRITORY: ";
	gets(sut);
	cout<<"Enter POPULATION: ";
	cin>>pop;
	cout<<"Enter DECADAL GROWTH (in %): ";
	cin>>dg;
	cout<<"Enter RURAL POPULATION: ";
	cin>>rp;
	cout<<"Enter URBAN POPULATION: ";
	cin>>up;
	cout<<"Enter AREA (square miles): ";
	cin>>a;
	cout<<"Enter DENSITY (per km): ";
	cin>>d;
	cout<<"Enter SEX RATIO: ";
	cin>>sr;
}


//FUNCTION FOR GETTING TOTAL.

void CENSUS::total()
{
	double tp=0,tdg=0,trp=0,tup=0,ta=0,td=0,tsr=0;
	ifstream fi("kumar.dat",ios::in|ios::binary);
	while(fi.read(((char*)&s),sizeof(s)))
	{
	tp=tp+pop;
	tdg=tdg+dg;
	trp+=rp;
	tup+=up;
	ta+=a;
	td+=d;
	tsr+=sr;
	}
	cout<<"\nTotal POPULATION: "<<tp;
	cout<<"\nTotal DECADAL GROWTH: "<<tdg;
	cout<<"\nTotal RURAL POPULATION: "<<trp;
	cout<<"\nTotal URBAN POPULATION: "<<tup;
	cout<<"\nTotal AREA: "<<ta;
	cout<<"\nTotal DENSITY: "<<td;
	cout<<"\nTotal SEX RATIO: "<<tsr;
	fi.close();
}


//GLOBAL DECLARATION OF STREAM OBJECT.

fstream f;

//FUNCTION FOR WRITING IN FILE.

void write()
{
	f.open("kumar.dat",ios::binary|ios::out|ios::app);
	char ch='y';
	while(ch=='y')
	{
	s.getdata();
	f.write(((char *)&s),sizeof(s));
	cout<<"Do You Want To Enter More Records (y/n): ";
	cin>>ch;
	}
	f.close();
	cout<<"Record Has Been Entered\n";
	getch();
}

//FUNCTION FOR READING FROM THE FILE.

void read()
{
	int found=0;
	cout<<"\n\n\n\t\tDISPLAYING ALL RECORD\n\n";
	f.open("kumar.dat",ios::in|ios::binary);
	while(f.read(((char*)&s),sizeof(s)))
	{
	found=1;
	s.putdata();
	getch();
	cout<<"\n";
	}
	if(found==0)
	cout<<"No Records Found\n";
	f.close();
	getch();
}

//FUNCTION TO READ SPECIFIC RECORD FROM THE FILE.

void specific()
{clrscr();
	char ch[30],c;
	int found;
	f.open("kumar.dat",ios::in|ios::out|ios::binary);
	cout<<"Enter Name of the State whose record is to be searched: ";
	gets(ch);
	while(f.read(((char *)&s),sizeof(s)))
	{
	found=s.compare1(ch);
	if(found==1)
	{
	cout<<"Record Found\n";
	s.putdata();
	}
	}
	f.close();
	getch();
}

//FUNCTION TO MODIFY A RECORD.

void modify()
{       char ch[30],c;
	int found=0;
	long pos;
	f.open("kumar.dat",ios::in|ios::out|ios::binary);
	cout<<"Enter Name of the State whose record is to be modified: ";
	gets(ch);
	while(f.read(((char*)&s),sizeof(s)))
	{
	found=s.compare1(ch);
	if(found==1)
	{
	s.putdata();
	pos=f.tellg();
	cout<<"\nEnter New Details: \n";
	s.getdata();
	f.seekg(pos-sizeof(s));
	f.write(((char*)&s),sizeof(s));
	cout<<"Record updated\n";
	}
	}
	if(found==0)
	cout<<"Record not found\n";
	f.close();
getch();
}

//FUNCTION TO DELETE RECORD OF FILE.

void remove()
{
	char ch[30];
	int found=0,t=0;
	cout<<"Enter Name of the State whose record is to be deleted: ";
	gets(ch);
	fstream f1("temp.dat",ios::out|ios::binary);
	f.open("kumar.dat",ios::in|ios::out|ios::binary);
	while(!f.eof())
	{
	f.read(((char*)&s),sizeof(s));
	found=s.compare2(ch);
	if(found==1)
	{t=1;
	f1.write(((char*)&s),sizeof(s));
	}
	}
	if(t==0)
	cout<<"Record Not Found!!!\n";
	f.close();
	f1.close();

	if(t==1)
	{
	remove("kumar.dat");
	rename("temp.dat","kumar.dat");
	cout<<"Record deleted\n";
	}
getch();
}

void main()
{
	clrscr();
	int c;
	char ch;
	do{
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1. ADD MORE CENSUS RECORDS. " ;
	cout<<"\n\t2. DISPLAY ALL RECORDS.";
	cout<<"\n\t3. SEARCH FOR A SPECIFIC RECORD.";
	cout<<"\n\t4. DELETE A RECORD.";
	cout<<"\n\t5. MODIFY A RECORD. ";
	cout<<"\n\t6. GET TOTAL.";
	cout<<"\n\n\tPlease Enter Your Choice (1-6): ";
	cin>>c;

	switch(c)
	{
	case 1:write();
	       break;

	case 2:read();
	       break;

	case 3:specific();
	       break;

	case 4:remove();
	       break;

	case 5:modify();
	       break;

	case 6:s.total();
	       break;

	default:cout<<"\n\n\tWRONG CHOICE!!!";
	}cout<<"\n\n\tWant To Continue (y/n): ";
	cin>>ch;
	}while(ch=='y'||ch=='Y');
getch();
}