#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/texture.hpp>
#include "tools/Object.cpp"
#include "tools/Shader.h"
#include <typeinfo>


GLFWwindow* window;

using namespace glm;

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 camera_position   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//rotation
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

bool isPressed = false;

int resolution = 19;
int size = 25;

ObjectSnake snakeBody[256];

Collider colliders[512];

bool debug = true;

float snakeSpeed=0.1;

int maxRank=1;

bool gameOver = false;

std::vector<float> mouvements;
Transform snakeTransforms[256];
vec3 snakeRP[256];

std::vector<Object*> GDS;

Object null = Object();

struct Light {
    vec3 position;
    vec3 color;
}; 

Light light;



void setLight(){
    light.position;
    light.color = vec3 (300, 300, 300);
}

//mise à jour du mouvement et des rotations des parties du corps
void updateSnake(){
    for(int i=maxRank;i>=1;i--){
        mouvements[i]=mouvements[i-1];
    }
    for(int i=0;i<=maxRank;i++){
        mat3 rot = mat3(vec3(cos(mouvements[i]), sin(mouvements[i]), 0.0), vec3(-sin(mouvements[i]), cos(mouvements[i]), 0.0), vec3(0.0, 0.0, mouvements[i]));
        mat3 rot2=mat3(vec3(cos(snakeBody[i].transform->newangle), sin(snakeBody[i].transform->newangle), 0.0), vec3(-sin(snakeBody[i].transform->newangle), cos(snakeBody[i].transform->newangle), 0.0), vec3(0.0, 0.0, snakeBody[i].transform->newangle));                    
        snakeBody[i].transform->m[0] = vec3(0.f,0.f,snakeSpeed);
        snakeBody[i].transform->angle = mouvements[i];
        snakeBody[i].transform->t = rot2*vec3(snakeSpeed,0.f,0.f);
        *snakeBody[i].relativParent = rot2*vec3(-0.9*i,0.f,0.f);
    }
}

