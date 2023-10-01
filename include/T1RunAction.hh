/*
 * Testing v1.0
 *
 */

#ifndef T1RunAction_h
#define T1RunAction_h 1

// Geant4 Headers
#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

// Testing1 Headers
#include "T1DetectorConstruction.hh"

/// Run action class
///

namespace T1
{

class T1RunAction : public G4UserRunAction
{

  public:
	T1RunAction();
    ~T1RunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    void CountEdepEvent(){ fEDepEvents+=1;};
    void AddTotalEdep(G4double Edep) {fTotalEdep+=Edep; fTotalEdep2+=Edep*Edep;}

private:
    G4Accumulable<G4int>    			fEDepEvents;
    G4Accumulable<G4double>     		fTotalEdep;
    G4Accumulable<G4double>	   			fTotalEdep2;

};

}

#endif // T1RunAction_h
