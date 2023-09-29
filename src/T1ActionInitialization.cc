/*
 * Testing 1.0
 *
 */

#include "T1ActionInitialization.hh"
#include "T1PrimaryGeneratorAction.hh"

T1ActionInitialization::T1ActionInitialization()
 : G4VUserActionInitialization()
{}

T1ActionInitialization::~T1ActionInitialization()
{}

void T1ActionInitialization::BuildForMaster() const
{}

void T1ActionInitialization::Build() const
{
  SetUserAction(new T1PrimaryGeneratorAction);

}  
