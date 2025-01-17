#ifndef LOADING_H
#define LOADING_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class Loading;
}

class Loading : public QDialog
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = nullptr);
     int progressValue;
    ~Loading();

private:
    Ui::Loading *ui;

    QTimer* timer;
private slots:
    void updateProgress();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // LOADING_H
