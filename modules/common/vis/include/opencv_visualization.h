/**
  ******************************************************************************
  * @file           : opencv_visualization.h
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/28/24
  ******************************************************************************
  */


#ifndef MONOLANEMAPPINGINTERFACE_OPENCV_VISUALIZATION_H
#define MONOLANEMAPPINGINTERFACE_OPENCV_VISUALIZATION_H

#include <opencv2/opencv.hpp>
#include <vector>

class DrawingCanvas {
public:
    // 固定图幅高度，横向大小根据点的y分布，计算y方向的y_scale_factor;
    DrawingCanvas(int canvasHeight = 800,double spatialResolution = 0.2)
            :canvasHeight_(canvasHeight),spatialResolution_(spatialResolution) {};

    // 枚举类型表示点的形状
    enum Shape { CIRCLE, RECTANGLE, MARKER };

    // 枚举类型表示线的形状
    enum LineType { LINE, POLYLINE };

    // 枚举类型表示Marker的类型
    enum MarkerType { MARKER_CROSS, MARKER_STAR, MARKER_DIAMOND, MARKER_SQUARE, MARKER_TRIANGLE_UP, None};

    // 添加点
    void addPoint(const cv::Point& point, const cv::Scalar& color = cv::Scalar(255, 0, 0),
                  int size = 5, Shape shape = Shape::CIRCLE, MarkerType markerType = MarkerType::MARKER_STAR) {
        points_info_.emplace_back(PointInfo(point, color, size, shape, markerType));
    };

    // 添加线
    void addLine(const std::vector<cv::Point>& line_points, const cv::Scalar& color = cv::Scalar(0, 255, 0),
                 int thickness = 2, LineType type = LINE) {
            lines_info_.emplace_back(LineInfo(line_points, color, thickness, LINE));
    }

    // 添加文本
    void addText(const std::string& text, cv::Point point, const cv::Scalar& color = cv::Scalar(255, 255, 255),
                 int fontFace = cv::FONT_HERSHEY_SIMPLEX, double fontScale = 0.8, int thickness = 1) {
        texts_info_.emplace_back(TextInfo(text, point, color, fontFace, fontScale, thickness));
    }

    // 绘制图幅
    void drawCanvas() {
        double x_mean,y_mean;
        int origin_width,origin_height;
        getPtsMeanAndScaleFactor(x_mean, y_mean,origin_width,origin_height);
        std::cout<<" x_mean is "<< x_mean << std::endl;
        std::cout<<" y_mean is "<< y_mean << std::endl;
        std::cout<<" origin_width is "<< origin_width << std::endl;
        std::cout<<" origin_height is "<< origin_height << std::endl;
        cv::Mat originImage = cv::Mat(origin_width, origin_height, CV_8UC3, cv::Scalar(65, 65, 65));
        // 显示图幅

//        cv::imshow("Drawing originImage", originImage);
//        cv::waitKey(0);

        // 绘制所有元素在大图上
        drawElements(originImage,x_mean,y_mean,origin_width,origin_height);

        // Resize图幅
        cv::Mat resizedImage;
        double scaleFactor = (double)canvasHeight_ / (double)origin_height;
        // std::cout<<" scaleFactor is "<< scaleFactor << std::endl;
        canvasWidth_ = (int)(scaleFactor * origin_width);
//        std::cout<<" canvasWidth_ " << canvasWidth_ << std::endl;
//        std::cout<<" canvasHeight_ " << canvasHeight_ << std::endl;
        cv::resize(originImage, resizedImage, cv::Size(canvasWidth_, canvasHeight_));
        cv::imwrite("test.jpg",originImage);
        // 显示图幅
//        cv::imshow("Drawing Canvas", resizedImage);
//        cv::waitKey(0);
    }

private:
    int canvasWidth_, canvasHeight_;
    double spatialResolution_;

    struct PointInfo {
        cv::Point point_;
        cv::Scalar color_;
        int size_;
        Shape shape_;   // circle, rectangle,or markers;
        MarkerType markerType_; // marker type

