/**
  ******************************************************************************
  * @file           : json_transform.h
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/27/24
  ******************************************************************************
  */


#ifndef MONOLANEMAPPINGINTERFACE_JSON_TRANSFORM_H
#define MONOLANEMAPPINGINTERFACE_JSON_TRANSFORM_H

#include<iostream>

#include "Eigen/Dense"

#include "nlohmann/json.hpp"
#include "glog/logging.h"

namespace IO {
    namespace JsonTransForm{

        void readJsonToMatrixXd(nlohmann::json& json,Eigen::MatrixXd& res_em);
    }
}




#endif //MONOLANEMAPPINGINTERFACE_JSON_TRANSFORM_H
