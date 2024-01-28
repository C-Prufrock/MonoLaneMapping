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
        void from_json( const nlohmann::json& jsonObject, Eigen::Matrix< ScalarType, rows, cols >& matrix )
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

    }
}




#endif //MONOLANEMAPPINGINTERFACE_JSON_TRANSFORM_H
