#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;
layout(location = 1) in vec2 vertexUV;
uniform sampler2D heightmap;
uniform int useHeightmap;

out vec2 UV;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 mvp;
uniform bool isSphere;

uniform float x;
uniform float y;
uniform vec3 barycentre;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

void main(){

        vec4 Position = vec4(vertices_position_modelspace,1);

        if(useHeightmap == 1){
                //Position.z = -texture(heightmap, vertexUV).r;
        }
        else{
                //Position.z += -texture(heightmap, vec2(x,y)).r * 10 + 1.05;
        }

        gl_Position = mvp * Position;

        UV = vertexUV;

        TexCoords = vertexUV;
        WorldPos = vec3(model * vec4(vertices_position_modelspace, 1.0));

        if(isSphere){
                Normal = -(vertices_position_modelspace - barycentre) ;     
        }
        else{
                Normal =  mat3(model) * WorldPos;
        }

}

