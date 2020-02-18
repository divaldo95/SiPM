
# SiPM Detector simulation using CERN Geant4

## Description
Simulation of detecting photons using Silicon photomultiplier.
The output file is a ROOT file. Can be checked by TBrowser.

## Prerequisities
* CERN Geant4
* CERN Root (tested on 6.19/01)
* Linux or MacOS (should work on Windows, not tested)
* Also tested on WLS Ubuntu (X11 (for e.g. VcXsrv) and OpenGL needed)

## Building
Before building, be sure that you changed the macroPath to the right directory in sipm.cc.
```
git clone https://git.divaldo.hu/divaldo/SiPM.git
mkdir build_dir && cd build_dir
cmake ../SiPM
make -jN (where N is the number of jobs to run simultaneously)
```

## Running
Run with default parameters (not always works)
```
./sipm
```
Run with default config file (config.conf)
```
./sipm -df
```
Run with custom config file
```
./sipm -f config_file_name.conf
```

## Config file parameters
* pgpositionx - Particle Gun X position
* pgpositiony - Particle Gun Y position
* pgpositionz - Particle Gun Z position
* pgmomentumx - Particle Gun X momentum
* pgmomentumy - Particle Gun Y momentum
* pgmomentumz - Particle Gun Z momentum
* sipmsizex - SiPM X Size
* sipmsizey - SiPM Y Size
* sipmsizez - SiPM Z Size
* scintillatorsizex - Scintillator X Size
* scintillatorsizey - Scintillator Y Size
* scintillatorlength - Scintillator Z Size
* scintillatorisbox - Scintillator can be a tube or a box
* coatingthickness - Scintillator coating thickness
* scintillatorradius - Radius of the scintillator. Only used when it is a tube.
* xdivision - How many detectors should be placed along the X axis
* ydivision - How many detectors should be placed along the Y axis
* pgenergy - Particle Gun energy
* numberofevents - Number of events
* lengthunit - Size unit in detector construction (mm | cm | m)
* firstsipmenabled - Enable the first SiPM
* secondsipmenabled - Enable the second SiPM

# Changelog
## 2020-02-18
* Both SiPMs can be enabled or disabled
* Added an option to change between a box and tube scintillator (only box tested yet)
* Added new parameters
* Cleaned up the detector construction
* Small changes according to the new parameters

## 2020-02-06
* SiPMAnalisys' and SiPMParameters' GetInstance functions are returning a static reference instead of pointer
* G4Mutex replaced with std::mutex
* Input config file and output data file name can be changed with the GetInstance functions on the first call
