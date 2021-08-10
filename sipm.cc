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
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "SiPMParameters.hh"
#include "SiPMAnalysis.hh"
#include "OpNovicePhysicsList.hh"

#define G4MULTITHREADED

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
    SiPMParameters& parameters = SiPMParameters::GetInstance();
    
    
    bool visualization = true;
    int NoE=0;
    
    // parameter from command line
    std::string data_filename = "data.root";
    for(int i = 1; i < argc; i++)
    {
        if(!strcmp("-df", argv[i])) //number of events
        {
            std::cout << "Settings will be read from the default file." << std::endl;
            parameters.ParseConfigFile();
        }
        else if(!strcmp("-f", argv[i])) //number of events
        {
            std::string filename;
            if(argc-1 >= i+1)
            {
                filename = argv[i+1];
                std::cout << "Settings will be read from " << filename << "." << std::endl;
                parameters.ParseConfigFile(filename);
            }
            if(filename.empty())
            {
                std::cout << "File name not given, using the default values" << std::endl;
            }
        }
        else if(!strcmp("-v", argv[i])) //number of events
        {
            std::cout << "Visualization disabled." << std::endl;
            visualization = false;
        }
        else if(!strcmp("-d", argv[i])) //datafile
        {
            data_filename = argv[i+1];
            std::cout << "Using output file: " << data_filename << "." << std::endl;
        }
    }
    SiPMAnalysis& analysis = SiPMAnalysis::getInstance(data_filename);
    NoE = parameters.GetNumberOfEvents();
    
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    unsigned nthreads = 4;
    runManager->SetNumberOfThreads(nthreads);
#else
    G4RunManager* runManager = new G4RunManager;
#endif
    runManager-> SetUserInitialization(new OpNovicePhysicsList());
    runManager->SetUserInitialization(new SiPMDetectorConstruction());
    runManager->SetUserInitialization(new SiPMActionInitialization());
    ///////////////
    
    //Initialize the analysis instance here first to avoid crash
    //SiPMAnalysis *analysis = SiPMAnalysis::getInstance();
    
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if (visualization == false)
    {
        // batch mode
        runManager->Initialize();
        runManager->BeamOn(NoE);
    }
    else
    {
        // interactive mode
        G4UIExecutive* ui = 0;
        ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/macroPath ./macros"); //set for your environment
        UImanager->ApplyCommand("/control/execute gui.mac");
	NoE = parameters.GetNumberOfEvents();
	runManager->BeamOn(NoE);  //ez nem volt itt es itt nem a config NoE-je futott le  UB
        ui->SessionStart();
        delete ui;
    }
    
    
    delete visManager;
    delete runManager;
}

