#include "Asteroids.h"
//-------------------------------------
#include <engine/CWindow.h>
//-------------------------------------
#include <Core/utils/pathUtils.h>
//-------------------------------------
// #include <stdlib.h>
// #include <time.h>
// #include <engine/CSceneManager.h>
//-------------------------------------

#include <CRendererAsteroids.h>

#define kWidth      800
#define kHeight     600
#define kDepth      1024
#define kNumStars   512

//-------------------------------------
int
main(int, char* argv[]) {
    srand((unsigned)time(nullptr));
    SetApplicationDirectory(argv);

    CWindow win("Asteroids", kWidth, kHeight, WF_FULLSCREEN_DESKTOP, new CRendererAsteroids(kWidth, kHeight));
    Asteroids asteroids(&win);
    win.Run();

    return 0;
}