#include <mpi.h>
#include <hdf5.h>
#include <cmath>

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);

    const int N = 8;                         // 8*8*8 
    const hsize_t dims[3] = {N,N,N};

    /*  create HDF5 file */
    hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_mpio(fapl, MPI_COMM_WORLD, MPI_INFO_NULL);
    hid_t file = H5Fcreate("../data/cube.h5", H5F_ACC_TRUNC,
                           H5P_DEFAULT, fapl);
    H5Pclose(fapl);

    /*  prepare data */
    double* buf = new double[N*N*N];
    for(int k=0;k<N;++k)
      for(int j=0;j<N;++j)
        for(int i=0;i<N;++i)
          buf[k*N*N+j*N+i] = i*j*k;          // p=x*y*z

    hid_t dspace = H5Screate_simple(3, dims, NULL);
    hid_t dcpl   = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_chunk(dcpl, 3, dims);             // 3D chunking

    hid_t dset = H5Dcreate2(file, "pressure",
                            H5T_IEEE_F64LE, dspace,
                            H5P_DEFAULT, dcpl, H5P_DEFAULT);

    /*  perform collective write */
    hid_t dxpl = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(dxpl, H5FD_MPIO_COLLECTIVE);
    H5Dwrite(dset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL,
             dxpl, buf);

    /* 4. clean up */
    delete[] buf;
    H5Pclose(dxpl);  H5Pclose(dcpl);
    H5Dclose(dset);  H5Sclose(dspace);
    H5Fclose(file);

    MPI_Finalize();
    return 0;
}
