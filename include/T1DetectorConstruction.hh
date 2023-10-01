/*
 * Testing v1.0
 *
 */

#ifndef T1DetectorConstruction_h
#define T1DetectorConstruction_h 1

// Geant4 Headers
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

using namespace std;

class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

namespace T1
{

class T1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    T1DetectorConstruction() = default;
    ~T1DetectorConstruction() override = default;

    G4VPhysicalVolume* Construct() override;

    vector<G4LogicalVolume*> GetScoringVolumeVector() const { return fScoringVolumeVector; }

  private:

    void SetupGeometry(G4LogicalVolume* motherVolume);
    // Scoring volume
    vector<G4LogicalVolume*>  		fScoringVolumeVector;

};

}

#endif // T1DetectorConstruction_h
