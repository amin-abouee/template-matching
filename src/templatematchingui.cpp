#include "templatematchingui.h"
#include "ui_templatematchingui.h"


TemplateMatchingUI::TemplateMatchingUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplateMatchingUI),
    leftPixmap(NULL),
    rightPixmap(NULL),
    leftPatch(NULL),
    rightPatch(NULL),
    activeThread(20)
{
    ui->setupUi(this);
    graphicSceneLeftImage = new QGraphicsScene(this);
    graphicSceneRightImage = new QGraphicsScene(this);
    ui->graphicsViewLeftImage->setScene(graphicSceneLeftImage);
    ui->graphicsViewLeftImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewLeftImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsViewRightImage->setScene(graphicSceneRightImage);
    ui->graphicsViewRightImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewRightImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->horizontalSliderPatchSize->setValue(20);
    connect(ui->horizontalSliderPatchSize, SIGNAL(valueChanged(int)) , ui->labelPatchSize, SLOT(setNum(int)));
    // {
    //     int width = ui->graphicsViewLeftImage->size().width();
    //     int heigth = ui->graphicsViewLeftImage->size().height();
    //     QImage image("/Users/Abouee/Desktop/IMG_4936_resize.jpg");
    //     QPixmap leftImage = QPixmap::fromImage(image);
    //     leftPixmap = graphicSceneLeftImage->addPixmap(leftImage.scaled(width - 10, heigth - 10, Qt::KeepAspectRatio));
    //     activeThread.setLeftImage(leftPixmap->pixmap());
    // }

    // {
    //     int width = ui->graphicsViewRightImage->size().width();
    //     int heigth = ui->graphicsViewRightImage->size().height();
    //     QImage image("/Users/Abouee/Desktop/IMG_4934_resize.jpg");
    //     QPixmap rightImage = QPixmap::fromImage(image);
    //     rightPixmap = graphicSceneRightImage->addPixmap(rightImage.scaled(width - 10, heigth - 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //     activeThread.setRightImage(rightPixmap->pixmap());
    // }

}

TemplateMatchingUI::~TemplateMatchingUI()
{
    delete ui;
}

void TemplateMatchingUI::on_pushButtonLeftImage_clicked()
{
    graphicSceneLeftImage->clear();
    leftPatch = NULL;
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
        QPixmap leftImage = QPixmap::fromImage(image);
        leftPixmap = graphicSceneLeftImage->addPixmap(leftImage.scaled(width - 10, heigth - 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        activeThread.setLeftImage(leftPixmap->pixmap());
    }
}

void TemplateMatchingUI::on_pushButtonRightImage_clicked()
{
    graphicSceneRightImage->clear();
    rightPatch = NULL;
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
        QPixmap rightImage = QPixmap::fromImage(image);
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

        if (rightPatch != NULL)
        {
            graphicSceneRightImage->removeItem(rightPatch);
            rightPatch = NULL;
        }

        std::size_t patchSize = ui->horizontalSliderPatchSize->value();
        QPointF selectedPoint = ui->graphicsViewLeftImage->mapToScene(event->pos());
        selectedPoint.setX(selectedPoint.x() - ui->graphicsViewLeftImage->geometry().x() - 1);
        selectedPoint.setY(selectedPoint.y() - ui->graphicsViewLeftImage->geometry().y() - 1);

        if (selectedPoint.x() >= 0 && selectedPoint.x() <= leftPixmap->pixmap().width() &&
                selectedPoint.y() >= 0 && selectedPoint.y() <= rightPixmap->pixmap().height())
        {
            qDebug() << "Selected Point: " << selectedPoint;
            QPen redPen = QPen(Qt::red);
            QRect referenceRect(selectedPoint.x() - patchSize / 2, selectedPoint.y() - patchSize / 2, patchSize, patchSize);
            leftPatch = graphicSceneLeftImage->addRect(referenceRect, redPen);

            activeThread.setPatchSize(patchSize);
            QPointF final = activeThread.findCorrespondingTemplate(selectedPoint);

            qDebug() << "Final Point: " << final;
            QPen greenPen = QPen(Qt::green);
            QRect followingRect(final.x(), final.y(), patchSize, patchSize);
            rightPatch = graphicSceneRightImage->addRect(followingRect, greenPen);
        }
    }
    else
    {

    }
}
