# GEANT4_MuC_Nu_Flux_Gen
Scripts that generate flux files using GEANT4, specifically for neutrino interaction studies for future Muon Colliders.

These scripts are built with an installation of GEANT4 version 11.4.2. The code is meant to be fairly lightweight and focused solely on the generation of particles and flux distribution. Running a simulation will start with a beam of certain parameters defined by the user composed of particles defined by the user. This beam will travel a prescribed distance and undergo physicsal processes along the way. The output particles and distributions are saved as a flux file, which is a root file. This file may then be passed to GEANT4 or GENIE for further physics investigations.

The parameters of the flux you wish to generate can be edited from within the gps.mac file as it contains the most relevant beam information and settings.

## Setup:
```
mkdir build
cd build
cmake ..
make
```

## Run:
```
./flux_gen ../gps.mac
```
