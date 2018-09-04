//
//  SiPMPrimaryGeneratorAction.cpp
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//

#include "SiPMPrimaryGeneratorAction.hh"

SiPMPrimaryGeneratorAction::SiPMPrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
    SiPMParameters *parameters = SiPMParameters::GetInstance();
    G4int n_particle = 1;   //particles per event
    fParticleGun  = new G4ParticleGun(n_particle);
    
    // default particle kinematic
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName="mu+");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(parameters -> GetParticleGunMomentumDirection());
    fParticleGun->SetParticleEnergy(parameters -> GetParticleGunEnergy()*GeV); //1GeV
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMPrimaryGeneratorAction::~SiPMPrimaryGeneratorAction()
{
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    SiPMParameters *parameters = SiPMParameters::GetInstance();
    fParticleGun->SetParticlePosition(parameters -> GetParticleGunPosition());
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
