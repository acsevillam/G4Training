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
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit3D.hh"
#include "G4PSNofStep3D.hh"
#include "G4PSCellFlux3D.hh"
#include "G4PSPassageCellFlux3D.hh"
#include "G4PSFlatSurfaceFlux3D.hh"
#include "G4PSFlatSurfaceCurrent3D.hh"
#include "G4PSPassageCellCurrent3D.hh"
#include "G4SDParticleWithEnergyFilter.hh"
#include "G4SDParticleFilter.hh"
#include "G4SDChargedFilter.hh"

// NP1 Headers
#include "T1DetectorConstruction.hh"

namespace T1
{

G4VPhysicalVolume* T1DetectorConstruction::Construct()
{  

	// Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();

	// Define materials
	// => Step HVL-2A
	G4Material* Vacuum = nist->FindOrBuildMaterial("G4_Galactic");
	//G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");


	// Option to switch on/off checking of volumes overlaps
	//
	G4bool checkOverlaps = true;

	// Geometrical Volume =========================================================================================

	// World
	G4double world_size_X = (10/2.)*m;
	auto world_geo = new G4Box("world_geo", world_size_X, world_size_X, world_size_X);

	//Logical Volume ==============================================================================================

	// World
	// => Step HVL-2B
	auto world_log = new G4LogicalVolume(world_geo,Vacuum,"world_log");
	//auto world_log = new G4LogicalVolume(world_geo,Air,"world_log");

	// General Attributes
	G4VisAttributes* simpleInvisibleSVisAtt;
	simpleInvisibleSVisAtt= new G4VisAttributes(G4Colour(0.,0.5,0.5,0.1));
	simpleInvisibleSVisAtt->SetVisibility(false);
	world_log -> SetVisAttributes(simpleInvisibleSVisAtt);

	//Physics Volume  =============================================================================================

	auto world_phys =
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
	// => Step HVL-4A
	//G4Material* Pb = nist->FindOrBuildMaterial("G4_Pb");
	// => Step HVL-3A
	G4Material* Water = nist->FindOrBuildMaterial("G4_WATER");
	//G4Material* NaI = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

	// Geometrical Volume =========================================================================================

	// Lead Layer
	// => Step HVL-4B
	/*
	G4double leadLayer_dx = (10./2.)*mm, leadLayer_dy=(50./2.)*cm, leadLayer_dz=leadLayer_dy;
	auto leadLayer_geo = new G4Box("leadLayer_geo", leadLayer_dx, leadLayer_dy, leadLayer_dz);
	*/

	// Sensitive Layer
	// => Step PDD-2A
	G4double sdCube_dx = (2./2.)*cm, sdCube_dy=sdCube_dx, sdCube_dz=sdCube_dx;
	//G4double sdCube_dx = (50./2.)*cm, sdCube_dy=sdCube_dx, sdCube_dz=sdCube_dx;
	auto sdCube_geo = new G4Box("sdCube_geo", sdCube_dx, sdCube_dx, sdCube_dx);

	//Logical Volume ==============================================================================================

	// Lead Layer
	// => Step HVL-4C
	/*
	auto leadLayer_log = new G4LogicalVolume(leadLayer_geo,Pb,"leadLayer_log");

	G4VisAttributes* leadLayerVisAtt;
	leadLayerVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,0.0,1.0));
	leadLayerVisAtt->SetVisibility(true);

	leadLayer_log -> SetVisAttributes(leadLayerVisAtt);
	*/

	// Sensitive Layer
	// => Step HVL-3B
	auto sdCube_log = new G4LogicalVolume(sdCube_geo,Water,"sdCube_log");
	//auto sdCube_log = new G4LogicalVolume(sdCube_geo,NaI,"sdCube_log");

	G4VisAttributes* sdCubeVisAtt;
	sdCubeVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0,0.5));
	sdCubeVisAtt->SetVisibility(true);

	sdCube_log -> SetVisAttributes(sdCubeVisAtt);

	// => Step HVL-5E
	//fScoringVolumeVector.push_back(sdCube_log);

	//Physics Volume  =============================================================================================

	// Lead Layer
	// => Step HVL-4D
	/*
	new G4PVPlacement(0,                     		//no rotation
			G4ThreeVector(0,0,0),           		//at (0,0,0)
			leadLayer_log,     						//its logical volume
			"leadLayer_phys", 	 					//its name
			motherVolume, 							//its mother  volume
			false,                 					//no boolean operation
			0,                     					//copy number
			true);      			     			//overlaps checking
	*/

	// Lead Layer
	new G4PVPlacement(0,                     		//no rotation
			// => Step HVL-4E
			G4ThreeVector(0,0,0),   		   		//at (0,0,0)
			//G4ThreeVector(100*cm,0,0),   	  	    //at (100,0,0) cm
			sdCube_log,     						//its logical volume
			"sdCube_phys", 	 						//its name
			motherVolume, 							//its mother  volume
			false,                 					//no boolean operation
			0,                     					//copy number
			true);      			     			//overlaps checking

}

}


