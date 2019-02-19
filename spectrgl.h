#ifndef SPECTRGL_H
#define SPECTRGL_H

#include <QtOpenGL>
#include "mainwindow.h"

class spectrGL : public QGLWidget
{
public:
    explicit spectrGL(QWidget *parent = 0);
    ~spectrGL();
    void setHandleToMainWindow(MainWindow *aMainWindow);
    void getMesh(dataReader aData);
    float getMinData();
    float getMaxData();

    void setDrawMesh(bool aState);
    void setMouseTrackSt(bool aState);
    void update();

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

    void mouseMoveEvent(QMouseEvent* pe);
    float getZCoord(int x, int y);

    void drawSpectrogram(CVertex3 *quadVertexArray, CColor3 *quadColorArray, CFace *quadIndexArray);
    void drawMesh();
    void drawText();

private:
    void calcEdgeXYcoords();

private:
    QVector<MeshCell> mSpectrData;
    float mMinX;
    float mMinY;
    float mMaxX;
    float mMaxY;
    float mMinData;
    float mMaxData;
    int mVertexNum;
    bool mDrawMesh;

    bool mMouseTrack;
    QPointF mMovePoint;

    MainWindow *mMainWindow;
};

#endif // SPECTRGL_H
