//
//  SiPMRun.cpp
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//

#include "SiPMRun.hh"

SiPMRun::SiPMRun()
: G4Run()
{fEdep=0.0;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMRun::~SiPMRun()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMRun::Merge(const G4Run* run)
{
    const SiPMRun* localRun = static_cast<const SiPMRun*>(run);
    fEdep  += localRun->fEdep;
    
    G4Run::Merge(run);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMRun::AddEdep (G4double edep)
{
    fEdep  += edep;
}
