#pragma once

#include "base.hpp"

class Object_Loader
{
    private:


    public:

        void fill_data( std::vector < std::string > &data, const std::string &line);
        void seperate_face_data( std::vector < std::string > &data, const std::string &line);
        std::string trim( std::string line );
        void Load_Object( const std::string &obj_path );
};
