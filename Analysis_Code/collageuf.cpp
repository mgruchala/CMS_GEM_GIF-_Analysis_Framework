#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>
#include "TGraph.h"
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
void collageuf(){
char premierFichier[256],secondFichier[256];
string text;
cout<<"Enter the name of the first root file (xxx.root) : "<<endl;
cin.getline(premierFichier,256);

cout<<"Enter the name of the second root file (xxx.root) : "<<endl;
cin.getline(secondFichier,256);

cout<<"Enter the name of the output text file (yyy.txt) : "<<endl;
cin>>text;
char* textName=text.c_str();



TFile *fichier1=new TFile(premierFichier,"READ");
int N1=ntuple->GetEntries();
cout<<"going through first file..."<<endl;
vector<float> I1v;
vector<float> I2v;
vector<float> I3v;
vector<float> I4v;
vector<float> tp1v;
vector<float> tp2v;
vector<float> pressurev;
vector<float> humidityv;
vector<float> dateabsv;
vector<int> jour;
vector<int> mois;
vector<int> annee;
vector <float> Ifinalv;
//vector <float> I1nv;
vector <float> E1v;
vector <float> E2v;
vector <float> E3v;
vector <float> E4v;
vector <float> I1nv;
vector <float> I1nexpocv;
vector <float> I2nv;
vector <float> I2nexpocv;
vector <float> I3nv;
vector <float> I3nexpocv;
vector <float> I4nv;
vector <float> I4nexpocv;
vector <float> chargev;
vector <float> I1nerrorv;
vector <float> I2nerrorv;
vector <float> I3nerrorv;
vector <float> I4nerrorv;
vector <float> I1ncerrorv;
vector <float> I2ncerrorv;
vector <float> I3ncerrorv;
vector <float> I4ncerrorv;


for (int i=0;i<N1;i++){
I1v.push_back(getdata(i,"I1",ntuple));
I2v.push_back(getdata(i,"I2",ntuple));
I3v.push_back(getdata(i,"I3",ntuple));
I4v.push_back(getdata(i,"I4",ntuple));
tp1v.push_back(getdata(i,"tp1",ntuple));
tp2v.push_back(getdata(i,"tp2",ntuple));
pressurev.push_back(getdata(i,"pressure",ntuple));
humidityv.push_back(getdata(i,"humidity",ntuple));
dateabsv.push_back(getdata(i,"dateabs",ntuple));
jour.push_back(getdata(i,"jour",ntuple));
mois.push_back(getdata(i,"mois",ntuple));
annee.push_back(getdata(i,"annee",ntuple));
E1v.push_back(getdata(i,"I1error",ntuple));
E2v.push_back(getdata(i,"I2error",ntuple));
E3v.push_back(getdata(i,"I3error",ntuple));
E4v.push_back(getdata(i,"I4error",ntuple));
I1nv.push_back(getdata(i,"I1n",ntuple));
I2nv.push_back(getdata(i,"I2n",ntuple));
I3nv.push_back(getdata(i,"I3n",ntuple));
I4nv.push_back(getdata(i,"I4n",ntuple));
I1nexpocv.push_back(getdata(i,"I1nc",ntuple));
I2nexpocv.push_back(getdata(i,"I2nc",ntuple));
I3nexpocv.push_back(getdata(i,"I3nc",ntuple));
I4nexpocv.push_back(getdata(i,"I4nc",ntuple));
I1nerrorv.push_back(getdata(i,"I1nerror",ntuple));
I2nerrorv.push_back(getdata(i,"I2nerror",ntuple));
I3nerrorv.push_back(getdata(i,"I3nerror",ntuple));
I4nerrorv.push_back(getdata(i,"I4nerror",ntuple));
I1ncerrorv.push_back(getdata(i,"I1ncerror",ntuple));
I2ncerrorv.push_back(getdata(i,"I2ncerror",ntuple));
I3ncerrorv.push_back(getdata(i,"I3ncerror",ntuple));
I4ncerrorv.push_back(getdata(i,"I4ncerror",ntuple));
}
fichier1->Close();
cout<<" going through second file..."<<endl;
TFile *fichier2=new TFile(secondFichier,"READ");
int N2=ntuple->GetEntries();

for (int i=0;i<N2;i++){
I1v.push_back(getdata(i,"I1",ntuple));
I2v.push_back(getdata(i,"I2",ntuple));
I3v.push_back(getdata(i,"I3",ntuple));
I4v.push_back(getdata(i,"I4",ntuple));
tp1v.push_back(getdata(i,"tp1",ntuple));
tp2v.push_back(getdata(i,"tp2",ntuple));
pressurev.push_back(getdata(i,"pressure",ntuple));
humidityv.push_back(getdata(i,"humidity",ntuple));
dateabsv.push_back(getdata(i,"dateabs",ntuple));
jour.push_back(getdata(i,"jour",ntuple));
mois.push_back(getdata(i,"mois",ntuple));
annee.push_back(getdata(i,"annee",ntuple));
E1v.push_back(getdata(i,"I1error",ntuple));
E2v.push_back(getdata(i,"I2error",ntuple));
E3v.push_back(getdata(i,"I3error",ntuple));
E4v.push_back(getdata(i,"I4error",ntuple));
I1nv.push_back(getdata(i,"I1n",ntuple));
I2nv.push_back(getdata(i,"I2n",ntuple));
I3nv.push_back(getdata(i,"I3n",ntuple));
I4nv.push_back(getdata(i,"I4n",ntuple));
I1nexpocv.push_back(getdata(i,"I1nc",ntuple));
I2nexpocv.push_back(getdata(i,"I2nc",ntuple));
I3nexpocv.push_back(getdata(i,"I3nc",ntuple));
I4nexpocv.push_back(getdata(i,"I4nc",ntuple));
I1nerrorv.push_back(getdata(i,"I1nerror",ntuple));
I2nerrorv.push_back(getdata(i,"I2nerror",ntuple));
I3nerrorv.push_back(getdata(i,"I3nerror",ntuple));
I4nerrorv.push_back(getdata(i,"I4nerror",ntuple));
I1ncerrorv.push_back(getdata(i,"I1ncerror",ntuple));
I2ncerrorv.push_back(getdata(i,"I2ncerror",ntuple));
I3ncerrorv.push_back(getdata(i,"I3ncerror",ntuple));
I4ncerrorv.push_back(getdata(i,"I4ncerror",ntuple));
}


fichier2->Close();
int taille=dateabsv.size();

cout<<"The resulting size is "<<taille<<endl;
cout<<"Writing the file..."<<endl;

ofstream fichier(textName, ios::out | ios::trunc);
        if(fichier) {
        
            	int N=dateabsv.size();
            	for (Long64_t p = 0; p < taille; p++){
   
			fichier << jour[p]      << " " 
			        << mois[p]      << " " 
			        << annee[p]     << " "
			        << dateabsv[p]  << " "  
				<< I1v[p]       << " " 
				<< I2v[p]       << " "
				<< I3v[p]       << " "
				<< I4v[p]       << " "
				<< E1v[p]       << " "
				<< E2v[p]       << " "
				<< E3v[p]       << " "
				<< E4v[p]       << " "
				<< tp1v[p]      << " "
				<< tp2v[p]      << " "
				<< humidityv[p] << " "
				<< pressurev[p] << " "
				<< I1nv[p]      << " "
				<< I2nv[p]      << " "
				<< I3nv[p]      << " "
				<< I4nv[p]      << " "
				<< I1nerrorv[p] << " "
				<< I2nerrorv[p] << " "
				<< I3nerrorv[p] << " "
				<< I4nerrorv[p] << " "
				<< I1nexpocv[p] << " "
				<< I2nexpocv[p] << " "
				<< I3nexpocv[p] << " "
				<< I4nexpocv[p] << " "
				<< I1ncerrorv[p]<< " "
				<< I2ncerrorv[p]<< " "
				<< I3ncerrorv[p]<< " "
				<< I4ncerrorv[p]      
				
				
			<< endl;
   		}
            
                fichier.close();

        } else cerr << "Erreur à l'ouverture !" << endl;

	cout << "finished" << endl;}





