#ifndef DATAREADER_H
#define DATAREADER_H

#include <QVector>
#include <QGLWidget>
#include "datastruct.h"

class dataReader
{
public:
    dataReader();
    bool readMesh(QString aPath);
    int getDataSize();
    MeshCell getMeshCell(int i);

private:
    QVector<MeshCell> mMesh;
};

#endif // DATAREADER_H
