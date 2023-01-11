//
// Created by Crina Gherase on 02.11.2022.
//

#ifndef GFXFRAMEWORK_TEMA1EGC_H
#define GFXFRAMEWORK_TEMA1EGC_H

#endif //GFXFRAMEWORK_TEMA1EGC_H
#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1Egc : public gfxc::SimpleScene
    {
    public:
        Tema1Egc();
        ~Tema1Egc();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        float cx, coss, ssin;
        glm::mat3 modelMatrix;
        glm::mat3 modelMatrixWing1;
        glm::mat3 modelMatrixWing2;
        glm::mat3 modelMatrixAim;
        float translateX, translateY;
        float a,b;
        float angularStep;
        float rectangleCenterX, rectangleCenterY;
        int aux;
        int auxx;
        int ducks;
        float aimX;
        float aimY;
        int bulletsNo;
        int score;
        int dead;
        float timeOnScreen;
        int lives;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
