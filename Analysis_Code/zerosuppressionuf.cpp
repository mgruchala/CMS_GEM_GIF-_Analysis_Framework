#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>
#include <algorithm>
#include <iostream>
#include "math.h"

using namespace std;

float getdata(int i, const char* dataname, TNtuple* ntuple) {

	
	Float_t data;
	TBranch *dataBranch;
	
	ntuple->SetMakeClass(1);
	ntuple->SetBranchAddress(dataname, &data, &dataBranch);
	
	dataBranch->GetEntry(i);
	return data;}
		
void zerosuppressionuf (){


char fileName1[256],fileName2[256];
string fileName3;
float N1;
cout <<" Enter the name of the root file you want to modify (xxx.root) : "<<endl;
cin.getline(fileName1,256);
cout <<" Enter the name of the current you want to change : "<<endl;
cin.getline(fileName2,256);
cout <<" Enter the value of the threshold that you want in the form of a power of ten (for exemple -6 for 10^(-6)) : "<<endl;
cin>>N1;
cout <<" Enter the text file you want to create (yyy.txt) : "<<endl;
cin>>fileName3;
char* textName=fileName3.c_str();

TFile *MyFile=new TFile(fileName1,"READ");
int N=ntuple->GetEntries();


vector<float> I1v;
vector<float> I2v;
vector<float> I3v;
vector<float> I4v;
vector<float> tp1v;
vector<float> tp2v;
vector<float> pressurev;
vector<float> humidityv;
vector<float> dateabsv;
vector<int> jour;//*
vector<int> mois;//*
vector<int> annee;//*
vector<float> chargev;
vector<float> I1errorv;
vector<float> I2errorv;
vector<float> I3errorv;
vector<float> I4errorv;
cout<<"The previous size was "<<N<<endl;


for (int i=0;i<N;i++){
Float_t currentI=getdata(i,fileName2,ntuple);
bool b=false;
if (currentI>N1){b=true;}
if (b==false){
I1v.push_back(getdata(i,"I1",ntuple));
tp1v.push_back(getdata(i,"tp1",ntuple));
tp2v.push_back(getdata(i,"tp2",ntuple));
pressurev.push_back(getdata(i,"pressure",ntuple));
I2v.push_back(getdata(i,"I2",ntuple));
I3v.push_back(getdata(i,"I3",ntuple));
I4v.push_back(getdata(i,"I4",ntuple));
humidityv.push_back(getdata(i,"humidity",ntuple));
dateabsv.push_back(getdata(i,"dateabs",ntuple));
jour.push_back(getdata(i,"jour",ntuple));
mois.push_back(getdata(i,"mois",ntuple));
annee.push_back(getdata(i,"annee",ntuple));
I1errorv.push_back(getdata(i,"I1error",ntuple));
I2errorv.push_back(getdata(i,"I2error",ntuple));
I3errorv.push_back(getdata(i,"I3error",ntuple));
I4errorv.push_back(getdata(i,"I4error",ntuple));

//chargev.push_back(getdata(i,"charge",ntuple));
}}
MyFile->Close();
int taille=I1v.size();

	cout<<"The size of the new vector Izero is "<<taille<<endl;
	

   ofstream fichier(textName, ios::out | ios::trunc);
        if(fichier) {
        
            	int N=dateabsv.size();
            	for (Long64_t p = 0; p < N; p++){
   
			fichier << jour[p]      << " " 
			        << mois[p]      << " " 
			        << annee[p]     << " " 
			        << dateabsv[p]  << " "
				<< I1v[p]       << " " 
				<< I2v[p]       << " "
				<< I3v[p]       << " "
				<< I4v[p]       << " "
				<< I1errorv[p]  << " "
				<< I2errorv[p]  << " "
				<< I3errorv[p]  << " "
				<< I4errorv[p]  << " "
				<< tp1v[p]      << " "
				<< tp2v[p]      << " "
				<< humidityv[p] << " "
				<< pressurev[p] 
                               // << chargev[p]    << " "
			<< endl;
   		}
            
                fichier.close();

        } else cerr << "Error !" << endl;
        

	cout << "Finished !" << endl;
}




