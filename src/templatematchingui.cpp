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
    leftPixmap = NULL;
    rightPixmap = NULL;
    leftPatch = NULL;
    rightPatch = NULL;

    {
        int width = ui->graphicsViewLeftImage->size().width();
        int heigth = ui->graphicsViewLeftImage->size().height();
        QImage image("/Users/Abouee/Desktop/IMG_4934_resize.jpg");
        leftImage = QPixmap::fromImage(image);
        leftPixmap = graphicSceneLeftImage->addPixmap(leftImage.scaled(width - 10, heigth - 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        activeThread.setLeftImage(leftPixmap->pixmap());
    }

    {
        int width = ui->graphicsViewRightImage->size().width();
        int heigth = ui->graphicsViewRightImage->size().height();
        QImage image("/Users/Abouee/Desktop/IMG_4936_resize.jpg");
        rightImage = QPixmap::fromImage(image);
        rightPixmap = graphicSceneRightImage->addPixmap(rightImage.scaled(width - 10, heigth - 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        activeThread.setRightImage(rightPixmap->pixmap());
    }

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
        int width = ui->graphicsViewLeftImage->size().width();
        int heigth = ui->graphicsViewLeftImage->size().height();
        leftImage = QPixmap::fromImage(image);
        // qDebug() << "Width: " << leftImage.size().width() << " Height: " << leftImage.size().height();
        leftPixmap = graphicSceneLeftImage->addPixmap(leftImage.scaled(width - 10, heigth - 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        activeThread.setLeftImage(leftPixmap->pixmap());
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
        rightPixmap = graphicSceneRightImage->addPixmap(rightImage.scaled(width - 10, heigth - 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        activeThread.setRightImage(rightPixmap->pixmap());
    }
}

void TemplateMatchingUI::mousePressEvent(QMouseEvent * event)
{
    if (leftPixmap != NULL && rightPixmap != NULL)
    {
        if (leftPatch != NULL)
        {
            graphicSceneLeftImage->removeItem(leftPatch);
            leftPatch = NULL;
        }

        if(rightPatch != NULL)
        {
            graphicSceneRightImage->removeItem(rightPatch);
            rightPatch = NULL;
        }

        QPointF selectedPoint = ui->graphicsViewLeftImage->mapToScene(event->pos());
        selectedPoint.setX(selectedPoint.x() - ui->graphicsViewLeftImage->geometry().x() - 1);
        selectedPoint.setY(selectedPoint.y() - ui->graphicsViewLeftImage->geometry().y() - 1);
        QRect rectangle(selectedPoint.x() - 10, selectedPoint.y() - 10, 20, 20);
        QPen redPen = QPen(Qt::red);
        leftPatch = graphicSceneLeftImage->addRect(rectangle, redPen);
        qDebug() << "Selected Point: " << selectedPoint;
        QPointF final = activeThread.findCorrespondingTemplate(selectedPoint);
        qDebug() << "Final Point: " << final;
        QPen greenPen = QPen(Qt::green);
        QRect solution(final.x() + 10, final.y() + 10, 20, 20);
        rightPatch = graphicSceneRightImage->addRect(solution, greenPen);
    }
    else
    {

    }
}
