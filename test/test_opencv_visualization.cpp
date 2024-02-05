/**
  ******************************************************************************
  * @file           : test_opencv_visualization.cpp
  * @author         : lxy
  * @brief          : test opencv_visualization
  * @attention      : None
  * @date           : 2/4/24
  ******************************************************************************
  */
#include "opencv2/opencv.hpp"
#include "common/vis/include/opencv_visualization.h"

int main() {
    // 创建图幅，设置图幅大小为800x600
    DrawingCanvas canvas(800);

    // 添加多个点，每个点有不同的颜色、大小和形状
    canvas.addPoint(cv::Point(100.0, 150.0), cv::Scalar(255, 0, 0), 6, DrawingCanvas::CIRCLE, DrawingCanvas::MarkerType::None);
    canvas.addPoint(cv::Point(120.0, 180.0), cv::Scalar(0, 255, 0), 6, DrawingCanvas::RECTANGLE, DrawingCanvas::None);
    canvas.addPoint(cv::Point(80.0, 120.0),cv::Scalar(0, 0, 255), 6, DrawingCanvas::MARKER, DrawingCanvas::MARKER_STAR);

    // 添加多条线，每条线有不同的颜色和粗细
    //    canvas.addLine(50.0, 100.0, 200.0, 200.0, cv::Scalar(255, 255, 0), 2);
    //    canvas.addLine(120.0, 180.0, 250.0, 120.0, cv::Scalar(255, 0, 255), 3);

    // 添加多边形
    //    std::vector<cv::Point> polygonPoints = {{300, 300}, {350, 350}, {400, 300}, {350, 250}};
    //    canvas.addLine(polygonPoints, cv::Scalar(0, 0, 255), 2);

    // 绘制图幅
    canvas.drawCanvas();

    return 0;
}