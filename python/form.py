# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui/templatematchingui.ui'
#
# Created: Fri Apr  3 15:44:45 2015
#      by: PyQt4 UI code generator 4.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_TemplateMatching(object):
    def setupUi(self, TemplateMatching):
        TemplateMatching.setObjectName(_fromUtf8("TemplateMatching"))
        TemplateMatching.resize(1244, 687)
        self.graphicsViewLeftImage = QtGui.QGraphicsView(TemplateMatching)
        self.graphicsViewLeftImage.setGeometry(QtCore.QRect(10, 10, 600, 600))
        self.graphicsViewLeftImage.setObjectName(_fromUtf8("graphicsViewLeftImage"))
        self.graphicsViewRightImage = QtGui.QGraphicsView(TemplateMatching)
        self.graphicsViewRightImage.setGeometry(QtCore.QRect(630, 10, 600, 600))
        self.graphicsViewRightImage.setObjectName(_fromUtf8("graphicsViewRightImage"))
        self.pushButtonLeftImage = QtGui.QPushButton(TemplateMatching)
        self.pushButtonLeftImage.setGeometry(QtCore.QRect(230, 620, 170, 32))
        self.pushButtonLeftImage.setObjectName(_fromUtf8("pushButtonLeftImage"))
        self.pushButtonRightImage = QtGui.QPushButton(TemplateMatching)
        self.pushButtonRightImage.setGeometry(QtCore.QRect(880, 620, 170, 32))
        self.pushButtonRightImage.setObjectName(_fromUtf8("pushButtonRightImage"))
        self.layoutWidget = QtGui.QWidget(TemplateMatching)
        self.layoutWidget.setGeometry(QtCore.QRect(420, 660, 391, 26))
        self.layoutWidget.setObjectName(_fromUtf8("layoutWidget"))
        self.horizontalLayout_2 = QtGui.QHBoxLayout(self.layoutWidget)
        self.horizontalLayout_2.setMargin(0)
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.labelPatchSizeText = QtGui.QLabel(self.layoutWidget)
        self.labelPatchSizeText.setObjectName(_fromUtf8("labelPatchSizeText"))
        self.horizontalLayout_2.addWidget(self.labelPatchSizeText)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.horizontalSliderPatchSize = QtGui.QSlider(self.layoutWidget)
        self.horizontalSliderPatchSize.setMinimum(10)
        self.horizontalSliderPatchSize.setProperty("value", 20)
        self.horizontalSliderPatchSize.setOrientation(QtCore.Qt.Horizontal)
        self.horizontalSliderPatchSize.setObjectName(_fromUtf8("horizontalSliderPatchSize"))
        self.horizontalLayout.addWidget(self.horizontalSliderPatchSize)
        self.labelPatchSize = QtGui.QLabel(self.layoutWidget)
        self.labelPatchSize.setObjectName(_fromUtf8("labelPatchSize"))
        self.horizontalLayout.addWidget(self.labelPatchSize)
        self.horizontalLayout_2.addLayout(self.horizontalLayout)

        self.retranslateUi(TemplateMatching)
        QtCore.QMetaObject.connectSlotsByName(TemplateMatching)

    def retranslateUi(self, TemplateMatching):
        TemplateMatching.setWindowTitle(_translate("TemplateMatching", "Template Matching", None))
        self.pushButtonLeftImage.setText(_translate("TemplateMatching", "Load Left Image", None))
        self.pushButtonRightImage.setText(_translate("TemplateMatching", "Load Right Image", None))
        self.labelPatchSizeText.setText(_translate("TemplateMatching", "Patch Size", None))
        self.labelPatchSize.setText(_translate("TemplateMatching", "20", None))

