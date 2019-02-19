#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <QPointF>
#include <qwt_color_map.h>

struct MeshCell
{
    MeshCell():p1(QPointF(0, 0))
     , p2(QPointF(0, 0))
     , p3(QPointF(0, 0))
     , p4(QPointF(0, 0))
     , data(0)
    {};

    QPointF p1;
    QPointF p2;
    QPointF p3;
    QPointF p4;

    float data;
};

struct CFace{
  GLuint v1, v2, v3, v4;
};

struct CVertex3{
    GLfloat x, y, z;
};

struct CColor3{
    GLfloat r, g, b;
};

class ColorMap: public QwtLinearColorMap
{
public:
    ColorMap():
        QwtLinearColorMap( Qt::blue, Qt::red )
    {
        addColorStop( 0.2, Qt::cyan );
        addColorStop( 0.55, Qt::green );
        addColorStop( 0.85, Qt::yellow );
    }
};

#endif // DATASTRUCT_H
