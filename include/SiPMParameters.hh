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
#include "G4SystemOfUnits.hh"

class SiPMParameters
{
public:
    static SiPMParameters& GetInstance(const std::string& config_file_name = "config.conf");
    ~SiPMParameters();
    
    //---Units---------------------------------------------------------------------------------------------
    enum lengthUnit { mm, cm, m };

    void SetGlobalLengthUnit(lengthUnit l) { globalLengthUnit = l; }
    double GetLengthMultiplier() //returns the correct length multiplier for the global length unit (use it instead of *cm/*mm/*m)
    {
        switch (globalLengthUnit)
        {
            case mm:
                return millimeter;
                break;
            case cm:
                return centimeter;
                break;
            case m:
                return meter;
                break;
            default:
                return centimeter;
                break;
        }
    }


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
    void FirstSiPMEnabled(bool enabled) { sipm1Enabled = enabled; }
    bool FirstSiPMEnabled() { return sipm1Enabled; }
    void SecondSiPMEnabled(bool enabled) { sipm2Enabled = enabled; }
    bool SecondSiPMEnabled() { return sipm2Enabled; }
    
    //---Scintillator parameters---------------------------------------------------------------------------
    void SetScintillatorLength(G4double sc_l) { scintillator_length = sc_l; scintillator_Dimension.setZ(sc_l); }
    G4double GetScintillatorLength() { return scintillator_length; }
    void SetScintillatorSize(G4double x, G4double y, G4double z) { scintillator_Dimension.set(x, y, z); }
    G4ThreeVector GetScintillatorSize() { return scintillator_Dimension; }
    double CoatingThickness() { return cThickness; }
    void CoatingThickness(double t) { cThickness = t; }
    
    //---Division parameters-------------------------------------------------------------------------------
    void SetDivision(G4int x, G4int y) { x_division = x; y_division = y; };
    void SetXDivision(G4int x) { x_division = x; }
    void SetYDivision(G4int y) { y_division = y; }
    G4int GetXDivison() { return x_division; }
    G4int GetYDivison() { return y_division; }
    
    //---Radius parameters---------------------------------------------------------------------------------
    void SetScintillatorRadius(G4double sc_r) { scint_radius = sc_r; }
    G4double GetScintillatorRadius() { return scintIsBox ? 0.0 : scint_radius; } //If it is a box, return 0

    //---Scintillator Tube vs box parameters---------------------------------------------------------------
    void ScintillatorIsBox(bool isBox) { scintIsBox = isBox; }
    bool ScintillatorIsBox() { return scintIsBox; }
    
    //---Number of Events----------------------------------------------------------------------------------
    void SetNumberOfEvents(G4int noe1) { numberofevents = noe1; }
    G4int GetNumberOfEvents() { return numberofevents; }

    //Absorption lenght
    void SetAbsorptionLength1(G4double l) { absLength1 = l; }
    G4double GetAbsorptionLength1() { return absLength1; }
    void SetAbsorptionLength2(G4double l) { absLength2 = l; }
    G4double GetAbsorptionLength2() { return absLength2; }

    //Refraction Index
    void SetRefractiveIndex1(G4double i) { refrIndex1 = i; }
    G4double GetRefractiveIndex1() { return refrIndex1; }
    void SetRefractiveIndex2(G4double i) { refrIndex2 = i; }
    G4double GetRefractiveIndex2() { return refrIndex2; }

    //Coating reflectivity
    void SetCoatingReflectivity1(G4double r) { coatingreflectivity1 = r; }
    G4double GetCoatingReflectivity1() { return coatingreflectivity1; }
    void SetCoatingReflectivity2(G4double r) { coatingreflectivity2 = r; }
    G4double GetCoatingReflectivity2() { return coatingreflectivity2; }

    //Init things
    bool initialized = false;
    
    void ResetToDefaults();

    SiPMParameters(const SiPMParameters&) = delete;
    SiPMParameters& operator=(const SiPMParameters&) = delete;
    
private:
    SiPMParameters(const std::string& config_file_name);
    void PrintUsedFilename();
    
    //---Config file---------------------------------------------------------------------------------------
    std::string config_file;
    void StoreConfigValues(std::string key1, std::string value1);
    void CheckValues();
    bool conf_loaded = false;
    
    G4ThreeVector particleGun_position;
    G4ThreeVector particleGun_MomentumDirection;
    G4double particleGun_energy; //in GeV
    
    G4ThreeVector sipm_Dimension; //applies to both (in cm)
    G4double scintillator_length; //the size same as sipm
    G4double scint_radius;
    G4ThreeVector scintillator_Dimension;
    
    G4int x_division;
    G4int y_division;
    
    G4int numberofevents;

    G4double absLength1;
    G4double absLength2;
    G4double refrIndex1;
    G4double refrIndex2;

    G4double coatingreflectivity1;
    G4double coatingreflectivity2;

    bool scintIsBox = true;
    bool sipm1Enabled = true;
    bool sipm2Enabled = false;

    lengthUnit globalLengthUnit = cm; //default length is cm
    
    double cThickness = 1;
};

#endif /* Parameters_hh */
