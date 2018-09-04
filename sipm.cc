//
//  sipm.cpp
//  
//
//  Created by Baranyai David on 2018. 08. 22..
//

#include "SiPMDetectorConstruction.hh"
#include "SiPMActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "QGSP_BIC_HP.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "Randomize.hh"
#include "QGSP_BIC.hh"
#include "G4OpticalPhysics.hh"
#include "G4OpticalProcessIndex.hh"
#include "LXePhysicsList.hh"
#include "SiPMAnalysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
    // parameter from command line
    int NoE=0;
    if (argc==2) NoE=atoi(argv[1]);
    
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    unsigned nthreads = 8;
    runManager->SetNumberOfThreads(nthreads);
#else
    G4RunManager* runManager = new G4RunManager;
#endif
    //you will modify this part ///////////
    runManager->SetUserInitialization(new LXePhysicsList());
    runManager->SetUserInitialization(new SiPMDetectorConstruction());
    //runManager->SetUserInitialization(new QGSP_BIC);
    runManager->SetUserInitialization(new SiPMActionInitialization());
    ///////////////
    
    SiPMAnalysis *analysis = SiPMAnalysis::getInstance();
    
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if (argc==2) {
        // batch mode
        runManager->Initialize();
        runManager->BeamOn(NoE);
    }
    else {
        // interactive mode
        G4UIExecutive* ui = 0;
        if ( argc == 1 ) {
            ui = new G4UIExecutive(argc, argv);
        }
        UImanager->ApplyCommand("/control/macroPath /Users/divaldo/Programming/DE-Detector"); //set for your environment
        UImanager->ApplyCommand("/control/execute gui.mac");
        ui->SessionStart();
        delete ui;
    }
    
    
    delete visManager;
    delete runManager;
}

