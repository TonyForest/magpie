/**********************************************************************/
/*                     DO NOT MODIFY THIS HEADER                      */
/* MAGPIE - Mesoscale Atomistic Glue Program for Integrated Execution */
/*                                                                    */
/*            Copyright 2017 Battelle Energy Alliance, LLC            */
/*                        ALL RIGHTS RESERVED                         */
/**********************************************************************/

#pragma once

#include "GeneralUserObject.h"
#include "GEANT4Mesh.h"
#include "GEANT4MeshInterface.h"

class GEANT4Conditions;
class GEANT4MeshInterface;

template <>
InputParameters validParams<GEANT4Conditions>();

/**
 * PKAs with constant mass, charge, energy, and rate
 */
class GEANT4Conditions : public GeneralUserObject
{
public:
  GEANT4Conditions(const InputParameters & parameters);

  void execute() override;
  void initialize() override {}
  void finalize() override {}




protected:
  /// PKA Info
  virtual Real getPKARate() const { return _pka_rate; };
  virtual unsigned int getZ() const { return _Z; };
  virtual Real getM() const { return _m; };
  virtual Real getE() const { return _E; };
  Real _pka_rate;     /// Fission rate (per unit volume)
  unsigned int _Z;    /// PKA nuclear charge
  Real _m;            /// PKA mass
  Real _E;            /// PKA Energy (in eV)

  /// GEANT4 Options
  virtual int getSeed() const { return _seed; };
  virtual std::string getMFP() const { return _mfp; };
  virtual std::string getScreeningKey() const { return _ScreeningKey; };
  virtual int getGenerateRecoils() const { return _GenerateRecoils; };
  virtual std::string getRecoilCutoff() const { return _RecoilCutoff; };
  virtual std::string getPhysicsCutoff() const { return _PhysicsCutoff; };
  int _seed;              /// Seed number
  std::string _mfp;              /// MFP correction
  std::string _ScreeningKey;   /// ScreeningKey
  int _GenerateRecoils;   /// Generate Recoils
  std::string _RecoilCutoff;     /// Recoil cutoff
  std::string _PhysicsCutoff;    /// Physics cutoff


  /// Material Info
  virtual Real getRho() const { return _rho; };

  Real _rho;              /// material density (g/cm3)
  std::vector<unsigned int> _AtomicNumbers;
  std::vector<Real> _MassNumbers;
  std::vector<Real> _dispE;
  std::vector<Real> _latticeE;
  std::vector<Real> _surfaceE;
  std::vector<Real> _fraction;

  GEANT4MeshInterface * g4Mesh;

};