        // 构造函数，用于初始化成员变量
        PointInfo(const cv::Point& point, const cv::Scalar& color, int size, Shape shape, MarkerType markerType)
                : point_(point), color_(color), size_(size), shape_(shape), markerType_(markerType) {}
    };

    struct LineInfo {
        std::vector<cv::Point> points_;
        cv::Scalar color_;
        int thickness_;
        LineType type_;

        // 构造函数，用于初始化成员变量
        LineInfo(const std::vector<cv::Point>& points, const cv::Scalar& color, int thickness, LineType type)
                : points_(points),color_(color), thickness_(thickness), type_(type) {};

    };

    struct TextInfo {
        std::string text_;
        cv::Point point_;
        cv::Scalar color_;
        int fontFace_;
        double fontScale_;
        int thickness_;

        // 构造函数，用于初始化成员变量
        TextInfo(const std::string& text, cv::Point point, const cv::Scalar& color, int fontFace, double fontScale, int thickness)
                : text_(text), point_(point), color_(color), fontFace_(fontFace), fontScale_(fontScale), thickness_(thickness) {}
    };

    std::vector<PointInfo> points_info_;
    std::vector<LineInfo> lines_info_;
    std::vector<TextInfo> texts_info_;

    void findMeanPts(std::vector<double>& x_list,std::vector<double>& y_list,double& x_mean,double& y_mean) {
        double x_sum = 0.0,y_sum = 0.0;
        for(auto x:x_list) {
            x_sum += x;
        }
        for(auto y:y_list) {
            y_sum += y;
        }
        x_mean = x_sum / x_list.size();
        y_mean = y_sum / y_list.size();
        return;
    };

    void findMinMaxPts(std::vector<double>& x_list,std::vector<double>& y_list,
                       double& min_x,double& max_x,
                       double& min_y,double& max_y) {
        min_x = *std::min_element(x_list.begin(),x_list.end());
        max_x = *std::max_element(x_list.begin(),x_list.end());
        min_y = *std::min_element(y_list.begin(),y_list.end());
        max_y = *std::max_element(y_list.begin(),y_list.end());
        return;
    };

    void getPtsMeanAndScaleFactor(double& x_mean,double& y_mean,int& origin_width,int& origin_height) {
        // 根据点云的大小设置图幅大小;
        std::vector<double> x_list;
        std::vector<double> y_list;

        for(auto point_info:points_info_) {
            x_list.emplace_back(point_info.point_.x);
            y_list.emplace_back(point_info.point_.y);
        }

        for(auto line_info:lines_info_) {
            for(auto point:line_info.points_) {
                x_list.emplace_back(point.x);
                y_list.emplace_back(point.y);
            }
        }
        // 寻找平移向量;
        // findMeanPts(x_list,y_list,x_mean,y_mean);

        // 寻找最小点，最大点;
        double min_x,max_x,min_y,max_y;
        findMinMaxPts(x_list,y_list,min_x,max_x,min_y,max_y);
        x_mean = ( max_x + min_x ) / 2.0;
        y_mean = ( max_y + min_y ) / 2.0;


        origin_width  = (int) (  (max_x - min_x)  / spatialResolution_) + 200; // 2 为边界大小;
        origin_height = (int) (  (max_y - min_y)  / spatialResolution_) + 200;

        return;
    };

    inline void transCvPoint(const cv::Point& src_point,cv::Point& dst_point,
                             const double& x_mean,const double& y_mean,
                             const int& origin_width,const int& origin_height) {
        std::cout<<" origin_width is "<< origin_width << std::endl;
        std::cout<<" origin_width / 2 is "<< origin_width / 2 << std::endl;
        dst_point.x = (int) ((src_point.x - x_mean ) / spatialResolution_ ) + origin_width  / 2;
        dst_point.y = (int) ((src_point.y - y_mean ) / spatialResolution_ ) + origin_height / 2;
        std::cout<<" src_point x is "<< src_point.x << std::endl;
        std::cout<<" src_point y is "<< src_point.y << std::endl;
        std::cout<<" dst_point x is "<< dst_point.x << std::endl;
        std::cout<<" dst_point y is "<< dst_point.y << std::endl;
        return;
    };

