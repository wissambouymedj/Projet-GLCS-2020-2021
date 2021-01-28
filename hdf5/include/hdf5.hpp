#pragma once

// local headers
#include <simulationobserver.hpp>

/** An interface for any class */

class hdf5

		: public SimulationObserver
{
    // donner le nom de "file"
     string m_file_name;
     
     hid_t m_fapl; 
     
     // pour la creation de "file"
     hid_t m_h5file; 
     //pour le dataspace 
     hid_t m_file_space;
     
     //pour le dataset
     hid_t m_dataset;
     
     int m_cur_iter; 
     
     //frequence de configuration 
     int m_freq; 
     
   
   void simulation_updated(const Distributed2DField& data) override;
   
}































/*#pragma once
// the MPI library must be included before C++ headers

#include <mpi.h>

#include <hdf5.h>
// standard C++ library headers

#include <array>
#include <vector>




class hdf5
{
private 
     
            int dsize[2];
            double cur[dsize[0]][dsize[1]];
            double next[dsize[0]][dsize[1]];
            MPI_Comm cart_comm, int per[2];
            int cart_dims[2], int pcrd[2]);
public: 



     hdf5 (int dsize[2], double cur[dsize[0]][dsize[1]], double next[dsize[0]][dsize[1]], MPI_Comm cart_comm, int per[2], int cart_dims[2], int pcrd[2])




};*/
