/**********************************************************************/
/*                     DO NOT MODIFY THIS HEADER                      */
/* MAGPIE - Mesoscale Atomistic Glue Program for Integrated Execution */
/*                                                                    */
/*            Copyright 2017 Battelle Energy Alliance, LLC            */
/*                        ALL RIGHTS RESERVED                         */
/**********************************************************************/

#include "GEANT4Conditions.h"

registerMooseObject("MagpieApp", GEANT4Conditions);

template <>
InputParameters
validParams<GEANT4Conditions>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params += validParams<GEANT4Mesh>();

  params.addClassDescription("PKA inital conditions with constant mass, charge, energy, and rate");
  params.addParam<Real>(
      "pka_rate",
      1e-8,
      "PKA rate per unit volume (uses mesh units defined in the rasterizer and moose time units)");
  params.addRequiredParam<Real>("Z", "PKA nuclear charge");
  params.addRequiredParam<Real>("m", "PKA mass in amu");
  params.addRequiredParam<Real>("E", "PKA energy in eV");

  params.addParam<int>("Seed", 123, "Seed number");
  params.addParam<std::string>("mfp", "false", "MFP correction");
  params.addParam<std::string>("ScreeningKey", "zbl", "Screening Key used in scattering");
  params.addParam<int>("GenerateRecoils", 1, "Generate recoils for secondaries");
  params.addParam<std::string>("RecoilCutoff", "1 eV", "Energy to stop recoils");
  params.addParam<std::string>("PhysicsCutoff", "1 eV", "Energy to stop tracking");

  params.addRequiredParam<Real>("Rho", "Density of material in g/cm3");
  params.addRequiredParam<std::vector<unsigned int>>("AtomicNumbers", "Atomic numbers");
  params.addRequiredParam<std::vector<Real>>("MassNumbers", "Mass numbers");
  params.addRequiredParam<std::vector<Real>>("DispE", "Displacement energy in eV");
  params.addRequiredParam<std::vector<Real>>("LatticeE", "Lattice binding energy in eV");
  params.addRequiredParam<std::vector<Real>>("SurfaceE", "Surface binding energy in eV");
  params.addRequiredParam<std::vector<Real>>("Fraction", "Percentage of material");




  return params;
}

GEANT4Conditions::GEANT4Conditions(const InputParameters & parameters)
  : GeneralUserObject(parameters),
    GEANT4Mesh(parameters),
    _pka_rate(getParam<Real>("pka_rate")),
    _Z(getParam<Real>("Z")),
    _m(getParam<Real>("m")),
    _E(getParam<Real>("E")),
    _seed(getParam<int>("Seed")),
    _mfp(getParam<std::string>("mfp")),
    _ScreeningKey(getParam<std::string>("ScreeningKey")),
    _GenerateRecoils(getParam<int>("GenerateRecoils")),
    _RecoilCutoff(getParam<std::string>("RecoilCutoff")),
    _PhysicsCutoff(getParam<std::string>("PhysicsCutoff")),
    _rho(getParam<Real>("Rho")),
    _AtomicNumbers(getParam<std::vector<unsigned int>>("AtomicNumbers")),
    _MassNumbers(getParam<std::vector<Real>>("MassNumbers")),
    _dispE(getParam<std::vector<Real>>("DispE")),
    _latticeE(getParam<std::vector<Real>>("LatticeE")),
    _surfaceE(getParam<std::vector<Real>>("SurfaceE")),
    _fraction(getParam<std::vector<Real>>("Fraction"))


{
  std::cout << "initialize GEANT4Conditions" << std::endl;
  //const Real temp = _g4_mesh.getXmin();
  std::cout << "The minimum corner " << temp << std::endl;
  /// Create the json input file that GEANT4 will run on
  std::ofstream GEANT4jsonFile("GEANT4input.json");
  GEANT4jsonFile << "{\n";
  GEANT4jsonFile << " \"GEANT\"\n";
  GEANT4jsonFile << " {\n";
  GEANT4jsonFile << "    /// options\n";
  GEANT4jsonFile << "    \"options\" : { \"seed\" :";
  GEANT4jsonFile << _seed;
  GEANT4jsonFile << ", \"mfp\" :";
  GEANT4jsonFile <<  _mfp;
  GEANT4jsonFile << ", \"GenerateRecoils\" :";
  GEANT4jsonFile << _GenerateRecoils;
  GEANT4jsonFile << ", \"RecoilCutoff\" :";
  GEANT4jsonFile << _RecoilCutoff;
  GEANT4jsonFile << ", \"PhysicsCutoff\" :";
  GEANT4jsonFile << _PhysicsCutoff;
  GEANT4jsonFile << "},\n";
  GEANT4jsonFile << "    /// Incident Ions \n";
  GEANT4jsonFile << "    \"ion\" : {\"Z\": ";
  GEANT4jsonFile << _Z;
  GEANT4jsonFile << ", \"A(amu)\": ";
  GEANT4jsonFile << _m;
  GEANT4jsonFile << ", \"energy(eV)\": ";
  GEANT4jsonFile << _E;
  GEANT4jsonFile << ", \"number\": ";
  GEANT4jsonFile << "1";
  GEANT4jsonFile << " },\n";
  GEANT4jsonFile << "    \"ionInitPos\" : {\"x\": ";
  GEANT4jsonFile << "-40000";
  GEANT4jsonFile << ", \"y\": ";
  GEANT4jsonFile << "0";
  GEANT4jsonFile << ", \"z\": ";
  GEANT4jsonFile << "0";
  GEANT4jsonFile << "},";
  GEANT4jsonFile << "   \"ionInitMomVec\" : {\"px\": ";
  GEANT4jsonFile << "1";
  GEANT4jsonFile << ", \"py\": ";
  GEANT4jsonFile << "0";
  GEANT4jsonFile << ", \"pz\": ";
  GEANT4jsonFile << "0";
  GEANT4jsonFile << "},\n";
  GEANT4jsonFile << "    ///Target material\n";
  GEANT4jsonFile << "    \"sample\":\n";
  GEANT4jsonFile << "    [\n";
  GEANT4jsonFile << "       ///Node positions\n";



  for (unsigned int j=0; j< _AtomicNumbers.size(); j++)
  {

  }
}


void GEANT4Conditions::execute()
{

}
