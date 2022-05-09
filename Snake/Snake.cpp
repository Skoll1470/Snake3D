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
#include "tools/MapObject.cpp"
#include "tools/UI.cpp"

GLFWwindow* window;

using namespace glm;

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 camera_position   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 camera_target     = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up         = glm::vec3(0.0f, 1.0f,  0.0f);

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

float snakeSpeed = 0.1;

int maxRank = 1;

bool gameOver = false;
bool menuPlay = true;
bool quit = false;

std::vector<float> mouvements;
Transform snakeTransforms[256];
vec3 snakeRP[256];

std::vector<Object*> GDS;

Object null = Object();

struct Light {
    vec3 position;
    vec3 color;

    void setLight(){
        color = vec3 (300, 300, 300);
    }
}; 

Light light;

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

    // Set the mouse at the center of the screen
    glfwPollEvents();

    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    Shader shader("vertex_shader.glsl", "fragment_shader.glsl");
    shader.use();

    shader.setFloat("ao", 1.0f);

    shader.use();

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

    MapObject mpsurface = MapObject();
    mpsurface.createSurface(size/(float) resolution, resolution);

    mat3 m = glm::mat3(vec3(0.0f,0.0f,0.0f),vec3(1.0f,1.0f,1.0f),vec3(0.0f,0.0f,0.0f));
    vec3 t = glm::vec3(0.0,0.0f,0.0f);
    Transform trans1=Transform();

    mat3 mSurface = glm::mat3(vec3(0.0,1.0,0.0),vec3(1.0,1.0,1.0),vec3(1.0f));
    Transform transSurface = Transform(mSurface,t,0.f,0.f);
    
    vec3 rp1 = vec3(0.0f,0.0f,0.0f);
    Object surface = Object(mpsurface.indices, mpsurface.indexed_vertices, mpsurface.uv, triangles, &transSurface, &null, &rp1, "textures/tex_grass.bmp", "textures/hmap_defaut.bmp");
    GDS.push_back(&surface);

    Transform transFruit=Transform(mSurface,t,0.f,0.f);
    Object fruit = Object(indices_fruit,indexed_vertices_fruit,mpsurface.uv,triangles, &transFruit, &null, &rp1, "textures/cherries-textBis.bmp");
    fruit.calculUVSphere();
    fruit.transform->newt=vec3(size - (size/4.f), size/2.f, 0.f);
    GDS.push_back(&fruit);

    MapObject mpmurV = MapObject();
    mpmurV.createMurV(size);

    Object murG = Object(mpmurV.indices,mpmurV.indexed_vertices,mpsurface.uv,triangles,&transSurface,&null,&rp1,"textures/tex_rock.bmp");
    murG.calculUVSphere();
    GDS.push_back(&murG);

    Transform transMurD=Transform(mSurface,t,0.f,0.f);
    Object murD = Object(mpmurV.indices,mpmurV.indexed_vertices,mpsurface.uv,triangles,&transMurD,&null,&rp1,"textures/tex_rock.bmp");
    murD.calculUVSphere();
    murD.transform->newt=vec3(size-1,0.f,0.f);
    GDS.push_back(&murD);

    MapObject mpmurH = MapObject();
    mpmurH.createMurH(size);

    Object murB = Object(mpmurH.indices,mpmurH.indexed_vertices,mpsurface.uv,triangles,&transSurface,&null,&rp1,"textures/tex_rock.bmp");
    murB.calculUVSphere();
    GDS.push_back(&murB);

    Transform transMurH=Transform(mSurface,t,0.f,0.f);
    Object murH = Object(mpmurH.indices,mpmurH.indexed_vertices,mpsurface.uv,triangles,&transMurH,&null,&rp1,"textures/tex_rock.bmp");
    murH.calculUVSphere();
    murH.transform->newt=vec3(0.f,size-1,0.f);
    GDS.push_back(&murH);

    UI UImenu = UI();

    UImenu.createMenu();

    Transform transMenu = Transform(mSurface,t,0.f,0.f);
    Object menu = Object(UImenu.indices,UImenu.indexed_vertices,UImenu.uv,triangles,&transMenu,&null,&rp1,"textures/play-menu.bmp");
    GDS.push_back(&menu);

    UI UIscore = UI();
    UIscore.createScoreElement();
    Transform transScoreCerise = Transform(mSurface,t,0.f,0.f);
    Object scoreCerise = Object(UIscore.indices,UIscore.indexed_vertices,UIscore.uv,triangles,&transScoreCerise,&null,&rp1,"textures/cerise.bmp");
    GDS.push_back(&scoreCerise);
    scoreCerise.transform->m[1]=vec3(0.5,0.5,0.5);

    Transform transScoreUnit = Transform(mSurface,t,0.f,0.f);
    Object scoreUnit = Object(UIscore.indices,UIscore.indexed_vertices,UIscore.uv,triangles,&transScoreUnit,&null,&rp1,"textures/chiffres/0.bmp");
    GDS.push_back(&scoreUnit);
    scoreUnit.transform->m[1]=vec3(0.5,0.5,0.5);

    Transform transScoreDiz = Transform(mSurface,t,0.f,0.f);
    Object scoreDiz = Object(UIscore.indices,UIscore.indexed_vertices,UIscore.uv,triangles,&transScoreDiz,&null,&rp1,"textures/chiffres/0.bmp");
    GDS.push_back(&scoreDiz);
    scoreDiz.transform->m[1]=vec3(0.5,0.5,0.5);

    Transform transScoreCent = Transform(mSurface,t,0.f,0.f);
    Object scoreCent = Object(UIscore.indices,UIscore.indexed_vertices,UIscore.uv,triangles,&transScoreCent,&null,&rp1,"textures/chiffres/0.bmp");
    GDS.push_back(&scoreCent);
    scoreCent.transform->m[1]=vec3(0.5,0.5,0.5);

    mat3 m2 = glm::mat3(vec3(0.0f,-1.0f,0.0f),vec3(0.5f,0.5f,0.5f),vec3(.0f,0.0f,1.0f));
    Transform trans2 = Transform(m2, vec3(0.f,0.f,0.f), 0.f, 0.f);
    snakeTransforms[0]=trans2;
    snakeTransforms[1]=trans2;

    snakeRP[0]=rp1;
    ObjectSnake snake = ObjectSnake(indices, indexed_vertices, mpsurface.uv, triangles, &snakeTransforms[0], &null, &rp1, "textures/text_test2.bmp",0);
    snake.calculUVSphere();

    vec3 rp2 = vec3(-0.9f,0.0f,0.0f);
    snakeRP[1]=rp2;

    ObjectSnake snake2 = ObjectSnake(indices_body, indexed_vertices_body, mpsurface.uv, triangles, &snakeTransforms[1], &null, &snakeRP[1], "textures/text_test2.bmp",1);
    snake2.calculUVSphere();
    snakeBody[0]=snake;
    snakeBody[1]=snake2;

    //création du corps de départ
    for(int i=0;i<1;i++){
        maxRank++;
        snakeTransforms[maxRank]=trans2;
        snakeRP[maxRank]=vec3(-0.9*maxRank,0.f,0.f);
        ObjectSnake snake3 = ObjectSnake(indices_tail, indexed_vertices_tail, mpsurface.uv, triangles, &snakeTransforms[maxRank], &null, &snakeRP[maxRank], "textures/text_test2.bmp",maxRank);
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

    // Initialisation de la lumière
    light.setLight();

    do{
        if(!debug){

            // on enleve le menu
            menu.transform->newt=vec3(-30,-30,-30);

            // on position le score
            scoreCerise.transform->newt = camera_position - vec3(-1.f,-0.5,2.7*4.f/3.f);
            scoreUnit.transform->newt = camera_position - vec3(-0.75,-0.5,2.7*4.f/3.f);
            scoreDiz.transform->newt = camera_position - vec3(-0.5,-0.5,2.7*4.f/3.f);
            scoreCent.transform->newt = camera_position - vec3(-0.25,-0.5,2.7*4.f/3.f);

            // on place la lumière
            light.position = vec3(size,size,0.1);
        }
        else{

            // Position du menu
            menu.transform->newt = camera_position - vec3(0.f,0.f,2.7*4.f/3.f);

            //position de la lumière pour le menu
            light.position = camera_position + vec3(0.f,0.f,7.5);    
        }

        for(int i=0;i<maxRank;i++){
            snakeBody[i].transform->angle=0.f;
        }

        mouvements[0]=0.f;

        processInput(window);

        updateSnake();

        if(debug or gameOver){
            for(int i=0;i<=maxRank;i++){
                snakeBody[i].transform->t=vec3(0.f);
            }
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(shader.ID);

        unsigned int grapheSize = GDS.size();

        // Dessin et update du graphe de scenes
        for(unsigned int i = 0; i < grapheSize; i++){

            colliders[i].updateCollider(*GDS[i]);

            GDS[i]->update();

            if(i==11){
                //ajout de partie du corps
                if(colliders[1].isColliding(colliders[11])){
                    maxRank++;

                    mat3 rot=mat3(vec3(cos(snakeBody[maxRank-1].transform->newangle), sin(snakeBody[maxRank-1].transform->newangle), 0.0), vec3(-sin(snakeBody[maxRank-1].transform->newangle), cos(snakeBody[maxRank-1].transform->newangle), 0.0), vec3(0.0, 0.0, snakeBody[maxRank-1].transform->newangle));
                    snakeTransforms[maxRank]=trans2;
                    mouvements.push_back(mouvements[maxRank-1]);
                    ObjectSnake snake3 = ObjectSnake(indices_tail, indexed_vertices_tail, mpsurface.uv, triangles, &snakeTransforms[maxRank], &null, &snakeRP[maxRank], "textures/text_test2.bmp",maxRank);
                    snake3.calculUVSphere();
                    snake3.transform->newangle=snakeBody[maxRank-1].transform->newangle;
                    snake3.transform->t=rot*vec3(snakeSpeed,0.f,0.f);
                    snake3.transform->newt=snakeBody[maxRank-1].transform->newt;
                    snake3.transform->m[0]=snakeBody[maxRank-1].transform->m[0];
                    snakeBody[maxRank]=snake3;
                    GDS.push_back(&snakeBody[maxRank]);

                    snakeBody[maxRank-1].indices=indices_body;
                    snakeBody[maxRank-1].indexed_vertices=indexed_vertices_body;
                    snakeBody[maxRank-1].calculUVSphere();

                    float randomX = 1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(size-3)));
                    float randomY = 1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(size-3)));
                    GDS[1]->transform->newt=vec3(randomX,randomY,0.f);

                    std::string path = "textures/chiffres/"+std::to_string((maxRank-2)%10)+".bmp";
                    scoreUnit.loadTexture(path.c_str());
                    path = "textures/chiffres/"+std::to_string(((maxRank-2)%100)/10)+".bmp";
                    scoreDiz.loadTexture(path.c_str());
                    path = "textures/chiffres/"+std::to_string((maxRank-2)/100)+".bmp";
                    scoreCent.loadTexture(path.c_str());
                    snakeSpeed+=0.002;    
                }

                for(int j=2;j<6;j++){
                    if(colliders[j].isColliding(colliders[11])){
                        for(int i=0;i<=maxRank;i++){
                            snakeBody[i].transform->t=vec3(0.f,0.f,0.f);
                        }
                        snakeBody[0].indices=indices_headDead;
                        snakeBody[0].indexed_vertices=indexed_vertices_headDead;
                        gameOver = true;
                        camera_position = snake.transform->newt + vec3(0.f,0.f,10.f);
                    }
                }
            }

            // MVP
            mat4 model = GDS[i]->getModel();
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

            shader.setVec3("camPos",camera_position);

            shader.use();

            shader.setVec3("lightPosition", light.position);
            shader.setVec3("lightColor", light.color);
            shader.setVec3("barycentre", GDS[i]->barycentre + GDS[i]->transform->newt);

            if(i > 6){
                shader.setBool("isSphere", true);
            }
            else shader.setBool("isSphere", false);
        
            GDS[i]->draw();

            if(!debug and !gameOver)
             	camera_position = snake.transform->newt + vec3(0.,0., 20. + maxRank);
            
        }
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();   
    } // Check if the ESC key was pressed or the window was closed
    while( !quit &&
           glfwWindowShouldClose(window) == 0);

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

	    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
	        GDS[6]->loadTexture("textures/play-menu.bmp");
            menuPlay=true;
        }

	    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
	        GDS[6]->loadTexture("textures/quit-menu.bmp");
            menuPlay=false;
        }

        if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
            if(menuPlay){
                debug = false;
                for(int i=0;i<=maxRank;i++){
                    snakeBody[i].transform->t=vec3(snakeSpeed,0.f,0.f);
                }
            }
            else{
                quit=true;
            } 
        }
    }
    else if(!gameOver){ // Si on a pas perdu
        mat3 rot;
        float rad=snakeSpeed;

    	// Déplacement du serpent
	    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
	    {
	        mouvements[0]=rad;
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
