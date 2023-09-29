/*
 * Testing v1.0
 *
 */

// Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

// NP1 Headers
#include "T1DetectorConstruction.hh"

T1DetectorConstruction::T1DetectorConstruction()
: G4VUserDetectorConstruction()
{}

T1DetectorConstruction::~T1DetectorConstruction()
{}

G4VPhysicalVolume* T1DetectorConstruction::Construct()
{  

	// Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();

	// Define materials
	G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

	// General Attributes
	G4VisAttributes* simpleInvisibleSVisAtt;
	simpleInvisibleSVisAtt= new G4VisAttributes(G4Colour(0.,0.5,0.5,0.1));
	simpleInvisibleSVisAtt->SetVisibility(false);

	// Geometrical Volume =========================================================================================

	// World
	G4double world_size_X = (10/2.)*m;
	G4VSolid* world_geo = new G4Box("world_geo", world_size_X, world_size_X, world_size_X);

	//Logical Volume ==============================================================================================

	// World
	G4LogicalVolume* world_log = new G4LogicalVolume(world_geo,vacuum,"world_log");
	world_log -> SetVisAttributes(simpleInvisibleSVisAtt);

	//Physics Volume  =============================================================================================

	G4VPhysicalVolume* world_phys =
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(),       			//at (0,0,0)
					world_log,      					//its logical volume
					"world_phys",   					//its name
					0,                     			//its mother  volume
					false,                 			//no boolean operation
					0,                     			//copy number
					0);      			    			//overlaps checking

	SetupGeometry(world_log);

	//always return the physical World
	//
	return world_phys;

}

void T1DetectorConstruction::SetupGeometry(G4LogicalVolume* motherVolume){

	// Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();

	// Define materials
	G4Material* Pb = nist->FindOrBuildMaterial("G4_Pb");

	// Geometrical Volume =========================================================================================

	// Layer
	G4double layer_dx = (1./2.)*cm, layer_dy=(50./2.)*cm, layer_dz=layer_dy;
	G4VSolid* layer_geo = new G4Box("layer_geo", layer_dx, layer_dy, layer_dz);

	//Logical Volume ==============================================================================================

	// Layer
	G4LogicalVolume* layer_log = new G4LogicalVolume(layer_geo,Pb,"layer_log");

	G4VisAttributes* simpleLayerVisAtt;
	simpleLayerVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,0.0,1.0));
	simpleLayerVisAtt->SetVisibility(true);

	layer_log -> SetVisAttributes(simpleLayerVisAtt);

	//Physics Volume  =============================================================================================

	// Layer
	new G4PVPlacement(0,                     		//no rotation
			G4ThreeVector(),       					//at (0,0,0)
			layer_log,     							//its logical volume
			"layer_phys", 	 						//its name
			motherVolume, 							//its mother  volume
			false,                 					//no boolean operation
			0,                     					//copy number
			true);      			     				//overlaps checking

}


