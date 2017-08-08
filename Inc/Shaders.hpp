#pragma once

#include "base.hpp"

class Shaders
{
    private:
        GLuint program_id;
        GLuint vertex_id;
        GLuint fragment_id;
        int num_attr;

        void compile(const std::string &file_path, GLuint &tmp_id);

    public:

        Shaders();
        ~Shaders();

        GLuint GetProgramID() const;

        void compile_shaders(const std::string &vertexfile_path, const std::string &fragmentfile_path);
        void link_shaders();
        GLint UnifromLocation(const std::string& Uniform_name);
        void add_attributes(const std::string &attr_name);
        void use_prog();
        void unuse_prog();
};
