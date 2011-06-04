#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"
#include "geometriccalibration.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

/////////////////////////////////// GL DRAW CLASSES /////////////////////////////////

void GLExtraDraw::changeDrawStyle(DrawType drawType)
{
    currentDrawType = drawType;
}

void GLExtraDraw::drawSquare(float xCenter, float yCenter, float size)
{
    glBegin(GL_QUADS);
        glVertex3f(xCenter - size, yCenter - size, -1);
        glVertex3f(xCenter + size, yCenter - size, -1);
        glVertex3f(xCenter + size, yCenter + size, -1);
        glVertex3f(xCenter - size, yCenter + size, -1);
    glEnd();
}

void GLExtraDraw::setCustomColor(float r, float g, float b)
{
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

void GLExtraDraw::drawCommands()
{
    float size = 0.1;
    switch(currentDrawType)
    {
    case DrawType_NoCorners:
        break;
    case DrawType_BlackCorners:
        glDisable(GL_TEXTURE_2D);
        glColor3f(0,0,0);
        drawSquare(-1+size, -1+size, size);
        drawSquare(1-size, -1+size, size);
        drawSquare(1-size, 1-size, size);
        drawSquare(-1+size, 1-size, size);
        glEnable(GL_TEXTURE_2D);
        break;
    case DrawType_WhiteCorners:
        glDisable(GL_TEXTURE_2D);
        glColor3f(1,1,1);
        drawSquare(-1+size, -1+size, size);
        drawSquare(1-size, -1+size, size);
        drawSquare(1-size, 1-size, size);
        drawSquare(-1+size, 1-size, size);
        glEnable(GL_TEXTURE_2D);
        break;
    case DrawType_White:
        glDisable(GL_TEXTURE_2D);
        glColor3f(1,1,1);
        drawSquare(0, 0, 2);
        glEnable(GL_TEXTURE_2D);
        break;
    case DrawType_Black:
        glDisable(GL_TEXTURE_2D);
        glColor3f(0,0,0);
        drawSquare(0, 0, 2);
        glEnable(GL_TEXTURE_2D);
        break;
    case DrawType_CustomColor:
        glDisable(GL_TEXTURE_2D);
        glColor3f(rgb[0],rgb[1],rgb[2]);
        drawSquare(0, 0, 2);
        glEnable(GL_TEXTURE_2D);
        break;
    }
}

/////////////////////////////////// GL WIDGET ////////////////////////////////////////

GLWidget::GLWidget(IplImage** _image, QMutex* cameraLock, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent, 0, Qt::FramelessWindowHint), screenGrabber(this),
    imageGrabber(_image, cameraLock, this), userOffsetAmountX(0), userOffsetAmountY(0)
{    
    setWindowTitle(tr("ProjectOR"));
    QRect screenres = QApplication::desktop()->screenGeometry(1);
    move(QPoint(screenres.x(), screenres.y()));
    resize(screenres.width(), screenres.height());
    showFullScreen();
    startTimer(60);
    setFocusPolicy(Qt::StrongFocus);
    corners[0] = Vector2(-1,-1);
    corners[1] = Vector2(1,-1);
    corners[2] = Vector2(-1,1);
    corners[3] = Vector2(1,1);
    userOffsetDirectionX = corners[3] - corners[2];
    userOffsetDirectionY = corners[3] - corners[1];
    showCorrectedImage = true;    
    updateMode = UpdateMode_FirstMonitor;
}

GLWidget::~GLWidget()
{
}

void GLWidget::loadImageRGB(char* imageData, int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
}

void GLWidget::loadImageBGRA(char* imageData, int width, int height)
{
    for (int i = 0; i < width; i ++)
    {
        for (int j = 0; j < height; j++)
        {
            char r = imageData[4*(j*width+i)];
            char b = imageData[4*(j*width+i)+2];
            imageData[4*(j*width+i)] = b;
            imageData[4*(j*width+i)+2] = r;
        }
    }
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
}

IplImage* GLWidget::loadImageTakeScreenshot(GLExtraDraw::DrawType drawType)
{
    IplImage* out;
    extraDrawCommands.changeDrawStyle(drawType);
    updateGL();
    Sleep(350);
    out = imageGrabber.saveCameraImageIplImage();
    return out;
}

void GLWidget::calibration()
{
    // Load calibration images
    GeometricCalibration geometric;
    IplImage* cameraShotWhite;
    IplImage* cameraShotBlack;
    IplImage* cameraShotWhiteCorners;
    IplImage* cameraShotBlackCorners;
    cameraShotWhiteCorners = loadImageTakeScreenshot(GLExtraDraw::DrawType_WhiteCorners);
    cameraShotBlackCorners = loadImageTakeScreenshot(GLExtraDraw::DrawType_BlackCorners);
    cameraShotWhite = loadImageTakeScreenshot(GLExtraDraw::DrawType_White);
    cameraShotBlack = loadImageTakeScreenshot(GLExtraDraw::DrawType_Black);
    extraDrawCommands.changeDrawStyle(GLExtraDraw::DrawType_NoCorners);
    updateGL();
    // perform geometric transformation correction to get screen space corner points
    geometric.performGeometricCalibration(cameraShotWhite, cameraShotBlack, cameraShotWhiteCorners, cameraShotBlackCorners, corners);
    userOffsetDirectionX = corners[3] - corners[2];
    userOffsetDirectionY = corners[3] - corners[1];
    userOffsetDirectionX.normalize();
    userOffsetDirectionY.normalize();
    // save out images for debugging
    imageGrabber.saveImageToDiskIplImage(cameraShotWhite, "white.png");
    imageGrabber.saveImageToDiskIplImage(cameraShotBlack, "black.png");
    imageGrabber.saveImageToDiskIplImage(cameraShotWhiteCorners, "whiteCorners.png");
    imageGrabber.saveImageToDiskIplImage(cameraShotBlackCorners, "blackCorners.png");
    // release calibration images
    cvReleaseImage(&cameraShotWhite);
    cvReleaseImage(&cameraShotBlack);
    cvReleaseImage(&cameraShotWhiteCorners);
    cvReleaseImage(&cameraShotBlackCorners);

}

void GLWidget::timerEvent(QTimerEvent *event)
{        
    switch(updateMode)
    {
    case UpdateMode_None:
        break;
    case UpdateMode_FirstMonitor:
        screenGrabber.takeScreenshot();
        loadImageBGRA(screenGrabber.getData(), screenGrabber.width(), screenGrabber.height());
        break;
    case UpdateMode_Camera:
        imageGrabber.lockCamera();
        loadImageRGB(imageGrabber.getData(), imageGrabber.width(), imageGrabber.height());
        imageGrabber.unlockCamera();
        break;
    }
    updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{   
    switch (event->key())
    {
    case Qt::Key_A:
        imageGrabber.lockCamera();
        loadImageRGB(imageGrabber.getData(), imageGrabber.width(), imageGrabber.height());
        imageGrabber.unlockCamera();
        break;
    case Qt::Key_S:
        screenGrabber.takeScreenshot();
        loadImageBGRA(screenGrabber.getData(), screenGrabber.width(), screenGrabber.height());
        break;
    case Qt::Key_D:
        calibration();
        break;
    case Qt::Key_C:
        showCorrectedImage = !showCorrectedImage;
        break;
    case Qt::Key_P:
        imageGrabber.saveCameraImageToDisk();
        break;
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_R:
        switch(updateMode)
        {
        case UpdateMode_None:
            updateMode = UpdateMode_FirstMonitor;
            break;
        case UpdateMode_FirstMonitor:
            updateMode = UpdateMode_Camera;
            break;
        case UpdateMode_Camera:
            updateMode = UpdateMode_None;
            break;
        }
        break;
    case Qt::Key_Left:
        userOffsetAmountX -= .01f;
        break;
    case Qt::Key_Right:
        userOffsetAmountX += .01f;
        break;
    case Qt::Key_Up:
        userOffsetAmountY += .01f;
        break;
    case Qt::Key_Down:
        userOffsetAmountY -= .01f;
        break;

    default:
        QWidget::keyPressEvent(event);
    }
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QApplication::desktop()->size();
}

void GLWidget::initializeGL()
{
    qglClearColor(QColor::fromRgb(0,0,0));        
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glBegin (GL_QUADS);
    if (showCorrectedImage)
    {
        subdivisionRender();
//        glTexCoord2f(0.f,1.f); glVertex3f(corners[2][0], corners[2][1], -1);
//        glTexCoord2f(1.f,1.f); glVertex3f(corners[3][0], corners[3][1], -1);
//        glTexCoord2f(1.f,0.f); glVertex3f(corners[1][0], corners[1][1], -1);
//        glTexCoord2f(0.f,0.f); glVertex3f(corners[0][0], corners[0][1], -1);
    }
    else
    {
        glTexCoord2f(0.f,0.f); glVertex3f(-1, -1, -1);
        // bottom right
        glTexCoord2f(1.f,0.f); glVertex3f(1, -1, -1);
        // top right
        glTexCoord2f(1.f,1.f); glVertex3f(1, 1, -1);
        // top left
        glTexCoord2f(0.f,1.f); glVertex3f(-1, 1, -1);
    }
    glEnd ();

    extraDrawCommands.drawCommands();

    glMatrixMode (GL_MODELVIEW);
}

void GLWidget::subdivisionRender()
{
    int subs = 20;
    float size = 1/(float)subs;

    float xOffset = userOffsetDirectionX.x*userOffsetAmountX + userOffsetDirectionY.x*userOffsetAmountY;
    float yOffset = userOffsetDirectionX.y*userOffsetAmountX + userOffsetDirectionY.y*userOffsetAmountY;
    float c0x = corners[0].x + xOffset;
    float c0y = corners[0].y + yOffset;
    float c1x = corners[1].x + xOffset;
    float c1y = corners[1].y + yOffset;
    float c2x = corners[2].x + xOffset;
    float c2y = corners[2].y + yOffset;
    float c3x = corners[3].x + xOffset;
    float c3y = corners[3].y + yOffset;
    for (int x=0; x<subs; x++)
    {
       for (int y=subs-1; y>=0; y--)
       {
           float a = x*size;
           float b = 1.0-(y+1)*size;
           glTexCoord2d(a,b);
           glVertex2d(a*b*(c0x-c1x-c2x+c3x)+b*(-c0x+c2x)+a*(-c0x+c1x)+c0x, \
           a*b*(c0y-c1y-c2y+c3y)+b*(-c0y+c2y)+a*(-c0y+c1y)+c0y);

           a = (x+1)*size;
           b = 1.0-(y+1)*size;
           glTexCoord2d(a,b);
           glVertex2d(a*b*(c0x-c1x-c2x+c3x)+b*(-c0x+c2x)+a*(-c0x+c1x)+c0x, \
           a*b*(c0y-c1y-c2y+c3y)+b*(-c0y+c2y)+a*(-c0y+c1y)+c0y);

           a = (x+1)*size;
           b = 1.0-y*size;
           glTexCoord2d(a,b);
           glVertex2d(a*b*(c0x-c1x-c2x+c3x)+b*(-c0x+c2x)+a*(-c0x+c1x)+c0x, \
           a*b*(c0y-c1y-c2y+c3y)+b*(-c0y+c2y)+a*(-c0y+c1y)+c0y);

           a = x*size;
           b = 1.0-y*size;
           glTexCoord2d(a,b);
           glVertex2d(a*b*(c0x-c1x-c2x+c3x)+b*(-c0x+c2x)+a*(-c0x+c1x)+c0x, \
           a*b*(c0y-c1y-c2y+c3y)+b*(-c0y+c2y)+a*(-c0y+c1y)+c0y);
       }
    }
}

void GLWidget::resizeGL(int width, int height)
{    
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}



