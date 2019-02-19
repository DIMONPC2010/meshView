#include "spectrgl.h"

spectrGL::spectrGL(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
  , mVertexNum(0)
  , mMinX(0.0)
  , mMaxX(1.0)
  , mMinY(0.0)
  , mMaxY(1.0)
  , mDrawMesh(true)
  , mMouseTrack(false)
{
}

spectrGL::~spectrGL()
{

}

void spectrGL::setHandleToMainWindow(MainWindow *aMainWindow)
{
    mMainWindow = aMainWindow;
}


void spectrGL::getMesh(dataReader aData)
{
    if(!mSpectrData.isEmpty())
        mSpectrData.clear();

    for(int i = 0; i < aData.getDataSize(); i++)
    {
        mSpectrData.push_back(aData.getMeshCell(i));
    }

    mMinData = getMinData();
    mMaxData = getMaxData();

    calcEdgeXYcoords();

    mVertexNum = mSpectrData.size()*4;

    resizeGL(width(), height());
    updateGL();
}

void spectrGL::drawSpectrogram(CVertex3 *quadVertexArray, CColor3 *quadColorArray, CFace *quadIndexArray)
{
    QColor *color = new QColor();
    ColorMap *colormap = new ColorMap();

    int vertexCounter = 0;

    for(int i = 0; i < (int)(mVertexNum/4); i++)
    {
        quadVertexArray[vertexCounter].x = mSpectrData.at(i).p1.x();
        quadVertexArray[vertexCounter].y = mSpectrData.at(i).p1.y();
        quadVertexArray[vertexCounter].z = 0;

        *color = colormap->color(QwtInterval(mMinData, mMaxData), mSpectrData.at(i).data);
        quadColorArray[vertexCounter].r = color->redF();
        quadColorArray[vertexCounter].g = color->greenF();
        quadColorArray[vertexCounter].b = color->blueF();
        quadIndexArray[i].v1 = vertexCounter;
        vertexCounter++;

        quadVertexArray[vertexCounter].x = mSpectrData.at(i).p2.x();
        quadVertexArray[vertexCounter].y = mSpectrData.at(i).p2.y();
        quadVertexArray[vertexCounter].z = 0;

        *color = colormap->color(QwtInterval(mMinData, mMaxData), mSpectrData.at(i).data);
        quadColorArray[vertexCounter].r = color->redF();
        quadColorArray[vertexCounter].g = color->greenF();
        quadColorArray[vertexCounter].b = color->blueF();
        quadIndexArray[i].v2 = vertexCounter;
        vertexCounter++;

        quadVertexArray[vertexCounter].x = mSpectrData.at(i).p3.x();
        quadVertexArray[vertexCounter].y = mSpectrData.at(i).p3.y();
        quadVertexArray[vertexCounter].z = 0;

        *color = colormap->color(QwtInterval(mMinData, mMaxData), mSpectrData.at(i).data);
        quadColorArray[vertexCounter].r = color->redF();
        quadColorArray[vertexCounter].g = color->greenF();
        quadColorArray[vertexCounter].b = color->blueF();
        quadIndexArray[i].v3 = vertexCounter;
        vertexCounter++;

        quadVertexArray[vertexCounter].x = mSpectrData.at(i).p4.x();
        quadVertexArray[vertexCounter].y = mSpectrData.at(i).p4.y();
        quadVertexArray[vertexCounter].z = 0;

        *color = colormap->color(QwtInterval(mMinData, mMaxData), mSpectrData.at(i).data);
        quadColorArray[vertexCounter].r = color->redF();
        quadColorArray[vertexCounter].g = color->greenF();
        quadColorArray[vertexCounter].b = color->blueF();
        quadIndexArray[i].v4 = vertexCounter;
        vertexCounter++;
    }

    glVertexPointer(3, GL_FLOAT, sizeof(CVertex3), quadVertexArray);
    glColorPointer(3, GL_FLOAT, sizeof(CColor3), quadColorArray);
    glDrawElements(GL_QUADS, mVertexNum, GL_UNSIGNED_INT, quadIndexArray);
}

void spectrGL::drawMesh()
{
    glLineWidth(0.25f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0F0F);

    glColor3f(0, 0, 0);

        for(int i = 0; i < mSpectrData.size(); i++)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2f(mSpectrData.at(i).p1.x(), mSpectrData.at(i).p1.y());
            glVertex2f(mSpectrData.at(i).p2.x(), mSpectrData.at(i).p2.y());
            glVertex2f(mSpectrData.at(i).p3.x(), mSpectrData.at(i).p3.y());
            glVertex2f(mSpectrData.at(i).p4.x(), mSpectrData.at(i).p4.y());
            glVertex2f(mSpectrData.at(i).p1.x(), mSpectrData.at(i).p1.y());
            glEnd();
        }

        glDisable(GL_LINE_STIPPLE);
}

