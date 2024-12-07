#include "triangle.h"
#include "constants.cpp"

void triangle::Draw(color _color, bool isWireFrame)
{
/*    glColor3f(_color.r, _color.g, _color.b);
    glBegin(GL_TRIANGLES);
    glVertex3f(a.x, a.y, 0.0);
    glVertex3f(b.x, b.y, 0.0);
    glVertex3f(c.x, c.y, 0.0);
    glEnd();*/

    size_t n_vertices = 3;
    vita2d_color_vertex *vertices = (vita2d_color_vertex *)vita2d_pool_memalign(
			n_vertices * sizeof(vita2d_color_vertex),
			sizeof(vita2d_color_vertex));

    vertices[0].x = a.x;
    vertices[0].y = a.y;
    vertices[0].z = 0;
    vertices[0].color = RGBA8(_color.r, _color.g, _color.b, 0xff);
    vertices[1].x = b.x;
    vertices[1].y = b.y;
    vertices[1].z = 0;
    vertices[1].color = RGBA8(_color.r, _color.g, _color.b, 0xff);
    vertices[2].x = c.x;
    vertices[2].y = c.y;
    vertices[2].z = 0;
    vertices[2].color = RGBA8(_color.r, _color.g, _color.b, 0xff);
    vita2d_draw_array(SCE_GXM_PRIMITIVE_TRIANGLES, vertices, n_vertices);

    if (!isWireFrame)
        return;

    vita2d_draw_line(a.x, a.y, b.x, b.y, RGBA8(0, 0, 0, 255));
    vita2d_draw_line(c.x, c.y, b.x, b.y, RGBA8(0, 0, 0, 255));
    vita2d_draw_line(a.x, a.y, c.x, c.y, RGBA8(0, 0, 0, 255));
    /*glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    // a -> b
    glVertex3f(a.x, a.y, 0.0);
    glVertex3f(b.x, b.y, 0.0);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    // b -> c
    glVertex3f(b.x, b.y, 0.0);
    glVertex3f(c.x, c.y, 0.0);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    // c -> a
    glVertex3f(c.x, c.y, 0.0);
    glVertex3f(a.x, a.y, 0.0);
    glEnd();*/
}