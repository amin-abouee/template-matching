#ifndef TEMPLATEMATCHINGOPENCV_H
#define TEMPLATEMATCHINGOPENCV_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtCore/QDebug>

#include <iostream>

class TemplateMatchingOpenCV
{
public:
    TemplateMatchingOpenCV();
    ~TemplateMatchingOpenCV();
    void setLeftImage(const QPixmap &image);
    void setRightImage(const QPixmap &image);
    QPointF findCorrespondingTemplate(QPointF selectedPoint);

private:
    cv::Mat leftImage;
    cv::Mat rightImage;
    cv::Mat qImage2CvMat(const QPixmap &image);
    cv::Mat selectPatchImage (cv::Mat &referenceImage, cv::Point &selectedPoint, int margin);
};

#endif // TEMPLATEMATCHINGOPENCV_H
