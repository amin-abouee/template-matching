#include "templatematchingopencv.h"

TemplateMatchingOpenCV::TemplateMatchingOpenCV(int iPatchSize):
patchSize(iPatchSize)
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
	cv::Mat temp = cv::Mat(qImage.height(), qImage.width(), CV_8UC4, 
                   const_cast<uchar*>(qImage.bits()), 
                   qImage.bytesPerLine()).clone();
	cv::Mat result;
	cvtColor(temp, result, cv::COLOR_BGRA2BGR);
	// cvtColor(result,result,cv::COLOR_RGB2GRAY);
	return result;
}

QPointF TemplateMatchingOpenCV::findCorrespondingTemplate(QPointF selectedPoint)
{
	cv::Point centerPoint (selectedPoint.x(), selectedPoint.y());
	std::pair <cv::Mat, cv::Point> referencePatch = selectPatchImage(leftImage, centerPoint, patchSize);
	std::pair <cv::Mat, cv::Point> followingPatch = selectPatchImage(rightImage, centerPoint, patchSize * 30);
	cv::Mat subImage = referencePatch.first;
	cv::Mat searchImage = followingPatch.first;
	// cv::imshow("SEARCH", searchImage);

	cv::Size resultSize;
	resultSize.width =  searchImage.cols - subImage.cols + 1;
	resultSize.height = searchImage.rows - subImage.rows + 1;
	// std::cout << resultSize << std::endl;

	cv::Mat result = cv::Mat(resultSize,  CV_32FC1);
	cv::matchTemplate (subImage, searchImage, result, cv::TM_CCORR_NORMED);
	cv::normalize (result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	double minVal; 
	double maxVal; 
	cv::Point minLocation; 
	cv::Point maxLocation;
	cv::Point bestLoc;
	cv::minMaxLoc (result, &minVal, &maxVal, &minLocation, &maxLocation, cv::Mat());
	bestLoc = maxLocation;
	return QPointF(bestLoc.x + followingPatch.second.x, bestLoc.y + followingPatch.second.y);
}

std::pair<cv::Mat, cv::Point> TemplateMatchingOpenCV::selectPatchImage (cv::Mat &referenceImage, cv::Point &centerPoint, int margin)
{
	std::pair <cv::Mat, cv::Point> result;
	// std::cout << "Patch Size: " << margin << std::endl;
	std::size_t halfPatchSize = margin / 2;
	
	int leftSideLoc = std::max(0, int(centerPoint.x - halfPatchSize));
	// std::cout << "left side: " << leftSideLoc << std::endl;

	int upSideLoc = std::max(0, int(centerPoint.y - halfPatchSize));
	// std::cout << "up side: " << upSideLoc << std::endl;
	cv::Point upperLeftCorner (leftSideLoc, upSideLoc);

	int rightSide = std::min(int(upperLeftCorner.x + margin), int(referenceImage.cols));
	// std::cout << "right side: " << rightSide << std::endl;

	int downSide = std::min(int(upperLeftCorner.y + margin), int(referenceImage.rows));
	// std::cout << "down side: " << downSide << std::endl;

	int width = rightSide - upperLeftCorner.x;
	// std::cout << "width: " << width << std::endl;
	int height = downSide - upperLeftCorner.y;
	// std::cout << "height: " << height << std::endl;

	cv::Rect patch (upperLeftCorner.x, upperLeftCorner.y, width, height);
	cv::Mat patchImage = referenceImage(patch);
	result.first = patchImage;
	result.second = upperLeftCorner;
	return result;
}