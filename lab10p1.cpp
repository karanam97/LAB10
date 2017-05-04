#include<iostream>
#include<math.h>
using namespace std;

class BaseConic{
protected:
double x;
double y;

public:
//BaseConic(double x0 = 0, double y0 = 0){ };
//virtual ~BaseConic(){};
virtual void move(double n_x, double n_y)  = 0;
virtual void resize() = 0;
virtual double Area()  = 0; 
virtual void print()  = 0;
};

class circle : public BaseConic {
	private:
	double r;
	public:
	circle();
	circle(double xc, double yc, double rc);
	//~circle();
 void move(double n_x, double n_y) { x = n_x; y = n_y; }
 void resize();
double Area() { return ((double(22/7))*r*r);}
	void position( double x1, double y1);
 void print();
	};
	
circle::circle()
{
	 x=0;
	 y=0;
	 cout<<"Enter the radius";
	 cin>>r;
}
circle::circle(double xc, double yc, double rc)
{
	x=xc;
	y=yc;
	r=rc;
}
void circle::position(double x1, double y1)
{
	double d;
	d = sqrt(pow((x1-x),2) + pow((y1-y),2));
	if(d<r)
		cout<<"inside circle"<<endl;
	else if (d>r)
		cout<<"outside circle"<<endl;
	else 
		cout<<"on the circle"<<endl;
}

void circle::resize() {
	cout<<"Enter the new radius:";
	cin>>r;
}
void circle::print(){
	cout<<"Co-ordinates of center are ("<<x<<","<<y<<")"<<endl;
	cout<<"Radius is "<<r<<endl;
	cout<<"Area of circle is "<<Area()<<endl;
}

class eclipse : public BaseConic {
	private:
	double a,b,ang;
	public:
	eclipse();
	eclipse(double xc, double yc, double ac, double bc, double angc) { x = xc; y = yc; a = ac; b = bc; ang = angc;}
	//~eclipse();
   void move(double n_x, double n_y) { x = n_x; y = n_y; }
	 void resize();
	 double Area() { return ((double (22/7))*a*b);}
	void position();
	void rotate();
 void print();
	};
	eclipse::eclipse()
{
	 x=0;
	 y=0;
	 cout<<"Enter the major axis radius";
	 cin>>a;
	 cout<<"Enter the minor axis radius";
	 cin>>b;
	 cout<<"Enter the angle";
	 cin>>ang;
}
	
	void eclipse::resize()
	{
		cout<<"\nEnter new major axis radius:";
		cin>>a;
		cout<<"\nEnter new minor axis radius:";
		cin>>b;
	}
	void eclipse::position()
	{
		cout<<" position of vertices on major axis is ("<<((a*sin(ang))+x)<<","<<((a*cos(ang))+y)<<") and ("<<-((a*sin(ang))+x)<<","<<-((a*cos(ang))+y)<<")"<<endl;
		cout<<" position of vertices on minor axis is ("<<((b*cos(ang))+x)<<","<<((b*sin(ang))+y)<<") and ("<<-((b*cos(ang))+x)<<","<<-((b*sin(ang))+y)<<")"<<endl;
	}
    void eclipse:: rotate()
    { double angl;
     cout<< "enter angle to rotate the eclipse:";
     cin>>angl;
	 ang+=angl;
    }
	void eclipse::print()
	{
	cout<<"Co-ordinates of center are ("<<x<<","<<y<<")"<<endl;
	cout<<"Major axis Radius is "<<a<<endl;
	cout<<"Minor axis Radius is "<<b<<endl;
	cout<<"Area of eclipse is "<<Area()<<endl;
	}
	
	int main()
	{
		circle objc;
		BaseConic* objp = NULL;
		 objp = &objc;
		objc.print();
		objc.move(3,5);
		objc.print();
		objc.resize();
		objc.print();
		objc.position(3,5);
		objc.position(25,90);
		objc.position(4,3);
		
		eclipse obje;
		BaseConic* objep = NULL;
		 objep = &obje;
		obje.print();
		obje.move(3,5);
		obje.print();
                obje.position();
		obje.resize();
		obje.print();
		obje.rotate();
		obje.print();
		obje.position();
		
		//BaseConic objcon;
		
		
		 objp->print();
		 objp->move(6,10);
		 objp->print();
		 objp->resize();
		 objp->print();
		 
		
		 
		 
		 objep->print();
		 objep->move(3,5);
		objep->print();
		objep->resize();
		objep->print();
		//objep->rotate();
		objep->print();
		
		return 0;
	}
