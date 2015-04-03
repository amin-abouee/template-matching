#! /usr/local/bin/python
import sys
import os
from PyQt4 import QtCore, QtGui
from form import Ui_TemplateMatching
from templatematchingopencv import TemplateMatchingOpenCV
 
 
class TemplateMatching(QtGui.QDialog):
    def __init__(self):
    	super(TemplateMatching, self).__init__()
        self.ui = Ui_TemplateMatching()
        self.ui.setupUi(self)

        self.graphicSceneLeftImage = QtGui.QGraphicsScene(self)
        self.graphicSceneRightImage = QtGui.QGraphicsScene(self)
        self.ui.graphicsViewLeftImage.setScene(self.graphicSceneLeftImage)
        self.ui.graphicsViewRightImage.setScene(self.graphicSceneRightImage)

        self.leftPixmap = QtGui.QGraphicsPixmapItem(None)
        self.rightPixmap = QtGui.QGraphicsPixmapItem(None)
        self.leftPatch = QtGui.QGraphicsRectItem(None)
        self.rightPatch = QtGui.QGraphicsRectItem(None)

        self.INITIALPATCHSIZE = 20
        self.PADSIZEGRAPHICSCENE = 10
        self.PADSIZEGRAPHICVIEW = 1
        self.templateMatcher = TemplateMatchingOpenCV(self.INITIALPATCHSIZE)
        self.ui.pushButtonLeftImage.clicked.connect(self.handleButtonLeftImage)
        self.ui.pushButtonRightImage.clicked.connect(self.handleButtonRightImage)
        self.connect(self.ui.horizontalSliderPatchSize, QtCore.SIGNAL("valueChanged(int)"),self.ui.labelPatchSize, QtCore.SLOT("setNum(int)"))

    def mousePressEvent(self, event):
        if self.leftPixmap is not None and self.rightPixmap is not None:
            self.removeRectItemsFromScene()
            patchSize = self.ui.horizontalSliderPatchSize.value();
            selectedPoint = self.ui.graphicsViewLeftImage.mapToScene(event.pos());
            selectedPoint.setX(selectedPoint.x() - self.ui.graphicsViewLeftImage.geometry().x() - self.PADSIZEGRAPHICVIEW)
            selectedPoint.setY(selectedPoint.y() - self.ui.graphicsViewLeftImage.geometry().y() - self.PADSIZEGRAPHICVIEW)
            if selectedPoint.x() >= 0 and selectedPoint.x() <= self.leftPixmap.pixmap().width() and selectedPoint.y() >= 0 and selectedPoint.y() <= self.rightPixmap.pixmap().height():
                bluePen = QtGui.QPen(QtCore.Qt.blue);
                referenceRect = QtCore.QRectF(selectedPoint.x() - patchSize / 2, selectedPoint.y() - patchSize / 2, patchSize, patchSize)
                self.leftPatch = self.graphicSceneLeftImage.addRect(referenceRect, bluePen)
                self.templateMatcher.setPatchSize(patchSize)
                final = self.templateMatcher.findCorrespondingTemplate(selectedPoint)
                greenPen = QtGui.QPen(QtCore.Qt.green)
                followingRect = QtCore.QRectF(final.x(), final.y(), patchSize, patchSize)
                self.rightPatch = self.graphicSceneRightImage.addRect(followingRect, greenPen)

    def handleButtonLeftImage(self):
        self.graphicSceneLeftImage.clear()
        self.leftPatch = None

        fileName = QtGui.QFileDialog.getOpenFileName(self, 'Open file', QtCore.QDir.currentPath())
        if os.path.exists(fileName):
            image = QtGui.QImage(fileName)
            szView = self.ui.graphicsViewLeftImage.size()
            leftImage = QtGui.QPixmap.fromImage(image)
            self.leftPixmap = self.graphicSceneLeftImage.addPixmap(leftImage.scaled(szView.width() - self.PADSIZEGRAPHICSCENE, szView.height() - self.PADSIZEGRAPHICSCENE, QtCore.Qt.KeepAspectRatio, QtCore.Qt.SmoothTransformation))
            self.templateMatcher.setLeftImage(self.leftPixmap.pixmap().toImage())
        else:
            QtGui.QMessageBox.information(self, "Image Viewer", "Cannot Loaf File")

    def handleButtonRightImage(self):
        self.graphicSceneRightImage.clear()
        self.rightPatch = None

        fileName = QtGui.QFileDialog.getOpenFileName(self, 'Open file', QtCore.QDir.currentPath())
        if os.path.exists(fileName):
            image = QtGui.QImage(fileName)
            szView = self.ui.graphicsViewRightImage.size()
            rightImage = QtGui.QPixmap.fromImage(image)
            self.rightPixmap = self.graphicSceneRightImage.addPixmap(rightImage.scaled(szView.width() - self.PADSIZEGRAPHICSCENE, szView.height() - self.PADSIZEGRAPHICSCENE, QtCore.Qt.KeepAspectRatio, QtCore.Qt.SmoothTransformation))
            self.templateMatcher.setRightImage(self.rightPixmap.pixmap().toImage())
        else:
            QtGui.QMessageBox.information(self, "Image Viewer", "Cannot Loaf File")

    def removeRectItemsFromScene(self):
        if self.leftPatch is not None:
            self.graphicSceneLeftImage.removeItem(self.leftPatch)
            self.leftPatch = None

        if self.rightPatch is not None:
            self.graphicSceneRightImage.removeItem(self.rightPatch)
            self.rightPatch = None
 
if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    templateMatchingapp = TemplateMatching()
    templateMatchingapp.show()
    sys.exit(app.exec_())