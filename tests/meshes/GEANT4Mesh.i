[Mesh]
 type = GEANT4Mesh
  dim = 3
  nx = 2
  ny = 1
  nz = 1
  xmin = 0
  xmax = 2
  ymin = 0
  ymax = 1
  zmin = 0
  zmax = 1
  elem_type = HEX8
  construct_node_list_from_side_list = true
[]
[Variables]
  [./c]
    [./InitialCondition]
      type = FunctionIC
      function = 0.3*((x/1000)+(y/1000)^2+(z/1000)^3)+0.1
    [../]
  [../]
[]
[Problem]
  solve = false
  kernel_coverage_check = false
[]

[Executioner]
  type = Transient
  num_steps = 1
[]
[Outputs]
  exodus = true
[]
