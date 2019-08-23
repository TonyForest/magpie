[Mesh]
 type = GEANT4Mesh
  dim = 3
  nx = 1
  ny = 1
  nz = 1
  xmin = -50000
  xmax = 50000
  ymin = -50000
  ymax = 50000
  zmin = -50000
  zmax = 50000
  elem_type = HEX8
  construct_node_list_from_side_list = true
[]

[Variables]
  [./c]
  [../]
[]

[UserObjects]
  [./PKA]
    type = GEANT4Conditions
    E = 1000
    Z = 60
    m = 120
    pka_rate = 1e-6
    Seed = 100
    mfp = 'false'
    ScreeningKey = 'zbl'
    GenerateRecoils = 1
    RecoilCutoff = 1
    PhysicsCutoff = 1
    Rho = 19.043
    AtomicNumbers = 92
    MassNumbers = 238
    DispE = 50
    LatticeE = 3
    SurfaceE = 5.42
    Fraction = 1
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
