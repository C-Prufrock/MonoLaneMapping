/**
  ******************************************************************************
  * @file           : Frame.h
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/25/24
  ******************************************************************************
  */


#ifndef MONOLANEMAPPINGINTERFACE_FRAME_H
#define MONOLANEMAPPINGINTERFACE_FRAME_H

#include<memory>

#include"Eigen/Dense"

#include "lane.h"

class Frame {
public:
    Frame();

public:
    Eigen::Matrix4d extrinsic_matrix_;
    Eigen::Matrix3d intrinsic_matrix_;
    Eigen::Matrix4d pose_;
    Lane lane_;
};

using FramePtr = std::shared_ptr<Frame>;




#endif //MONOLANEMAPPINGINTERFACE_FRAME_H
