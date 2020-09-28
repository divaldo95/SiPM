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
    
    int ret = 0;

    char filename1[30];
    char treename[30];
    snprintf(filename1, 30, "%s", filename.c_str());
    ttree = std::vector<TTree*>(noOfSipm+1,0);
    
    for(int i = 0; i < xDiv; i++)
    {
        for (int j = 0; j < yDiv; j++)
        {
            ret = snprintf(treename, 20, "%dx_%dy",i,j);
            if(ret < 0)
            {
                abort();
            }
            ttree[counter] = new TTree(treename, treename);
            ttree[counter] -> Branch("x", &x);
            ttree[counter] -> Branch("y", &y);
            ttree[counter] -> Branch("e", &e);
            ttree[counter] -> Branch("sipm", &sipm);
            ttree[counter] -> Branch("time", &time);
            ttree[counter] -> Branch("isout", &isOut);
            counter++;
        }
    }
    //One for post = world
    ttree[counter] = new TTree("postisworld", "postisworld");
    ttree[counter] -> Branch("x", &x);
    ttree[counter] -> Branch("y", &y);
    ttree[counter] -> Branch("e", &e);
    ttree[counter] -> Branch("sipm", &sipm);
    ttree[counter] -> Branch("time", &time);
    ttree[counter] -> Branch("isout", &isOut);
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

void SiPMAnalysis::Fill(int copyNo, double x1, double y1, double e1, int sipm1, double time1, bool isOut1)
{
    //std::lock_guard<std::mutex> guard(SiPMAnalysisMutex);

    SiPMAnalysisMutex.lock();
    x = x1;
    y = y1;
    e = e1;
    sipm = sipm1;
    time = time1;
    isOut = (isOut1 ? 0:1); //if it is out, then it is 1
    if(copyNo == 9999) //special copyNo for World
    {
        ttree.back() -> Fill();
        ttree.back() -> FlushBaskets();
    }
    else
    {
        ttree[copyNo] -> Fill();
        ttree[copyNo] -> FlushBaskets();
    }
    
    
    
    
    SiPMAnalysisMutex.unlock();
}

void SiPMAnalysis::Close()
{
    for(int i = 0; i < noOfSipm+1; i++)
    {
        ttree[i] -> Write();
    }
    file -> Close();
}
