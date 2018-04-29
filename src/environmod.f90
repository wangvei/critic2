! Copyright (c) 2007-2018 Alberto Otero de la Roza
! <aoterodelaroza@gmail.com>,
! Ángel Martín Pendás <angel@fluor.quimica.uniovi.es> and Víctor Luaña
! <victor@fluor.quimica.uniovi.es>.
!
! critic2 is free software: you can redistribute it and/or modify
! it under the terms of the GNU General Public License as published by
! the Free Software Foundation, either version 3 of the License, or
! (at
! your option) any later version.
!
! critic2 is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
! GNU General Public License for more details.
!
! You should have received a copy of the GNU General Public License
! along with this program.  If not, see
! <http://www.gnu.org/licenses/>.

! Atomic environment class
module environmod
  use types, only: celatom, species
  implicit none

  private

  !> Atomic environment type
  type environ
     real*8 :: dmax0 !< Maximum environment distance
     integer :: n = 0 !< Number of atoms
     type(celatom), allocatable :: at(:) !< Atoms 
   contains
     procedure :: init => environ_init !< Allocate arrays and nullify variables
     procedure :: end => environ_end !< Deallocate arrays and nullify variables
     procedure :: build_mol => environ_build_from_molecule !< Build an environment from molecule input
     procedure :: build_crys => environ_build_from_crystal !< Build an environment from molecule input
  end type environ
  public :: environ

  ! module procedure interfaces
  interface
     module subroutine environ_init(e)
       class(environ), intent(inout) :: e
     end subroutine environ_init
     module subroutine environ_end(e)
       class(environ), intent(inout) :: e
     end subroutine environ_end
     module subroutine environ_build_from_molecule(e,n,at)
       class(environ), intent(inout) :: e
       integer, intent(in) :: n
       type(celatom), intent(in) :: at(n)
     end subroutine environ_build_from_molecule
     module subroutine environ_build_from_crystal(e,nspc,spc,n,at,m_xr2c,m_x2xr,dmax0)
       class(environ), intent(inout) :: e
       integer, intent(in) :: nspc
       type(species), intent(in) :: spc(nspc)
       integer, intent(in) :: n
       type(celatom), intent(in) :: at(n)
       real*8, intent(in) :: m_xr2c(3,3)
       real*8, intent(in) :: m_x2xr(3,3)
       real*8, intent(in), optional :: dmax0
     end subroutine environ_build_from_crystal
  end interface

end module environmod
