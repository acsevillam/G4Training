/*
 * Testing v1.0
 *
 */

// Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

// T1 Headers
#include "T1PrimaryGeneratorAction.hh"


namespace T1
{

T1PrimaryGeneratorAction::T1PrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(),
fParticleGun(0)
{
	G4int n_particle = 1;
	fParticleGun  = new G4ParticleGun(n_particle);

	// default particle kinematic
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition* particle
	// => Step PDD-1A
	= particleTable->FindParticle(particleName="gamma");
	//= particleTable->FindParticle(particleName="proton");
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	// => Step PDD-1B | HVL-1A
	fParticleGun->SetParticleEnergy(1.*MeV);
	//fParticleGun->SetParticleEnergy(200.*MeV);
	//fParticleGun->SetParticleEnergy(662.*keV);
}

T1PrimaryGeneratorAction::~T1PrimaryGeneratorAction()
{
	delete fParticleGun;
}

void T1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

	G4double x0 = -100*cm , y0=0*cm, z0=0*cm;

	fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

}
