# Template_Matching
Template matching between two consecutive images. This project can load two images side by side and can find
a template (patch image) from left image in the right image accurately.
In this approach the matchTemplate function of opencv and Normalized Cross Corelation (NCC)
are exploited to find the best and precise template in the following (right) image. For this purpose instead of 
searching inside the whole image (common approach), I just select a bigger patch (30x bigger than the reference patch in the left image) for searching the corresponding patch. The benefit of this approach compare to the former approach (whole image) is the search space is more smaller and consequently the computation time is better.
This method is useful when the images have the nearby viewpoint.

To build:
mkdir build
cd build
cmake ..
make 
./bin/release/template_matching
