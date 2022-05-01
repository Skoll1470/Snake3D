#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertices_position_modelspace;
layout(location = 1) in vec2 vertexUV;
uniform sampler2D heightmap;
uniform int useHeightmap;

out vec2 UV;

uniform mat4 mvp;
out float z;

uniform float x;
uniform float y;

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
}

