/**********************************************************************/
/*                     DO NOT MODIFY THIS HEADER                      */
/* MAGPIE - Mesoscale Atomistic Glue Program for Integrated Execution */
/*                                                                    */
/*            Copyright 2017 Battelle Energy Alliance, LLC            */
/*                        ALL RIGHTS RESERVED                         */
/**********************************************************************/

#pragma once

#include <iostream>
#include "MooseTypes.h"

class GEANT4MeshInterface
{
public:
  GEANT4MeshInterface();
  virtual ~GEANT4MeshInterface(){};

  void PrintTest();

  inline void setXminBox(Real val) { _xMinBox = val; }
  inline void setYminBox(Real val) { _yMinBox = val; }
  inline void setZminBox(Real val) { _zMinBox = val; }
  inline void setXmaxBox(Real val) { _xMaxBox = val; }
  inline void setYmaxBox(Real val) { _yMaxBox = val; }
  inline void setZmaxBox(Real val) { _zMaxBox = val; }

  virtual Real getXmin() { return _xMinBox; };
protected:

  /// Mesh Info
  Real _xMinBox;
  Real _xMaxBox;
  Real _yMinBox;
  Real _yMaxBox;
  Real _zMinBox;
  Real _zMaxBox;


};
