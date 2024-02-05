/**
  ******************************************************************************
  * @file           : lane.h
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/25/24
  ******************************************************************************
  */


#ifndef MONOLANEMAPPINGINTERFACE_LANE_H
#define MONOLANEMAPPINGINTERFACE_LANE_H

#include<vector>
#include<memory>
#include<Eigen/Dense>
class Lane {
// ref: https://github.com/OpenDriveLab/OpenLane/blob/main/anno_criterion/Lane/README.md
public:
    Lane();
public:
    enum class LaneCateGory {
        Unkown = 0,
        WhiteDash = 1,
        WhiteSolid = 2,
        DoubleWhiteDash = 3,
        DoubleWhieSolid = 4,
        WhiteLdashRsolid = 5,
        WhiteLsolidRdash = 6,
        YelloDash = 7,
        YellowSolid = 8,
        DoubleYellowDash = 9,
        DoubleYellowSolid = 10,
        YellowLdashRsolid = 11,
        YellowlsolidRdash = 12,
        LeftCurbSide = 20,
        RightCurbSide = 21,
    };
    enum class LaneAttribute{
        LeftLeft = 1,
        Left = 2,
        Right = 3,
        RightRight = 4,
    };

    LaneCateGory category_;
    LaneAttribute attribute_;
    std::vector<int>visibilitys_;
    std::vector<Eigen::Vector2d>uvs_;
    std::vector<Eigen::Vector3d>xyzs_;

public:
    std::vector<Eigen::Vector2d> control_points_ ;

    int track_id_;

public:
    void preprocess();
};
using LanePtr = std::shared_ptr<Lane>;

#endif //MONOLANEMAPPINGINTERFACE_LANE_H
