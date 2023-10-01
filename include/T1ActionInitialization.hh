/*
 * Testing 1.0
 *
 */

#ifndef T1ActionInitialization_h
#define T1ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

namespace T1
{

class T1ActionInitialization : public G4VUserActionInitialization
{
  public:
    T1ActionInitialization() = default;
    ~T1ActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;
};

#endif //T1ActionInitialization_h

}
