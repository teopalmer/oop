#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include "work.h"

#include <QWidget>
#include <QtGui>
#include <QErrorMessage>
#include <QString>
#include <QStringList>
#include <string>
#include <stdio.h>
#include <vector>
#include <QLineEdit>
#include <QGraphicsScene>

using namespace std;
enum Text_Error { EMPTY, E_SYMBOL, NO_ER };


namespace Ui {
class MyController;
}

class MyController : public QWidget
{
    Q_OBJECT

public:
    explicit MyController(QWidget *parent = 0);
    ~MyController();
    void GetScene(My_Scene *scene);
signals:
    void AnswerChange(Model &mod);
    void SceneChange(QGraphicsScene *scene);
private slots:
    void on_rotateButton_clicked();
    void on_scaleButton_clicked();
    void on_moveButton_clicked();
    void on_fileButton_clicked();
    void on_saveButton_clicked();

private:

    double *GetData(vector <QLineEdit*> &vec);
    My_Scene scene;
    Ui::MyController *ui;
    Model model;
    QWidget *par;
    QRegExpValidator *Validator;

};

double analyze_text(QString str);
#endif // MYCONTROLLER_H
