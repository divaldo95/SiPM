//
//  SiPMDetectorConstruction.hh
//  sipm
//
// here you can create and place your experiment
//
//  Created by Baranyai David on 2018. 08. 22..
//

#ifndef SiPMDetectorConstruction_hh
#define SiPMDetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4PVParameterised.hh"
#include "SiPMParameterisation.hh"
#include "SiPMParameters.hh"


/// Detector construction class to define materials and geometry.
class SiPMDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    SiPMDetectorConstruction();
    virtual ~SiPMDetectorConstruction();
    
    virtual G4VPhysicalVolume* Construct();
    
};

#endif /* SiPMDetectorConstruction_hh */
