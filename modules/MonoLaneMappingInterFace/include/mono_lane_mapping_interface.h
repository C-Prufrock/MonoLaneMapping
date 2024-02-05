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

#include "MonoLaneSLAM/include/mono_lane_slam.h"
#include "parse_json.h"

class MonoLaneMappingInterface {
public:
    MonoLaneMappingInterface();

// interface for input-core transform;
public:
    ParseJsonPtr  parse_json_ptr_;

// Core Function;
public:
    MonoLaneSlamPtr mono_lane_slam_ptr_;

public:
    void lane_mapping_pipleline(nlohmann::json& all_data_json);


};
using MonoLaneMappingInterfacePtr = std::shared_ptr<MonoLaneMappingInterface>;


#endif //MONOLANEMAPPING_MONO_LANE_MAPPING_INTERFACE_H
