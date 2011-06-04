#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMutex>
#include <cv.h>

#include "screengrabber.h"
#include "imageGrabber.h"
#include "vector2.h"

class GLExtraDraw
{
public:
    enum DrawType
    {
        DrawType_NoCorners = 0,
        DrawType_BlackCorners,
        DrawType_WhiteCorners,
        DrawType_Black,
        DrawType_White,
        DrawType_CustomColor
    };

    GLExtraDraw(){currentDrawType = DrawType_NoCorners;}
    void setCustomColor(float r, float g, float b);
    void changeDrawStyle(DrawType drawType);    
    void drawCommands();

private:
    void drawSquare(float xCenter, float yCenter, float size);
    DrawType currentDrawType;
    float rgb[3];
};

enum UpdateMode
{
    UpdateMode_None = 0,
    UpdateMode_FirstMonitor,
    UpdateMode_Camera
};

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(IplImage** _image, QMutex* cameraLock, QWidget *parent = 0);
    ~GLWidget();

    void loadImageRGB(char* imageData, int width, int height);
    void loadImageBGRA(char* imageData, int width, int height);
    IplImage* loadImageTakeScreenshot(GLExtraDraw::DrawType drawType);
    void calibration();

    void createCalibrationFourCorners(Image& image);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void subdivisionRender();

private:        
    ScreenGrabber screenGrabber;
    ImageGrabber imageGrabber;
    GLuint texture;    
    GLExtraDraw extraDrawCommands;
    UpdateMode updateMode;
    bool showCorrectedImage;    
    Vector2 corners[4]; // top left, top right, bottom left, bottom right
    Vector2 userOffsetDirectionX;
    Vector2 userOffsetDirectionY;
    float userOffsetAmountX;
    float userOffsetAmountY;
};

#endif
