//
//  SiPMAnalysis.hh
//  SiPM
//
//  Created by Baranyai David on 2018. 04. 03 for Medtech simulation..
//  Modified for SiPM Simulation on 2018. 08. 23
//

#ifndef SiPMAnalysis_hh
#define SiPMAnalysis_hh

#include <stdio.h>
#include <iostream>
#include "G4Threading.hh"
#include "G4AutoLock.hh"
#include "TTree.h"
#include "TFile.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "SiPMParameters.hh"

class SiPMAnalysis
{
private:
    /* Here will be the instance stored. */
    static SiPMAnalysis* instance;
    
    std::vector<TTree*> ttree;
    //TTree *tree;
    //TTree *electrontree;
    TFile *file;
    
    G4Mutex SiPMAnalysisMutex;
    
    /* Private constructor to prevent instancing. */
    SiPMAnalysis();
    double x, y, e, time;
    int sipm;
    int noOfSipm = 0;
    
public:
    ~SiPMAnalysis();
    SiPMAnalysis(const SiPMAnalysis&) = delete;
    SiPMAnalysis& operator=(const SiPMAnalysis&) = delete;
    
    void Fill(int copyNo, double x1, double y1, double e1, int sipm1, double time1);
    void Close();
    
    /* Static access method. */
    static SiPMAnalysis* getInstance();
};

#endif /* SiPMAnalysis_hh */
