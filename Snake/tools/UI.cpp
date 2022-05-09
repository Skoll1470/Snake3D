// permet de créer les formes pour la carte
class UI{

	public :

		std::vector<unsigned short> indices;
		std::vector<vec3> indexed_vertices;
		std::vector<float> uv;

		UI(){
		}

		void createMenu(){
		    indices.clear();
		    indexed_vertices.clear();
		    uv.clear();

		    indices.push_back(0);
		    indices.push_back(1);
		    indices.push_back(2);
		    indices.push_back(2);
		    indices.push_back(3);
		    indices.push_back(0);

		    indexed_vertices.push_back(vec3(-2.f,-1.5,0.f));
		    indexed_vertices.push_back(vec3(2.f,-1.5,0.f));
		    indexed_vertices.push_back(vec3(2.f,1.5,0.f));
		    indexed_vertices.push_back(vec3(-2.f,1.5,0.f));

		    uv.push_back(0.f);
		    uv.push_back(0.f);

		    uv.push_back(1.f);
		    uv.push_back(0.f);

		    uv.push_back(1.f);
		    uv.push_back(1.f);

		    uv.push_back(0.f);
		    uv.push_back(1.f);
		}

		void createScoreElement(){
		    indices.clear();
		    indexed_vertices.clear();
		    uv.clear();

		    indices.push_back(0);
		    indices.push_back(1);
		    indices.push_back(2);
		    indices.push_back(2);
		    indices.push_back(3);
		    indices.push_back(0);

			indexed_vertices.push_back(vec3((2.0*3.0)/4.0,(1.5*3.0)/4.0,0.f));
    		indexed_vertices.push_back(vec3(2.0,(1.5*3.0)/4.0,0.f));
    		indexed_vertices.push_back(vec3(2.f,1.5,0.f));
    		indexed_vertices.push_back(vec3((2.0*3.0)/4,1.5,0.f));

		    uv.push_back(0.f);
		    uv.push_back(0.f);

		    uv.push_back(1.f);
		    uv.push_back(0.f);

		    uv.push_back(1.f);
		    uv.push_back(1.f);

		    uv.push_back(0.f);
		    uv.push_back(1.f);    
		}
};