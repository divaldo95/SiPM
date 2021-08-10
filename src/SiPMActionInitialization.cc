//
//  SiPMActionInitialization.cpp
//  sipm
//
// User actions like Run,Event,Stepping
//                   Stacking
//                   PrimaryGenerator
// for master and threads
//
//  Created by Baranyai David on 2018. 08. 22..
//

#include "SiPMActionInitialization.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMActionInitialization::SiPMActionInitialization()
: G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMActionInitialization::~SiPMActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMActionInitialization::BuildForMaster() const
{
    SetUserAction(new SiPMRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMActionInitialization::Build() const
{
    SetUserAction(new SiPMPrimaryGeneratorAction);
    SetUserAction(new SiPMRunAction);
    
    SiPMEventAction* eventAction = new SiPMEventAction;
    SetUserAction(eventAction);
    
    SetUserAction(new SiPMSteppingAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
