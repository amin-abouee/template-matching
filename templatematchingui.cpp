#include "templatematchingui.h"
#include "ui_templatematchingui.h"


TemplateMatchingUI::TemplateMatchingUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplateMatchingUI)
{
    ui->setupUi(this);
    graphicSceneLeftImage = new QGraphicsScene(this);
    graphicSceneRightImage = new QGraphicsScene(this);
    ui->graphicsViewLeftImage->setScene(graphicSceneLeftImage);
    ui->graphicsViewRightImage->setScene(graphicSceneRightImage);
}

TemplateMatchingUI::~TemplateMatchingUI()
{
    delete ui;
}

void TemplateMatchingUI::on_pushButtonLeftImage_clicked()
{
    graphicSceneLeftImage->clear();
    QString leftFileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"), QDir::currentPath());
    if (!leftFileName.isEmpty()) {
        QImage image(leftFileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(leftFileName));
            return;
        }
        //        testLabel.setPixmap(QPixmap::fromImage(image));
        //        testLabel.show();
        int width = ui->graphicsViewLeftImage->size().width();
        int heigth = ui->graphicsViewLeftImage->size().height();
        //        qDebug() << "Width: " << width << " Height: " << heigth ;
        leftImage = QPixmap::fromImage(image);
        qDebug() << "Width: " << leftImage.size().width() << " Height: " << leftImage.size().height() ;
        leftPixmap = graphicSceneLeftImage->addPixmap(leftImage.scaled(width-10,heigth-10,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void TemplateMatchingUI::on_pushButtonRightImage_clicked()
{
    graphicSceneRightImage->clear();
    QString rightFileName = QFileDialog::getOpenFileName(this,
                                                         tr("Open File"), QDir::currentPath());
    if (!rightFileName.isEmpty()) {
        QImage image(rightFileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(rightFileName));
            return;
        }
        int width = ui->graphicsViewRightImage->size().width();
        int heigth = ui->graphicsViewRightImage->size().height();
        rightImage = QPixmap::fromImage(image);
        rightPixmap = graphicSceneRightImage->addPixmap(rightImage.scaled(width-10,heigth-10,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void TemplateMatchingUI::mousePressEvent(QMouseEvent * event)
{
    QPointF selectedPoint = ui->graphicsViewLeftImage->mapToScene(event->pos());
    selectedPoint.setX(selectedPoint.x()-ui->graphicsViewLeftImage->geometry().x()-1);
    selectedPoint.setY(selectedPoint.y()-ui->graphicsViewLeftImage->geometry().y()-1);
    qDebug() << "Selected Point: " << selectedPoint;
}
