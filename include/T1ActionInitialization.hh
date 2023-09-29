/*
 * Testing 1.0
 *
 */

#ifndef T1ActionInitialization_h
#define T1ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class T1ActionInitialization : public G4VUserActionInitialization
{
  public:
    T1ActionInitialization();
    virtual ~T1ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif //T1ActionInitialization_h

    
