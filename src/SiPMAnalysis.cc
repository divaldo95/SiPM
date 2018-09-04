//
//  SiPMAnalysis.cc
//  SiPM
//
//  Created by Baranyai David on 2018. 04. 03..
//  Modified for SiPM Simulation on 2018. 08. 23
//

#include "SiPMAnalysis.hh"

SiPMAnalysis::SiPMAnalysis()
{
    SiPMParameters *parameters = SiPMParameters::GetInstance();
    G4int xDiv = parameters -> GetXDivison();
    G4int yDiv = parameters -> GetYDivison();
    noOfSipm = xDiv * yDiv;
    G4int counter = 0;
    
    char filename[20];
    char treename[20];
    snprintf(filename, 30, "data.root");
    ttree = std::vector<TTree*>(noOfSipm,0);
    
    for(int i = 0; i < xDiv; i++)
    {
        for (int j = 0; j < yDiv; j++)
        {
            snprintf(treename, 20, "%dx_%dy",i,j);
            ttree[counter] = new TTree(treename, treename);
            ttree[counter] -> Branch("x", &x, "x/D");
            ttree[counter] -> Branch("y", &y, "y/D");
            ttree[counter] -> Branch("e", &e, "e/D");
            ttree[counter] -> Branch("sipm", &sipm, "sipm/D");
            ttree[counter] -> Branch("time", &time, "x/D");
            counter++;
        }
    }
    counter = 0;
    
    //ttree[0] = new TTree("tree", "tree");
    file = new TFile(filename,"RECREATE");
    instance = this;
    SiPMAnalysisMutex = G4MUTEX_INITIALIZER;
    
    /*
    for(int i = 0; i < xDiv; i++)
    {
        for (int j = 0; j < yDiv; j++)
        {
            ttree[counter] -> Branch("x", &x, "x/D");
            ttree[counter] -> Branch("y", &y, "x/D");
            ttree[counter] -> Branch("e", &e, "x/D");
            ttree[counter] -> Branch("sipm", &sipm, "x/D");
            ttree[counter] -> Branch("time", &time, "x/D");
            counter++;
        }
        
    }
    counter = 0;
     */
}

SiPMAnalysis::~SiPMAnalysis()
{
    
}

SiPMAnalysis* SiPMAnalysis::getInstance()
{
    if (instance == 0)
    {
        std::cout << "Created analysis instance" << std::endl;
        instance = new SiPMAnalysis();
    }
    
    return instance;
}

void SiPMAnalysis::Fill(int copyNo, double x1, double y1, double e1, int sipm1, double time1)
{
    G4AutoLock lock(&SiPMAnalysisMutex);
    
    x = x1;
    y = y1;
    e = e1;
    sipm = sipm1;
    time = time1;
    
    ttree[copyNo] -> Fill();
    
    ttree[copyNo] -> FlushBaskets();
    
    lock.unlock();
}

void SiPMAnalysis::Close()
{
    for(int i = 0; i < noOfSipm; i++)
    {
        ttree[i] -> Write();
    }
    file -> Close();
}

/* Null, because instance will be initialized on demand. */
SiPMAnalysis* SiPMAnalysis::instance = 0;