void spectrGL::drawText()
{
    float mWidth = abs(mMinX - mMaxX);
    float mHeight = abs(mMinY - mMaxY);

    float dx = mMinX + (abs(0 - mMovePoint.x())/width()) * mWidth;
    float dy = mMaxY - (abs(0 - mMovePoint.y())/height()) * mHeight;
    glColor3f(1.0, 1.0, 1.0);
    renderText(5, height()-10, "X=" + QString::number(dx, 'f', 2) +
                              " Y=" + QString::number(dy, 'f', 2) +
                              " Z=" + QString::number(getZCoord(mMovePoint.x(), mMovePoint.y()), 'f', 1));
}

float spectrGL::getMinData()
{
    float min_data = mSpectrData.at(0).data;
    for(int i = 0; i < mSpectrData.size(); i++)
    {
        if (min_data > mSpectrData.at(i).data)
            min_data = mSpectrData.at(i).data;
    }

    return min_data;
}

float spectrGL::getMaxData()
{
    float max_data = mSpectrData.at(0).data;
    for(int i = 0; i < mSpectrData.size(); i++)
    {
        if (max_data < mSpectrData.at(i).data)
            max_data = mSpectrData.at(i).data;
    }
    return max_data;
}

void spectrGL::setDrawMesh(bool aState)
{
    mDrawMesh = aState;
    updateGL();
}

void spectrGL::setMouseTrackSt(bool aState)
{
    mMouseTrack = aState;
}

void spectrGL::update()
{
    updateGL();
}

void spectrGL::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
}

void spectrGL::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(mMinX, mMaxX, mMinY, mMaxY, -1.0, 1.0);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void spectrGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    CVertex3 *quadVertexArray = new CVertex3[mVertexNum];
    CColor3 *quadColorArray = new CColor3[mVertexNum];
    CFace *quadIndexArray = new CFace[(int)(mVertexNum/4)];

    drawSpectrogram(quadVertexArray, quadColorArray, quadIndexArray);

    if(mDrawMesh)
        drawMesh();

    if(mMouseTrack)
    {
        setMouseTracking(true);
        drawText();
    }
    else
        setMouseTracking(false);


    delete []quadVertexArray;
    delete []quadColorArray;
    delete []quadIndexArray;
}

void spectrGL::mouseMoveEvent(QMouseEvent *pe)
{
    mMovePoint = pe->pos();
    updateGL();
}

