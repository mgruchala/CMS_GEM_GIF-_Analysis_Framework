#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>
#include "TGraph.h"

int getdata(int i, const char* dataname, TNtuple* ntuple) //méthode très utile pour accéder à la donnée i d'une branche d'un arbre
{
	
	Float_t data;
	TBranch *dataBranch;
	
	ntuple->SetMakeClass(1);
	ntuple->SetBranchAddress(dataname, &data, &dataBranch);//fait pointer la branche dataBranch vers la branche dataname et data vers la case correspondante de dataBranch
	
	dataBranch->GetEntry(i);
	return data;	
}

using namespace std;
void Addcharge()
{
	char fileName[256];
	float ChargeOffSet=0;

	cout<<"Enter the name of the input root file (xxx.root) : "<<endl;
	cin.getline(fileName,256);
	cout<<"Please, enter the inital charge (C/cm2) : "<<endl;
	cin>>ChargeOffSet;

	TFile *MyFile=new TFile(fileName,"UPDATE");
	int N=ntuple->GetEntries();
	vector<float> accCharge1(N);
	vector<float> accCharge2(N);
	vector<float> accCharge3(N);
	vector<float> accCharge4(N);
	float sommeCharge1=0,sommeCharge2=0,sommeCharge3=0,sommeCharge4=0;

	sommeCharge1=ChargeOffSet;
	sommeCharge2=ChargeOffSet;
	sommeCharge3=ChargeOffSet;
	sommeCharge4=ChargeOffSet/15;

	for (int i=0;i<N;i++)
	{
		sommeCharge1=sommeCharge1-getdata(i,"I1",ntuple)*300/95;
		accCharge1[i]=sommeCharge1;

		sommeCharge2=sommeCharge2-getdata(i,"I2",ntuple)*300/95;
		accCharge2[i]=sommeCharge2;

		sommeCharge3=sommeCharge3-getdata(i,"I3",ntuple)*300/95;
		accCharge3[i]=sommeCharge3;

		sommeCharge4=sommeCharge4-getdata(i,"I4",ntuple)*300/95;
		accCharge4[i]=sommeCharge4;

	}

	float charge1r,charge2r,charge3r,charge4r;
	TBranch *newbranch1=ntuple->Branch("charge1r",&charge1r);
	TBranch *newbranch2=ntuple->Branch("charge2r",&charge2r);
	TBranch *newbranch3=ntuple->Branch("charge3r",&charge3r);
	TBranch *newbranch4=ntuple->Branch("charge4r",&charge4r);

	for (int i=0;i<N;i++)
	{

		charge1r=accCharge1[i];
		charge2r=accCharge2[i];
		charge3r=accCharge3[i];
		charge4r=accCharge4[i];

	   	newbranch1->Fill();
		newbranch2->Fill();
		newbranch3->Fill();
		newbranch4->Fill();

	}
	ntuple->Write();
}

