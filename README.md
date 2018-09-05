
# SiPM Detector simulation using CERN Geant4

## Description
Simulation of detecting photons using Silicon photomultiplier.
The output file is a ROOT file. Can be checked by TBrowser.

## Prerequisities
* CERN Geant4
* CERN Root (tested on 6.13/03)
* Linux or MacOS (should work on Windows, not tested)

## Building
Before building, be sure that you changed the macroPath to the right directory in sipm.cc.
```
git clone https://git.divaldo.hu/divaldo/SiPM.git
mkdir build_dir && cd build_dir
cmake ../SiPM
make -jN (where N is the number of jobs to run simultaneously)
```
