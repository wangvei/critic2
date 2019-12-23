set(TESTS
  001_load-wfn
  002_load-wfx
  003_load-cube
  004_load-cubeopts
  005_load-cubezpsp
  006_load-bincube
  007_load-abinit
  008_load-vasp
  009_load-xsf
  010_load-wien2k
  011_load-elk
  012_load-pi
  013_load-dftb+
  014_load-siesta
  015_load-elkgrid
  016_load-fchk
  017_load-molden
  018_load-gaussian_hf
  019_load-gaussian_uhf
  020_load-gaussian_mp2
  021_load-psi4_hf
  022_load-psi4_uhf
  023_load-fchk_virtuals
  024_load-molden_virtuals
  025_load-pwc
  026_load-vaspspin
  )

runtests(${TESTS})