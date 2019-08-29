/**********************************************************************/
/*                     DO NOT MODIFY THIS HEADER                      */
/* MAGPIE - Mesoscale Atomistic Glue Program for Integrated Execution */
/*                                                                    */
/*            Copyright 2017 Battelle Energy Alliance, LLC            */
/*                        ALL RIGHTS RESERVED                         */
/**********************************************************************/

#include "GEANT4MeshInterface.h"

GEANT4MeshInterface::GEANT4MeshInterface()
{
  std::cout << "Initialize interface" << std::endl;

};

void GEANT4MeshInterface::PrintTest()
{
  std::cout << "Made it here" << std::endl;
  std::cout << "xmin=" << _xMinBox << std::endl;
}
