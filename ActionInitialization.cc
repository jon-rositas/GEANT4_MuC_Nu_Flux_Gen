#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

// Used only by the Master thread in multi-threaded mode for global run management
void ActionInitialization::BuildForMaster() const {
    SetUserAction(new RunAction());
}

// Used by worker threads to assign actions to individual event/track loops
void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction());
    
    RunAction* runAction = new RunAction();
    SetUserAction(runAction);
    
    SetUserAction(new SteppingAction());
}