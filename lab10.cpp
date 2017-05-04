#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<vector>

using namespace std;
int k;
class signal
{
    protected:
    int length;
    float max,aver;
    vector<float> Sdata;
    void average()
    {
        aver = 0 ;
        for(auto &i : Sdata)
        {
            aver += i ;
        }
        aver = aver/(float)length;
    }
    void maximum()
    {
        max = 0;
        for(auto &i : Sdata)
        {
            if(max < i )
                max = i;
        }
    }
    public:
friend signal operator+(const signal &ob1, const signal &ob2)throw(signal);
friend void menu(signal &obj) throw(signal,int);
    
    int sig_info()
    {
        //display sig_info
        maximum();
        average();
        cout<<endl<<endl<<"length\t\t:\t"<<length<<endl<<"maximum value\t:\t"<<max<<endl<<"average value\t:\t"<<aver;
        return 0;
    }
    int save_file() throw(string)
    {
        //save code
        char save_file_name[20];
        cout<<"enter file name to save without extension";
        cin>>save_file_name;
		if(save_file_name == "Raw_data")
			throw("wrong file name");
        strcat(save_file_name,".txt");
        maximum();
        fstream file;
        file.open(save_file_name,ios::out);
        file<<length<<" "<<max;
        for(auto i : Sdata)
        {
            file<<endl<<i;
        };
        file.close();
    }
    signal()
    {
        length = 0;
        
    }
    signal(int number)
    {
        char file_name[20]="Raw_data_";
        if(number&&number<10)
        {
            strcat(file_name,"0");
        }
        char file_number[5];
        sprintf(file_number,"%d",number);
        strcat(file_name,file_number);
        strcat(file_name,".txt");
        file_read(file_name);
    }
    signal(char* file_name)
    {
        file_read(file_name);
    }
    int file_read(char* file_name)
    {
        int un;
        float temp;
        fstream file;
        file.open(file_name,ios::in);
        file>>length>>un;
        for(int i=0;i<length;i++)
        {
            file>>temp;
            Sdata.push_back(temp);
            //cout<<signal_data[i]<<endl;
        }
        return 0;
    }
    ~signal()
    {
        //destructor
    }
    void operator+(float off)
{   
    
	for(auto &i: Sdata)
	{
		i += off;
	  cout<<i<<endl;
	}

}

 void operator*(int scale) 
{ 
	for(auto &i: Sdata)
	{
		i *= scale;
	  cout<<i<<endl;
	}
}

    void center(signal &y)
    {
        //center code
        average();
        y+( -aver );
    }
    void normalize(signal &y)
    {
        //normal code
        maximum();
        y*( (1 / float(max)) );
        
    }
    void statistics()
    {
        //statistics code
        maximum();
        average();
        sig_info();
    }
    
};

void menu(signal &obj) throw(signal,int)
{ 	
    try{
	menul:
        cout<<endl<<endl<<"----------MENU----------"<<endl<<"1.Offset"<<endl<<"2.Scale"<<endl<<"3.Center"<<endl<<"4.Normalize"<<endl<<"5.Statistics"<<endl<<"6.Signal Information"<<endl<<"7.Save file"<<endl<<"8. exit"<<endl<<endl<<"Enter your option  ";
        int choice=0;
        cin>>choice;
		 switch(choice)
        {
            case 1 : try{
			if(obj.length==0)
				throw(obj);}
             catch(signal)
			{ cout<<"Empty object"<<endl;
                          throw;
			}
            float offset_value;
            cout<<"enter offset value ";
            cin>>offset_value;
            obj+(offset_value);
			
            break;

            case 2 : try{
			if(obj.length==0)
				throw(obj); }
                  catch(signal)
			{ cout<<"Empty object"<<endl;
                          throw;
			}
            float scale_factor;
            cout<<"enter scale factor ";
            cin>>scale_factor; 
			if(scale_factor==0)
				throw(0);
			  obj*(scale_factor);
			break;

            case 3 :
            obj.center(obj);
            break;

            case 4:
			if(obj.length==0)
				throw(obj);
            obj.normalize(obj);
            break;

            case 5:
            obj.statistics();
            break;

            case 6:
            obj.sig_info();
            break;

            case 7:
			try{
            obj.save_file();}
			catch(string){
				cout<<"file name exception"<<endl;}
            break;

            
            case 8: goto ret;
            break;

            default: cout<<"wrong choice"<<endl;
			goto menul;
        }
goto menul;	
	
 
}
         catch(int){ cout<<"Scaling by zero exception"<<endl; throw;}
	catch(signal)
	{
		cout<<"Exception found empty object"<<endl;
		throw;}
ret: cout<<"good bye"<<endl;
}

signal operator+(const signal &ob1, const signal &ob2) throw(signal) 
{
	signal sum = ob1;
	try{ if(sum.length != ob2.length)
		   throw(ob2);
	}
catch(signal)
{ cout<<"Operator exception"<<endl; throw; }
	if(sum.length == ob2.length)
       {
          for(int i=0; i < sum.length; i++ ){
            sum.Sdata[i] +=ob2.Sdata[i];
             cout<<sum.Sdata[i]<<endl;}
            k =1;
                    }
        else
       { k=0;
        cout<<"addition is not possible"<<endl;
       }
 return sum;
}
    
int main(int argc,char* argv[])
{ try{
    if(argc==1)
	{
     try{
        signal ob;
        menu(ob);
	}
	catch(signal){ cout<<"caught exception"<<endl; throw;}
    }
    else
    {
        if(argv[1][1]=='n')
        {
            signal ob(atoi(argv[2]));
            menu(ob);
        }
        else if(argv[1][1]=='f')
        {
            signal ob(argv[2]);
            menu(ob);
        }
        else if(argv[1][1]=='a')
        {
            signal ob1(atoi(argv[2]));
            signal ob2(atoi(argv[3]));
            signal ob3;
         try{
            ob3 = operator+(ob1, ob2);}

            catch(signal b){
				cout<<"signals are not of same length"<<endl;
			throw(-1);}

            if ( k != 0)
            {
            ob3.statistics();
            menu(ob3);
            }
			
        }
        else
        { 
            //input invalid 
            cout<<"entered command line argument is wrong. please try again.";
throw('v');
        }
		
    }
}               catch(int){cout<<"signal not of same length exception"<<endl;}
catch(char){cout<<"command line argument exception"<<endl;}
		catch(...){cout<<"exception found"<<endl;}
    return 0;
}

