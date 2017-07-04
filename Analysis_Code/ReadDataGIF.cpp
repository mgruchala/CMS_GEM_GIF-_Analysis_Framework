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
#include <iostream>
#include "Riostream.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "TTree.h"
#include "TBranch.h"
#include "TFrame.h"
#include "TCanvas.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFile.h"
#include "TString.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1.h"
#include "TF1.h"
#include "TLorentzVector.h"
#include "math.h"
#include "time.h"
#include "TRandom.h"
#include "TSpectrum.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include <algorithm>
#include "tdrstyle.C"

	

using namespace std;

float getdata(int i, const char* dataname, TNtuple* ntuple) 
{	
	Float_t data;
	TBranch *dataBranch;
	
	ntuple->SetMakeClass(1);
	ntuple->SetBranchAddress(dataname, &data, &dataBranch);
	
	dataBranch->GetEntry(i);
	return data;
}
		
void ReadDataGIF(void)
{
	char fileName[256];
	string current;
	float Ref=1; 

	cout << "Please, enter your root file's name (fileName.root) : ";
	cin.getline (fileName,256);

	double  *Charge1=NULL, *Charge2=NULL, *Charge3=NULL, *Charge4=NULL, *Time=NULL;
	double  *I1n=NULL, *I2n=NULL, *I3n=NULL, *I4n=NULL, *I1nc=NULL, *I2nc=NULL, *I3nc=NULL, *I4nc=NULL;
	double  *I1nerror=NULL, *I2nerror=NULL, *I3nerror=NULL, *I4nerror=NULL, *I1ncerror=NULL, *I2ncerror=NULL, *I3ncerror=NULL, *I4ncerror=NULL;

	  
	TFile *MyFile=new TFile(fileName,"READ");
	int N=ntuple->GetEntries();
	
	Charge1 = malloc(N*sizeof(double));
	Charge2 = malloc(N*sizeof(double));
	Charge3 = malloc(N*sizeof(double));
	Charge4 = malloc(N*sizeof(double));
	Time = malloc(N*sizeof(double));
	I1n = malloc(N*sizeof(double));
	I2n = malloc(N*sizeof(double));
	I3n = malloc(N*sizeof(double));
	I4n = malloc(N*sizeof(double));
	I1nc = malloc(N*sizeof(double));
	I2nc = malloc(N*sizeof(double));
	I3nc = malloc(N*sizeof(double));
	I4nc = malloc(N*sizeof(double));
	I1nerror = malloc(N*sizeof(double));
	I2nerror = malloc(N*sizeof(double));
	I3nerror = malloc(N*sizeof(double));
	I4nerror = malloc(N*sizeof(double));
	I1ncerror = malloc(N*sizeof(double));
	I2ncerror = malloc(N*sizeof(double));
	I3ncerror = malloc(N*sizeof(double));
	I4ncerror = malloc(N*sizeof(double));

	for (int i=0;i<N;i++)
	{
		Charge1[i]=getdata(i,"charge1r",ntuple);
		Charge2[i]=getdata(i,"charge2r",ntuple);
		Charge3[i]=getdata(i,"charge3r",ntuple);
		Charge4[i]=getdata(i,"charge4r",ntuple);
		Time[i]=getdata(i,"dateabs",ntuple);

		I1n[i]=getdata(i,"I1n",ntuple);
		I2n[i]=getdata(i,"I2n",ntuple);
		I3n[i]=getdata(i,"I3n",ntuple);
		I4n[i]=getdata(i,"I4n",ntuple);

		I1nerror[i]=getdata(i,"I1nerror",ntuple)*1E-6;
		I2nerror[i]=getdata(i,"I2nerror",ntuple)*1E-6;
		I3nerror[i]=getdata(i,"I3nerror",ntuple)*1E-6;
		I4nerror[i]=getdata(i,"I4nerror",ntuple)*1E-6;

		I1nc[i]=getdata(i,"I1nc",ntuple);
		I2nc[i]=getdata(i,"I2nc",ntuple);
		I3nc[i]=getdata(i,"I3nc",ntuple);
		I4nc[i]=getdata(i,"I4nc",ntuple);

		I1ncerror[i]=getdata(i,"I1ncerror",ntuple)*1E-6;
		I2ncerror[i]=getdata(i,"I2ncerror",ntuple)*1E-6;
		I3ncerror[i]=getdata(i,"I3ncerror",ntuple)*1E-6;
		I4ncerror[i]=getdata(i,"I4ncerror",ntuple)*1E-6;
	}

	MyFile->Close();

	TCanvas *C1 = new TCanvas("C1","Sector 1",700,400);
	TCanvas *C2 = new TCanvas("C2","Sector 2",700,400);
	TCanvas *C3 = new TCanvas("C3","Sector 3",700,400);
	TCanvas *C4 = new TCanvas("C4","Sector 4",700,400);

	TMultiGraph *gI1=new TMultiGraph();
	TGraphErrors *gI1n=new TGraphErrors(N,Charge1,I1n,0,I1nerror);
	TGraphErrors *gI1nc=new TGraphErrors(N,Charge1,I1nc,0,I1ncerror);

	TMultiGraph *gI2=new TMultiGraph();
	TGraphErrors *gI2n=new TGraphErrors(N,Charge2,I2n,0,I2nerror);
	TGraphErrors *gI2nc=new TGraphErrors(N,Charge2,I2nc,0,I2ncerror);

	TMultiGraph *gI3=new TMultiGraph();
	TGraphErrors *gI3n=new TGraphErrors(N,Charge3,I3n,0,I3nerror);
	TGraphErrors *gI3nc=new TGraphErrors(N,Charge3,I3nc,0,I3ncerror);

	TMultiGraph *gI4=new TMultiGraph();
	TGraphErrors *gI4n=new TGraphErrors(N,Charge4,I4n,0,I4nerror);
	TGraphErrors *gI4nc=new TGraphErrors(N,Charge4,I4nc,0,I4ncerror);


	C1->cd()->SetLogy(0);
	C1->SetGrid();
	C1->cd();

   	gI1n->SetMarkerStyle(20);
	gI1n->SetMarkerColor(2);
   	gI1n->SetMarkerSize(0.3);
	gI1n->SetLineColor(46);
	gI1n->SetFillColor(2);
	gI1n->GetYaxis()->SetRangeUser(0,2);

	gI1nc->SetMarkerStyle(20);
	gI1nc->SetMarkerColor(1);
   	gI1nc->SetMarkerSize(0.3);
	gI1nc->SetLineColor(15);
	gI1nc->SetFillColor(1);
	gI1nc->GetYaxis()->SetRangeUser(0,2);

	gI1->Add(gI1n);
	gI1->Add(gI1nc);
	gI1->SetTitle("Sector 1 : Normalized and Corrected Gain;Accumulated Charge [C/cm^{2}];Normalized Gain [a.u];");
	gI1->Draw("A3");
	gI1->Draw("PX");

	TLegend *legendI1 = new TLegend(0.1,0.7,0.48,0.9);
   	legendI1->AddEntry(gI1n,"Norm. only","f");
	legendI1->AddEntry(gI1nc," Norm. and Corrected","f");
  	legendI1->Draw();


	C2->cd()->SetLogy(0);
	C2->SetGrid();
	C2->cd();

	gI2n->SetMarkerStyle(20);
	gI2n->SetMarkerColor(2);
   	gI2n->SetMarkerSize(0.3);
	gI2n->SetLineColor(46);
	gI2n->SetFillColor(2);
	gI2n->GetYaxis()->SetRangeUser(0,2);

	gI2nc->SetMarkerStyle(20);
	gI2nc->SetMarkerColor(1);
   	gI2nc->SetMarkerSize(0.3);
	gI2nc->SetLineColor(15);
	gI2nc->SetFillColor(1);
	gI2nc->GetYaxis()->SetRangeUser(0,2);

	gI2->Add(gI2n);
	gI2->Add(gI2nc);
	gI2->SetTitle("Sector 2 : Normalized and Corrected Gain;Accumulated Charge [C/cm^{2}];Normalized Gain [a.u];");
	gI2->Draw("A3");
	gI2->Draw("PX");

	TLegend *legendI2 = new TLegend(0.1,0.7,0.48,0.9);
   	legendI2->AddEntry(gI2n,"Norm. only","f");
	legendI2->AddEntry(gI2nc," Norm. and Corrected","f");
  	legendI2->Draw();

	C3->cd()->SetLogy(0);
	C3->SetGrid();
	C3->cd();

   	gI3n->SetMarkerStyle(20);
	gI3n->SetMarkerColor(2);
   	gI3n->SetMarkerSize(0.3);
	gI3n->SetLineColor(46);
	gI3n->SetFillColor(2);
	gI3n->GetYaxis()->SetRangeUser(0,2);

	gI3nc->SetMarkerStyle(20);
	gI3nc->SetMarkerColor(1);
   	gI3nc->SetMarkerSize(0.3);
	gI3nc->SetLineColor(15);
	gI3nc->SetFillColor(1);
	gI3nc->GetYaxis()->SetRangeUser(0,2);

	gI3->Add(gI3n);
	gI3->Add(gI3nc);
	gI3->SetTitle("Sector 3 : Normalized and Corrected Gain;Accumulated Charge [C/cm^{2}];Normalized Gain [a.u];");
	gI3->Draw("A3");
	gI3->Draw("PX");

	TLegend *legendI3 = new TLegend(0.1,0.7,0.48,0.9);
   	legendI3->AddEntry(gI3n,"Norm. only","f");
	legendI3->AddEntry(gI3nc," Norm. and Corrected","f");
  	legendI3->Draw();

	C4->cd()->SetLogy(0);
	C4->SetGrid();
	C4->cd();

   	gI4n->SetMarkerStyle(20);
	gI4n->SetMarkerColor(2);
   	gI4n->SetMarkerSize(0.3);
	gI4n->SetLineColor(46);
	gI4n->SetFillColor(2);
	gI4n->GetYaxis()->SetRangeUser(0,2);

	gI4nc->SetMarkerStyle(20);
	gI4nc->SetMarkerColor(1);
   	gI4nc->SetMarkerSize(0.3);
	gI4nc->SetLineColor(15);
	gI4nc->SetFillColor(1);
	gI4nc->GetYaxis()->SetRangeUser(0,2);

	gI4->Add(gI4n);
	gI4->Add(gI4nc);
	gI4->SetTitle("Sector 4 : Normalized and Corrected Gain;Accumulated Charge [C/cm^{2}];Normalized Gain [a.u];");
	gI4->Draw("A3");
	gI4->Draw("PX");

	TLegend *legendI4 = new TLegend(0.1,0.7,0.48,0.9);
   	legendI4->AddEntry(gI4n,"Norm. only","f");
	legendI4->AddEntry(gI4nc," Norm. and Corrected","f");
  	legendI4->Draw();

	free(Charge1);
	free(Charge2);
	free(Charge3);
	free(Charge4);
	free(Time);
	free(I1n);
	free(I2n);
	free(I3n);
	free(I4n);
	free(I1nc);
	free(I2nc);
	free(I3nc);
	free(I4nc);
	free(I1nerror);
	free(I2nerror);
	free(I3nerror);
	free(I4nerror);
	free(I1ncerror);
	free(I2ncerror);
	free(I3ncerror);
	free(I4ncerror);

	return(0);
}



