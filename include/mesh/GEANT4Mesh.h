/**********************************************************************/
/*                     DO NOT MODIFY THIS HEADER                      */
/* MAGPIE - Mesoscale Atomistic Glue Program for Integrated Execution */
/*                                                                    */
/*            Copyright 2017 Battelle Energy Alliance, LLC            */
/*                        ALL RIGHTS RESERVED                         */
/**********************************************************************/

#pragma once

#include "GeneratedMesh.h"
#include "PointLocatorRegularOrthogonal.h"
#include "GEANT4MeshInterface.h"

class GEANT4Mesh;

template <>
InputParameters validParams<GEANT4Mesh>();

/**
 * Restricted regular orthogonal generated mesh with equal size level 0 elements
 * (no bias) and EDGE2, QUAD4, or HEX8 elements only. These restrictions allow
 * the use of a custom super fast point locator to find elements based on spatial
 * locations (required for fast material property lookup in the Binary Collision
 * Monte Carlo stage). This mesh is also recommended for use with the FourierTransform
 * user object.
 */
class GEANT4Mesh : public GeneratedMesh, public GEANT4MeshInterface
{
public:
  GEANT4Mesh(const InputParameters & parameters);
  GEANT4Mesh(const GEANT4Mesh & other_mesh);

  // No copy assignment
  MooseMesh & operator=(const MooseMesh & other_mesh) = delete;
  virtual std::unique_ptr<MooseMesh> safeClone() const override;

  /// obtain a specialized PointLocator for the current mesh
  std::unique_ptr<PointLocatorBase> getPointLocator() const override;

  /// since this is a regular mesh we can report the grid size in each dimension
  unsigned int getCellCountInDimension(unsigned int component);




protected:



  std::vector<unsigned int> _cell_count;
  Point _min_corner;
  Point _max_corner;

  mutable std::unique_ptr<PointLocatorRegularOrthogonal> _point_locator;




};
