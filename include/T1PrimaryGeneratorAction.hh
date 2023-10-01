/*
 * Testing v1.0
 *
 */

#ifndef T1PrimaryGeneratorAction_h
#define T1PrimaryGeneratorAction_h 1

// Geant4 Headers
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;

namespace T1
{

class T1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:

    T1PrimaryGeneratorAction();
    ~T1PrimaryGeneratorAction() override;

    // method from the base class
    void GeneratePrimaries(G4Event*) override;

	// method to access particle gun
	const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

private:
	G4ParticleGun*  fParticleGun; // pointer a to G4 gun class

};

}


#endif // T1PrimaryGeneratorAction_h
