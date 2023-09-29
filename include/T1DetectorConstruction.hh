/*
 * Testing v1.0
 *
 */

#ifndef T1DetectorConstruction_h
#define T1DetectorConstruction_h 1

// Geant4 Headers
#include "G4VUserDetectorConstruction.hh"

/// Detector construction class to define materials and geometry.

class T1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    T1DetectorConstruction();
    virtual ~T1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    void SetupGeometry(G4LogicalVolume* motherVolume);

};

#endif // T1DetectorConstruction_h
