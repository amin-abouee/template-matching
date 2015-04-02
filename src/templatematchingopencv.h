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
    /**
     * @brief Convert the left image from the Qt::Pixmap to cv::Mat 
     * 
     * @param image The input image in the form of QPixmap
     */
    void setLeftImage(const QPixmap &image);

    /**
     * @brief Convert the right image from the Qt::Pixmap to cv::Mat 
     * 
     * @param image The input image in the form of QPixmap
     */
    void setRightImage(const QPixmap &image);

    /**
     * @brief Set the patch size
     */
    void setPatchSize(int iPatchSize);

    /**
     * @brief Find the corresponding template (patch) in the right (following) image
     * @details In this approach the matchTemplate function of opencv and Normalized Cross Corelation (NCC)
     * are exploited to find the best and precise template in the following (right) image. In this approach instead of 
     * searching inside the whole image (common approach), I just select a bigger patch (30x bigger than the reference patch in the left image
     * and especially for nearby viewpoint stereo vision) for searching the corresponding patch. The benefit of this approach 
     * compared to the former approach (whole image) is the serch space is more smaller and consequently the computation time is better.
     * 
     * @param selectedPoint The center of selected patch in the left image
     * @return The best corresponding point in the right image
     */
    QPointF findCorrespondingTemplate(QPointF selectedPoint);

private:
	std::size_t patchSize; /**< The size of patch around the selected point */
    cv::Mat leftImage; /**< The left image */
    cv::Mat rightImage; /**< The right image */
    const int scaleFactor; /**< The scale factor to magnitude the patch size in the right side compare to the left patch */

    /**
     * @brief Convert the Image data from the Qt::Pixmap form to cv::Mat
     * 
     * @param image the input image in the form of Qt::Pixmap
     * @return The output image in the form of cv::Mat
     */
    cv::Mat qImage2CvMat(const QPixmap &image);

    /**
     * @brief Crop a patch (template) from the reference image regarding to the center point and patch size around the center
     * 
     * @param referenceImage The main image
     * @param centerPoint The selected point or the center of patch image
     * @param followingimage The cropped image (patch image)
     * @param upperLeftCorner The position of crop image regarding to the reference image. It saves the Upper left corner position
     * @param margin The patch size based on the left or right image
     */
    void selectPatchImage (cv::Mat &referenceImage, cv::Point &centerPoint, cv::Mat &followingimage, cv::Point &upperLeftCorner, int margin);
};

#endif // TEMPLATEMATCHINGOPENCV_H
