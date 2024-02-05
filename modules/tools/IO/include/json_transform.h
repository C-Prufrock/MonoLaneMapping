/**
  ******************************************************************************
  * @file           : json_transform.h
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 1/27/24
  ******************************************************************************
  */


#ifndef MONOLANEMAPPINGINTERFACE_JSON_TRANSFORM_H
#define MONOLANEMAPPINGINTERFACE_JSON_TRANSFORM_H

#include<iostream>

#include "Eigen/Dense"

#include "nlohmann/json.hpp"
#include "glog/logging.h"

namespace IO {
    namespace JsonTransForm{

        template< typename ScalarType, int rows, int cols >
        void jsonToEigenMatrix( const nlohmann::json& jsonObject, Eigen::Matrix< ScalarType, rows, cols >& matrix )
        {
            nlohmann::json jsonArray;
            if ( jsonObject.is_array( ) )
            {
                if ( jsonObject.empty( ) )
                {
                    return;
                }
                jsonArray = jsonObject;
            }
            else if ( jsonObject.is_number( ) )
            {
                jsonArray.push_back( jsonObject );
            }

            nlohmann::json jsonArrayOfArrays;
            if ( jsonArray.front( ).is_array( ) )  // provided matrix
            {
                jsonArrayOfArrays = jsonArray;
            }
            else  // provided vector
            {
                if ( rows == 1 )  // expected row vector
                {
                    jsonArrayOfArrays.push_back( jsonArray );
                }
                else if ( cols == 1 )  // expected column vector
                {
                    for ( unsigned int i = 0; i < jsonArray.size( ); ++i )
                    {
                        jsonArrayOfArrays.push_back( { jsonArray.at( i ) } );
                    }
                }
            }

            const unsigned int providedRows = jsonArrayOfArrays.size( );
            const unsigned int providedCols = jsonArrayOfArrays.front( ).size( );
            if ( ( rows >= 0 && int( providedRows ) != rows ) || ( cols >= 0 && int( providedCols ) != cols ) )
            {
                std::cerr << "Expected matrix of size " << rows << "x" << cols
                          << ", received matrix of size " << providedRows << "x" << providedCols << "." << std::endl;
            }
            matrix.resize( providedRows, providedCols );

            for ( int r = 0; r < providedRows; ++r )
            {
                for ( int c = 0; c < providedCols; ++c )
                {
                    matrix( r, c ) = jsonArrayOfArrays[r][c].get<ScalarType>();
                }
            }
            return;
        }

        template<typename ScalarType>
        void jsonToStdVector(const nlohmann::json& jsonObject,std::vector<ScalarType>& vec) {
            if(!jsonObject.is_array( ) ) {
                std::cerr<<" Json Object is not iterable,check Json Key or Json data";
            }
            int json_array_size = jsonObject.size();
            for(int i = 0; i < json_array_size;i++) {
                vec.emplace_back((ScalarType)jsonObject[i].get<ScalarType>());
            }
            return;
        };

        template<typename ScalarType,int vec_dim>
        void jsonToVectorEigenVector(const nlohmann::json& jsonObject,std::vector<Eigen::Matrix<ScalarType,vec_dim,1>>& vec_ev) {
            const unsigned int dim_size = jsonObject.size( );
            const unsigned int json_vector_size = jsonObject.front( ).size( );
            if ( ( vec_dim >= 0 && int( dim_size) != vec_dim ))
            {
                std::cerr << "Expected Eigen Vector of size " << vec_dim
                          << ", received Eigen Vector of size " << dim_size << std::endl;
            }
            vec_ev.resize(json_vector_size);
            for(int j = 0; j < json_vector_size; j++) {
                Eigen::Matrix<ScalarType,vec_dim,1> cur_ev_;
                for(int i = 0; i < dim_size; i++) {
                    vec_ev[j][i] = jsonObject[i][j].get<ScalarType>();
                }
            }
            return;
        };

    }
}




#endif //MONOLANEMAPPINGINTERFACE_JSON_TRANSFORM_H
