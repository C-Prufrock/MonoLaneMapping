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
    FramePtr cur_frame;
    nlohmann::json extrin_j = j["extrinsic"];
    Eigen::MatrixXd temp_extrin_matrix;
    IO::JsonTransForm::readJsonToMatrixXd(j["extrinsic"],temp_extrin_matrix);
    cur_frame->extrinsic_matrix_ = Eigen::Map<Eigen::Matrix4d>(temp_extrin_matrix.data());
    LOG(INFO)<<" matrix " << cur_frame->extrinsic_matrix_;

    Eigen::Matrix4d extrinsic_matrix;

    // cur_frame->extrinsic_matrix_
//    LOG(INFO)<<" log well in  parse";

    return cur_frame;

};