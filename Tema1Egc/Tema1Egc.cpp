//
// Created by Crina Gherase on 02.11.2022.
//

#include "Tema1Egc.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1Egc//transform2D.h"
#include "lab_m1/Tema1Egc/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1Egc::Tema1Egc()
{
}


Tema1Egc::~Tema1Egc()
{
}

void Tema1Egc::Init()
{
    //window->HidePointer();
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    aux = 0;
    auxx = 0;
    cout<<resolution.y << "\n";
    cout<<resolution.x << "\n";
    aimX = resolution.x / 2;
    aimY = resolution.y / 2;
    rectangleCenterX = 131.25;
    rectangleCenterY = 0;
    cx = atan(2.3/5);
    ducks = 1;
    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;
    bulletsNo = 3;
    timeOnScreen = 0;
    // Initialize sx and sy (the scale factors)
    a = 5;
    b = 2.3;
    score = 0;
    lives = 3;
    // Initialize angularStep
    angularStep = 5;
    dead = false;
    Mesh* circle = object2D::DrawCircle("circle", 60);
    AddMeshToList(circle);
    Mesh* body =  object2D::CreateTriangle("body", glm::vec3(0, 0,0), glm::vec3(7, 2,0), glm::vec3(7, -2,0), glm::vec3(0.5f,0.3f,0.07f));
    AddMeshToList(body);
    Mesh* frame =  object2D::CreateRectangle("frame", glm::vec3(-1.75, -3,0), 8.75, 6,glm::vec3(1,1,1), false);
    AddMeshToList(frame);
    Mesh* beak =  object2D::CreateTriangle("beak", glm::vec3(-1.75, 0,0), glm::vec3(-1, -0.5,0), glm::vec3(-1, 0.5,0), glm::vec3(0.82f,0.74f,0.047f));
    AddMeshToList(beak);
    Mesh* wing1 =  object2D::CreateTriangle("wing1", glm::vec3(0, 0,0), glm::vec3(2, 0,0), glm::vec3(1.5, 3,0), glm::vec3(0.5f,0.3f,0.07f));
    AddMeshToList(wing1);
    Mesh* wing2 =  object2D::CreateTriangle("wing2", glm::vec3(0, 0,0), glm::vec3(2, 0,0), glm::vec3(1.5, -3,0), glm::vec3(0.5f,0.3f,0.07f));
    AddMeshToList(wing2);
    Mesh* grass =  object2D::CreateRectangle("grass", glm::vec3(0, 0,0), 100, 10,glm::vec3(0.10f,0.52f,0.15f), true);
    AddMeshToList(grass);
    Mesh* bullet =  object2D::CreateRectangle("bullet", glm::vec3(0, 0,0), 30, 80,glm::vec3(1,0,0), true);
    AddMeshToList(bullet);
    Mesh* score =  object2D::CreateRectangle("score", glm::vec3(0, 0,0), 700, 60,glm::vec3(1,1,1), false);
    AddMeshToList(score);
    Mesh* scoreFill =  object2D::CreateRectangle("scoreFill", glm::vec3(0, 0,0), 1, 60,glm::vec3(1,1,1), true);
    AddMeshToList(scoreFill);
    Mesh* aim1 = object2D::CreateRectangle("aim1", glm::vec3(-15 ,-5, 0), 40, 10, glm::vec3(1,1,1), true);
    AddMeshToList(aim1);
    Mesh* aim2 = object2D::CreateRectangle("aim2", glm::vec3(-5 ,-15,0), 10, 40, glm::vec3(1,1,1), true);
    AddMeshToList(aim2);
}


