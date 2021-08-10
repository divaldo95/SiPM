//
//  SiPMActionInitialization.hh
//  sipm
//
//  Created by Baranyai David on 2018. 08. 22..
//

#ifndef SiPMActionInitialization_hh
#define SiPMActionInitialization_hh

#include "G4VUserActionInitialization.hh"
#include "SiPMPrimaryGeneratorAction.hh"
#include "SiPMRunAction.hh"
#include "SiPMEventAction.hh"
#include "SiPMSteppingAction.hh"
/// Action initialization class.

class SiPMActionInitialization : public G4VUserActionInitialization
{
public:
    SiPMActionInitialization();
    virtual ~SiPMActionInitialization();
    
    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif /* SiPMActionInitialization_hh */
