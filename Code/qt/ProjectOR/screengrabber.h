#ifndef SCREENGRABBER_H
#define SCREENGRABBER_H

#include <QObject>
#include <QPixmap>

#include "screenshot.h"
class ScreenGrabber : public QObject
{
public:
    ScreenGrabber(QObject* parent = 0);
    ~ScreenGrabber();

    void takeScreenshot();
    int width() {return m_screenWidth;}
    int height() {return m_screenHeight;}
    char* getData() {return m_data;}
private:
    int m_screenWidth;
    int m_screenHeight;
    char* m_data;
    QPixmap m_pixmap;
};

#endif // SCREENGRABBER_H
