
# SiPM Detector simulation using CERN Geant4

## Description
Simulation of detecting photons using Silicon photomultiplier.
The output file is a ROOT file. Can be checked by TBrowser.

## Prerequisities
* CERN Geant4
* CERN Root (tested on 6.19/01)
* Linux or MacOS (should work on Windows, not tested)
* Also tested on WLS Ubuntu (X11 needed)

## Building
Before building, be sure that you changed the macroPath to the right directory in sipm.cc.
```
git clone https://git.divaldo.hu/divaldo/SiPM.git
mkdir build_dir && cd build_dir
cmake ../SiPM
make -jN (where N is the number of jobs to run simultaneously)
```

## Updates
* 2020/02/06 - SiPMAnalisys' and SiPMParameters' GetInstance functions are returning a static reference instead of pointer
* 2020/02/06 - G4Mutex replaced with std::mutex
* 2020/02/06 - Input config file and output data file name can be changed with the GetInstance functions on the first call
