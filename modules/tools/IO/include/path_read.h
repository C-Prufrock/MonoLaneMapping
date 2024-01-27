/**
  ******************************************************************************
  * @file           : path_read.h
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/18/24
  ******************************************************************************
  */


#ifndef MONOLANEMAPPING_PATH_READ_H
#define MONOLANEMAPPING_PATH_READ_H

#include<iostream>

//#include <glog/logging.h>
//#include <gflags/gflags.h>

namespace IO {

    std::vector<std::string> readSortedPathFromFolder(std::string data_path);

}



#endif //MONOLANEMAPPING_PATH_READ_H
