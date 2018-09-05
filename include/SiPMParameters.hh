//
//  Parameters.hh
//  Parameters
//
//  Created by Baranyai David on 2018. 06. 30..
//  Modified for SiPM Simulation on 2018. 08. 23..
//  Copyright © 2018. Baranyai David. All rights reserved.
//

#ifndef SiPMParameters_hh
#define SiPMParameters_hh

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "G4ThreeVector.hh"

class SiPMParameters
{
public:
    static SiPMParameters *GetInstance();
    ~SiPMParameters();
    
    //---Config file---------------------------------------------------------------------------------------
    void ParseConfigFile(); //Read the default config file
    void ParseConfigFile(std::string config_file1); //Read another config file
    
    //---Particle Gun parameters---------------------------------------------------------------------------
    void SetParticleGunPosition(G4ThreeVector pgp) { particleGun_position = pgp; }
    void SetParticleGunPosition(G4double x, G4double y, G4double z) { particleGun_position.set(x, y, z); }
    G4ThreeVector GetParticleGunPosition() { return particleGun_position; }
    
    void SetParticleGunMomentumDirection(G4ThreeVector pgm) { particleGun_MomentumDirection = pgm; }
    void SetParticleGunMomentumDirection(G4double x, G4double y, G4double z) { particleGun_MomentumDirection.set(x, y, z); }
    G4ThreeVector GetParticleGunMomentumDirection() { return particleGun_MomentumDirection; }
    
    void SetParticleGunEnergy(G4double pge) { particleGun_energy = pge; }
    G4double GetParticleGunEnergy() { return particleGun_energy; }
    
    //---SiPM parameters-----------------------------------------------------------------------------------
    void SetSiPMSize(G4ThreeVector sipm_s) { sipm_Dimension = sipm_s; }
    void SetSiPMSize(G4double x, G4double y, G4double z) { sipm_Dimension.set(x, y, z); }
    G4ThreeVector GetSiPMSize() { return sipm_Dimension; }
    
    //---Scintillator parameters---------------------------------------------------------------------------
    void SetScintillatorLength(G4double sc_l) { scintillator_length = sc_l; }
    G4double GetScintillatorLength() { return scintillator_length; }
    
    //---Division parameters-------------------------------------------------------------------------------
    void SetDivision(G4int x, G4int y) { x_division = x; y_division = y; };
    void SetXDivision(G4int x) { x_division = x; }
    void SetYDivision(G4int y) { y_division = y; }
    G4int GetXDivison() { return x_division; }
    G4int GetYDivison() { return y_division; }
    
    //---Radius parameters---------------------------------------------------------------------------------
    void SetScintillatorRadius(G4double sc_r) { scint_radius = sc_r; }
    G4double GetScintillatorRadius() { return scint_radius; }
    
    //---Number of Events----------------------------------------------------------------------------------
    void SetNumberOfEvents(G4int noe1) { numberofevents = noe1; }
    G4int GetNumberOfEvents() { return numberofevents; }
    
    void ResetToDefaults();
    
private:
    SiPMParameters();
    static SiPMParameters *instance;
    
    //---Config file---------------------------------------------------------------------------------------
    std::string config_file;
    void StoreConfigValues(std::string key1, std::string value1);
    void CheckValues();
    
    G4ThreeVector particleGun_position;
    G4ThreeVector particleGun_MomentumDirection;
    G4double particleGun_energy; //in GeV
    
    G4ThreeVector sipm_Dimension; //applies to both (in cm)
    G4double scintillator_length; //the size same as sipm
    
    G4int x_division;
    G4int y_division;
    
    G4double scint_radius;
    
    G4int numberofevents;
    
};

#endif /* Parameters_hh */
