#ifndef MYTRIANGLE_H
#define MYTRIANGLE_H

#include "point.h"
#include <vita2d.h>
#include "color.h"

class triangle
{
    public:
        point a;
        point b;
        point c;

        triangle()
        {
            this->a = point();
            this->b = point();
            this->c = point();
        }

        triangle(point a, point b, point c)
        {
            this->a = a;
            this->b = b;
            this->c = c;
        }

        void Draw(color _color, bool isWireFrame = false);

        point MidA()
        {
            return point((a.x + b.x) / 2, (a.y + b.y) / 2);
        }

        point MidB()
        {
            return point((b.x + c.x) / 2, (b.y + c.y) / 2);
        }

        point MidC()
        {
            return point((a.x + c.x) / 2, (a.y + c.y) / 2);
        }
};

#endif