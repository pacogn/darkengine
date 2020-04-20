#include "Stars.h"
//-------------------------------------
#include <engine/CWindow.h>
//-------------------------------------
#include <Core/utils/pathUtils.h>
//-------------------------------------
#include <stdlib.h>
#include <time.h>
#include <engine/CSceneManager.h>
//-------------------------------------
#define kWidth      800
#define kHeight     600
#define kDepth      1024
#define kNumStars   512

//-------------------------------------
int
main(int, char* argv[]) {
    // Initialize stuff
    srand((unsigned)time(nullptr));
    SetApplicationDirectory(argv);

    CWindow win("Stars", kWidth, kHeight, WF_RESIZABLE);
    Stars   stars(&win, kNumStars, kDepth);
    win.Run();

    return 0;
}