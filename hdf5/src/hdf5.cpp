// the implemented class  to save data in hdf5 file 
// library headers

#include "hdf5.hpp"


#include <chrono>
#include <vector>
#include <string>
#include <cmath>

using std::cout; 
using std::endl; 
using std::flush; 
using std::thread::sleep;
using std::chrono::miliseconds; 


hdf5::hdf5(const Configuration& config, MPI_Comm comm)
     :m_config(config)
     
     
  //definir la taille des block  (x,y)
  
  m_file_name = std::tostring(m_config.output_file());
  
  // // CREATION DU FILE ACCESS PROPERTY LIST
  m_fapl = H5Pcreate(H5P_FILE_ACCESS);
  H5Pset_fapl_mpio(fapl,comm,MPI_INFO_NULL);
  
  //create the file 
  m_h5file = H5Fcreate(m_file_name.c_str(),H5F_ACC_TRUNC,H5P_DEFAULT,fapl);
  
  //create the dataspace 
  int y_size = m_config.();
  int x_size = m_config.();
  
  int block_height = m_config.();   
  int block_width = m_config.(); 
  
  const vector<hsize_t> file _dims(block_height * y_size, block_width * x_size);
  m_file_space = HS5create_simple(file_dims.size(), file_dims.data(). NULL);
  
  
  //initialisation le compteur iter a 0
  m_cur_iter = 0;
  //set the frequence of saving data to,hdf5 file 
  m_freq = m_config.frequence();
  //update de data  with class simulation_updated a chaque iter
  
void hdf5::simulation_updated(const Distributed2DField& data)
{
 
//  create the hdf5 dataset pour stocker l data 

                       for ( int xx= 0 ; xx < data.noghost_view().extent(DX);  +xx)
                       
                       { 
                       
                       if ( 0 == data.noghost_view(yy,xx)){
                       
                      m_data[yy * data.noghost_view().extent(DX) +xx] = NAN;
                       } else {
                       
                      m_data[yy * data.noghost_view().extent(DX) +xx] = data.noghost_view(yy, xx);
                      
                      }
                      }
                      }
                     
                      
                      //TABLEAU START POUR LE MEMORY DATASPACE
                     
                      
                      
                      int rank_y = data.distribution().coord()[DY];
                      int rank_x = data.distribution().coord()[DX];
                      
                      const vector<hsize_t> file _start {rank_y * block_height , rank_x *block_width}; 
                      const vector<hsize_t> file _count (data.noghost_view().extent(DY),data.noghost_view().extent(DX)};
                      
                      H5Select_hyperslab(m_h5file,HS5_SELECT,file_start.data(), NULL,file_count().data(), NULL);
                      
                      //create memory dataspace 
                      
                      const vector<hsize_t> mem_dims (data.noghost_view().extent(DY),data.noghost_view().extent(DX)};
                      
                      const hid_t mem_space = H5Screate_simple(mem_dims.size(),mem_dims.data(),NULL);
                      
                      //select the region we want to writein the memory dataspace
                      const vector<hsize_t> file _start {m_ghost_y, m_ghost_x}; 
                      const vector<hsize_t> file _count (data.noghost_view().extent(DY),data.noghost_view().extent(DX)};
                      
                      
                       // HYPERSLAB DU FILE DATASPACE ET DU MEMORY DATASPACE
                      H5Select_hyperslab(mem_space,HS5_SELECT_SET,mem_start.data(), NULL,mem_count().data(), NULL);
                      
                      
                      
                    //FILE TRANSFER PROPERTY LIST
                     const hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);
                     H5Pset_dxpl_mpio(xfer_plist,H5FD_MPIO_COLLECTIVE);
                     
                     
                    // ECRITURES
                     
                     if(m_cur_iter % m_freq == 0)
                     
                       H5Dwrite(m_dataset, H5T_NATIVE_DOUBLE,mem_space,m_file_space,m_xfer_plist,data.data());
                       
                       //
                       m_cur_iter++;
                       
                       }
                  
                      
                      
                      

















































/*



    
    


