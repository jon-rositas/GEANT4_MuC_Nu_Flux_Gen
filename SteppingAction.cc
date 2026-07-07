#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction() : G4UserSteppingAction() {}
SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    
    // 1. Filter: Only look at neutrinos (PDG 12, -12, 14, -14)
    G4int pdg = std::abs(track->GetDefinition()->GetPDGEncoding());
    if (pdg != 12 && pdg != 14) return;
    
    G4StepPoint* prePoint = step->GetPreStepPoint();
    G4StepPoint* postPoint = step->GetPostStepPoint();
    
    // 2. Geometry Filter: Check if the track just crossed z = 0
    if (prePoint->GetPosition().z() < 0.0 && postPoint->GetPosition().z() >= 0.0) {
        
        // 3. Project the exact position at z = 0 (since the step likely overshot)
        G4ThreeVector pos = prePoint->GetPosition();
        G4ThreeVector dir = prePoint->GetMomentumDirection();
        
        // Distance along Z to get to 0
        G4double z_dist = 0.0 - pos.z(); 
        
        // Calculate exact X and Y at z = 0 using similar triangles
        G4double exact_x = pos.x() + dir.x() * (z_dist / dir.z());
        G4double exact_y = pos.y() + dir.y() * (z_dist / dir.z());
        
        auto analysisManager = G4AnalysisManager::Instance();
        
        // 4. Save Kinematics to ROOT
        analysisManager->FillNtupleIColumn(0, track->GetDefinition()->GetPDGEncoding());
        analysisManager->FillNtupleDColumn(1, track->GetKineticEnergy() / GeV);
        analysisManager->FillNtupleDColumn(2, exact_x / mm);
        analysisManager->FillNtupleDColumn(3, exact_y / mm);
        analysisManager->FillNtupleDColumn(4, dir.x());
        analysisManager->FillNtupleDColumn(5, dir.y());
        analysisManager->FillNtupleDColumn(6, dir.z());
        analysisManager->AddNtupleRow();
        
        // 5. Kill track to save CPU
        track->SetTrackStatus(fStopAndKill);
    }
}
