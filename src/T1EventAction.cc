/*
 * Testing v1.0
 *
 */

// Geant4 Headers
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4Event.hh"

// Testing1 Headers
#include "T1EventAction.hh"
#include "T1RunAction.hh"


namespace T1
{

T1EventAction::T1EventAction(T1RunAction* runAction):
fRunAction(runAction),
fTotalEdep(0.)
{}

void T1EventAction::BeginOfEventAction(const G4Event* anEvent)
{

	G4int nEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed() ;
	if(nEvents>10){
		G4int 	fraction 	= G4int(nEvents/10) ;
		if(anEvent->GetEventID()%fraction == 0)
			G4cout<<"("<<(anEvent->GetEventID()/(nEvents*1.0)*100)<<" %)"<<G4endl ;

	}else {
		G4int 	fraction 	= G4int(nEvents/1) ;
		if(anEvent->GetEventID()%fraction == 0)
			G4cout<<"("<<(anEvent->GetEventID()/(nEvents*1.0)*100)<<" %)"<<G4endl ;
	}

	fTotalEdep=0.;

}

void T1EventAction::EndOfEventAction(const G4Event* /*anEvent*/)
{

	if(fTotalEdep==0.) return;

	fRunAction->AddTotalEdep(fTotalEdep);
	fRunAction->CountEdepEvent();

}

}
