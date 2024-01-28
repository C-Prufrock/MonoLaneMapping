/**
  ******************************************************************************
  * @file           : parse_json.cpp
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/25/24
  ******************************************************************************
  */
#include<iostream>

#include "glog/logging.h"

#include "parse_json.h"
#include "tools/IO/include/json_transform.h"


ParseJson::ParseJson() {};

FramePtr ParseJson::parse_json_data(nlohmann::json &j) {
    FramePtr cur_frame = std::make_shared<Frame>();

    IO::JsonTransForm::from_json<double,4,4>(j["extrinsic"],cur_frame->extrinsic_matrix_);
    LOG(INFO)<<" cur farme extrinsic matrix is \n"<< cur_frame->extrinsic_matrix_;

    IO::JsonTransForm::from_json<double,3,3>(j["intrinsic"],cur_frame->intrinsic_matrix_);
    LOG(INFO)<<" cur farme intrinsic matrix is \n"<< cur_frame->intrinsic_matrix_;

    IO::JsonTransForm::from_json<double,4,4>(j["pose"],cur_frame->pose_);
    LOG(INFO)<<" cur frame pose is "<< cur_frame->pose_;



    return cur_frame;

};