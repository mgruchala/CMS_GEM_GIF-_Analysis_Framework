#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>
#include "TGraph.h"

int getdata(int i, const char* dataname, TNtuple* ntuple) {//méthode très utile pour accéder à la donnée i d'une branche d'un arbre

	
	Float_t data;
	TBranch *dataBranch;
	
	ntuple->SetMakeClass(1);
	ntuple->SetBranchAddress(dataname, &data, &dataBranch);//fait pointer la branche dataBranch vers la branche dataname et data vers la case correspondante de dataBranch
	
	dataBranch->GetEntry(i);
	return data;	
	
}

using namespace std;
void tempuf(){

int ncols;
int nlines=0;
int j, mois, a, h, m;
float m1,m2,tp1,tp2,m3,m4,m5,m6,pressure,humidity,m7,m8,m9;
char fileName[256],rfileName[256];


	cout << "Please, enter your input file's name (xxx.txt) : ";
  	cin.getline (fileName,256);
	
	cout << "Enter the name you want for the output (yyy.root) : ";
  	cin.getline (rfileName,256);

	TFile *MyFile = new TFile(rfileName,"RECREATE");//Création d'un nouveau fichier temp.root à chaque execution du programme
	TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","j:mois:a:h:m:m1:m2:tp1:tp2:m3:m4:m5:m6:pressure:humidity:m7:m8:m9");
	ntuple->ReadFile(fileName);//lis le flux du fichier en identifiant les entiers et flottants dans l'ordre voulu dans les variables j,mois,année etc.
	ntuple->Write();//Les écrit dans le fichier temp.root


	int N=ntuple->GetEntries();//Nombre de lignes du fichiers (pas de boucle inutile)
	cout<<" This file contains "<<N<<" entries"<<endl;


vector<int> dates(N);//initialisation d'un vecteur de dates qui va utiliser les variables j,mois,a,h,m.
vector<float> press(N);
vector<int> month(12);
int nbjfev;

month[0]=31;
month[2]=31;
month[3]=30;
month[4]=31;
month[5]=30;
month[6]=31;
month[7]=31;
month[8]=30;
month[9]=31;
month[10]=30;
month[11]=31;
for (int i=0;i<N;i++){
int anneeactuelle=getdata(i,"a",ntuple);
if (anneeactuelle==2008||anneeactuelle==2012||anneeactuelle==2016||anneeactuelle==2020||anneeactuelle==2024){nbjfev=29;} else {nbjfev=28;}
month[1]=nbjfev;//Prise en compte de l'année bissextile ou pas en cours

if (anneeactuelle==2013){
	int moisactuel=getdata(i,"mois",ntuple);
	int somme=0;
		for (int j=0;j<moisactuel;j++){somme+=month[j]*24*60;}
	dates[i]=somme+getdata(i,"h",ntuple)*60+getdata(i,"m",ntuple);}
else {
	int somme=0;
	int moisactuel=getdata(i,"mois",ntuple);
		for (int k=2013;k<anneeactuelle;k++){somme=somme+365*24*60;}
		for (int j=0;j<moisactuel-1;j++){somme=somme+month[j]*24*60;}
	dates[i]=somme+getdata(i,"h",ntuple)*60+getdata(i,"m",ntuple)+getdata(i,"j",ntuple)*24*60;
	}//dates absolues référence 1er janvier 2013 00:00 comptée en minute

	
	
}
	cout<<"The beginning date of this file is : "<<dates[0]<<endl;
	cout<<"The end date of this file is : "<<dates[N-1]<<endl;


  
  Float_t date;
   TBranch *newbranch = ntuple->Branch("dateabs", &date);
   for (Long64_t p = 0; p < N; p++){
     date= dates[p];
     newbranch->Fill();
   }//Après avoir créé une nouvelle branche on la remplit avec les valeurs du vecteur de date 
   ntuple->Write();//necessaire pour la sauvegarde de la nouvelle branche
   MyFile->Close();
 
}


