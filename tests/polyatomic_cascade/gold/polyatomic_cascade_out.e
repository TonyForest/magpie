CDF      
      
len_string     !   len_line   Q   four      	time_step          len_name   !   num_dim       	num_nodes         num_elem      
num_el_blk        num_node_sets         num_side_sets         num_el_in_blk1        num_nod_per_el1       num_side_ss1      num_side_ss2      num_side_ss3      num_side_ss4      num_side_ss5      num_side_ss6      num_nod_ns1    	   num_nod_ns2    	   num_nod_ns3    	   num_nod_ns4    	   num_nod_ns5    	   num_nod_ns6    	   num_nod_var       num_elem_var      num_glo_var       num_info  A         api_version       @�
=   version       @�
=   floating_point_word_size            	file_size               int64_status             title         polyatomic_cascade_out.e       maximum_name_length                 -   
time_whole                            zp   	eb_status                             �   eb_prop1               name      ID              �   	ns_status         	                        ns_prop1      	         name      ID                 	ss_status         
                    0   ss_prop1      
         name      ID              H   coordx                      �      `   coordy                      �      8   coordz                      �         eb_names                       $      �   ns_names      	                 �         ss_names      
                 �      �   
coor_names                         d      �   node_num_map                    l          connect1                  	elem_type         HEX8                l   elem_num_map                           l   elem_ss1                          �   side_ss1                          �   elem_ss2                          �   side_ss2                          �   elem_ss3                          �   side_ss3                          �   elem_ss4                          �   side_ss4                          �   elem_ss5                             side_ss5                             elem_ss6                          ,   side_ss6                          <   node_ns1                    $      L   node_ns2                    $      p   node_ns3                    $      �   node_ns4                    $      �   node_ns5                    $      �   node_ns6                    $          vals_nod_var1                          �      zx   name_nod_var                       $      $   name_elem_var                          d      H   vals_elem_var1eb1                          @      {P   vals_elem_var2eb1                          @      {�   vals_elem_var3eb1                          @      {�   elem_var_tab                             �   name_glo_var                       $      �   vals_glo_var                             |   info_records                      e�      �                                                                                         @I      @I                      @I      @I              @Y      @Y      @Y      @Y      @I              @I              @Y      @Y              @I      @I              @Y      @Y      @I              @Y                      @I      @I                      @I      @I              @I              @I      @Y      @Y      @Y      @Y      @Y      @Y                      @I      @I              @I      @Y      @Y      @Y                                      @I      @I      @I      @I                      @I      @I                      @I      @I              @I      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y      @Y                                          back                             bottom                           left                             right                            top                              front                              back                             bottom                           left                             right                            top                              front                                                                                                                                                             	   
                                                                                 	   
                                             
                                                                                                                                                                                                                                                                                                   	         
                  	                                                	   
                                                                           dummy                               cC                               cSi                              vac                                        total_vacancies                     ####################                                                             # Created by MOOSE #                                                       ?�    ####################      ?�      ?�      ?�      ?�      ?�      ?�      ?�     ### Command Line Arguments ###   ?�                                              -i                                                                               polyatomic_cascade.i                                                             UserObjects/rasterizer/Ebind=3.0  3.3                                            UserObjects/rasterizer/Edisp=16.3 92.6                                           --no-gdb-backtrace                                                                                                                                                ### Version Info ###                                                             Framework Information:                                                           MOOSE version:           git commit 96013fe0b on 2017-04-27                      PETSc Version:           3.6.4                                                   Current Time:            Fri May  5 10:25:42 2017                                Executable Timestamp:    Fri May  5 10:19:34 2017                                                                                                                                                                                                  ### Input File ###                                                                                                                                                []                                                                                 element_order                  = AUTO                                            order                          = AUTO                                            side_order                     = AUTO                                            type                           = GAUSS                                         []                                                                                                                                                                [AuxKernels]                                                                                                                                                        [./vac]                                                                            type                         = MyTRIMElementResultAux                            block                        = INVALID                                           boundary                     = INVALID                                           control_tags                 = AuxKernels                                        defect                       = VAC                                               enable                       = 1                                                 execute_on                   = LINEAR                                            ivar                         = 0                                                 runner                       = runner                                            seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = vac                                             [../]                                                                          []                                                                                                                                                                [AuxVariables]                                                                                                                                                      [./cC]                                                                             block                        = INVALID                                           family                       = MONOMIAL                                          initial_condition            = 0.5                                               order                        = CONSTANT                                          outputs                      = INVALID                                           initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                                                                                                             [./cSi]                                                                            block                        = INVALID                                           family                       = MONOMIAL                                          initial_condition            = 0.5                                               order                        = CONSTANT                                          outputs                      = INVALID                                           initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                                                                                                             [./vac]                                                                            block                        = INVALID                                           family                       = MONOMIAL                                          initial_condition            = INVALID                                           order                        = CONSTANT                                          outputs                      = INVALID                                           initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                          []                                                                                                                                                                [BCs]                                                                                                                                                               [./Periodic]                                                                                                                                                        [./all]                                                                            auto_direction             = 'x y z'                                             inv_transform_func         = INVALID                                             primary                    = INVALID                                             secondary                  = INVALID                                             transform_func             = INVALID                                             translation                = INVALID                                             variable                   = INVALID                                           [../]                                                                          [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      type                           = Transient                                       abort_on_solve_fail            = 0                                               compute_initial_residual_before_preset_bcs = 0                                   control_tags                   =                                                 dt                             = 1                                               dtmax                          = 1e+30                                           dtmin                          = 2e-14                                           enable                         = 1                                               end_time                       = 1e+30                                           l_abs_step_tol                 = -1                                              l_max_its                      = 10000                                           l_tol                          = 1e-05                                           line_search                    = default                                         max_xfem_update                = 4294967295                                      n_startup_steps                = 0                                               nl_abs_step_tol                = 1e-50                                           nl_abs_tol                     = 1e-10                                           nl_max_funcs                   = 10000                                           nl_max_its                     = 50                                              nl_rel_step_tol                = 1e-50                                           nl_rel_tol                     = 1e-08                                           no_fe_reinit                   = 0                                               num_steps                      = 1                                               petsc_options                  = INVALID                                         petsc_options_iname            = INVALID                                         petsc_options_value            = INVALID                                         picard_abs_tol                 = 1e-50                                           picard_max_its                 = 1                                               picard_rel_tol                 = 1e-08                                           reset_dt                       = 0                                               restart_file_base              =                                                 scheme                         = INVALID                                         solve_type                     = INVALID                                         splitting                      = INVALID                                         ss_check_tol                   = 1e-08                                           ss_tmin                        = 0                                               start_time                     = 0                                               time_period_ends               = INVALID                                         time_period_starts             = INVALID                                         time_periods                   = INVALID                                         timestep_tolerance             = 2e-14                                           trans_ss_check                 = 0                                               use_multiapp_dt                = 0                                               verbose                        = 0                                             []                                                                                                                                                                [Executioner]                                                                      _fe_problem                    = 0x7fab8e000000                                  _fe_problem_base               = 0x7fab8e000000                                []                                                                                                                                                                [Mesh]                                                                             displacements                  = INVALID                                         block_id                       = INVALID                                         block_name                     = INVALID                                         boundary_id                    = INVALID                                         boundary_name                  = INVALID                                         construct_side_list_from_node_list = 0                                           ghosted_boundaries             = INVALID                                         ghosted_boundaries_inflation   = INVALID                                         patch_size                     = 40                                              second_order                   = 0                                               skip_partitioning              = 0                                               type                           = MyTRIMMesh                                      uniform_refine                 = 0                                               allow_renumbering              = 1                                               centroid_partitioner_direction = INVALID                                         construct_node_list_from_side_list = 1                                           control_tags                   =                                                 dim                            = 3                                               distribution                   = DEFAULT                                         elem_type                      = HEX8                                            enable                         = 1                                               gauss_lobatto_grid             = 0                                               ghost_point_neighbors          = 0                                               nemesis                        = 0                                               num_ghosted_layers             = 1                                               nx                             = 2                                               ny                             = 2                                               nz                             = 2                                               parallel_type                  = DEFAULT                                         partitioner                    = default                                         patch_update_strategy          = never                                           xmax                           = 100                                             xmin                           = 0                                               ymax                           = 100                                             ymin                           = 0                                               zmax                           = 100                                             zmin                           = 0                                             []                                                                                                                                                                [Mesh]                                                                           []                                                                                                                                                                [Outputs]                                                                          append_date                    = 0                                               append_date_format             = INVALID                                         checkpoint                     = 0                                               color                          = 1                                               console                        = 1                                               controls                       = 0                                               csv                            = 0                                               dofmap                         = 0                                               execute_on                     = 'INITIAL TIMESTEP_END'                          exodus                         = 1                                               file_base                      = INVALID                                         gmv                            = 0                                               gnuplot                        = 0                                               hide                           = INVALID                                         interval                       = 1                                               nemesis                        = 0                                               output_if_base_contains        = INVALID                                         print_linear_residuals         = 1                                               print_mesh_changed_info        = 0                                               print_perf_log                 = 0                                               show                           = INVALID                                         solution_history               = 0                                               sync_times                     =                                                 tecplot                        = 0                                               vtk                            = 0                                               xda                            = 0                                               xdr                            = 0                                             []                                                                                                                                                                [Postprocessors]                                                                                                                                                    [./total_vacancies]                                                                type                         = ElementIntegralVariablePostprocessor              block                        = INVALID                                           control_tags                 = Postprocessors                                    enable                       = 1                                                 execute_on                   = TIMESTEP_END                                      outputs                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = vac                                             [../]                                                                          []                                                                                                                                                                [Problem]                                                                          block                          = INVALID                                         coord_type                     = XYZ                                             fe_cache                       = 0                                               kernel_coverage_check          = 0                                               material_coverage_check        = 1                                               name                           = 'MOOSE Problem'                                 restart_file_base              = INVALID                                         rz_coord_axis                  = Y                                               type                           = FEProblem                                       library_path                   =                                                 object_names                   = INVALID                                         register_objects_from          = INVALID                                         control_tags                   =                                                 enable                         = 1                                               error_on_jacobian_nonzero_reallocation = 0                                       force_restart                  = 0                                               near_null_space_dimension      = 0                                               null_space_dimension           = 0                                               petsc_inames                   =                                                 petsc_options                  = INVALID                                         petsc_values                   =                                                 solve                          = 1                                               transpose_null_space_dimension = 0                                               use_nonlinear                  = 1                                             []                                                                                                                                                                [UserObjects]                                                                                                                                                       [./constant]                                                                       type                         = PKAConstant                                       E                            = 1000                                              Z                            = 14                                                block                        = INVALID                                           control_tags                 = UserObjects                                       enable                       = 1                                                 m                            = 28                                                pka_rate                     = 0.001                                             seed                         = 0                                                 use_displaced_mesh           = 0                                               [../]                                                                                                                                                             [./rasterizer]                                                                     type                         = MyTRIMRasterizer                                  Ebind                        = '3 3.3'                                           Edisp                        = '16.3 92.6'                                       M                            = '12 28'                                           Z                            = '6 14'                                            analytical_energy_cutoff     = 0                                                 block                        = INVALID                                           control_tags                 = UserObjects                                       enable                       = 1                                                 execute_on                   = TIMESTEP_BEGIN                                    interval                     = 1                                                 length_unit                  = ANGSTROM                                          periodic_var                 = dummy                                             pka_generator                = constant                                          seed                         = 0                                                 site_volume                  = 0.0404                                            trim_module                  = CORE                                              use_displaced_mesh           = 0                                                 var                          = 'cC cSi'                                        [../]                                                                                                                                                             [./runner]                                                                         type                         = MyTRIMElementRun                                  control_tags                 = UserObjects                                       enable                       = 1                                                 rasterizer                   = rasterizer                                        use_displaced_mesh           = 0                                               [../]                                                                          []                                                                                                                                                                [Variables]                                                                                                                                                         [./dummy]                                                                          block                        = INVALID                                           eigen                        = 0                                                 family                       = LAGRANGE                                          initial_condition            = INVALID                                           order                        = FIRST                                             outputs                      = INVALID                                           scaling                      = 1                                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                          []                                                                                                                                                                                                                                                                                                                  ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�                                                                              ?�                                                                                                                                                                                                                              ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?x�W���?z�:!d?y��.��?x��8:��?zP^�T?y�>�'�?z&�{�??vY�Um@�     