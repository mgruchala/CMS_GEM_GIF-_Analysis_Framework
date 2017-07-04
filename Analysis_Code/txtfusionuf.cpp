#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>

using namespace std;
void txtfusionuf(){


int dateabs,jour,mois,annee;
float I1,I2,I3,I4,pressure,humidity,tp1,tp2,Ifinal,I1n,I1error,I2error,I3error,I4error,I1n,I2n,I3n,I4n,I1nexpoc,I2nexpoc,I3nexpoc,I4nexpoc;
char fileName1[256], fileName2[256];
cout<<"First of all please check the syntaxe of your text file it must not contain any not float symbol and the measurements must be in order"<<endl;
cout<<"Enter the name of the input text file (xxx.txt) : "<<endl;
cin.getline(fileName1,256);

cout<<"Enter the name of the output root file you want to create (yyy.root) : "<<endl;
cin.getline(fileName2,256);


	TFile *MyFile = new TFile(fileName2,"RECREATE");

	TNtuple *ntuple = new TNtuple("ntuple","data from two files","jour:mois:annee:dateabs:I1:I2:I3:I4:I1error:I2error:I3error:I4error:tp1:tp2:humidity:pressure");
    	ntuple->ReadFile(fileName1);
    	ntuple->Write();



int N=ntuple->GetEntries();


		cout<<"This file contains "<<N<<" entries"<<endl;
	MyFile->Close();
		
		
			}
