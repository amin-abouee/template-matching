#include "templatematchingui.h"
#include "ui_templatematchingui.h"


TemplateMatchingUI::TemplateMatchingUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplateMatchingUI),
    graphicSceneLeftImage(new QGraphicsScene(this)),
    graphicSceneRightImage(new QGraphicsScene(this)),
    leftPixmap(NULL),
    rightPixmap(NULL),
    leftPatch(NULL),
    rightPatch(NULL),
    initilPatchSize(20),
    padSizeGraphicScene(10),
    padSizeGraphicView(1),
    templateMatcher(initilPatchSize)
{
    ui->setupUi(this);
    ui->graphicsViewLeftImage->setScene(graphicSceneLeftImage);
    ui->graphicsViewLeftImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewLeftImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewRightImage->setScene(graphicSceneRightImage);
    ui->graphicsViewRightImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewRightImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->horizontalSliderPatchSize->setValue(initilPatchSize);
    connect(ui->horizontalSliderPatchSize, SIGNAL(valueChanged(int)) , ui->labelPatchSize, SLOT(setNum(int)));
}

TemplateMatchingUI::~TemplateMatchingUI()
{
    delete ui;
}

void TemplateMatchingUI::on_pushButtonLeftImage_clicked()
{
    // clear the left graphic scene and left patch indicator
    graphicSceneLeftImage->clear();
    leftPatch = NULL;

    // read the file path of left image and load the image inside the Qimage image var
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
        // convert the Qimage to Qpixmap for pushing inside the left graphic scene
        QPixmap leftImage = QPixmap::fromImage(image);
        leftPixmap = graphicSceneLeftImage->addPixmap(leftImage.scaled(width - padSizeGraphicScene, heigth - padSizeGraphicScene, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        // set the left image in templateMatcher object to use in OpenCV. The data should be converted from Qt:: to cv::Mat !
        templateMatcher.setLeftImage(leftPixmap->pixmap());
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
        rightPixmap = graphicSceneRightImage->addPixmap(rightImage.scaled(width - padSizeGraphicScene, heigth - padSizeGraphicScene, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        templateMatcher.setRightImage(rightPixmap->pixmap());
    }
}

void TemplateMatchingUI::mousePressEvent(QMouseEvent * event)
{
    // check the both left and right images. Their values should be filled already by the image data
    if (leftPixmap != NULL && rightPixmap != NULL)
    {
        // remove the left and right rectangles indicator
        removeRectItemsFromScene();

        // read the position of mouse click from the input event and also the patch size around the each selected point.
        std::size_t patchSize = ui->horizontalSliderPatchSize->value();
        QPointF selectedPoint = ui->graphicsViewLeftImage->mapToScene(event->pos());
        // compute the accurate location of mouse relative to the left graphic view
        selectedPoint.setX(selectedPoint.x() - ui->graphicsViewLeftImage->geometry().x() - padSizeGraphicView);
        selectedPoint.setY(selectedPoint.y() - ui->graphicsViewLeftImage->geometry().y() - padSizeGraphicView);

        // check the boundary of mouse click. It should be located inside the left image border
        if (selectedPoint.x() >= 0 && selectedPoint.x() <= leftPixmap->pixmap().width() &&
                selectedPoint.y() >= 0 && selectedPoint.y() <= rightPixmap->pixmap().height())
        {
            // draw a blue rectangle around the selected patch.
            QPen bluePen = QPen(Qt::blue);
            QRect referenceRect(selectedPoint.x() - patchSize / 2, selectedPoint.y() - patchSize / 2, patchSize, patchSize);
            leftPatch = graphicSceneLeftImage->addRect(referenceRect, bluePen);

            // set the patch size and find the corresponding template (patch) in the following image
            templateMatcher.setPatchSize(patchSize);
            QPointF final = templateMatcher.findCorrespondingTemplate(selectedPoint);

            // draw a green rectangles around the computed patch in the right side
            QPen greenPen = QPen(Qt::green);
            QRect followingRect(final.x(), final.y(), patchSize, patchSize);
            rightPatch = graphicSceneRightImage->addRect(followingRect, greenPen);
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Please select images for the both sides");
    }
}

void TemplateMatchingUI::removeRectItemsFromScene()
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
}
