/**
  ******************************************************************************
  * @file           : mono_lane_mapping_interface.h
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 24-1-4
  ******************************************************************************
  */


#ifndef MONOLANEMAPPING_MONO_LANE_MAPPING_INTERFACE_H
#define MONOLANEMAPPING_MONO_LANE_MAPPING_INTERFACE_H

#include<memory>

#include <nlohmann/json.hpp>
#include <glog/logging.h>

#include "parse_json.h"

class MonoLaneMappingInterface {
public:
    MonoLaneMappingInterface();

public:
    ParseJsonPtr  parse_json_ptr_;

public:
    void lane_mapping_pipleline(nlohmann::json& all_data_json);


};
using MonoLaneMappingInterfacePtr = std::shared_ptr<MonoLaneMappingInterface>;


#endif //MONOLANEMAPPING_MONO_LANE_MAPPING_INTERFACE_H
