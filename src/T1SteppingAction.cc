/*
 * Testing v1.0
 *
 */

// Geant4 Headers
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackingManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Step.hh"
#include "G4Event.hh"

// Testing1 Headers
#include "T1EventAction.hh"
#include "T1SteppingAction.hh"
#include "T1DetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

using namespace std;

namespace T1
{

T1SteppingAction::T1SteppingAction(T1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolumeVector(0)
{}

void T1SteppingAction::UserSteppingAction(const G4Step* aStep)
{

	if (fScoringVolumeVector.empty()) {
		const auto detectorConstruction
		= static_cast<const T1DetectorConstruction*>
		(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
		fScoringVolumeVector = detectorConstruction->GetScoringVolumeVector();
	}

	// get volume of the current step
	G4LogicalVolume* currentVolume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

	G4bool IsScoringVolume = false;

	// check if we are in scoring volume
	for (unsigned i=0; i < fScoringVolumeVector.size(); i++) {
		if (currentVolume == fScoringVolumeVector[i]) IsScoringVolume = true;
	}

	if(!IsScoringVolume) return;

	// collect energy deposited in this step
	G4double TotalEnergyDeposit = aStep->GetTotalEnergyDeposit();

	if(TotalEnergyDeposit==0.) return;

	fEventAction->AddEdep(TotalEnergyDeposit);
}

}
