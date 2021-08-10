//
//  SiPMPrimaryGeneratorAction.hh
//  sipm
//
// particle, energy, momentum, position...
//
//  Created by Baranyai David on 2018. 08. 22..
//

#ifndef SiPMPrimaryGeneratorAction_hh
#define SiPMPrimaryGeneratorAction_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "SiPMParameters.hh"

class SiPMPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    SiPMPrimaryGeneratorAction();
    virtual ~SiPMPrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event*);
    
private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    
};

#endif /* SiPMPrimaryGeneratorAction_hh */
