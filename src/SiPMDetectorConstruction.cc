//
//  SiPMDetectorConstruction.cpp
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//
// 2020.02.07   - SiPM size fixed
//              - Scintillator is now a box

#include "SiPMDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMDetectorConstruction::SiPMDetectorConstruction() : G4VUserDetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMDetectorConstruction::~SiPMDetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* SiPMDetectorConstruction::Construct()
{
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    
    //Get the parameters instance
    SiPMParameters& parameters = SiPMParameters::GetInstance();
    
    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = true;

    //---Object size calculations-----------------------------------------------------------------------------------
    //Calculate everything with real lengths
    double lengthMultiplier = parameters.GetLengthMultiplier();

    G4ThreeVector sipm_size = parameters.GetSiPMSize();
    sipm_size.setX(sipm_size.getX() * lengthMultiplier);
    sipm_size.setY(sipm_size.getY() * lengthMultiplier);
    sipm_size.setZ(sipm_size.getZ() * lengthMultiplier);

    G4ThreeVector scintillator_size = parameters.GetScintillatorSize();
    scintillator_size.setX(scintillator_size.getX() * lengthMultiplier);
    scintillator_size.setY(scintillator_size.getY() * lengthMultiplier);
    scintillator_size.setZ(scintillator_size.getZ() * lengthMultiplier);

    //Scintillator radius | only used if the shape of the scintillator is set to tube
    G4double scint_radius = parameters.GetScintillatorRadius() * lengthMultiplier;

    G4double coatingThickness = parameters.CoatingThickness() * lengthMultiplier;

    //Scintillator size with coating
    G4ThreeVector coated_scintillator_size = scintillator_size; //scintillator size already calculated with the length mulitiplier
    coated_scintillator_size.setX(coated_scintillator_size.getX() + (coatingThickness * 2));
    coated_scintillator_size.setY(coated_scintillator_size.getY() + (coatingThickness * 2));
    coated_scintillator_size.setZ(coated_scintillator_size.getZ() + (coatingThickness * 2)); //both sides

    //World size
    int sipm_size_multiplier = 0;
    if(parameters.FirstSiPMEnabled() || parameters.SecondSiPMEnabled()) sipm_size_multiplier = 1; //if at least one sipm is enabled, then increase the world size by sipm size * 1
    else if (parameters.FirstSiPMEnabled() && parameters.SecondSiPMEnabled()) sipm_size_multiplier = 2; //if both sipm is enabled, then increase the world size by sipm size * 2
    
    G4double world_sizeZ = 0;
    if (coatingThickness > sipm_size.getZ()) //if coating thicker than sipm, then increase the worldZ by the coating thickness
    {
        world_sizeZ = coated_scintillator_size.getZ()+2*cm;
    }
    else
    {
      world_sizeZ = sipm_size_multiplier * sipm_size.getZ() + scintillator_size.getZ()+2*cm; //itt miert nem a  coated_scintillator_size.getZ van? UB
    }
    //add +2*cm to see the scattered out gammas 
    G4double world_sizeX = (parameters.GetXDivison()) * coated_scintillator_size.getX();
    G4double world_sizeY = (parameters.GetYDivison()) * coated_scintillator_size.getY();

    //Container sizes
    G4double container_sizeX = coated_scintillator_size.getX();
    G4double container_sizeY = coated_scintillator_size.getY();
    G4double container_sizeZ = world_sizeZ;

    G4double absLength1 = parameters.GetAbsorptionLength1();
    G4double absLength2 = parameters.GetAbsorptionLength2();
    G4double refrIndex1 = parameters.GetRefractiveIndex1();
    G4double refrIndex2 = parameters.GetRefractiveIndex2();

    G4double coatingReflectivity1 = parameters.GetCoatingReflectivity1();
    G4double coatingReflectivity2 = parameters.GetCoatingReflectivity2();

    //------------------------------------------------------------------------------------------------------------------

    //---Object position calculations-----------------------------------------------------------------------------------
    G4ThreeVector pos_sipm0 = G4ThreeVector();
    G4ThreeVector pos_sipm1 = G4ThreeVector();
    G4ThreeVector posScint = G4ThreeVector();
    G4ThreeVector posScintCoating = G4ThreeVector();
    double z_pos_helper = 0;

    //World position
    G4ThreeVector posWorld = G4ThreeVector(); //at (0, 0, 0)

    //SiPM0 position
    if (parameters.FirstSiPMEnabled())
    {
        if (coatingThickness > sipm_size.getZ())
        {
            z_pos_helper = coatingThickness - (sipm_size.getZ() / 2);
        }
        else
        {
            z_pos_helper = sipm_size.getZ() / 2;
        }
        z_pos_helper = z_pos_helper - (container_sizeZ / 2);
        pos_sipm0 = G4ThreeVector(0, 0, z_pos_helper); //center on X and Y
    }

    //SiPM1 position
    if (parameters.SecondSiPMEnabled())
    {
        if (coatingThickness > sipm_size.getZ())
        {
            z_pos_helper = coatingThickness + scintillator_size.getZ() + (sipm_size.getZ() / 2);
        }
        else
        {
            z_pos_helper = sipm_size.getZ() + scintillator_size.getZ() + sipm_size.getZ() / 2;
        }
        z_pos_helper = z_pos_helper - (container_sizeZ / 2);
        pos_sipm1 = G4ThreeVector(0, 0, z_pos_helper); //center on X and Y
    }

    //Coating position
    if (parameters.FirstSiPMEnabled())
    {
        if (coatingThickness > sipm_size.getZ())
        {
            z_pos_helper = coated_scintillator_size.getZ() / 2;
        }
        else
        {
            z_pos_helper = sipm_size.getZ() - coatingThickness + (coated_scintillator_size.getZ() / 2);
        }
        z_pos_helper = z_pos_helper - (container_sizeZ / 2);
        posScintCoating = G4ThreeVector(0, 0, z_pos_helper); //center on X and Y
    }
    else
    {
        z_pos_helper = coated_scintillator_size.getZ() / 2;
        z_pos_helper = z_pos_helper - (container_sizeZ / 2);
        posScintCoating = G4ThreeVector(0, 0, z_pos_helper); //center on X and Y
    }

    //Scintillator position
    if (parameters.FirstSiPMEnabled())
    {
        if (coatingThickness > sipm_size.getZ())
        {
            z_pos_helper = coatingThickness + (scintillator_size.getZ() / 2);
        }
        else
        {
            z_pos_helper = sipm_size.getZ() + (scintillator_size.getZ() / 2);
        }
        z_pos_helper = z_pos_helper - (container_sizeZ / 2);
        posScint = G4ThreeVector(0, 0, z_pos_helper); //center on X and Y
    }
    else
    {
        z_pos_helper = coatingThickness + (scintillator_size.getZ() / 2);
        z_pos_helper = z_pos_helper - (container_sizeZ / 2);
        //posScint = G4ThreeVector(0, 0, z_pos_helper); //center on X and Y
    }

    //------------------------------------------------------------------------------------------------------------------

    //---Material definitions-------------------------------------------------------------------------------------------
    G4double a, z, density;
    G4int nelements;

    // Air
    G4Element* N = new G4Element("Nitrogen", "N", z = 7, a = 14.01 * g / mole);
    G4Element* O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);
    G4Material* air = new G4Material("Air", density = 1.29 * mg / cm3, nelements = 2);
    air->AddElement(N, 70. * perCent);
    air->AddElement(O, 30. * perCent);

    //Water
    G4Element* H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * g / mole);
    G4Material* water = new G4Material("Water", density = 1.0 * g / cm3, nelements = 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);

    G4Material* Sci  = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    G4Material* pvc  = nist->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE"); 
    
    G4Material* wolfram = nist->FindOrBuildMaterial("G4_W");

    //Object materials
    G4Material* world_mat = air;            //nist->FindOrBuildMaterial("G4_AIR");
    G4Material* scint_mat = Sci;          //nist->FindOrBuildMaterial("G4_Si");
    G4Material* scint_coating = pvc;    //nist->FindOrBuildMaterial("G4_W");
    G4Material* sipm0_mat = air;            //nist->FindOrBuildMaterial("G4_Si");
    G4Material* sipm1_mat = air;            //nist->FindOrBuildMaterial("G4_Si");
    //------------------------------------------------------------------------------------------------------------------

    //---World definitions----------------------------------------------------------------------------------------------
    G4Box* solidWorld = new G4Box(  "World",                //its name
                                    world_sizeX,
                                    world_sizeY,
                                    world_sizeZ);   //its size
    //Prevent overlapping so the world size is doubled
    
    G4LogicalVolume* logicWorld = new G4LogicalVolume(  solidWorld, //its solid
                                                        world_mat,  //its material
                                                        "World");   //its name
    
    G4VPhysicalVolume* physWorld = new G4PVPlacement(   0,                  //no rotation
                                                        posWorld,           //at (0,0,0)
                                                        logicWorld,         //its logical volume
                                                        "World",            //its name
                                                        0,                  //its mother  volume
                                                        false,              //no boolean operation
                                                        0,                  //copy lxenumber
                                                        checkOverlaps);     //overlaps checking
    //------------------------------------------------------------------------------------------------------------------

    //---Container definitions------------------------------------------------------------------------------------------
    //Place a container which contains everything (sipms, scintillator, coating) for G4PVPlacement
    G4Box *solidContainer = new G4Box(  "Container",            //name
                                        container_sizeX * 0.5,
                                        container_sizeY * 0.5, 
                                        container_sizeZ * 0.5); //size
    
    G4LogicalVolume *logicContainer = new G4LogicalVolume(  solidContainer, //its solid
                                                            world_mat,      //its material
                                                            "Container");   //its name
    
    G4Colour containerColour( 1.0, 1.0, 0.0);
    G4VisAttributes* containerVisAtt = new G4VisAttributes( containerColour );
    logicContainer -> SetVisAttributes(containerVisAtt);
    logicContainer -> SetVisAttributes(G4VisAttributes::GetInvisible());
    //------------------------------------------------------------------------------------------------------------------

    //---Scintillator coating definitions-------------------------------------------------------------------------------
    G4Box* solidScintCoating = new G4Box(   "ScintillatorCoating",                      //its name
                                            0.5 * coated_scintillator_size.getX(),
                                            0.5 * coated_scintillator_size.getY(),
                                            0.5 * coated_scintillator_size.getZ());     //its size


    //---Scintillator definitions---------------------------------------------------------------------------------------

    G4Box* solidScint = new G4Box(  "Scintillator",                      //its name
                                    0.5 * scintillator_size.getX(),
                                    0.5 * scintillator_size.getY(),
                                    0.5 * scintillator_size.getZ());     //its size

    G4LogicalVolume* logicScint = new G4LogicalVolume(  solidScint,         //its solid
                                                        scint_mat,          //its material
                                                        "Scintillator");    //its name

    G4VSolid* solidCoating = new G4SubtractionSolid("ScintillatorCoating", 
                                                    solidScintCoating, 
                                                    solidScint/*, 
                                                    0, 
                                                    G4ThreeVector(0, 0, 0)*/);

    G4LogicalVolume* logicScintCoating = new G4LogicalVolume(   solidCoating,           //its solid
                                                                scint_coating,          //its material
                                                                "ScintillatorCoating"); //its name

    G4VPhysicalVolume* physScint = new G4PVPlacement(   0,               //no rotation
                                                        posScint,        //at position
                                                        logicScint,      //its logical volume
                                                        "Scintillator",  //its name
        logicContainer,  //its mother  volume
                                                        false,           //no boolean operation
                                                        0,               //copy lxenumber
                                                        checkOverlaps);  //overlaps checking

    G4VPhysicalVolume* physScintCoating = new G4PVPlacement(0,                      //no rotation
                                                            posScintCoating,        //at position
                                                            logicScintCoating,      //its logical volume
                                                            "ScintillatorCoating",  //its name
                                                            logicContainer,         //its mother  volume
                                                            false,                  //no boolean operation
                                                            0,                      //copy lxenumber
                                                            checkOverlaps);         //overlaps checking


    G4Colour scintColour(1.0, 0, 0.0);
    G4VisAttributes* scintVisAtt = new G4VisAttributes(scintColour);
    logicScint->SetVisAttributes(scintVisAtt);
    //------------------------------------------------------------------------------------------------------------------

    //---SiPM0 definitions----------------------------------------------------------------------------------------------
    G4Colour sipmColour(0.0, 1.0, 0.0);
    G4Box* solidSipm0;
    G4LogicalVolume* logicSipm0;
    G4VPhysicalVolume* physSipm0;
    G4VisAttributes* sipmVisAtt;

    if (parameters.FirstSiPMEnabled())
    {
        solidSipm0 = new G4Box(  "Sipm0",                //its name
                                 0.5 * sipm_size.getX(),
                                 0.5 * sipm_size.getY(),
                                 0.5 * sipm_size.getZ()); //its size

        logicSipm0 = new G4LogicalVolume(  solidSipm0, //its solid
                                           sipm0_mat,  //its material
                                           "Sipm0");   //its name

        physSipm0 = new G4PVPlacement(  0,              //no rotation
                                        pos_sipm0,      //at position
                                        logicSipm0,     //its logical volume
                                        "Sipm0",        //its name
                                        logicContainer, //its mother  volume
                                        false,          //no boolean operation
                                        0,              //copy lxenumber
                                        checkOverlaps); //overlaps checking
        sipmVisAtt = new G4VisAttributes(sipmColour);
        logicSipm0->SetVisAttributes(sipmVisAtt);
    }
    //------------------------------------------------------------------------------------------------------------------

    //---SiPM1 definitions----------------------------------------------------------------------------------------------
    // sipm1 shape -> same as sipm0
    G4Box* solidSipm1;
    G4LogicalVolume* logicSipm1;
    G4VPhysicalVolume* physSipm1;

    if (parameters.SecondSiPMEnabled())
    {
        solidSipm1 = new G4Box(  "Sipm1",                    //its name
                                 0.5 * sipm_size.getX(),
                                 0.5 * sipm_size.getY(),
                                 0.5 * sipm_size.getZ());    //its size

        logicSipm1 = new G4LogicalVolume(   solidSipm1, //its solid
                                            sipm1_mat,  //its material
                                            "Sipm1");   //its name

        physSipm1 = new G4PVPlacement(  0,              //no rotation
                                        pos_sipm1,      //at position
                                        logicSipm1,     //its logical volume
                                        "Sipm1",        //its name
                                        logicContainer, //its mother  volume
                                        false,          //no boolean operation
                                        0,              //copy lxenumber
                                        checkOverlaps); //overlaps checking

        logicSipm1->SetVisAttributes(sipmVisAtt);
    }
    //------------------------------------------------------------------------------------------------------------------
    
    //---General values-------------------------------------------------------------------------------------------------
    const G4int n = 2;
    G4double pp[n] = {2.0 * eV, 3.0 * eV}; //distribution of optical photons produced in eV
    //------------------------------------------------------------------------------------------------------------------
    
    //---General Material Settings--------------------------------------------------------------------------------------   
    //material of scintillator
    G4double rind_scintillator[n] = {refrIndex1, refrIndex2}; //{1.59, 1.57}; //refraction index
    G4double absl[n] = {absLength1*m, absLength2*m}; //{35*m, 35*m}; //absorption length
    G4double slow[n] = {1, 1};  //keresd meg ez mi a fenet csinal UB
    G4double fast[n] = {1, 1};  //meg ez UB
    
    G4MaterialPropertiesTable *scint_material_mpt = new G4MaterialPropertiesTable();
    
    scint_material_mpt -> AddProperty("RINDEX", pp, rind_scintillator, n);
    scint_material_mpt -> AddProperty("ABSLENGTH", pp, absl, n);
    scint_material_mpt -> AddProperty("SLOWCOMPONENT", pp, slow, n);
    scint_material_mpt -> AddProperty("FASTCOMPONENT", pp, fast, n);
    scint_material_mpt -> AddConstProperty("SCINTILLATIONYIELD", 1000./MeV); //50 volt
    scint_material_mpt -> AddConstProperty("RESOLUTIONSCALE", 1.0);
    scint_material_mpt -> AddConstProperty("FASTTIMECONSTANT", 0.01*ns);  //meg ez UB
    scint_material_mpt -> AddConstProperty("SLOWTIMECONSTANT", 1.*ns);//meg ez UB
    scint_material_mpt -> AddConstProperty("YIELDRATIO", 0.1);//meg ez UB
    
    scint_mat -> SetMaterialPropertiesTable(scint_material_mpt);
    
    //Surface of scintillator to wolfram
    G4OpticalSurface *OpScintillatorSurface = new G4OpticalSurface("Scintillator Surface to Wolfram",glisur, polished, dielectric_metal);
    
    G4LogicalBorderSurface *ScintillatorSurface = new G4LogicalBorderSurface("Scintillator Surface", physScint, physScintCoating, OpScintillatorSurface);
    
    G4double reflectivityCoating[n] = {coatingReflectivity1, coatingReflectivity2};
    G4double efficiencyCoating[n] = {0, 0};
    
    G4MaterialPropertiesTable *ScintillatorToWolframMaterialPropertyTable = new G4MaterialPropertiesTable();
    ScintillatorToWolframMaterialPropertyTable -> AddProperty("REFLECTIVITY", pp, reflectivityCoating, n);
    ScintillatorToWolframMaterialPropertyTable -> AddProperty("EFFICIENCY", pp, efficiencyCoating, n);
    
    OpScintillatorSurface -> SetMaterialPropertiesTable(ScintillatorToWolframMaterialPropertyTable);
    
    
    //Surface from scintillator to sipm0 and sipm1
    G4OpticalSurface *SurfacefromScintillatorToSipm = new G4OpticalSurface("SurfacefromScintillatorToSipm", glisur, polished, dielectric_metal);
    
    G4LogicalBorderSurface* SurfacefromScintillatorToSipm0_logical;
    G4LogicalBorderSurface* SurfacefromScintillatorToSipm1_logical;

    if (parameters.FirstSiPMEnabled())
    {
        SurfacefromScintillatorToSipm0_logical = new G4LogicalBorderSurface("SurfacefromScintillatorToSipm0", physScint, physSipm0, SurfacefromScintillatorToSipm);
    }

    if (parameters.SecondSiPMEnabled())
    {
        SurfacefromScintillatorToSipm1_logical = new G4LogicalBorderSurface("SurfacefromScintillatorToSipm1", physScint, physSipm1, SurfacefromScintillatorToSipm);
    }
    
    G4double reflectivity[n] = {1, 1}; //ha nem 1,1 akkor nem éri el a sipm-et az aki eléri a scint végét.
    
    G4MaterialPropertiesTable *ScintillatorMaterialPropertyTable = new G4MaterialPropertiesTable();
    ScintillatorMaterialPropertyTable -> AddProperty("REFLECTIVITY", pp, reflectivity, n);
    
    SurfacefromScintillatorToSipm -> SetMaterialPropertiesTable(ScintillatorMaterialPropertyTable);
    
    //------------------------------------------------------------------------------------------------------------------

    //---Container placement--------------------------------------------------------------------------------------------
    //Using G4PVPlacement instead of replica or others
    
     int x = parameters.GetXDivison();
     int y = parameters.GetYDivison();
     int copyNumber = 0;
     G4VPhysicalVolume *physContainer[x][y];
     char s1[30];
     
     for(int i = 0; i < x; i++)
     {
         for(int j = 0; j < y; j++)
         {
             snprintf(s1, 30, "Container_x%d_y%d", i, j);
             logicContainer -> SetName(s1);
             physContainer[i][j] = new G4PVPlacement(   0,
                                                        G4ThreeVector(i * container_sizeX + (container_sizeX / 2) - (world_sizeX / 2), j * container_sizeY + (container_sizeY / 2) - (world_sizeY / 2), container_sizeZ / 2),
                                                        logicContainer,
                                                        s1, //its name
                                                        logicWorld,
                                                        false,
                                                        copyNumber, //copy number
                                                        checkOverlaps);
             copyNumber++;
         }
     }
     //------------------------------------------------------------------------------------------------------------------
    return physWorld;
}
