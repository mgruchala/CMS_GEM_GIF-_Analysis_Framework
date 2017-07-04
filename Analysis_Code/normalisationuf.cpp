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
#include <string>

	

using namespace std;

float getdata(int i, const char* dataname, TNtuple* ntuple) {

	
	Float_t data;
	TBranch *dataBranch;
	
	ntuple->SetMakeClass(1);
	ntuple->SetBranchAddress(dataname, &data, &dataBranch);
	
	dataBranch->GetEntry(i);
	return data;}
		
void normalisationuf (){
char fileName[256];
string current;
int N1;
float Ref=1; 

  cout << "Please, enter your root file's name (fileName.root) : ";
  cin.getline (fileName,256);

  cout<<"This program will calculate the mean of the first N measurements and use it to normalise the current, please enter the integer N :"<<endl;
  cin>>N1;

  cout<<"Please, enter the reference number for normalization :"<<endl;
  cin>>Ref;
  
TFile *MyFile=new TFile(fileName,"UPDATE");
int N=ntuple->GetEntries();
float sommeI1=0,sommeI2=0,sommeI3=0,sommeI4=0;

float meanI1,meanI2,meanI3,meanI4;

for (int i=0;i<N1;i++){
sommeI1=sommeI1+getdata(i,"I1",ntuple);
sommeI2=sommeI2+getdata(i,"I2",ntuple);
sommeI3=sommeI3+getdata(i,"I3",ntuple);
sommeI4=sommeI4+getdata(i,"I4",ntuple);

}
meanI1=sommeI1/(N1*Ref);
meanI2=sommeI2/(N1*Ref);
meanI3=sommeI3/(N1*Ref);
meanI4=sommeI4/(N1*Ref);

float I1n,I2n,I3n,I4n;
float I1nerror,I2nerror,I3nerror,I4nerror;

TBranch *newbranch1=ntuple->Branch("I1n",&I1n);
TBranch *newbranch2=ntuple->Branch("I2n",&I2n);
TBranch *newbranch3=ntuple->Branch("I3n",&I3n);
TBranch *newbranch4=ntuple->Branch("I4n",&I4n);
TBranch *newbranch5=ntuple->Branch("I1nerror",&I1nerror);
TBranch *newbranch6=ntuple->Branch("I2nerror",&I1nerror);
TBranch *newbranch7=ntuple->Branch("I3nerror",&I1nerror);
TBranch *newbranch8=ntuple->Branch("I4nerror",&I1nerror);
for (Long64_t p = 0; p < N; p++){
     I1n=getdata(p,"I1",ntuple)/meanI1;
     I1nerror=getdata(p,"I1error",ntuple)/(-meanI1);
     I2n=getdata(p,"I2",ntuple)/meanI2;
     I2nerror=getdata(p,"I2error",ntuple)/(-meanI2);
     I3n=getdata(p,"I3",ntuple)/meanI3;
     I3nerror=getdata(p,"I3error",ntuple)/(-meanI3);
     I4n=getdata(p,"I4",ntuple)/meanI4;
     I4nerror=getdata(p,"I4error",ntuple)/(-meanI4);
     newbranch1->Fill();
     newbranch2->Fill();
     newbranch3->Fill();
     newbranch4->Fill();
     newbranch5->Fill();
     newbranch6->Fill();
     newbranch7->Fill();
     newbranch8->Fill();
   }
   ntuple->Write();
   MyFile->Close();}



