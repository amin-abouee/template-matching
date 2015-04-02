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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPatchSizeText;
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSliderPatchSize;
    QLabel *labelPatchSize;

    void setupUi(QDialog *TemplateMatchingUI)
    {
        if (TemplateMatchingUI->objectName().isEmpty())
            TemplateMatchingUI->setObjectName(QString::fromUtf8("TemplateMatchingUI"));
        TemplateMatchingUI->resize(1290, 687);
        graphicsViewLeftImage = new QGraphicsView(TemplateMatchingUI);
        graphicsViewLeftImage->setObjectName(QString::fromUtf8("graphicsViewLeftImage"));
        graphicsViewLeftImage->setGeometry(QRect(10, 10, 600, 600));
        graphicsViewRightImage = new QGraphicsView(TemplateMatchingUI);
        graphicsViewRightImage->setObjectName(QString::fromUtf8("graphicsViewRightImage"));
        graphicsViewRightImage->setGeometry(QRect(630, 10, 600, 600));
        pushButtonLeftImage = new QPushButton(TemplateMatchingUI);
        pushButtonLeftImage->setObjectName(QString::fromUtf8("pushButtonLeftImage"));
        pushButtonLeftImage->setGeometry(QRect(230, 610, 170, 32));
        pushButtonRightImage = new QPushButton(TemplateMatchingUI);
        pushButtonRightImage->setObjectName(QString::fromUtf8("pushButtonRightImage"));
        pushButtonRightImage->setGeometry(QRect(880, 610, 170, 32));
        layoutWidget = new QWidget(TemplateMatchingUI);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(350, 650, 391, 26));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelPatchSizeText = new QLabel(layoutWidget);
        labelPatchSizeText->setObjectName(QString::fromUtf8("labelPatchSizeText"));

        horizontalLayout_2->addWidget(labelPatchSizeText);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSliderPatchSize = new QSlider(layoutWidget);
        horizontalSliderPatchSize->setObjectName(QString::fromUtf8("horizontalSliderPatchSize"));
        horizontalSliderPatchSize->setMinimum(10);
        horizontalSliderPatchSize->setValue(20);
        horizontalSliderPatchSize->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSliderPatchSize);

        labelPatchSize = new QLabel(layoutWidget);
        labelPatchSize->setObjectName(QString::fromUtf8("labelPatchSize"));

        horizontalLayout->addWidget(labelPatchSize);


        horizontalLayout_2->addLayout(horizontalLayout);

        layoutWidget->raise();
        graphicsViewLeftImage->raise();
        graphicsViewRightImage->raise();
        pushButtonLeftImage->raise();
        pushButtonRightImage->raise();

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
