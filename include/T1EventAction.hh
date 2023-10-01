/*
 * Testing v1.0
 *
 */

#ifndef T1EventAction_h
#define T1EventAction_h 1

// Geant4 Headers
#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4THitsMap.hh"

/// Event action class
///

namespace T1
{

class T1RunAction;

class T1EventAction : public G4UserEventAction
{
  public:
	T1EventAction(T1RunAction* runAction);
    ~T1EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddEdep(G4double edep) { fTotalEdep += edep; }

  private:
    T1RunAction*			fRunAction;
    G4double				fTotalEdep;
};

}

#endif

