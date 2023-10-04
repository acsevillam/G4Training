/*
 * Testing 1.0
 *
 */

//Testing1 Headers
#include "T1ActionInitialization.hh"
#include "T1PrimaryGeneratorAction.hh"
#include "T1RunAction.hh"
#include "T1EventAction.hh"
#include "T1SteppingAction.hh"

namespace T1
{

void T1ActionInitialization::BuildForMaster() const
{
	// => Step HVL-5A
	//auto runAction = new T1RunAction;
	//SetUserAction(runAction);
}

void T1ActionInitialization::Build() const
{
  SetUserAction(new T1PrimaryGeneratorAction);

  // => Step HVL-5B
  //auto runAction = new T1RunAction;
  //SetUserAction(runAction);

  // => Step HVL-5C
  //auto eventAction = new T1EventAction(runAction);
  //SetUserAction(eventAction);

  // => Step HVL-5D
  //SetUserAction(new T1SteppingAction(eventAction));

}  

}
