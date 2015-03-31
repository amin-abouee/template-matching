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
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TemplateMatchingUI
{
public:
    QGraphicsView *graphicsViewLeftImage;
    QGraphicsView *graphicsViewRightImage;
    QPushButton *pushButtonLeftImage;
    QPushButton *pushButtonRightImage;

    void setupUi(QDialog *TemplateMatchingUI)
    {
        if (TemplateMatchingUI->objectName().isEmpty())
            TemplateMatchingUI->setObjectName(QString::fromUtf8("TemplateMatchingUI"));
        TemplateMatchingUI->resize(800, 617);
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

        retranslateUi(TemplateMatchingUI);

        QMetaObject::connectSlotsByName(TemplateMatchingUI);
    } // setupUi

    void retranslateUi(QDialog *TemplateMatchingUI)
    {
        TemplateMatchingUI->setWindowTitle(QApplication::translate("TemplateMatchingUI", "TemplateMatchingUI", 0, QApplication::UnicodeUTF8));
        pushButtonLeftImage->setText(QApplication::translate("TemplateMatchingUI", "Load Left Image", 0, QApplication::UnicodeUTF8));
        pushButtonRightImage->setText(QApplication::translate("TemplateMatchingUI", "Load Right Image", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TemplateMatchingUI: public Ui_TemplateMatchingUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATEMATCHINGUI_H
