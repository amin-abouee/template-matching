#include "templatematchingopencv.h"

TemplateMatchingOpenCV::TemplateMatchingOpenCV(int iPatchSize):
patchSize(iPatchSize),
scaleFactor(30)
{

}

TemplateMatchingOpenCV::~TemplateMatchingOpenCV()
{

}

void TemplateMatchingOpenCV::setPatchSize(int iPatchSize)
{
	patchSize = iPatchSize;
}

void TemplateMatchingOpenCV::setLeftImage(const QPixmap &image)
{
	leftImage = qImage2CvMat(image);
}

void TemplateMatchingOpenCV::setRightImage(const QPixmap &image)
{
	rightImage = qImage2CvMat(image);
}

cv::Mat TemplateMatchingOpenCV::qImage2CvMat(const QPixmap &image)
{
	const QImage qImage = image.toImage();
	// The format of Qt::Image format is RGB32 and contains 4 channels of 8 bit (uchar)
	cv::Mat temp = cv::Mat(qImage.height(), qImage.width(), CV_8UC4, 
                   const_cast<uchar*>(qImage.bits()), 
                   qImage.bytesPerLine()).clone();
	cv::Mat result;
	// The result should be converted from BGRA to BGR
	cvtColor(temp, result, cv::COLOR_BGRA2BGR);
	return result;
}

QPointF TemplateMatchingOpenCV::findCorrespondingTemplate(QPointF selectedPoint)
{

	cv::Point centerPoint (selectedPoint.x(), selectedPoint.y());
	cv::Mat subImage;
	cv::Mat searchImage;
	cv::Point upperLeftCorner (0,0);
	// crop a patch image from the left image based on the center point and the patch size
	selectPatchImage(leftImage, centerPoint, subImage, upperLeftCorner, patchSize);
	// crop a patch image (search space) from the right image based on the center point and the 30 x patch size
	selectPatchImage(rightImage, centerPoint, searchImage, upperLeftCorner, patchSize * scaleFactor);

	// store the matching results for each template location
	cv::Size resultSize;
	resultSize.width =  searchImage.cols - subImage.cols + 1;
	resultSize.height = searchImage.rows - subImage.rows + 1;
	cv::Mat result = cv::Mat(resultSize,  CV_32FC1);

	// compute the subImage inside the search image. The Normalized Correlation Approach is used.
	cv::matchTemplate (subImage, searchImage, result, cv::TM_CCORR_NORMED);
	cv::normalize (result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	double minVal; 
	double maxVal; 
	cv::Point minLocation; 
	cv::Point maxLocation;
	cv::Point bestLoc;
	// find the minimum and maximum value inside the result matrix and their corresponding point
	cv::minMaxLoc (result, &minVal, &maxVal, &minLocation, &maxLocation, cv::Mat());
	// higher value represents the best point and the best template for our sun image.
	bestLoc = maxLocation;

	// return the best template center. Because the search image is cropped from the image, it is necessary to add 
	// the upper left corner to the computed point.
	return QPointF(bestLoc.x + upperLeftCorner.x, bestLoc.y + upperLeftCorner.y);
}

void TemplateMatchingOpenCV::selectPatchImage (cv::Mat &referenceImage, cv::Point &centerPoint, cv::Mat &followingimage, cv::Point &upperLeftCorner, int margin)
{
	std::size_t halfPatchSize = margin / 2;
	
	// set the boundary for the left and upper sides of patch image
	int leftSideLoc = std::max(0, int(centerPoint.x - halfPatchSize));
	int upSideLoc = std::max(0, int(centerPoint.y - halfPatchSize));
	upperLeftCorner.x = leftSideLoc;
	upperLeftCorner.y = upSideLoc;

	// set the boundary for the right and down sides of patch image
	int rightSide = std::min(int(upperLeftCorner.x + margin), int(referenceImage.cols));
	int downSide = std::min(int(upperLeftCorner.y + margin), int(referenceImage.rows));

	// set the width and height of patch image based on the computed rightSide and downSide
	int width = rightSide - upperLeftCorner.x;
	int height = downSide - upperLeftCorner.y;

	// crop the patch image from the reference image rely on the computed rectangle
	cv::Rect patch (upperLeftCorner.x, upperLeftCorner.y, width, height);
	followingimage = referenceImage(patch);
}