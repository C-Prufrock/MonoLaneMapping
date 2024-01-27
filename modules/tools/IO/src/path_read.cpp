/**
  ******************************************************************************
  * @file           : path_read.cpp
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/18/24
  ******************************************************************************
  */
#include <dirent.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>

#include "path_read.h"


namespace IO {

    struct JsonName {
        double timestamp;
        std::string name;
    };

    bool compare(JsonName name1, JsonName name2) {
      return name1.timestamp < name2.timestamp;
    };

    std::vector<std::string> readSortedPathFromFolder(std::string data_dir) {
        DIR* dp;
        struct dirent* dirp;

        std::vector<JsonName> json_names;
        if ((dp = opendir(data_dir.c_str())) != NULL) {
            while ((dirp = readdir(dp)) != NULL) {
                if (strcmp(".", dirp->d_name) == 0 || strcmp("..", dirp->d_name) == 0)
                    continue;
                std::stringstream ss;
                ss << dirp->d_name;
                std::string t;
                while (getline(ss, t)) {
                    JsonName cur_json_name;
                    cur_json_name.name = t;
                    cur_json_name.timestamp = std::stod(t.substr(8,12).c_str());
                    json_names.emplace_back(cur_json_name);
                }
            }
        } else {
             std::cout <<" Check Dir please, no json files there" << std::endl;
        }
        closedir(dp);

        std::sort(json_names.begin(),json_names.end(), compare);
        std::vector<std::string> filenames;
        for(auto json_name:json_names) {
            filenames.emplace_back( data_dir + "/" + json_name.name);
        }

        return filenames;
    };
}