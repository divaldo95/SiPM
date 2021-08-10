//
//  SiPMEventAction.hh
//  sipm
//
// event, like one gamma from start till leaving the world
// collect event-level information, like total energy deposit of one gamma
//
//  Created by Baranyai David on 2018. 08. 22..
//

#ifndef SiPMEventAction_hh
#define SiPMEventAction_hh

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "SiPMRun.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"

/// Event action class

class SiPMEventAction : public G4UserEventAction
{
public:
    SiPMEventAction();
    virtual ~SiPMEventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
    
    void AddEdep(G4double edep) { fEdep += edep; }

    void IncrementPhotonNumber() { numberOfPhotons++; }
    
private:
    G4double  fEdep;
    int numberOfPhotons;
    bool fForcedrawphotons;
    bool fForcenophotons;
};

#endif /* SiPMEventAction_hh */
