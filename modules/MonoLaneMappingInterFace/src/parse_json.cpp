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

    IO::JsonTransForm::jsonToEigenMatrix<double,4,4>(j["extrinsic"],cur_frame->extrinsic_matrix_);
    // LOG(INFO)<<" cur farme extrinsic matrix is \n"<< cur_frame->extrinsic_matrix_;

    IO::JsonTransForm::jsonToEigenMatrix<double,3,3>(j["intrinsic"],cur_frame->intrinsic_matrix_);
    // LOG(INFO)<<" cur farme intrinsic matrix is \n"<< cur_frame->intrinsic_matrix_;

    IO::JsonTransForm::jsonToEigenMatrix<double,4,4>(j["pose"],cur_frame->pose_);
    // LOG(INFO)<<" cur frame pose is "<< cur_frame->pose_;

    Parse_lane_ptrs(j["lane_lines"],cur_frame->lane_ptrs_);

//    for(auto lane_ptr:cur_frame->lane_ptrs_) {
//        LOG(INFO)<<" Cur lane category is "<< (int)lane_ptr->category_;
//        LOG(INFO)<<" Cur lane attribute is "<< (int)lane_ptr->attribute_;
//        LOG(INFO)<<" Cur lane track_id is "<< (int)lane_ptr->track_id_;
//        for(int i = 0 ; i < lane_ptr->visibilitys_.size(); i++) {
//            LOG(INFO)<<" vis is "<< lane_ptr->visibilitys_[i];
//            LOG(INFO)<<" uvs is "<< lane_ptr->uvs_[i];
//            LOG(INFO)<<" xyzs is "<< lane_ptr->xyzs_[i];
//        }
//    }

    return cur_frame;

};

void ParseJson::Parse_lane_ptrs(nlohmann::json &j,std::vector<LanePtr>&lane_ptrs_) {
    for(auto laneline:j) {
        LanePtr cur_lane_ptr = std::make_shared<Lane>();
        cur_lane_ptr->category_ = Lane::LaneCateGory(laneline["category"]);
        cur_lane_ptr->attribute_ = Lane::LaneAttribute(laneline["attribute"]);
        cur_lane_ptr->track_id_ = (int)laneline["track_id"];
        IO::JsonTransForm::jsonToStdVector<int>(laneline["visibility"],cur_lane_ptr->visibilitys_);
        IO::JsonTransForm::jsonToVectorEigenVector<double,2>(laneline["uv"],cur_lane_ptr->uvs_);
        IO::JsonTransForm::jsonToVectorEigenVector<double,3>(laneline["xyz"],cur_lane_ptr->xyzs_);
//        LOG(INFO)<<"cur_lane_ptr->visibilitys_.size() is  "<< cur_lane_ptr->visibilitys_.size();
//        LOG(INFO)<<"cur_lane_ptr->uvs_.size() is  "<< cur_lane_ptr->uvs_.size();
//        LOG(INFO)<<"cur_lane_ptr->xyz.size() is  "<< cur_lane_ptr->xyzs_.size();
//        if(cur_lane_ptr->visibilitys_.size() != cur_lane_ptr->uvs_.size() || cur_lane_ptr->uvs_.size()!= cur_lane_ptr->xyzs_.size() ) {
//            LOG(ERROR)<<" Json Data Error: uvs has no same size with xyzs or visibility";
//            continue;
//        }
        lane_ptrs_.emplace_back(cur_lane_ptr);
    }
    return;
};
