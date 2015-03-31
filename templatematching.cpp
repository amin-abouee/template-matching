#include "templatematching.h"
#include "ui_templatematching.h"

TemplateMatching::TemplateMatching(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplateMatching)
{
    ui->setupUi(this);
}

TemplateMatching::~TemplateMatching()
{
    delete ui;
}
