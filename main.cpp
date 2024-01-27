/**
  ******************************************************************************
  * @file           : main.cpp
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 24-1-3
  ******************************************************************************
  */
#include<iostream>

#include <nlohmann/json.hpp>
#include <glog/logging.h>
#include <gflags/gflags.h>

#include "tools/IO/include/json_read.h"
#include "tools/IO/include/path_read.h"

#include "MonoLaneMappingInterFace/include/mono_lane_mapping_interface.h"


int main(int argc,char *argv[])  {
    // 1. init glog
    // InitGlog(argv[0]);
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "/home/MonoLaneMapping/log/INFO_");
    google::SetStderrLogging(google::GLOG_INFO);
    google::SetLogFilenameExtension(".log");
    FLAGS_colorlogtostderr = true;  // Set log color
    FLAGS_logbufsecs = 0;  // Set log output speed(s)
    LOG(INFO) <<" *************  system begin ************** ";
    // read config path;

    // 2. read manager.json
    nlohmann::json AllConfigJson = IO::readJson(argv[1]);
    LOG(INFO)<<" all config json is "<< AllConfigJson;

    // 3. read jsons path from manager.json
    std::vector<std::string> files_path = IO::readSortedPathFromFolder(AllConfigJson["data_dir"]);

    // 4. init mono_lane_mapping_interface;
    MonoLaneMappingInterfacePtr mono_lane_mapping_interface_ptr = std::make_shared<MonoLaneMappingInterface>();

    for(auto file_path:files_path) {
        LOG(INFO)<<" Cur Dealing Json Name is "<< file_path;
        nlohmann::json all_data_json = IO::readJson(file_path);
        mono_lane_mapping_interface_ptr->lane_mapping_pipleline(all_data_json);

    }





    // 3. init MonoLaneMapping Interface;






    google::ShutdownGoogleLogging();
    return 0;
}
