import numpy
import cv2

class TemplateMatchingOpenCV:

	""" OpenCV implementation for template matching """

	def __init__ (self, patchSize):
		self.__patchSize = patchSize
		self.__scaleFactor = 30

	def setPatchSize(self, patchSize):
		self.__patchSize = patchSize

	def setLeftImage(self, leftImage):
		self.__leftImage = qImage2CvMat(leftImage)

	def setRightImage(self, rightImage):
		self.__rightImage = qImage2CvMat(rightImage)

	def qImage2CvMat(self, image):
		image = image.convertToFormat(4)
    	width = image.width()
    	height = image.height()
    	ptr = image.bits()
    	ptr.setsize(image.byteCount())
    	arr = numpy.array(ptr).reshape(height, width, 4)  #  Copies the data
    	res = arr
    	cv2.cvtColor (arr, res, cv2.COLOR_BGRA2BGR)
    	return res

    def findCorrespondingTemplate(self, selectedPoint):
    	centerPoint = numpy.array([selectedPoint.x(), selectedPoint.y()])
    	subImage = numpy.array()
		searchImage = numpy.array()
		upperLeftCorner = numpy.array([0,0])

		subImage , upperLeftCorner = selectPatchImage(self.__leftImage, centerPoint)
		searchImage , upperLeftCorner = selectPatchImage(self.__rightImage, centerPoint)

		res = cv2.matchTemplate(searchImage, subImage, cv2.TM_CCORR_NORMED)
   		minVal, maxVal, minLoc, maxLoc = cv2.minMaxLoc(res)
   		bestLoc = maxLoc
   		
   		return numpy.array([bestLoc[0] + upperLeftCorner[0], bestLoc[1] + upperLeftCorner[1]])



	def selectPatchImage(self, referenceImage, centerPoint, margin):
		halfPatchSize = margin / 2
		leftSide = numpy.max(0, centerPoint[0] - halfPatchSize)
		upSide = numpy.max(0, centerPoint[1] - halfPatchSize)
		upperLeftCorner[0] = leftSideLoc
		upperLeftCorner[1] = upSideLoc

		rows, cols = reference.shape[:2]
		rightSide = numpy.min(upperLeftCorner[0] + margin, cols)
		downSide = numpy.min(upperLeftCorner[1] + margin, rows)

		width = rightSide - upperLeftCorner[0]
		height = downSide - upperLeftCorner[1]

		followingimage = reference[leftSide:rightSide, upSide:downSide]
		return (followingimage, upperLeftCorner)


