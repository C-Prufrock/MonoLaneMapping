/**
  ******************************************************************************
  * @file           : json_transform.cpp
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/27/24
  ******************************************************************************
  */

#include "json_transform.h"

namespace IO {
    namespace JsonTransForm {

        void readJsonToMatrixXd(nlohmann::json& json,Eigen::MatrixXd& res_em) {
            int rows_num = json.size();
            if( rows_num == 0 ) {
                LOG(INFO) <<" Json has no data, Check Json Data Please!!! ";
                return;
            }

            int cols_num = json[0].size();
            if(cols_num == 0) {
                LOG(INFO)<<" No Data in First Rows, Check Json Data Please !!!";
            }
            Eigen::MatrixXd tem_em(rows_num,cols_num);

            for(int i = 0; i < rows_num; i++) {
                for(int j = 0; j < cols_num; j++){
                    tem_em(i,j) = json[i][j];
                }
            }
            res_em = tem_em;
            return;
        }


    }
}