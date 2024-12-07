#include "triangle.h"
#include "random.h"
#include <vector>
#include <ctime>
#include "constants.cpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#define CHECK_BIN(x) ((pad.buttons & x) && (!(old_buttons & x)))

int criteria1 = -10;
int criteria2 = 30;
int countOfRecursive = 0;

bool isWireFrame = false;

std::vector<triangle> triangles;
std::vector<triangle> secTriangles;

void DrawLines()
{
    for (int i = 0; i < secTriangles.size(); i++)
        secTriangles[i].Draw(color(119, 58, 0));
    for (int i = 0; i < triangles.size(); i++)
        if (i % 2 == 0)
            triangles[i].Draw(color(28, 89, 0), isWireFrame);
        else if (i % 3 == 0)
            triangles[i].Draw(color(20, 110, 0), isWireFrame);
        else
            triangles[i].Draw(color(35, 158, 0), isWireFrame);
}

void ClearScene()
{
    triangles.clear();
    triangles.push_back(triangle(point(Range(0, 960), Range(0, 544)), point(Range(0, 960), Range(0, 544)), point(Range(0, 960), Range(0, 544))));

    countOfRecursive = 0;

    secTriangles = std::vector<triangle>();
}

int Fluctuate(int a)
{
    return a - (Range(criteria1, criteria2));
}

void Divide()
{
    int num = 0;

    point a, a1;
    point b, b1;
    point c, c1;

    std::vector<triangle> temp(triangles.size() * 4, triangle());

    for(int i = 0; i < triangles.size(); i++)
    {
        a = triangles[i].MidA();
        a1 = point(a.x, Fluctuate(a.y));
        b = triangles[i].MidB();
        b1 = point(b.x, Fluctuate(b.y));
        c = triangles[i].MidC();
        c1 = point(c.x, Fluctuate(c.y));

        num = i * 4;
        temp[num] = triangle(triangles[i].a, a1, c1);
        temp[num + 1] = triangle(triangles[i].b, b1, a1);
        temp[num + 2] = triangle(triangles[i].c, c1, b1);
        temp[num + 3] = triangle(a1, b1, c1);

        secTriangles.push_back(triangle(triangles[i].a, a1, triangles[i].b));
        secTriangles.push_back(triangle(triangles[i].b, b1, triangles[i].c));
        secTriangles.push_back(triangle(triangles[i].c, c1, triangles[i].a));
    }

    triangles = temp;

    temp.clear();
}

void Generate()
{
    if (countOfRecursive < 6)
    {
        Divide();
        countOfRecursive++;
    }
}

int main()
{
    srand(time(NULL));

    uint32_t old_buttons = 0;
    vita2d_pgf *pvf;

    ClearScene();

    vita2d_init();
	vita2d_set_clear_color(RGBA8(0x00, 0x9B, 0xCE, 0xFF));
    pvf = vita2d_load_default_pgf();
/*
    vglInit(0x800000);

    glClearColor(0.0f, 0.61f, 0.81f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/

    SceCtrlData pad;
    memset(&pad, 0, sizeof(pad));

    while (1)
    {
        sceCtrlPeekBufferPositive(0, &pad, 1);
       // glClear(GL_COLOR_BUFFER_BIT);

        vita2d_start_drawing();
		vita2d_clear_screen();

        DrawLines();

        vita2d_pgf_draw_text(pvf, 10, 30, RGBA8(255,255,255,255), 1.0f, "Made by JaKeN");
        vita2d_pgf_draw_textf(pvf, 10, 50, RGBA8(255,255,255,255), 1.0f, "First criteria: %d", criteria1);
        vita2d_pgf_draw_textf(pvf, 10, 70, RGBA8(255,255,255,255), 1.0f, "Second criteria: %d", criteria2);

        if (CHECK_BIN(SCE_CTRL_CROSS))
            Generate();
        if (CHECK_BIN(SCE_CTRL_CIRCLE))
            ClearScene();
        if (CHECK_BIN(SCE_CTRL_TRIANGLE))
            isWireFrame = !isWireFrame;

        criteria1 += CHECK_BIN(SCE_CTRL_UP) ? 1 : (CHECK_BIN(SCE_CTRL_DOWN) ? -1 : 0);
        criteria2 += CHECK_BIN(SCE_CTRL_RIGHT) ? 1 : (CHECK_BIN(SCE_CTRL_LEFT) ? -1 : 0);
       // vglSwapBuffers(GL_FALSE);

        vita2d_end_drawing();
		vita2d_swap_buffers();
        old_buttons = pad.buttons;
    }

    vita2d_fini();
    vita2d_free_pgf(pvf);
//    vglEnd();
    sceKernelExitProcess(0);
	return 0;
}