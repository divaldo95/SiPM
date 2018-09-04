//
//  Parameters.cc
//  Parameters
//
//  Created by Baranyai David on 2018. 06. 30..
//  Modified for SiPM Simulation on 2018. 08. 23..
//  Copyright © 2018. Baranyai David. All rights reserved.
//

#include "SiPMParameters.hh"

SiPMParameters* SiPMParameters::GetInstance()
{
    if (instance == 0)
    {
        instance = new SiPMParameters();
    }
    
    return instance;
}

SiPMParameters* SiPMParameters::instance = 0;

SiPMParameters::SiPMParameters()
{
    ResetToDefaults();
}

SiPMParameters::~SiPMParameters()
{
}

void SiPMParameters::ResetToDefaults()
{
    particleGun_position = G4ThreeVector(50, -5, 0);
    particleGun_MomentumDirection = G4ThreeVector(0.5, 1, 0);
    particleGun_energy = 1; //in GeV
    
    sipm_Dimension = G4ThreeVector(1, 1, 1); //applies to both (in cm)
    scintillator_length = 40; //the size same as sipm
    
    x_division = 10;
    y_division = 10;
    
    scint_radius = 0.25; //in cm
}
