# HDF5 + XDMF prototype
# test-hdf5: HemeLB I/O Replacement Testing with HDF5

This repository contains a prototype implementation for evaluating HDF5 as a replacement for HemeLB's custom MPI-IO output format. The goal is to assess whether HDF5 can provide sufficient performance, flexibility, and compatibility with visualization tools such as ParaView.

---

## Background

HemeLB is a parallel lattice-Boltzmann blood flow simulator used in biomedical research. It currently writes output using a custom MPI-IO binary format, which is fast but incompatible with mainstream post-processing tools. Users must run an additional conversion script to visualize data with ParaView.

This project explores the use of **HDF5**, a widely adopted scientific data format, to improve:

- I/O performance
- Ease of post-processing
- Compatibility with tools like **ParaView** (via `.xdmf`).

---

## Project Structure
test-hdf5/
├── LocalPropertyOutput.cc # Original output format implementation (MPI-IO)
├── LocalPropertyOutput.h
├── LocalDistributionInput.cc # Original input format implementation
├── LocalDistributionInput.h
├── OutputField.h # Output field specification
├── PropertyActor.h # Property writer orchestration
├── XdrPropertyOutput.cc #  New: HDF5-based output (under development)
├── XdrPropertyOutput.h #  Interface for HDF5 writer
├── test/
│ ├── test_hdf5.cpp # Minimal test case
│ └── data/ # Small-scale test input
├── CMakeLists.txt
└── README.md # ← You are here



##   Running the Test
mkdir build 
cd build
rm -rf *               
cmake ../src
make -j
mpirun -np 2 ./demo_write
This test runs a minimal data dump using HDF5.
It creates an .h5 output file (e.g., cube.h5) and optionally an .xdmf companion file for ParaView visualization.

##  Example Visualization
- Open test-data.xdmf in ParaView
- Enable Xdmf3 Reader S
- Press "Apply"