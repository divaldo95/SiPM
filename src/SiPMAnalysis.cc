//
//  SiPMAnalysis.cc
//  SiPM
//
//  Created by Baranyai David on 2018. 04. 03..
//  Modified for SiPM Simulation on 2018. 08. 23
//

#include "SiPMAnalysis.hh"

SiPMAnalysis::SiPMAnalysis(const std::string& _filename) : filename(_filename)
{
    SiPMParameters &parameters = SiPMParameters::GetInstance();
    G4int xDiv = parameters.GetXDivison();
    G4int yDiv = parameters.GetYDivison();
    noOfSipm = xDiv * yDiv;
    G4int counter = 0;
    
    char filename1[30];
    char treename[30];
    snprintf(filename1, 30, filename.c_str());
    std::cout << "Data file: " << filename1 << std::endl;
    ttree = std::vector<TTree*>(noOfSipm,0);
    
    for(int i = 0; i < xDiv; i++)
    {
        for (int j = 0; j < yDiv; j++)
        {
            snprintf(treename, 20, "%dx_%dy",i,j);
            ttree[counter] = new TTree(treename, treename);
            ttree[counter] -> Branch("x", &x);
            ttree[counter] -> Branch("y", &y);
            ttree[counter] -> Branch("e", &e);
            ttree[counter] -> Branch("sipm", &sipm);
            ttree[counter] -> Branch("time", &time);
            ttree[counter]->Branch("leftScintillator", &leftScintillator);
            counter++;
        }
    }
    counter = 0;
    
    file = new TFile(filename1,"RECREATE");
}

SiPMAnalysis::~SiPMAnalysis()
{
    
}

SiPMAnalysis& SiPMAnalysis::getInstance(const std::string& _filename)
{
    static SiPMAnalysis instance(_filename);    
    return instance;
}

void SiPMAnalysis::Fill(const int& copyNo, const double& x1, const double& y1, const double& e1, const int& sipm1, const double& time1, const int& leftscint)
{
    //std::lock_guard<std::mutex> guard(SiPMAnalysisMutex);

    SiPMAnalysisMutex.lock();
    x = x1;
    y = y1;
    e = e1;
    sipm = sipm1; //which sipm
    time = time1;
    leftScintillator = leftscint;

    ttree[copyNo]->Fill();

    ttree[copyNo]->FlushBaskets();
    SiPMAnalysisMutex.unlock();
}

void SiPMAnalysis::Fill(int copyNo, double x1, double y1, double e1, int sipm1, double time1)
{
    //std::lock_guard<std::mutex> guard(SiPMAnalysisMutex);

    SiPMAnalysisMutex.lock();
    x = x1;
    y = y1;
    e = e1;
    sipm = sipm1;
    time = time1;
    
    ttree[copyNo] -> Fill();
    
    ttree[copyNo] -> FlushBaskets();
    SiPMAnalysisMutex.unlock();
}

void SiPMAnalysis::Close()
{
    for(int i = 0; i < noOfSipm; i++)
    {
        ttree[i] -> Write();
    }
    file -> Close();
}
