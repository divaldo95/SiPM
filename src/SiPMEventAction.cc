//
//  SiPMEventAction.cpp
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//

#include "SiPMEventAction.hh"

SiPMEventAction::SiPMEventAction() : G4UserEventAction()
{
    fForcenophotons = false;
    fForcedrawphotons = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMEventAction::~SiPMEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMEventAction::EndOfEventAction(const G4Event* anEvent)
{
    // accumulate statistics in DERun
    SiPMRun* run = static_cast<SiPMRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    run->AddEdep(fEdep);
}
