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

#include <glog/logging.h>
#include <gflags/gflags.h>


int main(int argc,char *argv[])  {
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "/home/MonoLaneMapping/log/");
    google::SetStderrLogging(google::GLOG_INFO);
    google::SetLogFilenameExtension("log_");
    FLAGS_colorlogtostderr = true;  // Set log color
    FLAGS_logbufsecs = 0;  // Set log output speed(s)
    LOG(INFO) << "info test" << "hello log!";  //输出一个Info日志
    LOG(WARNING) << "warning test";  //输出一个Warning日志
    LOG(ERROR) << "error test";  //输出一个Error日志
    google::ShutdownGoogleLogging();
    return 0;
}
