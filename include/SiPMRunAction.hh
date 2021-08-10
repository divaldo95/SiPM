//
//  SiPMRunAction.hh
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//

#ifndef SiPMRunAction_hh
#define SiPMRunAction_hh

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "SiPMPrimaryGeneratorAction.hh"
#include "SiPMDetectorConstruction.hh"
#include "SiPMRun.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "SiPMAnalysis.hh"

class SiPMRunAction : public G4UserRunAction
{
public:
    SiPMRunAction();
    virtual ~SiPMRunAction();
    
    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};


#endif /* SiPMRunAction_hh */
