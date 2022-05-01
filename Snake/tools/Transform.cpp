#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

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
#include <cmath>

class Transform{

	public:

		mat3 m;

		vec3 t;
		vec3 newt;

		float angle=0.01;
		float newangle=0.01;

		float scew=0.0;

		// Constructeur
		Transform(){
			m = glm::mat3(vec3(1.0,0.0,0.0),vec3(1.0,1.0,1.0),vec3(1.0f));
			t = glm::vec3(0.0f,0.0f,0.0f);
			newt = t;
			angle = 0.0;
			newangle = 0.0;
		}

		Transform(mat3 M, vec3 T, float a, float s){
			m = M;
			t = T;
			newt = T;
			angle = a;
			newangle = angle;
			scew = s;
		}

		// Applique une transformation à un point
		vec3 applyToPoint(vec3 p, mat4 &model){
			return p + t;
		}

		// Applique une transformation au model
		void applyToModel(mat4 &model, vec3 rp, vec3 bary){

			model = glm::mat4(1.0f);

			model = glm::translate(model,newt);

			model = glm::translate(model,rp);

			model = glm::translate(model,-bary);
			model = glm::rotate(model,radians(scew),m[2]);
			model = glm::translate(model,bary);

			model = glm::rotate(model,newangle, m[0]);

			model = glm::scale(model,m[1]);

			newangle += angle;
			newt += t;
		}

		// Applique une transformation à un vecteur
		void applyToVector(vec3 &v){
			mat3 rot;
			float rad = angle;

			if(m[0][0] != 0){
				rot = mat3(vec3(m[0][0], 0.0, 0.0), vec3(0.0, cos(rad), sin(rad)), vec3(0.0, -sin(rad), cos(rad)));
				v = rot * v;
			}
			if(m[0][1] != 0){
				rot = mat3(vec3(cos(rad), 0.0, -sin(rad)), vec3(0.0, m[0][1], 0.0), vec3(sin(rad), 0.0, cos(rad)));
				v=rot*v;
			}
			if(m[0][2]!=0){
				rot = mat3(vec3(cos(rad), sin(rad), 0.0), vec3(-sin(rad), cos(rad), 0.0), vec3(0.0, 0.0, m[0][2]));
				v = rot * v;
			}

			//v+=t;
		}

		void addT(vec3 T){
			t = t + T;
		}

		void addM(mat3 M){
			m[0] = m[0] + M[0];
			m[1] = m[1] * M[1];
			m[2] = m[2] + M[2];
		}

		void setT(vec3 vec){
			t = vec;
		}

};


