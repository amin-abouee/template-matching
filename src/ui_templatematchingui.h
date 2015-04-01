/********************************************************************************
** Form generated from reading UI file 'templatematchingui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLATEMATCHINGUI_H
#define UI_TEMPLATEMATCHINGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemplateMatchingUI
{
public:
    QGraphicsView *graphicsViewLeftImage;
    QGraphicsView *graphicsViewRightImage;
    QPushButton *pushButtonLeftImage;
    QPushButton *pushButtonRightImage;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPatchSizeText;
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSliderPatchSize;
    QLabel *labelPatchSize;

    void setupUi(QDialog *TemplateMatchingUI)
    {
        if (TemplateMatchingUI->objectName().isEmpty())
            TemplateMatchingUI->setObjectName(QString::fromUtf8("TemplateMatchingUI"));
        TemplateMatchingUI->resize(800, 662);
        graphicsViewLeftImage = new QGraphicsView(TemplateMatchingUI);
        graphicsViewLeftImage->setObjectName(QString::fromUtf8("graphicsViewLeftImage"));
        graphicsViewLeftImage->setGeometry(QRect(10, 10, 370, 555));
        graphicsViewRightImage = new QGraphicsView(TemplateMatchingUI);
        graphicsViewRightImage->setObjectName(QString::fromUtf8("graphicsViewRightImage"));
        graphicsViewRightImage->setGeometry(QRect(420, 10, 370, 555));
        pushButtonLeftImage = new QPushButton(TemplateMatchingUI);
        pushButtonLeftImage->setObjectName(QString::fromUtf8("pushButtonLeftImage"));
        pushButtonLeftImage->setGeometry(QRect(110, 570, 170, 32));
        pushButtonRightImage = new QPushButton(TemplateMatchingUI);
        pushButtonRightImage->setObjectName(QString::fromUtf8("pushButtonRightImage"));
        pushButtonRightImage->setGeometry(QRect(530, 570, 170, 32));
        widget = new QWidget(TemplateMatchingUI);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(200, 620, 391, 26));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelPatchSizeText = new QLabel(widget);
        labelPatchSizeText->setObjectName(QString::fromUtf8("labelPatchSizeText"));

        horizontalLayout_2->addWidget(labelPatchSizeText);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSliderPatchSize = new QSlider(widget);
        horizontalSliderPatchSize->setObjectName(QString::fromUtf8("horizontalSliderPatchSize"));
        horizontalSliderPatchSize->setMinimum(10);
        horizontalSliderPatchSize->setValue(20);
        horizontalSliderPatchSize->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSliderPatchSize);

        labelPatchSize = new QLabel(widget);
        labelPatchSize->setObjectName(QString::fromUtf8("labelPatchSize"));

        horizontalLayout->addWidget(labelPatchSize);


        horizontalLayout_2->addLayout(horizontalLayout);

        graphicsViewLeftImage->raise();
        graphicsViewRightImage->raise();
        pushButtonLeftImage->raise();
        pushButtonRightImage->raise();
        labelPatchSize->raise();
        horizontalSliderPatchSize->raise();

        retranslateUi(TemplateMatchingUI);

        QMetaObject::connectSlotsByName(TemplateMatchingUI);
    } // setupUi

    void retranslateUi(QDialog *TemplateMatchingUI)
    {
        TemplateMatchingUI->setWindowTitle(QApplication::translate("TemplateMatchingUI", "TemplateMatchingUI", 0, QApplication::UnicodeUTF8));
        pushButtonLeftImage->setText(QApplication::translate("TemplateMatchingUI", "Load Left Image", 0, QApplication::UnicodeUTF8));
        pushButtonRightImage->setText(QApplication::translate("TemplateMatchingUI", "Load Right Image", 0, QApplication::UnicodeUTF8));
        labelPatchSizeText->setText(QApplication::translate("TemplateMatchingUI", "Patch Size", 0, QApplication::UnicodeUTF8));
        labelPatchSize->setText(QApplication::translate("TemplateMatchingUI", "20", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TemplateMatchingUI: public Ui_TemplateMatchingUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATEMATCHINGUI_H
