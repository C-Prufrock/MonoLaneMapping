/**
  ******************************************************************************
  * @file           : json_read.h
  * @author         : lxy
  * @brief          : read json to string
  * @attention      : None
  * @date           : 1/18/24
  ******************************************************************************
  */


#ifndef MONOLANEMAPPING_JSON_READ_H
#define MONOLANEMAPPING_JSON_READ_H

#include<iostream>
#include<fstream>

#include<nlohmann/json.hpp>

namespace IO {

    nlohmann::json readJson(std::string json_path);




}





#endif //MONOLANEMAPPING_JSON_READ_H
