// permet de créer les formes pour la carte
class MapObject{

	public :

		std::vector<unsigned short> indices;
		std::vector<vec3> indexed_vertices;
		std::vector<float> uv;

		MapObject(){
		}

		// Fonction qui permet de créer la surface.
		void createSurface(float step, float resolution){
		    
		    indices.clear();
		    uv.clear();
		    indexed_vertices.clear();

		    int nbSommets = resolution;

		    srand(time(NULL));

		    for (int i = 0; i < nbSommets-1; ++i){
		        for (int j = 0; j < nbSommets-1; ++j)
		        {
		            indices.push_back(i * nbSommets + j);
		            indices.push_back(i * nbSommets+ j + 1);
		            indices.push_back((i+1) * nbSommets + j);

		            indices.push_back(i* nbSommets + j + 1);
		            indices.push_back((i+1) * nbSommets + j + 1);
		            indices.push_back((i+1) * nbSommets + j);
		        }
		    }

		    for(int i = 0; i < nbSommets; i++){
		        for(int j = 0; j < nbSommets; j++){
		            indexed_vertices.push_back(glm::vec3((float)j*step,(float)i*step,0 ));

		            uv.push_back((float)j/(nbSommets-1));
		            uv.push_back((float)i/(nbSommets-1));
		        }
		    }
		}

		void createMurV(float size){
		    indices.clear();
		    indexed_vertices.clear();

		    indices.push_back(0);
		    indices.push_back(1);
		    indices.push_back(2);
		    indices.push_back(2);
		    indices.push_back(3);
		    indices.push_back(0);

		    indices.push_back(3);
		    indices.push_back(2);
		    indices.push_back(6);
		    indices.push_back(6);
		    indices.push_back(7);
		    indices.push_back(3);

		    indices.push_back(0);
		    indices.push_back(1);
		    indices.push_back(5);
		    indices.push_back(5);
		    indices.push_back(4);
		    indices.push_back(0);

		    indices.push_back(2);
		    indices.push_back(1);
		    indices.push_back(5);
		    indices.push_back(5);
		    indices.push_back(6);
		    indices.push_back(2);

		    indices.push_back(0);
		    indices.push_back(3);
		    indices.push_back(7);
		    indices.push_back(7);
		    indices.push_back(4);
		    indices.push_back(0);

		    indices.push_back(4);
		    indices.push_back(5);
		    indices.push_back(6);
		    indices.push_back(6);
		    indices.push_back(7);
		    indices.push_back(4);

		    indexed_vertices.push_back(vec3(-1.f,-1.f,0.f));
		    indexed_vertices.push_back(vec3(0.f,-1.f,0.f));
		    indexed_vertices.push_back(vec3(0.f,-1.f,2.f));
		    indexed_vertices.push_back(vec3(-1.f,-1.f,2.f));

		    indexed_vertices.push_back(vec3(-1.f,size-1,0.f));
		    indexed_vertices.push_back(vec3(0.f,size-1,0.f));
		    indexed_vertices.push_back(vec3(0.f,size-1,2.f));
		    indexed_vertices.push_back(vec3(-1.f,size-1,2.f));
		}

		void createMurH(float size){
		    indices.clear();
		    indexed_vertices.clear();

		    indices.push_back(0);
		    indices.push_back(1);
		    indices.push_back(2);
		    indices.push_back(2);
		    indices.push_back(3);
		    indices.push_back(0);

		    indices.push_back(3);
		    indices.push_back(2);
		    indices.push_back(6);
		    indices.push_back(6);
		    indices.push_back(7);
		    indices.push_back(3);

		    indices.push_back(0);
		    indices.push_back(1);
		    indices.push_back(5);
		    indices.push_back(5);
		    indices.push_back(4);
		    indices.push_back(0);

		    indices.push_back(2);
		    indices.push_back(1);
		    indices.push_back(5);
		    indices.push_back(5);
		    indices.push_back(6);
		    indices.push_back(2);

		    indices.push_back(0);
		    indices.push_back(3);
		    indices.push_back(7);
		    indices.push_back(7);
		    indices.push_back(4);
		    indices.push_back(0);

		    indices.push_back(4);
		    indices.push_back(5);
		    indices.push_back(6);
		    indices.push_back(6);
		    indices.push_back(7);
		    indices.push_back(4);

		    indexed_vertices.push_back(vec3(-1.f,0.f,0.f));
		    indexed_vertices.push_back(vec3(-1.f,-1.f,0.f));
		    indexed_vertices.push_back(vec3(-1.f,-1.f,2.f));
		    indexed_vertices.push_back(vec3(-1.f,0.f,2.f));

		    indexed_vertices.push_back(vec3(size-1,0.f,0.f));
		    indexed_vertices.push_back(vec3(size-1,-1.f,0.f));
		    indexed_vertices.push_back(vec3(size-1,-1.f,2.f));
		    indexed_vertices.push_back(vec3(size-1,0.f,2.f));
		}
};