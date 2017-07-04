#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>
#include "TGraph.h"
#include "math.h"
#include <string>

int getdata(int i, const char* dataname, TNtuple* ntuple) {//méthode très utile pour accéder à la donnée i d'une branche d'un arbre

	
	Float_t data;
	TBranch *dataBranch;
	
	ntuple->SetMakeClass(1);
	ntuple->SetBranchAddress(dataname, &data, &dataBranch);//fait pointer la branche dataBranch vers la branche dataname et data vers la case correspondante de dataBranch
	
	dataBranch->GetEntry(i);
	return data;	
	
}


using namespace std;
void moyuf(){

char fileName1[256];
string fileName2;
int N1;
cout<<"Enter the name of the input root file (xxx.root) : ";
cin.getline(fileName1,256);
cout<<"Enter the number of measurements you want to take the mean from: ";
cin>>N1;
cout<<"Enter the name of the output text file (yyy.txt) : ";
cin>>fileName2;
char* textName=fileName2.c_str();


TFile *MyFile=new TFile(fileName1,"READ");
int N=ntuple->GetEntries();
cout<<"There were "<<N<<" entries"<<endl;


vector<float> I1v;
vector<float> I2v;
vector<float> I3v;
vector<float> I4v;
vector<float> tp1v;
vector<float> tp2v;
vector<float> pressurev;
vector<float> humidityv;
vector<float> dateabsv;
vector<int> days;
int u=1;
float sommeerror1=0;
float sommeerror2=0;
float sommeerror3=0;
float sommeerror4=0;
float sommetp1=0;
float sommetp2=0;
float sommeI1=0;
float sommeI2=0;
float sommeI3=0;
float sommeI4=0;
float sommepressure=0;
float sommehumidity=0;
int sommedateabs=0;
vector<float> E1v;
vector<float> E2v;
vector<float> E3v;
vector<float> E4v;
/*vector<float> I1errorv;
vector<float> I2errorv;
vector<float> I3errorv;
vector<float> I4errorv;
vector<float> humidityerrorv;
vector<float> pressureerrorv;
vector<float> tp1errorv; 
vector<float> tp2errorv;
float I1error=0;
float I2error=0;
float I3error=0;
float I4error=0;
float pressureerror=0;
float humidityerror=0;
float tp1error=0;
float tp2error=0;
int pday=0;*/

for (int i=0;i<N;i++){
if (u<N1){
sommeI1=sommeI1+getdata(i,"I1",ntuple);
sommeI2=sommeI2+getdata(i,"I2",ntuple);
sommeI3=sommeI3+getdata(i,"I3",ntuple);
sommeI4=sommeI4+getdata(i,"I4",ntuple);
sommepressure=sommepressure+getdata(i,"pressure",ntuple);
sommehumidity=sommehumidity+getdata(i,"humidity",ntuple);
sommetp1=sommetp1+getdata(i,"tp1",ntuple);
sommetp2=sommetp2+getdata(i,"tp2",ntuple);
sommedateabs=sommedateabs+getdata(i,"dateabs",ntuple);
sommeerror1=sommeerror1+getdata(i,"I1error",ntuple);
sommeerror2=sommeerror2+getdata(i,"I2error",ntuple);
sommeerror3=sommeerror3+getdata(i,"I3error",ntuple);
sommeerror4=sommeerror4+getdata(i,"I4error",ntuple);
u++;}
else if (i==N1-1){
I1v.push_back(sommeI1/u);
I2v.push_back(sommeI2/u);
I3v.push_back(sommeI3/u);
I4v.push_back(sommeI4/u);
tp1v.push_back(sommetp1/u);
tp2v.push_back(sommetp2/u);
pressurev.push_back(sommepressure/u);
humidityv.push_back(sommehumidity/u);
dateabsv.push_back(sommedateabs/u);
E1v.push_back(sommeerror1/u);
E2v.push_back(sommeerror2/u);
E3v.push_back(sommeerror3/u);
E4v.push_back(sommeerror4/u);}
else {
I1v.push_back(sommeI1/N1);
I2v.push_back(sommeI2/N1);
I3v.push_back(sommeI3/N1);
I4v.push_back(sommeI4/N1);
tp1v.push_back(sommetp1/N1);
tp2v.push_back(sommetp2/N1);
pressurev.push_back(sommepressure/N1);
humidityv.push_back(sommehumidity/N1);
dateabsv.push_back(sommedateabs/N1);
E1v.push_back(sommeerror1/N1);
E2v.push_back(sommeerror2/N1);
E3v.push_back(sommeerror3/N1);
E4v.push_back(sommeerror4/N1);
u=1;
sommeI1=getdata(i,"I1",ntuple);
sommeI2=getdata(i,"I2",ntuple);
sommeI3=getdata(i,"I3",ntuple);
sommeI4=getdata(i,"I4",ntuple);
sommepressure=getdata(i,"pressure",ntuple);
sommehumidity=getdata(i,"humidity",ntuple);
sommetp1=getdata(i,"tp1",ntuple);
sommetp2=getdata(i,"tp2",ntuple);
sommedateabs=getdata(i,"dateabs",ntuple);
sommeerror1=getdata(i,"I1error",ntuple);
sommeerror2=getdata(i,"I2error",ntuple);
sommeerror3=getdata(i,"I3error",ntuple);
sommeerror4=getdata(i,"I4error",ntuple);}}


int taille=dateabsv.size();
cout<<"the new size is "<<taille<<endl;
ofstream fichier(textName, ios::out | ios::trunc);
        if(fichier) {
        
            	int N=dateabsv.size();
            	for (Long64_t p = 0; p < taille; p++){
   
			fichier << dateabsv[p]  << " "  
				<< I1v[p]       << " " 
				//<< I1errorv[p]       << " " 
				<< I2v[p]       << " "
				//<< I2errorv[p]       << " " 
				<< I3v[p]       << " "
				//<< I3errorv[p]       << " " 
				<< I4v[p]       << " "
				//<< I4errorv[p]       << " " 
				<< E1v[p]       << " " 
				<< E2v[p]       << " " 
				<< E3v[p]       << " " 
				<< E4v[p]       << " " 
				<< tp1v[p]      << " "
				//<< tp1errorv[p]       << " " 
				<< tp2v[p]      << " "
				//<< tp2errorv[p]       << " "
				<< humidityv[p] << " "
				//<< humidityerrorv[p]       << " "
				<< pressurev[p]
				//<< pressureerrorv[p]       << " "
			<< endl;
   		}
            
                fichier.close();

        } else cerr << "Error" << endl;

	cout << "finished" << endl;}









