#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>
#include "TGraph.h"
#include "TH1.h"
#include "math.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "tdrstyle.C"
#include <sstream>
using namespace std;

double getdata(int i, const char* dataname, TNtuple* ntuple) {

	
	Float_t data;
	TBranch *dataBranch;
	
	ntuple->SetMakeClass(1);
	ntuple->SetBranchAddress(dataname, &data, &dataBranch);
	
	dataBranch->GetEntry(i);
	return data;}

void powercuf(){
char name[256], name3[256],name2[256];

  std::cout << "Please, enter your root file's name (fileName.root) : "<<endl;
  std::cin.getline (name,256);

  
  std::cout<< "Enter the name of the branch containing the current normalised you want to study : "<<endl;
  std::cin.getline(name3,256);
  std::cout<< "Enter the name of the branch that will be created after the correction : "<<endl;
  std::cin.getline(name2,256);
   	
   	
   	
   	TFile *MyFile=new TFile(name,"READ");
   
   	int N = ntuple->GetEntries();
   	

   					cout<<"There is "<<N<<" entries"<<endl;
   
   ostringstream error;
   error<<name3;
   string errorName=error.str();
   char* branchName=(errorName+"error").c_str();
   
   TCanvas *c1=new TCanvas("Canvas1","Canvas1");
   TCanvas *c2=new TCanvas("Canvas2","Canvas2");
   TCanvas *c3=new TCanvas("Canvas3","Canvas3");
   TCanvas *c4=new TCanvas("Canvas4","Canvas4");
   TCanvas *c5=new TCanvas("Canvas5","Canvas5");
   c1->SetFillColor(0);
    c1->SetGrid();
     c2->SetFillColor(0);
     c2->SetGrid();
      c3->SetFillColor(0);
      c3->SetGrid();
       c4->SetFillColor(0);
       c4->SetGrid();
        c5->SetFillColor(0);
        c5->SetGrid();
   
   
   float *I1n,*pressure,*tp1,*date,*lnI1n,*lnpressure,*lntp1,*Ierror;
   	
   	I1n=(float*) malloc(sizeof(float)*N);
   	pressure=(float*) malloc(sizeof(float)*N);
   	tp1=(float*) malloc(sizeof(float)*N);
   	date=(float*) malloc(sizeof(float)*N);
   	lnI1n=(float*) malloc(sizeof(float)*N);
   	lnpressure=(float*) malloc(sizeof(float)*N);
   	lntp1=(float*) malloc(sizeof(float)*N);
   	Ierror=(float*) malloc(sizeof(float)*N);
       
       
       
       for (int i=0;i<N;i++){
       
       I1n[i]=getdata(i,name3,ntuple);
       pressure[i]=getdata(i,"pressure",ntuple);
       tp1[i]=getdata(i,"tp1",ntuple);
       date[i]=getdata(i,"dateabs",ntuple);
       lnpressure[i]=log(pressure[i]);
       lntp1[i]=log(tp1[i]);
       lnI1n[i]=log(I1n[i]);
       Ierror[i]=getdata(i,branchName,ntuple);}
       
   
   
   
	c1->cd();
   
   	TGraph *I1pressure=new TGraph(N,lnpressure,lnI1n);
   	I1pressure->SetMarkerColor(1);
   	I1pressure->SetMarkerSize(0);
   	I1pressure->SetTitle("log(I1n)=f(log(pressure))");
   	I1pressure->GetXaxis()->SetTitle("log(pressure)");
   	I1pressure->GetYaxis()->SetTitle("log(Intensity)");
   	TFitResultPtr res1 = I1pressure->Fit("pol1","SQ");
   	I1pressure->Draw("AP*");
   	//gStyle->SetOptFit(111);



float a0=res1->Value(0);
float b0=res1->Value(1);




	c2->cd();
	
	
	float *I1cp,*lnI1cp;
	I1cp=(float*) malloc(sizeof(float)*N);
	lnI1cp=(float*) malloc(sizeof(float)*N);
	for (int i=0;i<N;i++){
	float pressureFactor=exp(a0)*pow(pressure[i],b0);
	I1cp[i]=I1n[i]/pressureFactor;
	lnI1cp[i]=log(I1cp[i]);}
	
	




	TGraph *I1cpt=new TGraph(N,lntp1,lnI1cp);
	I1cpt->SetMarkerColor(1);
	I1cpt->SetMarkerSize(0);
	I1cpt->GetXaxis()->SetTitle("log(temperature)");
	I1cpt->GetYaxis()->SetTitle("log(Intensity)");
	I1cpt->SetTitle("log(I1n corrected by the pressure) =f(log(temp1))");
	TFitResultPtr res2 = I1cpt->Fit("pol1","SQ");
	I1cpt->Draw("AP*");
	
	
	
float a1=res2->Value(0);
float b1=res2->Value(1);




	c3->cd();


	float *I1c,*lnI1c,*I1cerror;
	I1c=(float*) malloc(sizeof(float)*N);
	I1cerror=(float*) malloc(sizeof(float)*N);
	lnI1c=(float*) malloc(sizeof(float)*N);
	for (int i=0;i<N;i++){
	float tempFactor=exp(a1)*pow(tp1[i],b1);
	I1c[i]=I1cp[i]/tempFactor;
	I1cerror[i]=Ierror[i]/(exp(a0)*pow(pressure[i],b0)*tempFactor);
	
	lnI1c[i]=log(I1c[i]);}



	TGraph *I1corrected=new TGraph(N,lnpressure,lnI1c);
	I1corrected->SetMarkerColor(1);
	I1corrected->SetMarkerSize(0);
	I1corrected->GetXaxis()->SetTitle("log(pressure)");
	I1corrected->GetYaxis()->SetTitle("log(Intensity)");
	I1corrected->SetTitle("log(I1n already corrected once) =f(log(pressure))");
	TFitResultPtr res3 = I1corrected->Fit("pol1","SQ");
	
	I1corrected->Draw("AP*");




float a2=res3->Value(0);
float b2=res3->Value(1);




	c4->cd();
	
	
	
	
	float *I1cc,*lnI1cc,*I1ccerror;;
	I1cc=(float*) malloc (sizeof(float)*N);
	I1ccerror=(float*) malloc (sizeof(float)*N);
	lnI1cc=(float*) malloc (sizeof(float)*N);
   	for (int i=0;i<N;i++){
   	I1cc[i]=I1c[i]/(exp(a2)*pow(pressure[i],b2));
   	lnI1cc[i]=log(I1cc[i]);
   	I1ccerror[i]=I1cerror[i]/(exp(a2)*pow(pressure[i],b2));}
   	
	
	TGraph *I1blue=new TGraph(N,lntp1,lnI1cc);
	I1blue->SetMarkerSize(0);
	I1blue->SetMarkerColor(1);
	I1blue->GetXaxis()->SetTitle("log(temperature)");
	I1blue->GetYaxis()->SetTitle("log(intensity)");
	I1blue->SetTitle("log(I1n after fine correction) =f(log(temp1))");
	TFitResultPtr res4=I1blue->Fit("pol1","SQ");
	
	I1blue->Draw("AP*");




float a3=res4->Value(0);
float b3=res4->Value(1);
	
	
	
	
	float *I1ccc,*I1cccerror;
	I1ccc=(float*)malloc(sizeof(float)*N);
	I1cccerror=(float*)malloc(sizeof(float)*N);
	for (int i=0;i<N;i++){
	I1ccc[i]=I1cc[i]/(exp(a3)*pow(tp1[i],b3));
	I1cccerror[i]=I1ccerror[i]/(exp(a3)*pow(tp1[i],b3));}



	c5->cd();
   	//gStyle->SetOptStat(0);
   	
   	TMultiGraph *final=new TMultiGraph();
   	
   	
   	

   	TGraphErrors *gr2=new TGraphErrors(N,date,I1n,0,0);//Remplacer le second zéro par Ierror
   	gr2->SetMarkerColor(2);
   	gr2->SetMarkerSize(0.3);
   	gr2->SetMarkerStyle(20);
   	gr2->SetLineColor(2);
   	TGraphErrors *gr3=new TGraphErrors(N,date,I1c,0,0);//Remplacer le second zéro par I1cerror
   	gr3->SetMarkerColor(1);
   	gr3->SetMarkerSize(0.3);
   	gr3->SetMarkerStyle(20);
   	gr3->SetLineColor(1);
   	//TGraphErrors *gr5=new TGraphErrors(N,date,I1ccc,0,0);//Remplacer le second zéro par I1cccerror
   	//gr5->SetMarkerColor(1);
   	//gr5->SetMarkerSize(0.5);
   	//gr5->SetMarkerStyle(33);
   	//gr5->SetLineColor(1);
   	final->SetTitle("GE1/1 readout current I_{1} vs Time");
   	final->Add(gr2);
   	final->Add(gr3);
   	//final->Add(gr5);
   	final->Draw("AP");

   	leg = new TLegend(0.1,0.7,0.48,0.9);
        //leg->SetHeader("Legends");
        leg->AddEntry(gr2,"I_{1} without correction","p");
        leg->AddEntry(gr3,"I_{1} corrected","p");
    	//leg->AddEntry(gr5,"I_{1} corrected twice","p");
    	final->GetXaxis()->SetTitle("Time [min]");
   	final->GetYaxis()->SetTitle("Intensity [a.u]");
   	leg->Draw("P");

   	ostringstream ss3;
   	ss3<<name3;   	
   	string nameImage=ss3.str();
   	char* image=("./"+nameImage+"powercorrectedpt.jpg").c_str();
	//c5->SaveAs(image);
    
   	
   	
   
   
   MyFile->Close();
    ostringstream o;
   o<<name2;
   char* namebranch2=(o.str()+"error").c_str();
   
  TFile *MyFile2=new TFile(name,"UPDATE");
   float Ifinale,errorFinale;
	cout << "mane is :" << name2 << endl;
   TBranch *newbranch=ntuple->Branch(name2,&Ifinale);
   TBranch *newbranch2=ntuple->Branch(namebranch2,&errorFinale);
   for (int i=0;i<N;i++){
   
   
   errorFinale=I1cccerror[i];
   newbranch2->Fill();
   
   Ifinale=I1ccc[i];
   newbranch->Fill();
   }
   ntuple->Write();
   
free(date);
free(pressure);
free(tp1);
free(I1n);
free(I1cp);
free(I1c);
free(I1cc);
free(I1ccc);
free(lnI1n);
free(lnpressure);
free(lntp1);
free(lnI1cp);
free(lnI1c);
free(lnI1cc);
free(Ierror);
free(I1cerror);
free(I1ccerror);
free(I1cccerror);

}
