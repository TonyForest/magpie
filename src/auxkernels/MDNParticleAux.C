/**********************************************************************/
/*                     DO NOT MODIFY THIS HEADER                      */
/* MAGPIE - Mesoscale Atomistic Glue Program for Integrated Execution */
/*                                                                    */
/*            Copyright 2017 Battelle Energy Alliance, LLC            */
/*                        ALL RIGHTS RESERVED                         */
/**********************************************************************/

#include "MDNParticleAux.h"
#include "MDRunBase.h"

registerMooseObject("MagpieApp", MDNParticleAux);

template <>
InputParameters
validParams<MDNParticleAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<UserObjectName>("user_object", "Name of MD runner UserObject");
  params.addClassDescription("Injects the number of MD particles from MDRunBase object user_object "
                             "into auxiliary variable.");
  return params;
}

MDNParticleAux::MDNParticleAux(const InputParameters & parameters)
  : AuxKernel(parameters), _md_uo(getUserObject<MDRunBase>("user_object"))
{
}

Real
MDNParticleAux::computeValue()
{
  return _md_uo.elemParticles(_current_elem->unique_id()).size();
}