    inline void transCvPoints(const std::vector<cv::Point>& src_points, std::vector<cv::Point>& dst_points,
                              const double& x_mean,const double& y_mean,
                              const int& origin_width,const int& origin_height) {
        for(auto src_point:src_points) {
            cv::Point dst_point;
            transCvPoint(src_point,dst_point,x_mean,y_mean,origin_width,origin_height);
            dst_points.emplace_back(dst_point);
        }
        return;
    }



    void drawMarker(cv::Mat& img, const cv::Point& center, const cv::Scalar& color,
                    MarkerType markerType, int markerSize, int thickness) {
        int markerThickness = markerSize / 5;
        int markerLineSize = markerSize / 2;

        switch (markerType) {
            case MARKER_CROSS:
                cv::line(img, center - cv::Point(0, markerLineSize), center + cv::Point(0, markerLineSize), color, markerThickness, cv::LINE_AA);
                cv::line(img, center - cv::Point(markerLineSize, 0), center + cv::Point(markerLineSize, 0), color, markerThickness, cv::LINE_AA);
                break;
            case MARKER_STAR:
                cv::drawMarker(img, center, color, cv::MARKER_STAR, markerSize, thickness);
                break;
            case MARKER_DIAMOND:
                cv::drawMarker(img, center, color, cv::MARKER_DIAMOND, markerSize, thickness);
                break;
            case MARKER_SQUARE:
                cv::drawMarker(img, center, color, cv::MARKER_SQUARE, markerSize, thickness);
                break;
            case MARKER_TRIANGLE_UP:
                cv::drawMarker(img, center, color, cv::MARKER_TRIANGLE_UP, markerSize, thickness);
                break;
        }
    }

    void drawElements(cv::Mat& img,double x_mean,double y_mean,int origin_width,int origin_height) {
        // draw points_info;
        for (const auto& point_info : points_info_) {
            // 根据用户设置绘制不同形状
            cv::Point draw_point;

            transCvPoint(point_info.point_,draw_point,x_mean,y_mean,origin_width,origin_height);
            std::cout<<" draw_point x is "<< draw_point.x << std::endl;
            std::cout<<" draw_point y is "<< draw_point.y << std::endl;
            if( point_info.shape_ == Shape::CIRCLE) {
                // 绘制圆形
                cv::circle(img, draw_point, point_info.size_, point_info.color_, cv::FILLED);
            } else if( point_info.shape_ == Shape::RECTANGLE) {
                // 绘制矩形
                cv::rectangle(img, cv::Point(draw_point.x - point_info.size_ / 2, draw_point.y - point_info.size_ / 2),
                              cv::Point(draw_point.x + point_info.size_ / 2, draw_point.y + point_info.size_ / 2),
                              point_info.color_, cv::FILLED);
            } else if( point_info.shape_ == Shape::MARKER ) {
                // 使用drawMarker绘制Marker
                drawMarker(img, draw_point, point_info.color_, point_info.markerType_,
                           point_info.size_, point_info.size_ / 5);
            } else {
                std::cout<<" ***  Check: Set Point Shape Please! ***";
            }
        }

        // draw lines_info
        for (const auto& line_info : lines_info_) {
            // 根据线的类型选择不同的绘制方式
            std::vector<cv::Point> dst_points;
            transCvPoints(line_info.points_,dst_points,x_mean,y_mean,origin_width,origin_height);
            if (line_info.type_ == LINE) {
                // 绘制非封闭线;s
                cv::polylines(img, dst_points, false, line_info.color_, line_info.thickness_);
            } else if (line_info.type_ == POLYLINE) {
                // 绘制封闭多边形
                cv::polylines(img, dst_points, true, line_info.color_, line_info.thickness_);
            } else {
                std::cout<<" ***  Check: Set Line Shape Please! ***";
            }
        }

        //        for (const auto& text : texts) {
        //            cv::putText(img, text.text, cv::Point(text.x, text.y), text.fontFace, text.fontScale, text.color, text.thickness);
        //        }
    }
};












#endif //MONOLANEMAPPINGINTERFACE_OPENCV_VISUALIZATION_H
