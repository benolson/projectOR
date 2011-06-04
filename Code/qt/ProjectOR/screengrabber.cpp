#include "screengrabber.h"

#include <QPixmap>
#include <QApplication>

ScreenGrabber::ScreenGrabber(QObject* parent)
    : QObject(parent)
{
    ScreenSize(m_screenHeight, m_screenWidth);
    m_data = new char[m_screenWidth*m_screenHeight*4];
}

ScreenGrabber::~ScreenGrabber()
{
    delete[] m_data;
}

void ScreenGrabber::takeScreenshot()
{
    CaptureScreen(m_data);
//    m_pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
//    QImage img = m_pixmap.toImage();
//    m_data = (char*) img.bits();
}
