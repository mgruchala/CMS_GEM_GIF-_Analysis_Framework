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
#include<string>

using namespace std;

float getdata(int i, const char* dataname, TNtuple* ntuple) {

	
	Float_t data;
	TBranch *dataBranch;
	
	ntuple->SetMakeClass(1);
	ntuple->SetBranchAddress(dataname, &data, &dataBranch);
	
	dataBranch->GetEntry(i);
	return data;	
	
}

void fusionuf(){

	
	char fileName1[256],fileName2[256];
	string fileName3;
	cout << "Please, enter the TEMPERATURE file's name (x1x1x1.root) : ";
        cin.getline (fileName1,256);
        cout << "Please, enter the GIF file's name (x2x2x2.root) : ";
        cin.getline (fileName2,256);
        cout << "Enter the name of the output text file you want to create (yyy.txt) : ";
        cin>>fileName3;
        char* textName=fileName3.c_str();
	
	
	cout << "Reading of the number of entries and the start/end dates of the first file.. " << endl;
	  
	// On récupère les données de temps.root pour comparaison
	// Pour s'en servir plus tard
	TFile *fTemp = new TFile(fileName1,"READ");
	int N1 = ntuple->GetEntries();
	int dateTempBegin = getdata(0,	  "dateabs", ntuple);
	int dateTempEnd	  = getdata(N1-1, "dateabs", ntuple);
	fTemp->Close();
	
	
	cout <<"Reading of the number of entries and the start/end dates of the second file.. " << endl;
	
	// On récupère les données de gif2.root pour comparaison
	TFile *fGif= new TFile(fileName2,"READ");
	int N2 = ntuple->GetEntries();
	int dateGifBegin = getdata(0,	"dateabs",ntuple);
	int dateGifEnd 	 = getdata(N2-1,"dateabs",ntuple);
	
	// A présent on compare les dates de données de Gif2
	int indexStartOfGif = 0;

	// Cas d'arrêt du programme
	if(dateGifEnd < dateTempBegin) {
	
		cout << "Impossible fusion.." << endl;
		return;
	}
	
	// Intersection : recupérer les limites du tableau final

	int tailleMaxFinal = min(N1,N2);
	for (int i = 0; i < tailleMaxFinal; i++){
	
		int currentDateOfGif = getdata(i,"dateabs",ntuple);

		if (currentDateOfGif <= dateTempBegin) indexStartOfGif = i;
		else break;
	}
	
	fGif->Close();
	
	
	
	// A présent on stocke tout le fichier temps pour fusionner les intersections	
	TFile *fTemp =new TFile(fileName1,"READ");
	
	vector<float> tp1vi;
	vector<float> tp2vi;
	vector<float> pressurevi;
	vector<float> humidityvi;
	vector<int> dateabsvi;
	cout << "Storage of temp.root file.." << endl;
	for(int i = 0; i < N1; i++){ 

		
			dateabsvi.push_back(getdata(i,"dateabs",ntuple));

			pressurevi.push_back(getdata(i,"pressure",ntuple));
			humidityvi.push_back(getdata(i,"humidity",ntuple));
			tp1vi.push_back(getdata(i,"tp1",ntuple));
			tp2vi.push_back(getdata(i,"tp2",ntuple));
		
	}

	fTemp->Close();
	cout << "Comparison of the two files (this may take a while).." << endl;
	
	// On stocke le premier fichier temp dans la mémoire à partir de la première ligne 
	// de la coincidence car on ne peut pas ouvrir deux fichiers root en même temps
	TFile *fGif = new TFile(fileName2,"READ");
	vector<float> I1v;
	vector<float> I2v;
	vector<float> I3v;
	vector<float> I4v;
	vector<float> tp1v;
	vector<float> tp2v;
	vector<float> pressurev;
	vector<float> humidityv;
	vector<int> dateabsv;
	vector<int> jour;//*
	vector<int> mois;//*
        vector<int> annee;//*
        vector<float> E1v;
        vector<float> E2v;
        vector<float> E3v;
        vector<float> E4v;

	int nbTotalOccurence = 0;
	for (int k = indexStartOfGif, u = 0; k < tailleMaxFinal; k++){

		if(currentDateOfGif > dateabsvi[N1-1]) break;
		
		
		int currentDateOfGif = getdata(k,"dateabs",ntuple);
		
		float I1vi = getdata(k,"I1",ntuple);
		float I2vi = getdata(k,"I2",ntuple);
		float I3vi = getdata(k,"I3",ntuple);
		float I4vi = getdata(k,"I4",ntuple);
		float E1vi=getdata(k,"E1",ntuple);
		float E2vi=getdata(k,"E2",ntuple);
		float E3vi=getdata(k,"E3",ntuple);
		float E4vi=getdata(k,"E4",ntuple);
		
		while(currentDateOfGif >= dateabsvi[u]) {
			
			if (currentDateOfGif == dateabsvi[u]){

				dateabsv.push_back(dateabsvi[u]);
				
				pressurev.push_back(pressurevi[u]);
				humidityv.push_back(humidityvi[u]);
				
				tp1v.push_back(tp1vi[u]);
				tp2v.push_back(tp2vi[u]);
				
				I1v.push_back(I1vi);
				I2v.push_back(I2vi);
				I3v.push_back(I3vi);
				I4v.push_back(I4vi);
				E1v.push_back(E1vi);
				E2v.push_back(E2vi);
				E3v.push_back(E3vi);
				E4v.push_back(E4vi);
				
				jour.push_back(getdata(k,"j",ntuple));//*
				mois.push_back(getdata(k,"mois",ntuple));//*
				annee.push_back(getdata(k,"a",ntuple));//*
				
				nbTotalOccurence++;

				break;
			}

			u++;
		}
	}

	cout << "I found " << nbTotalOccurence << " coincidences" << endl;
	fGif->Close();

	cout << "Creation of the output text file.." << endl;
	// On sauvegarde les resultats dans un fichier txt
        ofstream fichier(textName, ios::out | ios::trunc);
        if(fichier) {
        
            	int N=dateabsv.size();
            	for (Long64_t p = 0; p < N; p++){
   
			fichier << jour[p]      << " "//J'ai décidé de garder jour mois et année car la reconversion dateabs vers jour/mois/anne est
			        << mois[p]      << " "//non triviale et prendrait beaucoup de temps inutilement (dans moy.cpp par exemple on a
			        << annee[p]     << " "//besoin du jour courant)mais cela dépend de l'utilisateur (cela ralentit un peu le programme)
			        << dateabsv[p]  << " "//si besoin est supprimez toutes les lignes marquées * plus celles là 
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
				<< pressurev[p]
			<< endl;
   		}
            
                fichier.close();

        } else cerr << "Error " << endl;

	cout << "finished" << endl;
}

