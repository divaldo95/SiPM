//
//  SiPMRun.hh
//  sipm
//
// run for threads
//
//  Created by Baranyai David on 2018. 08. 22..
//

#ifndef SiPMRun_hh
#define SiPMRun_hh

#include "G4Run.hh"
#include "globals.hh"

class SiPMRun : public G4Run
{
public:
    SiPMRun();
    virtual ~SiPMRun();
    
    virtual void Merge(const G4Run*);
    
    void AddEdep (G4double edep);
    
    G4double GetEdep()  const { return fEdep; }
    
private:
    G4double  fEdep;
};

#endif /* SiPMRun_hh */
