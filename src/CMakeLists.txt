set(SOURCES abinit_private.f90 abinit_private@proc.f90 autocp.f90
  autocp@proc.f90 bader.f90 bader@proc.f90 bisect.f90 bisect@proc.f90
  cfftnd.f90 c_interface_module.f90 config.f90
  crystalmod.f90 crystalmod@proc.f90 crystalseedmod.f90
  crystalseedmod@proc.f90 dftb_private.f90
  dftb_private@proc.f90 elk_private.f90 elk_private@proc.f90
  environmod.f90 environmod@proc.f90 fieldmod.f90
  fieldmod@proc.f90 fieldseedmod.f90 fieldseedmod@proc.f90
  flux.f90 flux@proc.f90 fragmentmod.f90
  fragmentmod@proc.f90 global.f90 global@proc.F90
  graphics.f90 graphics@proc.f90 grid1mod.f90
  grid1mod@proc.f90 grid3mod.f90 grid3mod@proc.f90
  gui_interface.f90 hashmod.f90 hashmod@proc.f90
  hirshfeld.f90 hirshfeld@proc.f90 integration.f90
  integration@proc.f90 keast.f90 meshmod.f90
  meshmod@proc.f90 molcalc.f90 nci.f90 nci@proc.f90
  pi_private.f90 pi_private@proc.f90 qtree_basic.f90
  qtree_basic@proc.f90 qtree.f90 qtree_gpaths.f90
  qtree_gpaths@proc.f90 qtree@proc.f90 qtree_tetrawork.f90
  qtree_tetrawork@proc.f90 qtree_utils.f90
  qtree_utils@proc.f90 quadpack.f90 rhoplot.f90
  rhoplot@proc.f90 spglib.f90 spglib@proc.f90 stm.f90
  stm@proc.f90 struct_drivers.f90 struct_drivers@proc.f90
  surface.f90 surface@proc.f90 systemmod.f90
  systemmod@proc.f90 tools.f90 tools_io.f90 tools_math.f90
  tools_math@lebedev.f90 tools_math@proc.f90 tools@proc.f90
  tricks.f90 types.f90 types@proc.f90 wfn_private.f90
  wien_private.f90 wien_private@proc.f90 xdm.f90
  xdm@proc.f90 yt.f90 yt@proc.f90
  doqhull.c
  arithmetic.F90 arithmetic@proc.F90 config@proc.F90
  molcalc@proc.F90 param.F90
  tools_io@proc.F90 wfn_private@proc.F90
  )
set(SOURCESP critic2.F90)

include_directories(cubpack ${CMAKE_CURRENT_BINARY_DIR}/cubpack qhull)
add_subdirectory(cubpack)
add_subdirectory(ciftbx)
add_subdirectory(oldlibs)
add_subdirectory(qhull)
add_subdirectory(spglib)

set(PACKAGE ${CMAKE_PROJECT_NAME})
set(VERSION 1.0)
set(F77 ${CMAKE_Fortran_COMPILER})
set(FC ${CMAKE_Fortran_COMPILER})
set(CC ${CMAKE_CXX_COMPILER})
set(FFLAGS ${CMAKE_Fortran_FLAGS})
set(FCFLAGS ${CMAKE_Fortran_FLAGS})
set(CFLAGS ${CMAKE_C_FLAGS})
set(LDFLAGS "")
set(TARGET ${CMAKE_SYSTEM})
string(TIMESTAMP DATE "%Y%m%d")
set(DEBUG "")
set(AC_REVISION "")
set_property(SOURCE config@proc.F90 APPEND PROPERTY COMPILE_FLAGS "-DDATADIR='\"${CMAKE_INSTALL_FULL_DATADIR}\"'")
configure_file(config@proc.F90.in ${CMAKE_CURRENT_SOURCE_DIR}/config@proc.F90)

add_executable(critic2 ${SOURCES} ${SOURCESP} $<TARGET_OBJECTS:cubpack>
  $<TARGET_OBJECTS:ciftbx> $<TARGET_OBJECTS:oldlibs>
  $<TARGET_OBJECTS:qhull> $<TARGET_OBJECTS:spglib>
  )
target_link_libraries(critic2 OpenMP::OpenMP_Fortran)

if (ENABLE_GUI)
  add_library(lcritic2 OBJECT ${SOURCES})
  target_link_libraries(lcritic2 OpenMP::OpenMP_Fortran)
endif()

install(TARGETS critic2 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})