float spectrGL::getZCoord(int x, int y)
{
    QColor tmp = mMainWindow->getPixelColor(x, y);

    ColorMap *colormap = new ColorMap;

    QVector<QRgb> mCTable;

    mCTable = colormap->colorTable(QwtInterval(mMinData, mMaxData));

    float z = 0.0;
    float distanceMin = sqrt(pow((tmp.red() - QColor(mCTable.at(0)).red()),2) + pow((tmp.green() - QColor(mCTable.at(0)).green()),2) + pow((tmp.blue() - QColor(mCTable.at(0)).blue()),2));;
    float distance = 0;
    float indexOfMinDistColor = 0;
    for(int i = 0; i < mCTable.size(); i++)
    {
        distance = sqrt(pow((tmp.red() - QColor(mCTable.at(i)).red()),2) + pow((tmp.green() - QColor(mCTable.at(i)).green()),2) + pow((tmp.blue() - QColor(mCTable.at(i)).blue()),2));

        if(distance < distanceMin)
        {
            distanceMin = distance;
            indexOfMinDistColor = i;
        }
    }

    float extraInterval = 0;
    if(indexOfMinDistColor == 0)
        z = mMinData;
    else if(indexOfMinDistColor == (mCTable.size()-1))
        z = mMaxData;
    else
    {
        float distanseToIPlus1 = sqrt(pow((tmp.red() - QColor(mCTable.at(indexOfMinDistColor + 1)).red()),2) + pow((tmp.green() - QColor(mCTable.at(indexOfMinDistColor + 1)).green()),2) + pow((tmp.blue() - QColor(mCTable.at(indexOfMinDistColor + 1)).blue()),2));
        float distanseToIMinus1 = sqrt(pow((tmp.red() - QColor(mCTable.at(indexOfMinDistColor - 1)).red()),2) + pow((tmp.green() - QColor(mCTable.at(indexOfMinDistColor - 1)).green()),2) + pow((tmp.blue() - QColor(mCTable.at(indexOfMinDistColor - 1)).blue()),2));
        if (distanseToIPlus1 < distanseToIMinus1)
        {
            float firstInterval = mMinData + (mMaxData - mMinData)*(indexOfMinDistColor/(mCTable.size()-1));
            float secondInterval = mMinData + (mMaxData - mMinData)*((indexOfMinDistColor + 1)/(mCTable.size()-1));
            extraInterval = (secondInterval - firstInterval)*(distanceMin/(distanceMin+distanseToIPlus1));
            z = extraInterval + mMinData + (mMaxData - mMinData)*(indexOfMinDistColor/(mCTable.size()-1));
        }
        else
        {
            float firstInterval = mMinData + (mMaxData - mMinData)*(indexOfMinDistColor/(mCTable.size()-1));
            float secondInterval = mMinData + (mMaxData - mMinData)*((indexOfMinDistColor + 1)/(mCTable.size()-1));
            extraInterval = (firstInterval - secondInterval)*(distanceMin/(distanceMin+distanseToIPlus1));
            z = mMinData - extraInterval + (mMaxData - mMinData)*(indexOfMinDistColor/(mCTable.size()-1));
        }

    }

    if(tmp.red() == 0 && tmp.green() == 0 && tmp.blue() == 0)
        z = 0.0;

    return z;
}

void spectrGL::calcEdgeXYcoords()
{
    mMinX = mSpectrData.at(0).p1.x();
    mMaxX = mSpectrData.at(0).p1.x();
    mMinY = mSpectrData.at(0).p1.y();
    mMaxY = mSpectrData.at(0).p1.y();
    for(int i = 0; i < mSpectrData.size(); i++)
    {
        if( mMinX > mSpectrData.at(i).p1.x() )
            mMinX = mSpectrData.at(i).p1.x();
        if( mMinX > mSpectrData.at(i).p2.x() )
            mMinX = mSpectrData.at(i).p2.x();
        if( mMinX > mSpectrData.at(i).p3.x() )
            mMinX = mSpectrData.at(i).p3.x();
        if( mMinX > mSpectrData.at(i).p4.x() )
            mMinX = mSpectrData.at(i).p4.x();

        if( mMaxX < mSpectrData.at(i).p1.x() )
            mMaxX = mSpectrData.at(i).p1.x();
        if( mMaxX < mSpectrData.at(i).p2.x() )
            mMaxX = mSpectrData.at(i).p2.x();
        if( mMaxX < mSpectrData.at(i).p3.x() )
            mMaxX = mSpectrData.at(i).p3.x();
        if( mMaxX < mSpectrData.at(i).p4.x() )
            mMaxX = mSpectrData.at(i).p4.x();

        if( mMinY > mSpectrData.at(i).p1.y() )
            mMinY = mSpectrData.at(i).p1.y();
        if( mMinY > mSpectrData.at(i).p2.y() )
            mMinY = mSpectrData.at(i).p2.y();
        if( mMinY > mSpectrData.at(i).p3.y() )
            mMinY = mSpectrData.at(i).p3.y();
        if( mMinY > mSpectrData.at(i).p4.y() )
            mMinY = mSpectrData.at(i).p4.y();

        if( mMaxY < mSpectrData.at(i).p1.y() )
            mMaxY = mSpectrData.at(i).p1.y();
        if( mMaxY < mSpectrData.at(i).p2.y() )
            mMaxY = mSpectrData.at(i).p2.y();
        if( mMaxY < mSpectrData.at(i).p3.y() )
            mMaxY = mSpectrData.at(i).p3.y();
        if( mMaxY < mSpectrData.at(i).p4.y() )
            mMaxY = mSpectrData.at(i).p4.y();
    }
}
