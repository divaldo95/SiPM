//
//  SiPMSteppingAction.cpp
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//

#include "SiPMSteppingAction.hh"

SiPMSteppingAction::SiPMSteppingAction(SiPMEventAction* eventAction) : G4UserSteppingAction(),
fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMSteppingAction::~SiPMSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void SiPMSteppingAction::UserSteppingAction(const G4Step* step)
{
    SiPMAnalysis& analysis = SiPMAnalysis::getInstance();

    G4LogicalVolume* volume
        = step->GetPreStepPoint()->GetTouchableHandle()
        ->GetVolume()->GetLogicalVolume();

    G4Track* fTrack = step->GetTrack();
    G4int trackID = fTrack->GetTrackID();

    G4double postTime = step->GetPostStepPoint()->GetLocalTime();

    if (fTrack->GetTrackStatus() != fAlive) { return; } /// check if it is alive

    G4VPhysicalVolume* prevolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4VPhysicalVolume* postvolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();


    G4double preX = step->GetPreStepPoint()->GetPosition().x();
    G4double preY = step->GetPreStepPoint()->GetPosition().y();
    G4double preZ = step->GetPreStepPoint()->GetPosition().z();
    G4double prekinE = step->GetPreStepPoint()->GetKineticEnergy();

    G4double postX = step->GetPostStepPoint()->GetPosition().x();
    G4double postY = step->GetPostStepPoint()->GetPosition().y();
    G4double postZ = step->GetPostStepPoint()->GetPosition().z();
    G4double postkinE = step->GetPostStepPoint()->GetKineticEnergy();

    G4String preName = prevolume->GetName();
    G4String postName = postvolume->GetName();


    G4Track* theTrack = step->GetTrack();
    G4ParticleDefinition* particleType = theTrack->GetDefinition();
    if (particleType == G4OpticalPhoton::OpticalPhotonDefinition())
    {
        if (postZ >= 40.9 * cm)
        {
            //std::cout << "Possibly hits sipm1: " << postZ  << " | " << particleType -> GetParticleName() << std::endl;
        }
        //std::cout << "Optical photon\n";
        /*if(preName == "Scintillator" && postName == "Scintillator")
         {
         std::cout << "Photon inside Scintillator" << std::endl;
         }*/
        if (postName == "Sipm0")
        {
            fEventAction -> IncrementPhotonNumber();
            fTrack->SetTrackStatus(fStopAndKill);
            //std::cout << "Photon reached Sipm0 at: " << step -> GetPostStepPoint() -> GetTouchableHandle() -> GetVolume(1) -> GetCopyNo() << std::endl;
            //std::cout << "Mother Logical name: " << step -> GetPostStepPoint() -> GetTouchableHandle() -> GetVolume(1) -> GetName() << std::endl;

            analysis.Fill(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume(1)->GetCopyNo(), postX, postY, postkinE, 1, fTrack->GetGlobalTime(), 0);

            //sipm0_num++;
        }
        if (postName == "Sipm1")
        {
            fEventAction -> IncrementPhotonNumber();
            fTrack->SetTrackStatus(fStopAndKill);
            //std::cout << "Photon reached Sipm1 at: " << step -> GetPostStepPoint() -> GetTouchableHandle() -> GetVolume(1) -> GetCopyNo() << std::endl;
            //std::cout << "Mother Logical name: " << step -> GetPostStepPoint() -> GetTouchableHandle() -> GetVolume(1) -> GetName() << std::endl;
            //std::cout << "Coordinates: " << postX << " " << postY << std::endl;
            //std::cout << "Global time: " << step -> GetPostStepPoint() -> GetGlobalTime() << std::endl;
            //std::cout << "Local time: " << postTime << std::endl;
            //std::cout << "Photon reached Sipm1 at copy no: " << postvolume -> GetCopyNo() << std::endl;
            //sipm1_num++;
            analysis.Fill(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume(1)->GetCopyNo(), postX, postY, postkinE, 2, fTrack->GetGlobalTime(), 0);
        }
        if (postName == "World")
        {
            fTrack->SetTrackStatus(fStopAndKill);
            std::cout << "Photon left World at: " << step->GetPostStepPoint()->GetTouchableHandle()->GetVolume(1)->GetCopyNo() << std::endl;
            //std::cout << "Mother Logical name: " << step -> GetPostStepPoint() -> GetTouchableHandle() -> GetVolume(1) -> GetName() << std::endl;
            std::cout << "Coordinates: " << postX << " " << postY << std::endl;
            std::cout << "Global time: " << step->GetPostStepPoint()->GetGlobalTime() << std::endl;
            std::cout << "Local time: " << postTime << std::endl;
            //std::cout << "Photon reached Sipm1 at copy no: " << postvolume -> GetCopyNo() << std::endl;
            //sipm1_num++;
            analysis.Fill(step -> GetPostStepPoint() -> GetTouchableHandle() -> GetVolume(1) -> GetCopyNo(), postX, postY, postkinE, 2, fTrack -> GetGlobalTime(), 1);
        }
        /*if(postName == "Scintillator_W")
         {
         //std::cout << "Photon reached wolfram" << std::endl;
         }*/
    }
    else if (particleType == G4Electron::ElectronDefinition())
    {
        //std::cout << "Electron\n";
    }
    //std::cout << "Sipm0: " << sipm0_num << std::endl << "Sipm1: " << sipm1_num << std::endl;


    // collect energy deposited in this step
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep);

}