void Tema1Egc::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.67f, 0.81f, 0.91f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1Egc::Update(float deltaTimeSeconds)
{
    angularStep += deltaTimeSeconds * 1.5;
    if(angularStep >= 0.8)
        angularStep -= 0.8;
    glm::ivec2 resolution = window->GetResolution();
    meshes["circle"] ->SetDrawMode(GL_TRIANGLE_FAN);
    modelMatrix = glm::mat3(1);
    modelMatrixWing1 = glm::mat3(1);
    modelMatrixWing2 = glm::mat3(1);
    timeOnScreen += deltaTimeSeconds;
    if(timeOnScreen > 20 || bulletsNo < 1){
        dead = 2;
    }
    if(dead == 0) {
        //duck is alive
        if(translateX * 50 > resolution.x - 20){
            aux = 1;
            cx = M_PI -  cx;
        }
        else
            if(translateX * 50 < 0){
                aux = 0;
                cx = M_PI -  cx;
            }
        if(translateY * 50 > resolution.y -20){
            auxx = 1;
            cx = 2 * (M_PI) - cx;
        }
        else
            if(translateY * 50 < 0){
                auxx = 0;
                cx = 2 * (M_PI) - cx;
            }

        if(aux == 1)
        {
            translateX -= deltaTimeSeconds * 5 * (ducks+1/2);
        }
        else{
            translateX += deltaTimeSeconds * 5* (ducks+1/2);
        }
        if(auxx == 1)
        {
            translateY -= deltaTimeSeconds * 2.3* (ducks+1/2);
        }
        else{
            translateY += deltaTimeSeconds * 2.3* (ducks+1/2);
        }
        modelMatrix *= transform2D::Scale(50, 50);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Rotate(cx);
        modelMatrix *= transform2D::Rotate(M_PI);

        modelMatrixWing1 *= transform2D::Scale(50, 50);
        modelMatrixWing1 *= transform2D::Translate(translateX, translateY);
        modelMatrixWing1 *= transform2D::Rotate(cx + M_PI);
        modelMatrixWing1 *= transform2D::Translate(-translateX, -translateY);
        modelMatrixWing1 *= transform2D::Translate(translateX + 3, translateY);
        modelMatrixWing1 *= transform2D::Rotate(-angularStep);

        modelMatrixWing2 *= transform2D::Scale(50, 50);
        modelMatrixWing2 *= transform2D::Translate(translateX, translateY);
        modelMatrixWing2 *= transform2D::Rotate(cx + M_PI);
        modelMatrixWing2 *= transform2D::Translate(-translateX, -translateY);
        modelMatrixWing2 *= transform2D::Translate(translateX + 3, translateY);
        modelMatrixWing2 *= transform2D::Rotate(angularStep);
    }
    else if(dead == 1){
            //duck is dead
            translateY -= deltaTimeSeconds * 5;
            modelMatrix *= transform2D::Scale(50, 50);
            modelMatrix *= transform2D::Translate(translateX, translateY);
            modelMatrix *= transform2D::Rotate(M_PI / 2);

            modelMatrixWing1 *= transform2D::Scale(50, 50);
            modelMatrixWing1 *= transform2D::Translate(translateX, translateY);
            modelMatrixWing1 *= transform2D::Rotate(M_PI / 2);
            modelMatrixWing1 *= transform2D::Translate(-translateX, -translateY);
            modelMatrixWing1 *= transform2D::Translate(translateX + 3, translateY);
            modelMatrixWing1 *= transform2D::Rotate(-angularStep);

            modelMatrixWing2 *= transform2D::Scale(50, 50);
            modelMatrixWing2 *= transform2D::Translate(translateX, translateY);
            modelMatrixWing2 *= transform2D::Rotate(M_PI / 2);
            modelMatrixWing2 *= transform2D::Translate(-translateX, -translateY);
            modelMatrixWing2 *= transform2D::Translate(translateX + 3, translateY);
            modelMatrixWing2 *= transform2D::Rotate(angularStep);
        }
        else{
            //duck is escaping
            translateY += deltaTimeSeconds * 9;
            modelMatrix *= transform2D::Scale(50, 50);
            modelMatrix *= transform2D::Translate(translateX, translateY);
            modelMatrix *= transform2D::Rotate(-M_PI / 2);

            modelMatrixWing1 *= transform2D::Scale(50, 50);
            modelMatrixWing1 *= transform2D::Translate(translateX, translateY);
            modelMatrixWing1 *= transform2D::Rotate(-M_PI / 2);
            modelMatrixWing1 *= transform2D::Translate(3, 0);

            modelMatrixWing2 *= transform2D::Scale(50, 50);
            modelMatrixWing2 *= transform2D::Translate(translateX, translateY);
            modelMatrixWing2 *= transform2D::Rotate(-M_PI / 2);
            modelMatrixWing2 *= transform2D::Translate(3, 0);
        }
    if(translateY * 50 > resolution.y + 200 && lives > 0)
    {
        timeOnScreen = 0;
        bulletsNo = 3;
        lives--;
        dead = 0;
        translateX = 0;
        translateY = 0;
        cx = atan(2.3/5);
        ducks++;
    }
    if(translateY * 50 < -10 )
    {
        timeOnScreen = 0;
        bulletsNo = 3;
        dead = 0;
        translateX = 0;
        translateY = 0;
        cx = atan(2.3/5);
        ducks++;
    }
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], glm::mat3(1) * transform2D::Scale(50,20));
    RenderMesh2D(meshes["aim1"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(aimX,aimY));
    RenderMesh2D(meshes["aim2"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(aimX,aimY));
    //draw the lives, bullets and the level
    if(lives > 0)
    {
        RenderMesh2D(meshes["circle"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(35,1400) * transform2D::Scale(30,30));
        if(lives > 1){
            RenderMesh2D(meshes["circle"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(105,1400) * transform2D::Scale(30,30));
            if(lives > 2)
                RenderMesh2D(meshes["circle"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(175,1400) * transform2D::Scale(30,30));
        }
    }
    if(bulletsNo > 0)
    {
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(25,1270));
        if(bulletsNo > 1){
            RenderMesh2D(meshes["bullet"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(95,1270));
            if(bulletsNo > 2)
                RenderMesh2D(meshes["bullet"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(165,1270));
        }
    }
    RenderMesh2D(meshes["score"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(1800,1350));
    RenderMesh2D(meshes["scoreFill"], shaders["VertexColor"], glm::mat3(1) * transform2D::Translate(1800,1350) * transform2D::Scale(score, 1));
    //draw the duck
    RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["wing1"], shaders["VertexColor"], modelMatrixWing1);
    RenderMesh2D(meshes["wing2"], shaders["VertexColor"], modelMatrixWing2);
    }


void Tema1Egc::FrameEnd()
{
}

void Tema1Egc::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1Egc::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1Egc::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1Egc::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    aimX = mouseX * 2;
    aimY = (720- mouseY) * 2 ;
}


void Tema1Egc::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_2 && bulletsNo > -100){
        bulletsNo--;
        coss = cos(cx + M_PI);
        ssin = sin(cx + M_PI);
        if(aux == 0)
            rectangleCenterX -= 131.25;
        glm::ivec2 resolution = window->GetResolution();
        float r1x = -218.5 * coss - 150 * ssin;
        float r1y = -218.5 * ssin + 150 * coss;
        float r2x =  218.5 * coss - 150 * ssin;
        float r2y =  218.5 * ssin + 150 * coss;
        float Px = mouseX * 2;
        float Py = (resolution.y/2 -mouseY) * 2;
        float Ax = rectangleCenterX + r1x + translateX * 50;
        float Ay = rectangleCenterY + r1y + translateY * 50;
        float Bx = rectangleCenterX + r2x + translateX * 50;
        float By = rectangleCenterY + r2y + translateY * 50;
        float Cx = rectangleCenterX - r1x + translateX * 50;
        float Cy = rectangleCenterY - r1y + translateY * 50;
        float Dx = rectangleCenterX - r2x + translateX * 50;
        float Dy = rectangleCenterY - r2y + translateY * 50;
        if(((Dx - Ax)*(Py - Ay) - (Px - Ax)*(Dy - Ay)) >= 0
            && ((Cx - Dx)*(Py - Dy) - (Px - Dx)*(Cy - Dy)) >= 0
            && ((Bx - Cx)*(Py - Cy) - (Px - Cx)*(By - Cy)) >= 0
            && ((Ax - Bx)*(Py - By) - (Px - Bx)*(Ay - By)) >= 0
            && score <= 600){
            score +=100;
            dead = 1;
        }
            else cout <<"NU";
        cout<<'\n';
        if(aux == 0)
            rectangleCenterX += 131.25;
    }
}


void Tema1Egc::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1Egc::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1Egc::OnWindowResize(int width, int height)
{
}
