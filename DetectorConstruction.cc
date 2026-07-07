#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // 1. Define Materials
    // We use "G4_Galactic" to represent the ultra-high vacuum of the accelerator beam pipe
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

    // 2. Define World Geometry
    // A cylinder centered at (0,0,0) with a total length of 500 meters (z spans -250m to +250m)
    // This safely encloses our -200m injection point and the 0m scoring plane.
    G4double innerRadius = 0.0 * cm;
    G4double outerRadius = 1.0 * m;
    G4double halfLength  = 250.0 * m;
    G4double startAngle  = 0.0 * deg;
    G4double spanningAngle = 360.0 * deg;

    G4Tubs* solidWorld = new G4Tubs("World_Solid", 
                                    innerRadius, outerRadius, halfLength, 
                                    startAngle, spanningAngle);

    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World_Logic");

    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr,         // No rotation
                                                     G4ThreeVector(), // Centered at (0,0,0)
                                                     logicWorld,      // Its logical volume
                                                     "World_Phys",    // Its name
                                                     nullptr,         // No mother volume
                                                     false,           // No boolean operations
                                                     0,               // Copy number
                                                     true);           // Check for overlaps

    return physWorld;
}
