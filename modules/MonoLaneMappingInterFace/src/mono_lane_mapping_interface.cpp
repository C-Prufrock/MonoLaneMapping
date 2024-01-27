/**
  ******************************************************************************
  * @file           : mono_lane_mapping_interface.cpp
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 24-1-4
  ******************************************************************************
  */

#include<iostream>
#include "glog/logging.h"
#include "mono_lane_mapping_interface.h"

MonoLaneMappingInterface::MonoLaneMappingInterface() {
    parse_json_ptr_ = std::make_shared<ParseJson>();
};

void MonoLaneMappingInterface::lane_mapping_pipleline(nlohmann::json& all_data_json) {
    FramePtr cur_frame_ptr = parse_json_ptr_->parse_json_data(all_data_json);

    return;
};