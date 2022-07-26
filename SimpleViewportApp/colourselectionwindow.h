#ifndef COLOURSELECTIONWINDOW_H
#define COLOURSELECTIONWINDOW_H

#include <QDialog>
#include <QVector3D>
#include <QSettings>

namespace Ui {
class ColourSelectionWindow;
}

class ColourSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ColourSelectionWindow(QWidget *parent = nullptr);
    ~ColourSelectionWindow();

    QVector3D getColourVector();
    bool getStateOfNormalMap();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ColourSelectionWindow *ui;

    QVector3D colourVector;
    bool normalMapOn = false;
};

#endif // COLOURSELECTIONWINDOW_H
