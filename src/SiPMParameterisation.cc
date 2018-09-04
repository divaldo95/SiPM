//
//  SiPMParameterisation.cc
//  sipm
//
//  Created by Baranyai David on 2018. 08. 23..
//

#include "SiPMParameterisation.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMParameterisation::SiPMParameterisation(G4int    noChambersX,
                                           G4int    noChambersY,
                                           G4double spacingZ,        //  Z spacing of centers | The distance between the chambers' center
                                           G4double widthChamber)
: G4VPVParameterisation()
{
    fNoChambersX =  noChambersX;
    fNoChambersY = noChambersY;
    fWidth = widthChamber + spacingZ;
    fHalfWidth  =  0.5*widthChamber;
    fSpacing    =  spacingZ;
    if (fNoChambersX < 0 || fNoChambersY < 0)
    {
        G4Exception("SiPMParameterisation::SiPMParameterisation()",
                    "InvalidSetup", FatalException,
                    "fNoChambersX or fNoChambersX < 0");
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMParameterisation::~SiPMParameterisation()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMParameterisation::ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
    // Note: copyNo will start with zero!
    G4double Xposition = copyNo * fWidth;
    G4ThreeVector origin(0,Xposition,0);
    physVol->SetTranslation(origin);
    physVol->SetRotation(0);
    std::cout << "ComputeTransform called | Copy no: " << copyNo << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMParameterisation::ComputeDimensions(G4Tubs& trackerChamber, const G4int copyNo, const G4VPhysicalVolume*) const
{
    // Note: copyNo will start with zero!
    /*
    G4double rmax = fRmaxFirst + copyNo * fRmaxIncr;
    trackerChamber.SetInnerRadius(0);
    trackerChamber.SetOuterRadius(rmax);
    trackerChamber.SetZHalfLength(fHalfWidth);
    trackerChamber.SetStartPhiAngle(0.*deg);
    trackerChamber.SetDeltaPhiAngle(360.*deg);
     */
}
