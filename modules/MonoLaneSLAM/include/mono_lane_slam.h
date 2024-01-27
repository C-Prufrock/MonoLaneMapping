/**
  ******************************************************************************
  * @file           : mono_lane_slam.h
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 24-1-4
  ******************************************************************************
  */


#ifndef MONOLANEMAPPING_MONO_LANE_SLAM_H
#define MONOLANEMAPPING_MONO_LANE_SLAM_H

#include <memory>

class MonoLaneSlam {
public:
    MonoLaneSlam();
};
using MonoLaneSlamPtr = std::shared_ptr<MonoLaneSlam>;

#endif //MONOLANEMAPPING_MONO_LANE_SLAM_H
