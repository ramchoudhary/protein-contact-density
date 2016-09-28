#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;
int y[2600][2600]={};
double x[2600][5]={};
double z[2600][5]={};
int saikat=0,saikat1=0;
string trim(string temp){
	int n=0;
	string fin="";
	while (n<temp.length()){
		if (temp[n]!=' ')
			fin=fin+temp[n];
		n++;
	}
	return fin;
}
double calc(int i,int j,int c){
	int a=0,b=0;
	double temporary=0.0,temp1=0.0,temp2=0.0;
	if (c){
		for (a=0;a<3;a++){
			temp1=x[i][a]-x[j][a];
			temp2=temp2+temp1*temp1;
		}
	}
	else{
		for (a=0;a<3;a++){
			temp1=z[i][a]-z[j][a];
			temp2=temp2+temp1*temp1;
		}
	}
	temporary=sqrt(temp2);
	if (c){
		if (temporary<=60.0){
			y[i][j]=1;
			y[j][i]=1;
			saikat++;
			cout<<"("<<x[i][4]<<","<<x[j][4]<<")"<<endl;
			/*cout<<"1) ";
			for(a=0;a<=4;a++)
				cout<<x[i][a]<<" ";
			cout<<"\n2)";
			for(a=0;a<=4;a++)
				cout<<x[j][a]<<" ";
			cout<<endl;*/
			
		}
		/*else{
			y[i][j]=0;
			y[j][i]=0;
		}*/
	}
	else{
		if (temporary<=60.0 && y[i][j]==1){   //unedit this
		//if (temporary<=6.0){
			cout<<"("<<z[i][4]<<","<<z[j][4]<<")"<<endl;
			saikat1++;
		}
	}
	
} 

int demo(int p,int c){
	if (c){
		return (1-x[p][3]);
	}
	else
		return (1-z[p][3]);
}


void master(char *fname,int check){
	cout<<"The list of CA atoms in this file is :"<<endl;
	double d=0.0,interior=0.0;
	string line="",temp_line_min="";
	int i=0,val=31,count=0,p=0,q=0,max_count=0;
	ifstream myfile (fname);
	//cout<<"aha "<<endl;
  	if (myfile.is_open())
  	{
		while (getline(myfile,line)){
			if ( ((line.length())<15) || trim(line.substr(13,3)).compare("CA")!=0 || (trim(line.substr(0,4)).compare("ATOM")!=0)){
				//cout<<line<<endl;
				continue;
				}
			cout<<atof(trim(line.substr(7,5)).c_str())<<" "<<line<<" "<<endl;
			//cout<<check<<") "<<trim(line.substr(12,3))<<"\n"<<line<<endl;
			interior=0.0;
			//count++;
			count=atof(trim(line.substr(7,5)).c_str());
			if(count>max_count)
				max_count=count;
			//x[count][3]=1;
			if(check){
				x[count][3]=1;
				x[count][4]=count;
				for(i=0;i<3;i++)
					x[count][i]=atof(trim(line.substr(val+i*8,8)).c_str());
				//for(a=0;a<=4;a++){
					//if (x[count][a]!=74.931)
				//	cout<<x[count][a]<<" ";}
				//cout<<endl;
			}
			else{
				z[count][3]=1;
				z[count][4]=count;
				for(i=0;i<3;i++)
					z[count][i]=atof(trim(line.substr(val+i*8,8)).c_str());
			}
		}
		 	myfile.close();
  	}
	else 
		cout << "Unable to open file"; 
		//cout << max_count<<endl; 
	cout<<"The pair of all CA atoms with distance between less than or equal to 6 Angstrom are:"<<endl;
	for (p=0;p<max_count;p++){
		if (demo(p,check))
			continue;
		for(q=p+1;q<max_count;q++){
		if (demo(q,check))
			continue;
			//if(x[count][3]==1)
				calc(p,q,check);
		}
	}
	/*for (p=0;p<count;p++){
		for(q=0;q<count;q++)
			cout<<y[p][q];
			cout<<endl;
		}*/
}





int main(int argc, char *argv[]){
	double ratio=0.0;
	//cout<<"Hey boy"<<endl;
	cout<<"\nLet's calculate for "<<argv[1]<<endl;
	master(argv[1],1);
	cout<<"\nLet's calculate for "<<argv[2]<<endl;
	master(argv[2],0);
	cout<<"\nFrom "<<argv[1]<<" "<<saikat<<" pairs, similarly from "<<argv[2]<<" "<<saikat1<<" pairs"<<endl;
	if (saikat){
		ratio=(double)saikat1/saikat;
		cout<<"The ratio is: "<<ratio<<"\nThank You\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"<<endl;
	}
	return 1;
}
