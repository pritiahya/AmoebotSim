/* Copyright (C) 2020 Joshua J. Daymude, Robert Gmyr, and Kristian Hinnenthal.
 * The full GNU GPLv3 can be found in the LICENSE file, and the full copyright
 * notice can be found at the top of main/main.cpp. */

// TODO: header comment.

#ifndef ALG_STATICENERGY_H_
#define ALG_STATICENERGY_H_

#include <vector>

#include "core/amoebotparticle.h"
#include "core/amoebotsystem.h"

class StaticEnergyParticle : public AmoebotParticle {
 public:
  enum class State {
    Root,
    Idle,
    Active
  };

  // TODO: comment.
  StaticEnergyParticle(const Node& head, int globalTailDir,
                       const int orientation, AmoebotSystem& system,
                       const double harvestRate, const double capacity,
                       const double threshold, const double sourceEnergy,
                       const bool isDynamic, const State state);

  // Executes one particle activation.
  void activate() override;

  // Functions for altering a particle's cosmetic appearance; headMarkColor
  // (respectively, tailMarkColor) returns the color to be used for the ring
  // drawn around the head (respectively, tail) node. Tail color is not shown
  // when the particle is contracted. headMarkDir returns the label of the port
  // on which the black head marker is drawn.
  int headMarkColor() const override;
  int headMarkDir() const override;
  int tailMarkColor() const override;

  // Returns the string to be displayed when this particle is inspected; used
  // to snapshot the current values of this particle's memory at runtime.
  QString inspectionText() const override;

  // Gets a reference to the neighboring particle incident to the specified port
  // label. Crashes if no such particle exists at this label; consider using
  // hasNbrAtLabel() first if unsure.
  StaticEnergyParticle& nbrAtLabel(int label) const;

  // Phase functions. TODO: comment.
  void communicate();
  void harvestEnergy();
  void useEnergy();

  // TODO: comment. Visualization helper functions
  int energyColor(int color1, int color2) const;

 protected:
  // Algorithm parameters.
  const double _harvestRate;
  const double _capacity;
  const double _threshold;
  const double _sourceEnergy;
  const bool _isDynamic;

  // Local variables.
  double _battery;
  double _buffer;
  bool _stress;
  bool _inhibit;

  // Spanning tree variables.
  State _state;
  int _parentDir;

 private:
  friend class StaticEnergySystem;
};

class StaticEnergySystem : public AmoebotSystem {
 public:
  StaticEnergySystem(int numParticles, const bool isDynamic,
                     const double harvestRate, const double capacity,
                     const double threshold, const double sourceEnergy);
};


#endif  // ALG_STATICENERGY_H_

