#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>
#include <string>
int getdata(int i, const char* dataname, TNtuple*     ntuple) {

	
	Float_t data;
	TBranch *dataBranch;
	
	    ntuple->SetMakeClass(1);
	    ntuple->SetBranchAddress(dataname, &data, &dataBranch);//fait pointer la branche dataBranch vers la branche dataname et data vers la case correspondante de dataBranch
	
	dataBranch->GetEntry(i);
	return data;	
	
}
using namespace std;
void gifuf(){

int ncols;
int nlines=0;
int j, mois, a, h, m;
float I1,E1,I2,E2,I3,E4,I4,E4;
char fileName[256],rfileName[256];


cout << "Please, enter your input file's name (xxx.txt) : "<<endl;
  cin.getline (fileName,256);
cout << "Enter the name you want for the output (yyy.root) : ";
  cin.getline (rfileName,256);


	TFile *MyFile = new TFile(rfileName,"RECREATE");

	TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","j:mois:a:h:m:I1:E1:I2:E2:I3:E3:I4:E4");
    	
    		ntuple->ReadFile(fileName);//attention ce fichier doit etre obtenu après avoir supprimés les / et les : avec la fonction find and replace d'un éditeur de texte (gedit par exemple)
    		ntuple->Write();
	
	
	int N=ntuple->GetEntries();
			
						cout<<"This file contains "<<N<<" entries"<<endl;

	vector<int> dates(N);
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
			if (anneeactuelle==2008||anneeactuelle==2012||anneeactuelle==2016||anneeactuelle==2020||anneeactuelle==2024){nbjfev=29;} 		else {nbjfev=28;}
	
	
	
	month[1]=nbjfev;


	int somme=0;
	int moisactuel=getdata(i,"mois",ntuple);
		for (int k=2013;k<anneeactuelle;k++){somme=somme+365*24*60;}
		for (int j=0;j<moisactuel-1;j++){somme=somme+month[j]*24*60;}
	dates[i]=somme+getdata(i,"h",ntuple)*60+getdata(i,"m",ntuple)+getdata(i,"j",ntuple)*24*60;
	

	
	
}
	cout<<"The beginning date of this file is : "<<dates[0]<<endl;
	cout<<"The end date of this file is : "  <<dates[N-1]<<endl;//On vient de créer le vecteur des dates absolues en prenant la référence le 1er janvier 2013 à 00:00 on compte en minute à partir de cette date


  
  Float_t date;
   TBranch *newbranch =ntuple->Branch("dateabs", &date);
   for (Long64_t p = 0; p < N; p++){
     date= dates[p];
     newbranch->Fill();
   }//Après avoir créé une nouvelle branche on la remplit avec les valeurs du vecteur de date
   
    ntuple->Write();
   
  
    MyFile->Close();//On oublie pas de fermer le fichier
}
