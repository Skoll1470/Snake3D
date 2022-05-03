#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <future>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;

#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/texture.hpp>

#include "Transform.cpp"

vec3 vide=vec3(0.0,0.0,0.0);

Transform transVide=Transform();

class Object{

private:

public:

	std::vector<std::vector<unsigned short> > triangles;
	std::vector<float> uv;

	Object* parent;
	glm::mat4 model;
	std::vector<Transform> parentTransforms;
	vec3 barycentre;

	char* texture_name;

	GLuint programmID;
	GLuint texture;
	GLuint textureID;

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;

	Transform* transform;
	glm::vec3* relativParent;

	int useHeightmap;
	GLuint heightmap;
	GLuint heightmapID;

	// Constructeur
	Object(){
		transform=&transVide;
		relativParent=&vide;
	}

	Object(std::vector<unsigned short> i, std::vector<glm::vec3> iv, std::vector<float> u, std::vector<std::vector<unsigned short> > tr, Transform* t, Object* p, vec3* rp, char* filename){

		indices=i;
		indexed_vertices=iv;
		uv=u;
		triangles=tr;
		transform=t;
		parent=p;
		model=glm::mat4(1.0f);

		relativParent=rp;
		for(unsigned int i=0;i<parent->parentTransforms.size();i++){
			parentTransforms.push_back(parent->parentTransforms[i]);
		}

		calculBarycentre();

		texture_name = filename;

		programmID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");
    	texture = loadBMP_custom(texture_name);
    	textureID = glGetUniformLocation(programmID,"textureSampler");
    	heightmap = loadBMP_custom("hmap_mountain.bmp");
    	heightmapID = glGetUniformLocation(programmID,"heightmap");
    	useHeightmap=0;
	}

	Object(std::vector<unsigned short> i, std::vector<glm::vec3> iv, std::vector<float> u, std::vector<std::vector<unsigned short> > tr, Transform* t, Object* p, vec3* rp, char* filename, char* hm){

		indices=i;
		indexed_vertices=iv;
		uv=u;
		triangles=tr;
		transform=t;
		parent=p;
		model=glm::mat4(1.0f);

		relativParent=rp;
		for(unsigned int i=0;i<parent->parentTransforms.size();i++)
			parentTransforms.push_back(parent->parentTransforms[i]);
		
		calculBarycentre();

		texture_name=filename;
		programmID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");
    	texture = loadBMP_custom(texture_name);
    	textureID = glGetUniformLocation(programmID,"textureSampler");
    	heightmap = loadBMP_custom(hm);
    	heightmapID = glGetUniformLocation(programmID,"heightmap");
    	useHeightmap=1;
	}

	// Update de l'objet
	void update(){
		
		parent->transform->applyToVector(*relativParent);
		transform->applyToModel(model,*this->relativParent+*parent->relativParent,barycentre);	
	}

	// Dessine l'objet
	void draw(){

		// Load vertex buffer
		GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

        // Generate a buffer for the indices as well
        GLuint elementbuffer;
        glGenBuffers(1, &elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

       	GLuint uvbuffer;
    	glGenBuffers(1,&uvbuffer);
    	glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
    	glBufferData(GL_ARRAY_BUFFER,uv.size()*sizeof(float),&uv[0],GL_STATIC_DRAW);

    	glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

        glUniform1i(glGetUniformLocation(programmID,"useHeightmap"),useHeightmap);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(textureID, 0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        // Draw the triangles !
        glDrawElements(
            GL_TRIANGLES,      // mode
            indices.size(),    // count
            GL_UNSIGNED_SHORT,   // type
            (void*)0           // element array buffer offset
            );

        glDeleteBuffers(1,&uvbuffer);
        glDeleteBuffers(1,&vertexbuffer);
        glDeleteBuffers(1,&elementbuffer);
	}

	// Retourne le model
	glm::mat4 getModel(){
		return model;
	}

	// Ajoute une texture
	void setTexture(char* filename){
		texture_name=filename;
	}

	// Calcul des uv d'une sphère
	void calculUVSphere(){
		uv.clear();
		for(unsigned int i=0;i<indexed_vertices.size();i++){
			vec3 n= normalize(indexed_vertices[i]-barycentre);
			float u = std::atan2(n[0],n[2])/(float)(2*M_PI)+0.5;
			float v = n[1]*0.5+0.5;
			uv.push_back(u);
			uv.push_back(v);
		}
	}

	// Calcul du barycentre
	void calculBarycentre(){
		this->barycentre=vec3(0.0f);
		for(int i=0; i < indexed_vertices.size(); i++)
			this->barycentre += indexed_vertices[i];
		
		this->barycentre /= (float) indexed_vertices.size();
	}

};

class ObjectSnake : public Object {

private:

public :

	int rank;

	ObjectSnake() : Object(){

	}

	ObjectSnake(std::vector<unsigned short> i, std::vector<glm::vec3> iv, std::vector<float> u, std::vector<std::vector<unsigned short> > tr, Transform* t, Object* p, vec3* rp, char* filename, int r) : Object(i,iv, u, tr, t, p, rp, filename){
		rank=r;
	}

};


class Collider {

private :

public :

	vec3 points[4];

	Collider(){
		for(int i=0;i<4;i++){
			points[i]=vec3(0.f,0.f,0.f);
		}
	}

	void updateCollider(Object &o){
		float minX=o.indexed_vertices[0][0];
		float minY=o.indexed_vertices[0][1];
		float maxX=o.indexed_vertices[0][0];
		float maxY=o.indexed_vertices[0][1];

		for(int i=1;i<o.indexed_vertices.size();i++){
			if(o.indexed_vertices[i][0]<minX){
				minX=o.indexed_vertices[i][0];	
			}

			if(o.indexed_vertices[i][1]<minY){
				minY=o.indexed_vertices[i][1];	
			}

			if(o.indexed_vertices[i][0]>maxX){
				maxX=o.indexed_vertices[i][0];	
			}

			if(o.indexed_vertices[i][1]>maxY){
				maxY=o.indexed_vertices[i][1];	
			}
		}

		points[0]=(o.transform->m[1] * vec3(minX,minY,0.f)) + o.transform->newt + *o.relativParent;
		points[1]=(o.transform->m[1] * vec3(maxX,minY,0.f)) + o.transform->newt + *o.relativParent;
		points[2]=(o.transform->m[1] * vec3(maxX,maxY,0.f)) + o.transform->newt + *o.relativParent;
		points[3]=(o.transform->m[1] * vec3(minX,maxY,0.f)) + o.transform->newt + *o.relativParent; 
	}

	bool isColliding(Collider &c){
		bool res=false;
		for(int i=0;i<4;i++){
			if(points[0][0]<=c.points[i][0] and points[2][0]>=c.points[i][0] and points[0][1]<=c.points[i][1] and points[2][1]>=c.points[i][1]){
				res=true;
				break;
			}
		}
		return res;
	}

};