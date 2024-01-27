/**
  ******************************************************************************
  * @file           : IO.cpp
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/18/24
  ******************************************************************************
  */

#include "json_read.h"

namespace IO {
    nlohmann::json readJson(std::string json_path) {
        nlohmann::json j;
        std::ifstream jfile(json_path);
        jfile >> j;
        return j;
    }
}
