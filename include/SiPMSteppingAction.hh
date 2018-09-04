//
//  SiPMSteppingAction.hh
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//

#ifndef SiPMSteppingAction_hh
#define SiPMSteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "SiPMEventAction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTypes.hh"
#include "SiPMAnalysis.hh"


/// Stepping action class
///

class SiPMSteppingAction : public G4UserSteppingAction
{
public:
    SiPMSteppingAction(SiPMEventAction* eventAction);
    SiPMSteppingAction(const SiPMSteppingAction &) = default;
    void TestFunction();
    virtual ~SiPMSteppingAction();
    
    G4int Sipm0_Num() {return sipm0_num;}
    G4int Sipm1_Num() {return sipm1_num;}
    
    // method from the base class
    virtual void UserSteppingAction(const G4Step*);
    
private:
    G4int sipm0_num = 0;
    G4int sipm1_num = 0;
    SiPMEventAction*  fEventAction;
    
};

#endif /* SiPMSteppingAction_hh */
