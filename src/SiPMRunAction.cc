//
//  SiPMRunAction.cpp
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//

#include "SiPMRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMRunAction::SiPMRunAction() : G4UserRunAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMRunAction::~SiPMRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* SiPMRunAction::GenerateRun()
{
    return new SiPMRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMRunAction::BeginOfRunAction(const G4Run*)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMRunAction::EndOfRunAction(const G4Run* run)
{
    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;
    
    const SiPMRun* siPMRun = static_cast<const SiPMRun*>(run);
    G4double edepInRuns  = siPMRun->GetEdep();
    
    // Print
    //
    if (IsMaster()) {
        SiPMAnalysis *analysis = SiPMAnalysis::getInstance();
        analysis -> Close();
        G4cout
        << G4endl
        << "--------------------End of Global Run-----------------------";
    }
    else {
        G4cout
        << G4endl
        << "--------------------End of Local Run------------------------";
    }
    
    G4cout
    << G4endl
    << " The run consists of " << nofEvents << " edep: "<< edepInRuns/keV
    << G4endl;
    
}
