#include <QFile>
#include "datareader.h"
#include <QDebug>

dataReader::dataReader()
{
}

bool dataReader::readMesh(QString aPath)
{
    QFile fileIn(aPath);
    MeshCell tmp;
    mMesh.clear();
    int dataCounter = 100;

    if(fileIn.open(QIODevice::ReadOnly))
    {
        while(!fileIn.atEnd())
        {
            QString str = fileIn.readLine();
            tmp.p1.setX(str.toFloat());
            str = fileIn.readLine();
            tmp.p1.setY(str.toFloat());
            str = fileIn.readLine();
            tmp.p2.setX(str.toFloat());
            str = fileIn.readLine();
            tmp.p2.setY(str.toFloat());
            str = fileIn.readLine();
            tmp.p3.setX(str.toFloat());
            str = fileIn.readLine();
            tmp.p3.setY(str.toFloat());
            str = fileIn.readLine();
            tmp.p4.setX(str.toFloat());
            str = fileIn.readLine();
            tmp.p4.setY(str.toFloat());

            tmp.data = dataCounter+=2;

            mMesh.push_back(tmp);
        }
        return true;
    }
    else
    {
        qDebug()<< "can't open file";
        return false;
    }
}

int dataReader::getDataSize()
{
    return mMesh.size();
}

MeshCell dataReader::getMeshCell(int i)
{
    if(mMesh.isEmpty() != true && i < mMesh.size())
        return mMesh.at(i);
    else
        return MeshCell();
}
