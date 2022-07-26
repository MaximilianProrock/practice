#include "colourselectionwindow.h"
#include "ui_colourselectionwindow.h"

ColourSelectionWindow::ColourSelectionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColourSelectionWindow)
{
    ui->setupUi(this);

}

ColourSelectionWindow::~ColourSelectionWindow()
{
    delete ui;
}

QVector3D ColourSelectionWindow::getColourVector()
{
    return colourVector;
}

bool ColourSelectionWindow::getStateOfNormalMap()
{
    return normalMapOn;
}

void ColourSelectionWindow::on_pushButton_clicked()
{
    normalMapOn = ui->NormalMapCheckBox->isChecked();
    colourVector.setX(ui->RedHorizontalSlider->value() / 100);
    colourVector.setY(ui->GreenHorizontalSlider_3->value() / 100);
    colourVector.setZ(ui->BlueHorizontalSlider_2->value() / 100);
}
