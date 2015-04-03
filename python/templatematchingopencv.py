import numpy
import cv2
from PyQt4 import QtCore

class TemplateMatchingOpenCV:

	""" OpenCV implementation for template matching """

	def __init__ (self, patchSize):
		self.__patchSize = patchSize
		self.__scaleFactor = 30

	def setPatchSize(self, patchSize):
		self.__patchSize = patchSize

	def setLeftImage(self, leftImage):
		self.__leftImage = self.qImage2CvMat(leftImage)
		# cv2.imshow("Left Image", self.__leftImage)

	def setRightImage(self, rightImage):
		self.__rightImage = self.qImage2CvMat(rightImage)
		# cv2.imshow("Right Image", self.__rightImage)

	def qImage2CvMat(self, image):
		image = image.convertToFormat(4)
		width = image.width()
		height = image.height()
		ptr = image.bits()
		ptr.setsize(image.byteCount())
		arr = numpy.array(ptr).reshape(height, width, 4)  #  Copies the data
		res = cv2.cvtColor (arr, cv2.COLOR_BGRA2BGR)
		return res

	def findCorrespondingTemplate(self, selectedPoint):
		centerPoint = numpy.array([selectedPoint.x(), selectedPoint.y()])
		subImage , upperLeftCorner = self.selectPatchImage(self.__leftImage, centerPoint, self.__patchSize)
		searchImage , upperLeftCorner = self.selectPatchImage(self.__rightImage, centerPoint, self.__patchSize * self.__scaleFactor)
		res = cv2.matchTemplate(searchImage, subImage, cv2.TM_CCORR_NORMED)
		minVal, maxVal, minLoc, maxLoc = cv2.minMaxLoc(res)
		bestLoc = maxLoc
		return QtCore.QPointF(bestLoc[0] + upperLeftCorner[0], bestLoc[1] + upperLeftCorner[1])
		# numpy.array([bestLoc[0] + upperLeftCorner[0], bestLoc[1] + upperLeftCorner[1]])


	def selectPatchImage(self, referenceImage, centerPoint, margin):
		halfPatchSize = margin / 2
		leftSide = max(0, centerPoint[0] - halfPatchSize)
		upSide = max(0, centerPoint[1] - halfPatchSize)
		upperLeftCorner = numpy.array([0,0])
		upperLeftCorner[0] = leftSide
		upperLeftCorner[1] = upSide

		rows , cols = referenceImage.shape[:2]
		rightSide = min(upperLeftCorner[0] + margin, cols)
		downSide = min(upperLeftCorner[1] + margin, rows)

		width = rightSide - upperLeftCorner[0]
		height = downSide - upperLeftCorner[1]

		followingimage = referenceImage[upSide:downSide, leftSide:rightSide]
		return (followingimage, upperLeftCorner)


