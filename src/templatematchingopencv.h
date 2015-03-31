#ifndef TEMPLATEMATCHINGOPENCV_H
#define TEMPLATEMATCHINGOPENCV_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class TemplateMatchingOpenCV
{
public:
    TemplateMatchingOpenCV();
    ~TemplateMatchingOpenCV();
    void setLeftImage(std::string );
    void setRightImage(std::string );

private:
    cv::Mat leftImage;
    cv::Mat RightImage;
};

#endif // TEMPLATEMATCHINGOPENCV_H
