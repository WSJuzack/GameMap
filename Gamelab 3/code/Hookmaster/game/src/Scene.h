#pragma once

#include "Game.h"
#include "forward.h"

namespace gl3
{
    class Scene {
    public:
        Scene(Game* game);
        ~Scene();

        [[nodiscard]] const int getLevelIndex() { return m_levelIndex; }

        void setupLevelFromIndex(int index);

    protected:
        int m_levelIndex;
        Game* m_game;

    private:

        void setupTutorial();
        void setupLevelOne();
        void setupLevelTwo();
        void setupLevelThree();
    };
}
