#include "templatematchingopencv.h"

TemplateMatchingOpenCV::TemplateMatchingOpenCV()
{

}

TemplateMatchingOpenCV::~TemplateMatchingOpenCV()
{

}

void TemplateMatchingOpenCV::setLeftImage(const QPixmap &image)
{
	leftImage = qImage2CvMat(image);
	// leftImage = cv::imread("/Users/Abouee/Desktop/IMG_4934_resize.jpg");
	// cv::imshow("Left", leftImage);
}

void TemplateMatchingOpenCV::setRightImage(const QPixmap &image)
{
	rightImage = qImage2CvMat(image);
	// rightImage = cv::imread("/Users/Abouee/Desktop/IMG_4936_resize.jpg");
	// cv::imshow("Right", rightImage);
}

cv::Mat TemplateMatchingOpenCV::qImage2CvMat(const QPixmap &image)
{
	const QImage qImage = image.toImage();
	// qDebug() << qImage.height() << " -- " << qImage.width();
	cv::Mat temp = cv::Mat(qImage.height(), qImage.width(), CV_8UC4, 
                   const_cast<uchar*>(qImage.bits()), 
                   qImage.bytesPerLine()).clone();
	cv::Mat result;
	cvtColor(temp, result, 1);
	// std::cout << result.rows << " // " << result.cols << std::endl;
	return result;
}

QPointF TemplateMatchingOpenCV::findCorrespondingTemplate(QPointF selectedPoint)
{
	cv::Point centerPoint (selectedPoint.x(), selectedPoint.y());
	int margin = 20;
	cv::Mat subImage = selectPatchImage(leftImage, centerPoint, margin);
	// std::cout << "Sub Image: " << subImage.rows << " - " << subImage.cols << std::endl;
	// std::cout << "right Image: " << rightImage.rows << " - " << rightImage.cols << std::endl;

	cv::Size resultSize;
	resultSize.width =  rightImage.cols - subImage.cols + 1;
	resultSize.height = rightImage.rows - subImage.rows + 1;
	std::cout << resultSize << std::endl;

	cv::Mat result = cv::Mat(resultSize,  CV_32FC1);
	cv::matchTemplate (subImage, rightImage, result, cv::TM_CCORR_NORMED);
	cv::normalize (result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	double minVal; 
	double maxVal; 
	cv::Point minLocation; 
	cv::Point maxLocation;
	cv::Point bestLoc;
	cv::minMaxLoc (result, &minVal, &maxVal, &minLocation, &maxLocation, cv::Mat());
	bestLoc = maxLocation;
	return QPointF(bestLoc.x, bestLoc.y);
}

cv::Mat TemplateMatchingOpenCV::selectPatchImage (cv::Mat &referenceImage, cv::Point &selectedPoint, int margin)
{
	std::size_t patchSize = margin / 2;
	cv::Point upperLeftCorner (selectedPoint.x - margin, selectedPoint.y - margin);
	cv::Rect patch (upperLeftCorner.x, upperLeftCorner.y, margin, margin);
	cv::Mat patchImage = referenceImage(patch);
	return patchImage;
}