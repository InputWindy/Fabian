#include "OpenGLRHIStruct.h"
#include <glad.h>

#include <iostream>

using std::cout;

void printProgramResources(GLuint program) {
    GLint numActiveAttribs, numActiveUniforms, numActiveUniformBlocks;
    glGetProgramInterfaceiv(program, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms);//查询普通Uniform类型，包括image2d，sampler2d
    
    glGetProgramInterfaceiv(program, GL_ATOMIC_COUNTER_BUFFER, GL_ATOMIC_COUNTER_BUFFER, &numActiveAttribs);//查询atomic counter buffer类型

    glGetProgramInterfaceiv(program, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);//查询varying,varying已经被淘汰了，现在用in\out
    glGetProgramInterfaceiv(program, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);//查询varying,varying已经被淘汰了，现在用in\out

    //查询Subroutine
    glGetProgramInterfaceiv(program, GL_VERTEX_SUBROUTINE, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_TESS_CONTROL_SUBROUTINE, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_TESS_EVALUATION_SUBROUTINE, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_GEOMETRY_SUBROUTINE, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_FRAGMENT_SUBROUTINE, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_COMPUTE_SUBROUTINE, GL_ACTIVE_RESOURCES, &numActiveAttribs);

    /*glGetProgramInterfaceiv(program, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);
    glGetProgramInterfaceiv(program, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);*/
    
    //transform feedback varying就是标记为out的变量，需要提前在c++代码里用 glTransformFeedbackVaryings 指定
    glGetProgramInterfaceiv(program, GL_TRANSFORM_FEEDBACK_VARYING, GL_ACTIVE_RESOURCES, &numActiveAttribs);

    glGetProgramInterfaceiv(program, GL_BUFFER_VARIABLE, GL_ACTIVE_RESOURCES, &numActiveAttribs);//ssbo和buffer block的总数
    glGetProgramInterfaceiv(program, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, &numActiveAttribs);//仅查询ssbo数量
    glGetProgramInterfaceiv(program, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &numActiveUniformBlocks);//仅查询ubo类型

    //transform feedback buffer可以在shader program里出现多次，捕获不同的数据
    glGetProgramInterfaceiv(program, GL_TRANSFORM_FEEDBACK_BUFFER, GL_ACTIVE_RESOURCES, &numActiveAttribs);

    

    

    std::cout << "Active Attributes:" << std::endl;
    for (int i = 0; i < numActiveAttribs; ++i) {
        GLsizei length;
        GLchar name[256];
        glGetProgramResourceName(program, GL_PROGRAM_INPUT, i, sizeof(name), &length, name);
        std::cout << "  " << name << std::endl;
    }

    std::cout << "Active Uniforms:" << std::endl;
    for (int i = 0; i < numActiveUniforms; ++i) {
        GLsizei length;
        GLchar name[256];
        glGetProgramResourceName(program, GL_UNIFORM, i, sizeof(name), &length, name);
        std::cout << "  " << name << std::endl;
    }

    std::cout << "Active Uniform Blocks:" << std::endl;
    for (int i = 0; i < numActiveUniformBlocks; ++i) {
        GLsizei length;
        GLchar name[256];
        glGetProgramResourceName(program, GL_UNIFORM_BLOCK, i, sizeof(name), &length, name);
        std::cout << "  " << name << std::endl;
    }
}