// Fonction qui permet de créer la surface.
void createSurface(std::vector<unsigned short>& indices,std::vector<glm::vec3>& indexed_vertices, std::vector<float>& uv, float step){
    
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

void createMurV(std::vector<unsigned short>& indices_mur, std::vector<vec3>& indexed_vertices_mur){
    indices_mur.clear();
    indexed_vertices_mur.clear();

    indices_mur.push_back(0);
    indices_mur.push_back(1);
    indices_mur.push_back(2);
    indices_mur.push_back(2);
    indices_mur.push_back(3);
    indices_mur.push_back(0);

    indices_mur.push_back(3);
    indices_mur.push_back(2);
    indices_mur.push_back(6);
    indices_mur.push_back(6);
    indices_mur.push_back(7);
    indices_mur.push_back(3);

    indices_mur.push_back(0);
    indices_mur.push_back(1);
    indices_mur.push_back(5);
    indices_mur.push_back(5);
    indices_mur.push_back(4);
    indices_mur.push_back(0);

    indices_mur.push_back(2);
    indices_mur.push_back(1);
    indices_mur.push_back(5);
    indices_mur.push_back(5);
    indices_mur.push_back(6);
    indices_mur.push_back(2);

    indices_mur.push_back(0);
    indices_mur.push_back(3);
    indices_mur.push_back(7);
    indices_mur.push_back(7);
    indices_mur.push_back(4);
    indices_mur.push_back(0);

    indices_mur.push_back(4);
    indices_mur.push_back(5);
    indices_mur.push_back(6);
    indices_mur.push_back(6);
    indices_mur.push_back(7);
    indices_mur.push_back(4);

    indexed_vertices_mur.push_back(vec3(-1.f,-1.f,0.f));
    indexed_vertices_mur.push_back(vec3(0.f,-1.f,0.f));
    indexed_vertices_mur.push_back(vec3(0.f,-1.f,2.f));
    indexed_vertices_mur.push_back(vec3(-1.f,-1.f,2.f));

    indexed_vertices_mur.push_back(vec3(-1.f,size-1,0.f));
    indexed_vertices_mur.push_back(vec3(0.f,size-1,0.f));
    indexed_vertices_mur.push_back(vec3(0.f,size-1,2.f));
    indexed_vertices_mur.push_back(vec3(-1.f,size-1,2.f));
}

void createMurH(std::vector<unsigned short>& indices_mur, std::vector<vec3>& indexed_vertices_mur){
    indices_mur.clear();
    indexed_vertices_mur.clear();

    indices_mur.push_back(0);
    indices_mur.push_back(1);
    indices_mur.push_back(2);
    indices_mur.push_back(2);
    indices_mur.push_back(3);
    indices_mur.push_back(0);

    indices_mur.push_back(3);
    indices_mur.push_back(2);
    indices_mur.push_back(6);
    indices_mur.push_back(6);
    indices_mur.push_back(7);
    indices_mur.push_back(3);

    indices_mur.push_back(0);
    indices_mur.push_back(1);
    indices_mur.push_back(5);
    indices_mur.push_back(5);
    indices_mur.push_back(4);
    indices_mur.push_back(0);

    indices_mur.push_back(2);
    indices_mur.push_back(1);
    indices_mur.push_back(5);
    indices_mur.push_back(5);
    indices_mur.push_back(6);
    indices_mur.push_back(2);

    indices_mur.push_back(0);
    indices_mur.push_back(3);
    indices_mur.push_back(7);
    indices_mur.push_back(7);
    indices_mur.push_back(4);
    indices_mur.push_back(0);

    indices_mur.push_back(4);
    indices_mur.push_back(5);
    indices_mur.push_back(6);
    indices_mur.push_back(6);
    indices_mur.push_back(7);
    indices_mur.push_back(4);

    indexed_vertices_mur.push_back(vec3(-1.f,0.f,0.f));
    indexed_vertices_mur.push_back(vec3(-1.f,-1.f,0.f));
    indexed_vertices_mur.push_back(vec3(-1.f,-1.f,2.f));
    indexed_vertices_mur.push_back(vec3(-1.f,0.f,2.f));

    indexed_vertices_mur.push_back(vec3(size-1,0.f,0.f));
    indexed_vertices_mur.push_back(vec3(size-1,-1.f,0.f));
    indexed_vertices_mur.push_back(vec3(size-1,-1.f,2.f));
    indexed_vertices_mur.push_back(vec3(size-1,0.f,2.f));
}

int main( void )
{
    GDS.clear();
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "SNAKE 3D", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Hide the mouse and enable unlimited mouvement
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    //glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    Shader shader("vertex_shader.glsl", "fragment_shader.glsl");
    shader.use();

    //shader.setVec3("albedo", 0.5f, 0.0f, 0.0f);
    shader.setFloat("ao", 1.0f);

    shader.use();

    // Chargement des 3 meshs selon la distance
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<std::vector<unsigned short> > triangles;
    std::string filename("modele_snake/head.off");
    loadOFF(filename, indexed_vertices, indices, triangles);


    std::vector<unsigned short> indices_body; //Triangles concaténés dans une liste
    std::vector<glm::vec3> indexed_vertices_body;
    loadOFF("modele_snake/body.off", indexed_vertices_body, indices_body, triangles);

    std::vector<unsigned short> indices_tail; //Triangles concaténés dans une liste
    std::vector<glm::vec3> indexed_vertices_tail;
    loadOFF("modele_snake/tail.off", indexed_vertices_tail, indices_tail, triangles);

    std::vector<unsigned short> indices_fruit; //Triangles concaténés dans une liste
    std::vector<glm::vec3> indexed_vertices_fruit;
    loadOFF("modele_snake/fruit.off", indexed_vertices_fruit, indices_fruit, triangles);

    std::vector<unsigned short> indices_headDead; //Triangles concaténés dans une liste
    std::vector<glm::vec3> indexed_vertices_headDead;
    loadOFF("modele_snake/headDead.off", indexed_vertices_headDead, indices_headDead, triangles);    

    std::vector<unsigned short> indices_surface;
    std::vector<glm::vec3> indexed_vertices_surface;
    std::vector<float> uv_surface;
    createSurface(indices_surface,indexed_vertices_surface,uv_surface,size/(float)resolution);

    mat3 m = glm::mat3(vec3(0.0f,0.0f,0.0f),vec3(1.0f,1.0f,1.0f),vec3(0.0f,0.0f,0.0f));
    vec3 t = glm::vec3(0.0,0.0f,0.0f);
    Transform trans1=Transform();

    mat3 mSurface = glm::mat3(vec3(0.0,1.0,0.0),vec3(1.0,1.0,1.0),vec3(1.0f));
    Transform transSurface = Transform(mSurface,t,0.f,0.f);
    
    vec3 rp1 = vec3(0.0f,0.0f,0.0f);
    Object surface = Object(indices_surface, indexed_vertices_surface, uv_surface, triangles, &transSurface, &null, &rp1, "tex_grass.bmp", "hmap_defaut.bmp");
    GDS.push_back(&surface);


    Transform transFruit=Transform(mSurface,t,0.f,0.f);
    Object fruit = Object(indices_fruit,indexed_vertices_fruit,uv_surface,triangles, &transFruit, &null, &rp1, "cherries-text.bmp");
    fruit.calculUVSphere();
    fruit.transform->newt=vec3(size - (size/4.f), size/2.f, 0.f);
    GDS.push_back(&fruit);
    

    std::vector<unsigned short> indices_murV;
    std::vector<vec3> indexed_vertices_murV;

    createMurV(indices_murV,indexed_vertices_murV);

    Object murG = Object(indices_murV,indexed_vertices_murV,uv_surface,triangles,&transSurface,&null,&rp1,"tex_rock.bmp");
    murG.calculUVSphere();
    GDS.push_back(&murG);

    Transform transMurD=Transform(mSurface,t,0.f,0.f);
    Object murD = Object(indices_murV,indexed_vertices_murV,uv_surface,triangles,&transMurD,&null,&rp1,"tex_rock.bmp");
    murD.calculUVSphere();
    murD.transform->newt=vec3(size-1,0.f,0.f);
    GDS.push_back(&murD);

    std::vector<unsigned short> indices_murH;
    std::vector<vec3> indexed_vertices_murH;

    createMurH(indices_murH,indexed_vertices_murH);

    Object murB = Object(indices_murH,indexed_vertices_murH,uv_surface,triangles,&transSurface,&null,&rp1,"tex_rock.bmp");
    murB.calculUVSphere();
    GDS.push_back(&murB);

    Transform transMurH=Transform(mSurface,t,0.f,0.f);
    Object murH = Object(indices_murH,indexed_vertices_murH,uv_surface,triangles,&transMurH,&null,&rp1,"tex_rock.bmp");
    murH.calculUVSphere();
    murH.transform->newt=vec3(0.f,size-1,0.f);
    GDS.push_back(&murH);

    mat3 m2 = glm::mat3(vec3(0.0f,-1.0f,0.0f),vec3(0.5f,0.5f,0.5f),vec3(.0f,0.0f,1.0f));
    Transform trans2 = Transform(m2, vec3(0.f,0.f,0.f), 0.f, 0.f);
    snakeTransforms[0]=trans2;
    snakeTransforms[1]=trans2;

    snakeRP[0]=rp1;
    ObjectSnake snake = ObjectSnake(indices, indexed_vertices, uv_surface, triangles, &snakeTransforms[0], &null, &rp1, "text_test2.bmp",0);
    snake.calculUVSphere();

    vec3 rp2 = vec3(-0.9f,0.0f,0.0f);
    snakeRP[1]=rp2;

    ObjectSnake snake2 = ObjectSnake(indices_body, indexed_vertices_body, uv_surface, triangles, &snakeTransforms[1], &null, &snakeRP[1], "text_test2.bmp",1);
    snake2.calculUVSphere();
    snakeBody[0]=snake;
    snakeBody[1]=snake2;

    //création du corps de départ
    for(int i=0;i<1;i++){
        maxRank++;
        snakeTransforms[maxRank]=trans2;
        snakeRP[maxRank]=vec3(-0.9*maxRank,0.f,0.f);
        ObjectSnake snake3 = ObjectSnake(indices_tail, indexed_vertices_tail, uv_surface, triangles, &snakeTransforms[maxRank], &null, &snakeRP[maxRank], "text_test2.bmp",maxRank);
        snake3.calculUVSphere();
        snakeBody[maxRank]=snake3;
    }    
    

    for(int i=0;i<=maxRank;i++){
        GDS.push_back(&snakeBody[i]);
        mouvements.push_back(0.f);
        snakeBody[i].transform->newt=vec3(0 + (size/4.f), size/2.f, 0.f);
    }
    camera_position = snake.transform->newt + vec3(0.,0., 20. + maxRank) * vec3(0.,0.,1.);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(shader.ID);
    GLuint LightID = glGetUniformLocation(shader.ID, "LightPosition_worldspace");

    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    setLight();
    int nbCeriseGraille = 0;

    do{
        if(!debug){
            nbFrames++;
        }
        // Measure speed
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----

        for(int i=0;i<maxRank;i++){
            //GDS[i].transform->m[0]=vec3(0.f);
            snakeBody[i].transform->angle=0.f;
        }

        mouvements[0]=0.f;

        processInput(window);

        updateSnake();

        if(debug){
            for(int i=0;i<=maxRank;i++){
                snakeBody[i].transform->t=vec3(0.f);
            }
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(shader.ID);

        // Change de mesh selon la distance
        unsigned int grapheSize = GDS.size();

        // Dessin et update du graphe de scenes
        for(unsigned int i = 0; i < grapheSize; i++){

            colliders[i].updateCollider(*GDS[i]);

            GDS[i]->update();

            if(i==6){
                //ajout de partie du corps
                if(colliders[1].isColliding(colliders[6])){
                    maxRank++;

                    mat3 rot=mat3(vec3(cos(snakeBody[maxRank-1].transform->newangle), sin(snakeBody[maxRank-1].transform->newangle), 0.0), vec3(-sin(snakeBody[maxRank-1].transform->newangle), cos(snakeBody[maxRank-1].transform->newangle), 0.0), vec3(0.0, 0.0, snakeBody[maxRank-1].transform->newangle));
                    snakeTransforms[maxRank]=trans2;
                    mouvements.push_back(mouvements[maxRank-1]);
                    ObjectSnake snake3 = ObjectSnake(indices_tail, indexed_vertices_tail, uv_surface, triangles, &snakeTransforms[maxRank], &null, &snakeRP[maxRank], "text_test2.bmp",maxRank);
                    snake3.calculUVSphere();
                    snake3.transform->newangle=snakeBody[maxRank-1].transform->newangle;
                    snake3.transform->t=rot*vec3(snakeSpeed,0.f,0.f);
                    snake3.transform->newt=snakeBody[maxRank-1].transform->newt;
                    snake3.transform->m[0]=snakeBody[maxRank-1].transform->m[0];
                    snakeBody[maxRank]=snake3;
                    GDS.push_back(&snakeBody[maxRank]);
                    nbFrames=0;

                    snakeBody[maxRank-1].indices=indices_body;
                    snakeBody[maxRank-1].indexed_vertices=indexed_vertices_body;
                    snakeBody[maxRank-1].calculUVSphere();

                    float randomX = 1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(size-3)));
                    float randomY = 1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(size-3)));
                    GDS[1]->transform->newt=vec3(randomX,randomY,0.f);  
                    nbCeriseGraille++;
                    std::cout << "Ta graille " << nbCeriseGraille << " cerises mon reuf" << std::endl;

                }

                for(int j=2;j<6;j++){
                    if(colliders[j].isColliding(colliders[6])){
                        debug=true;
                        for(int i=0;i<=maxRank;i++){
                            snakeBody[i].transform->t=vec3(0.f,0.f,0.f);
                        }
                        snakeBody[0].indices=indices_headDead;
                        snakeBody[0].indexed_vertices=indexed_vertices_headDead;
                        gameOver = true;
                        //std::cout<<"PERDU"<<std::endl;
                    }
                }
            }

            if(i>6){
                if(colliders[2].isColliding(colliders[i])){
                    //snakeBody[i-6].transform
                }
            }

            // MVP
            mat4 model = GDS[i]->getModel();
            if(i==1){
            	model = glm::translate(model,vec3(0.0,0.0,0.8));

            }
            shader.setMat4("model",model);

            mat4 view = glm::lookAt(camera_position, camera_position + camera_target, camera_up);

            // Rotation
            view = glm::rotate(view, angleX, glm::vec3(1,0,0));
            view = glm::rotate(view, angleY, glm::vec3(0,1,0));
            view = glm::rotate(view, angleZ, glm::vec3(0,0,1));
            shader.setMat4("view", view);


            mat4 projection = glm::perspective<float>(glm::radians(45.0f), 4.0f / 3.0f, 1.f, 100.f);
            shader.setMat4("projection", projection);


            mat4 mvp =  projection * view * model;
            GLuint mvpID = glGetUniformLocation(shader.ID, "mvp");

            glUniformMatrix4fv(mvpID,1,GL_FALSE, &mvp[0][0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,GDS[i]->heightmap);
            glUniform1i(GDS[i]->heightmapID,1);

            // Check si on touche quand on déplace
            shader.setVec3("camPos",camera_position);

            shader.use();

            shader.setVec3("lightPosition", light.position);
            shader.setVec3("lightColor", light.color);
            shader.setVec3("barycentre", GDS[i]->barycentre + GDS[i]->transform->newt);

            if(i > 5){
                shader.setBool("isSphere", true);
            }
            else shader.setBool("isSphere", false);
        

            GDS[i]->draw();

            if(!debug)
             	camera_position = snake.transform->newt + vec3(0.,0., 20. + maxRank);
            
            light.position = vec3(size,size,0.1);

        }
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();   
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
	    debug = true;
		for(int i=0;i<=maxRank;i++){
            snakeBody[i].transform->t=vec3(0.f,0.f,0.f);
        }
	}
    
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && !gameOver){
    	debug = false;
        for(int i=0;i<=maxRank;i++){
            snakeBody[i].transform->t=vec3(snakeSpeed,0.f,0.f);
        }
    }
    		

    // Debug mode
    if(debug){

    	// Caméra mouvement
    	float cameraSpeed = 2.5 * deltaTime;
	    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	        camera_position += cameraSpeed * camera_target;
	    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	        camera_position -= cameraSpeed * camera_target;

	    //rotation grosse chaise
	    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	        angleX -= 0.05 ; 
	    
	    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	        angleX += 0.05;
	    
	    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	        angleY -= 0.05 ; 
	    
	    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	        angleY += 0.05;

	    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	        angleZ -= 0.05 ; 
	    
	    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	        angleZ += 0.05;

	    //add translations
	    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	        camera_position -= glm::normalize(glm::cross(camera_target, camera_up)) * cameraSpeed;

	    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	        camera_position += glm::normalize(glm::cross(camera_target, camera_up)) * cameraSpeed;

	    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	        camera_position -= camera_up * cameraSpeed;

	    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	        camera_position += camera_up * cameraSpeed; 
    }
    else if(!gameOver){

        mat3 rot;
        float rad=snakeSpeed;

    	// Déplacement du serpent
	    
	    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
	    {
	        mouvements[0]=rad;
            //sleep(1);
	    }
	    
	    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
	    {
	        mouvements[0]=-rad;
	    }
	    
	    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS)
	        for(int i=0;i<=maxRank;i++){
                snakeBody[i].transform->t=vec3(0.f,0.f,0.f);
            }
    }
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
