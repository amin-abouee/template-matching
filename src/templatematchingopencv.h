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
#include <algorithm>

class TemplateMatchingOpenCV
{
public:
    TemplateMatchingOpenCV(int iPatchSize);
    ~TemplateMatchingOpenCV();
    void setLeftImage(const QPixmap &image);
    void setRightImage(const QPixmap &image);
    void setPatchSize(int iPatchSize);
    QPointF findCorrespondingTemplate(QPointF selectedPoint);

private:
	std::size_t patchSize;
    cv::Mat leftImage;
    cv::Mat rightImage;
    cv::Mat qImage2CvMat(const QPixmap &image);
    std::pair<cv::Mat, cv::Point> selectPatchImage (cv::Mat &referenceImage, cv::Point &centerPoint, int margin);
};

#endif // TEMPLATEMATCHINGOPENCV_H
