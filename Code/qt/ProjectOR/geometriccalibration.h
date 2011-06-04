#ifndef GEOMETRICCALIBRATION_H
#define GEOMETRICCALIBRATION_H

#include <QObject>
#include <QPoint>

#include <cv.h>
#include "vector2.h"

class GeometricCalibration : public QObject
{
    Q_OBJECT
public:
    explicit GeometricCalibration(QObject *parent = 0);

    void performGeometricCalibration(IplImage* white_img, IplImage* black_img, IplImage* white_corners_img, IplImage* black_corners_img, Vector2 outPoints[4]);

};

#endif // GEOMETRICCALIBRATION_H
