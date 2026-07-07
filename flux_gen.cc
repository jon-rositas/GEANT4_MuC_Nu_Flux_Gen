#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "FTFP_BERT.hh"

int main(int argc, char** argv) {
    // 1. Detect interactive mode (if no macro is provided)
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // 2. Construct the Run Manager
    // G4RunManagerType::Default automatically enables multithreading if available
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // 3. Set Mandatory Initialization Classes
    // Geometry
    runManager->SetUserInitialization(new DetectorConstruction());

    // Physics List (FTFP_BERT includes G4Decay for muons)
    G4VModularPhysicsList* physicsList = new FTFP_BERT;
    runManager->SetUserInitialization(physicsList);

    // Action Initialization (Generators, Stepping, Run actions)
    runManager->SetUserInitialization(new ActionInitialization());

    // 4. Initialize Visualization
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // 5. Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // 6. Process macro or start UI session
    if (!ui) {
        // Batch mode: execute the macro file provided as an argument
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // Interactive mode: start UI session
        ui->SessionStart();
        delete ui;
    }

    // 7. Job Termination
    delete visManager;
    delete runManager;
    
    return 0;
}
