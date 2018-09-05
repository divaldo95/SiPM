//
//  SiPMDetectorConstruction.cpp
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//

#include "SiPMDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMDetectorConstruction::SiPMDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMDetectorConstruction::~SiPMDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* SiPMDetectorConstruction::Construct()
{
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    
    //Get the parameters instance
    SiPMParameters *parameters = SiPMParameters::GetInstance();
    
    
    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = true;
    
    
    // ------------- Materials -------------
    
    G4double a, z, density;
    G4int nelements;
    
    // Air
    //
    G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
    G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
    
    G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
    air->AddElement(N, 70.*perCent);
    air->AddElement(O, 30.*perCent);
    
    // Water
    //
    G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
    
    G4Material* water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);
    
    /*
     * Wolfram material
     */
    G4Material *wolfram = nist -> FindOrBuildMaterial("G4_W");
    
    
    //
    // World
    //
    G4ThreeVector sipm_size = parameters -> GetSiPMSize();
    
    G4double world_sizeX = parameters -> GetXDivison() * sipm_size.getX() * cm; //2*m;
    G4double world_sizeY = parameters -> GetYDivison() * sipm_size.getY() * cm; //2*m;
    G4double world_sizeZ  = 2*sipm_size.getZ() + parameters -> GetScintillatorLength();
    G4Material* world_mat = air; //nist->FindOrBuildMaterial("G4_AIR");
    
    G4Box* solidWorld =
    new G4Box("World",                       //its name
              /*0.5**/world_sizeX, /*0.5**/world_sizeY, /*0.5**/world_sizeZ);     //its size
    
    G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
    
    G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy lxenumber
                      checkOverlaps);        //overlaps checking
    
    //Place a container which contains everything for G4Replica
    G4double container_sizeX = sipm_size.getX()*cm;
    G4double container_sizeY = sipm_size.getY()*cm;
    G4double container_sizeZ = (sipm_size.getZ()*2 + parameters -> GetScintillatorLength())*cm;
    
    G4Box *solidContainer =
    new G4Box("Container", container_sizeX*0.5, container_sizeY*0.5, container_sizeZ*0.5);
    
    G4LogicalVolume *logicContainer =
    new G4LogicalVolume(solidContainer, world_mat, "Container");
    
    G4Colour containerColour( 1.0, 1.0, 0.0);
    G4VisAttributes* containerVisAtt = new G4VisAttributes( containerColour );
    //logicContainer -> SetVisAttributes(containerVisAtt);
    
    G4double sizeX = sipm_size.getX()*cm;
    G4double sizeY = sipm_size.getY()*cm;
    G4double sipm_width = sipm_size.getZ()*cm;
    
    //
    // Sipm0
    //
    G4Material* sipm0_mat = air; //nist->FindOrBuildMaterial("G4_Si");
    
    // sipm0 shape
    G4double sipm0_sizeX = sizeX;
    G4double sipm0_sizeY = sizeY;
    G4double sipm0_sizeZ = sipm_width;
    
    G4ThreeVector pos_sipm0 = G4ThreeVector(0, 0*cm, (sipm_width/2)-container_sizeZ*0.5);
    
    G4Box* solidSipm0 =
    new G4Box("Sipm0",                      //its name
              0.5*sipm0_sizeX, 0.5*sipm0_sizeY,
              0.5*sipm0_sizeZ); //its size
    
    G4LogicalVolume* logicSipm0 =
    new G4LogicalVolume(solidSipm0,         //its solid
                        sipm0_mat,          //its material
                        "Sipm0");           //its name
    
    G4VPhysicalVolume *physSipm0 =
    new G4PVPlacement(0,                       //no rotation
                      pos_sipm0,                    //at position
                      logicSipm0,             //its logical volume
                      "Sipm0",                //its name
                      logicContainer,                //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy lxenumber
                      checkOverlaps);          //overlaps checking
    
    G4Colour sipmColour( 0.0, 1.0, 0.0);
    G4VisAttributes* sipmVisAtt = new G4VisAttributes( sipmColour );
    logicSipm0->SetVisAttributes(sipmVisAtt);
    
    
    //
    // Box
    // Changed the scintillator construction so now the box is Wolfram whic contains the scintillator
    //
    //
    G4Material* scint_mat = water; //nist->FindOrBuildMaterial("G4_Si");
    
    // box shape
    G4double scint_sizeX = sizeX;
    G4double scint_sizeY = sizeY;
    G4double scint_sizeZ = parameters -> GetScintillatorLength() * cm;
    
    G4double z_pos = sipm_width + (scint_sizeZ*0.5);
    
    G4ThreeVector posScint = G4ThreeVector(0, 0*cm, z_pos-container_sizeZ*0.5);
    
    G4Box* solidScint_W =
    new G4Box("Scintillator_W",                      //its name
              0.5*scint_sizeX, 0.5*scint_sizeY,
              0.5*scint_sizeZ); //its size
    
    G4LogicalVolume* logicScint_W =
    new G4LogicalVolume(solidScint_W,         //its solid
                        wolfram,          //its material
                        "Scintillator_W");           //its name
    
    G4VPhysicalVolume *physScint_W =
    new G4PVPlacement(0,                       //no rotation
                      posScint,                    //at position
                      logicScint_W,             //its logical volume
                      "Scintillator_W",                //its name
                      logicContainer,                //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy lxenumber
                      checkOverlaps);          //overlaps checking
    
    /*
     * Scintillator
     */
    
    G4double scint_radius = parameters -> GetScintillatorRadius()*cm;
    
    G4Tubs * solidScint = new G4Tubs("tube", 0, scint_radius, 0.5*(scint_sizeZ+(0.5*mm)), 0, 2*CLHEP::pi); //name, inner R, outter R, Half length in Z, starting angle, angle of the segment in rad
    new G4Box("Scintillator",
              0.5*scint_sizeX,
              0.5*scint_sizeY,
              0.5*scint_sizeZ);
    
    G4LogicalVolume *logicScint =
    new G4LogicalVolume(solidScint,         //its solid
                        scint_mat,          //its material
                        "Scintillator");    //its name
    
    G4VPhysicalVolume *physScint =
    new G4PVPlacement(0,                    //no rotation
                      G4ThreeVector(0,0,0), //at position (as the mother volume is not the world, maybe this will be the right place)
                      logicScint,           //its logical volume
                      "Scintillator",       //its name
                      logicScint_W,           //its mother volume
                      false,                //no boolean operation
                      0,                    //copy lxenumber
                      checkOverlaps);       //overlaps checking
    
    G4Colour scintColour( 1.0, 0, 0.0);
    G4VisAttributes* scintVisAtt = new G4VisAttributes( scintColour );
    logicScint -> SetVisAttributes(scintVisAtt);
    
    //
    // Sipm1
    //
    
    G4double sipm2_pos_z = (0.5*sipm_width) + scint_sizeZ;
    
    G4Material* sipm1_mat = air; //nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos_sipm1 = G4ThreeVector(0, 0*cm, sipm_width+sipm2_pos_z-container_sizeZ*0.5);
    
    // sipm1 shape -> same as sipm0
    G4Box* solidSipm1 =
    new G4Box("Sipm1",                      //its name
              0.5*sipm0_sizeX, 0.5*sipm0_sizeY,
              0.5*sipm0_sizeZ); //its size
    
    G4LogicalVolume* logicSipm1 =
    new G4LogicalVolume(solidSipm1,         //its solid
                        sipm1_mat,          //its material
                        "Sipm1");           //its name
    
    G4VPhysicalVolume *physSipm1 =
    new G4PVPlacement(0,                       //no rotation
                      pos_sipm1,                    //at position
                      logicSipm1,             //its logical volume
                      "Sipm1",                //its name
                      logicContainer,                //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy lxenumber
                      checkOverlaps);          //overlaps checking
    
    logicSipm1->SetVisAttributes(sipmVisAtt);
    
    //----------------------------------General values--------------------------------------------------------
    const G4int n = 2;
    G4double pp[n] = {2.0*eV, 3.0*eV}; //distribution of optical photons produced in eV
    
    //---------------------------------General Material Settings----------------------------------------------
    
    //material of scintillator
    G4double rind_scintillator[n] = {1.59, 1.57}; //refraction index
    G4double absl[n] = {35.*cm, 35.*cm}; //absorption length
    G4double slow[n] = {0.1, 1};
    G4double fast[n] = {0.1, 1};
    
    G4MaterialPropertiesTable *scint_material_mpt = new G4MaterialPropertiesTable();
    
    scint_material_mpt -> AddProperty("RINDEX", pp, rind_scintillator, n);
    scint_material_mpt -> AddProperty("ABSLENGTH", pp, absl, n);
    scint_material_mpt -> AddProperty("SLOWCOMPONENT", pp, slow, n);
    scint_material_mpt -> AddProperty("FASTCOMPONENT", pp, fast, n);
    scint_material_mpt -> AddConstProperty("SCINTILLATIONYIELD", 50./MeV); //50 volt
    scint_material_mpt -> AddConstProperty("RESOLUTIONSCALE", 1.0);
    scint_material_mpt -> AddConstProperty("FASTTIMECONSTANT", 20.*ns);
    scint_material_mpt -> AddConstProperty("SLOWTIMECONSTANT", 45.*ns);
    scint_material_mpt -> AddConstProperty("YIELDRATIO", 1);
    
    scint_mat -> SetMaterialPropertiesTable(scint_material_mpt);
    
    //Surface of scintillator to wolfram
    G4OpticalSurface *OpScintillatorSurface = new G4OpticalSurface("Scintillator Surface to Wolfram",glisur, polished, dielectric_metal);
    
    G4LogicalBorderSurface *ScintillatorSurface = new G4LogicalBorderSurface("Scintillator Surface", physScint, physScint_W, OpScintillatorSurface);
    
    G4double reflectivity_W[n] = {0.9, 0.9};
    G4double efficiency_W[n] = {0, 0};
    
    G4MaterialPropertiesTable *ScintillatorToWolframMaterialPropertyTable = new G4MaterialPropertiesTable();
    ScintillatorToWolframMaterialPropertyTable -> AddProperty("REFLECTIVITY", pp, reflectivity_W, n);
    ScintillatorToWolframMaterialPropertyTable -> AddProperty("EFFICIENCY", pp, efficiency_W, n);
    
    OpScintillatorSurface -> SetMaterialPropertiesTable(ScintillatorToWolframMaterialPropertyTable);
    
    
    //Surface from scintillator to sipm0 and sipm1
    G4OpticalSurface *SurfacefromScintillatorToSipm = new G4OpticalSurface("SurfacefromScintillatorToSipm", glisur, polished, dielectric_metal);
    
    G4LogicalBorderSurface *SurfacefromScintillatorToSipm0_logical = new G4LogicalBorderSurface("SurfacefromScintillatorToSipm0", physScint, physSipm0, SurfacefromScintillatorToSipm);
    
    G4LogicalBorderSurface *SurfacefromScintillatorToSipm1_logical2 = new G4LogicalBorderSurface("SurfacefromScintillatorToSipm1", physScint, physSipm1, SurfacefromScintillatorToSipm);
    
    
    //----------------------------------
    G4double reflectivity[n] = {1, 1}; //ha nem 1,1 akkor nem éri el a sipm-et az aki eléri a scint végét.
    
    G4MaterialPropertiesTable *ScintillatorMaterialPropertyTable = new G4MaterialPropertiesTable();
    ScintillatorMaterialPropertyTable -> AddProperty("REFLECTIVITY", pp, reflectivity, n);
    
    SurfacefromScintillatorToSipm -> SetMaterialPropertiesTable(ScintillatorMaterialPropertyTable);
    
    //Using G4PVPlacement instead of replica or others
    
     int x = parameters -> GetXDivison();
     int y = parameters -> GetYDivison();
     int helper = 0;
     G4VPhysicalVolume *physContainer[x][y];
     char s1[30];
     
     for(int i = 0; i < x; i++)
     {
         for(int j = 0; j < y; j++)
         {
             snprintf(s1, 30, "Container_x%d_y%d", i, j);
             logicContainer -> SetName(s1);
             physContainer[x][y] = new G4PVPlacement(0,
                                                     G4ThreeVector(i*container_sizeX, j*container_sizeY, 0),
                                                     logicContainer,
                                                     s1, //its name
                                                     logicWorld,
                                                     false,
                                                     helper, //copy number
                                                     checkOverlaps);
             helper++;
         }
     }
    
    return physWorld;
}
