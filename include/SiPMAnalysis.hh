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
#include "TTree.h"
#include "TFile.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <mutex>
#include "SiPMParameters.hh"

class SiPMAnalysis
{
private:    
    std::vector<TTree*> ttree;
    TFile *file;
    
    mutable std::mutex SiPMAnalysisMutex;
    
    /* Private constructor to prevent instancing. */
    SiPMAnalysis(const std::string& _filename);

    std::string filename;

    double x, y, e, time;
    int leftScintillator; //if one photon left the scintillator to world, set it to one
    int sipm;
    int isOut;
    int noOfSipm = 0;
    
public:
    ~SiPMAnalysis();
    
<<<<<<< HEAD
    //const int &copyNo, const double &x1, const double &y1, const double &e1, const int &sipm1, const double &time1, const int &leftscint
    void Fill(const int&, const double&, const double&, const double&, const int&, const double&, const int&);
=======
    void Fill(int copyNo, double x1, double y1, double e1, int sipm1, double time1, bool isOut1);
>>>>>>> f4069241a15758e328ac15379355c5910f43e006
    void Close();

    static SiPMAnalysis& getInstance(const std::string& _filename = "data.root");

    SiPMAnalysis(const SiPMAnalysis&) = delete;
    SiPMAnalysis& operator=(const SiPMAnalysis&) = delete;
};

#endif /* SiPMAnalysis_hh */
