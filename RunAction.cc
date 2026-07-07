#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

RunAction::RunAction() {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetVerboseLevel(1);

    // Make sure to merge all of your threads' work into one unified file
    analysisManager->SetNtupleMerging(true);
    
    // Create the Ntuple to store neutrino kinematics
    analysisManager->CreateNtuple("NeutrinoFlux", "Kinematics at z = 0");
    analysisManager->CreateNtupleIColumn("PDG");          // Particle ID
    analysisManager->CreateNtupleDColumn("Energy_GeV");   // Kinetic Energy
    analysisManager->CreateNtupleDColumn("x_mm");         // Position X
    analysisManager->CreateNtupleDColumn("y_mm");         // Position Y
    analysisManager->CreateNtupleDColumn("px");           // Direction X
    analysisManager->CreateNtupleDColumn("py");           // Direction Y
    analysisManager->CreateNtupleDColumn("pz");           // Direction Z
    analysisManager->FinishNtuple();
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    // We name our outputs from the macro file to be more easily modified
    analysisManager->OpenFile(); 
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}