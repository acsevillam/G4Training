/*
 * Testing v1.0
 *
 */

// Geant4 Headers
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

// NP1 Headers
#include "T1PrimaryGeneratorAction.hh"
#include "T1RunAction.hh"

class G4AccumulableManager;

using namespace std;

namespace T1
{

T1RunAction::T1RunAction(): G4UserRunAction(),
		fEDepEvents(0),
		fTotalEdep(0.),
		fTotalEdep2(0.)
{

	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	// Register accumulable to the accumulable manager
	accumulableManager->RegisterAccumulable(fEDepEvents);
	accumulableManager->RegisterAccumulable(fTotalEdep);
	accumulableManager->RegisterAccumulable(fTotalEdep2);

}

void T1RunAction::BeginOfRunAction(const G4Run*)
{

	// reset accumulables to their initial values
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Reset();

}

void T1RunAction::EndOfRunAction(const G4Run* run)
{

	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0) return;

	// Merge accumulables
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Merge();

	// Compute energy deposited event
	G4int eDepEvents = G4int(fEDepEvents.GetValue());

	// Total energy deposit in a run and its variance
	//
	G4double TotalEdep=0., TotalEdep2=0., rmsTotalEdep=0.;

	TotalEdep=fTotalEdep.GetValue();
	TotalEdep2=fTotalEdep2.GetValue();

	if(eDepEvents>0) rmsTotalEdep = TotalEdep2 - TotalEdep*TotalEdep/eDepEvents;
	if (rmsTotalEdep > 0.) rmsTotalEdep = std::sqrt(rmsTotalEdep);


	// Print
	//
	if (IsMaster()) {
		G4cout
		<< G4endl
		<< "--------------------End of Global Run-----------------------"
		<< G4endl;

		G4cout
		<< G4endl
		<< "(1)  Total events per run : "
		<< nofEvents
		<< G4endl;

		G4cout
		<< G4endl
		<< "(2)  Number of detected events per event: "
		<< G4double(eDepEvents)/G4double(nofEvents)
		<< G4endl
		<< "     [Total number of detected events / Total events per run (1)]"
		<< G4endl;
		G4cout
		<< G4endl
		<< "(3)  Cumulated total Edep per detected event in sensitive volume: "
		<< G4BestUnit(TotalEdep/eDepEvents,"Energy") << " rms = " << G4BestUnit(rmsTotalEdep/eDepEvents,"Energy")
		<< G4endl
		<< "     [Total Edep in sensitive volume / Total events per run (1)]"
		<< G4endl;


		G4cout
		<< G4endl
		<< "------------------------------------------------------------"
		<< G4endl;

	}

}

}
