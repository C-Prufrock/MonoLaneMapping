/**
  ******************************************************************************
  * @file           : parse_json.h
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/25/24
  ******************************************************************************
  */


#ifndef MONOLANEMAPPINGINTERFACE_PARSE_JSON_H
#define MONOLANEMAPPINGINTERFACE_PARSE_JSON_H

#include<memory>


#include<nlohmann/json.hpp>
//#include <glog/logging.h>
//#include <gflags/gflags.h>
#include "Eigen/Dense"

#include"MonoLaneSLAM/include/frame.h"
class ParseJson{
public:
    ParseJson();
public:
    FramePtr parse_json_data(nlohmann::json& j);


};
using ParseJsonPtr = std::shared_ptr<ParseJson>;


#endif //MONOLANEMAPPINGINTERFACE_PARSE_JSON_H
