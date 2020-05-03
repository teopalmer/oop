#include "mycontroller.h"
#include "ui_mycontroller.h"
#include <QRegExpValidator>
#include <QIntValidator>
#include <QFileDialog>
#include <iostream>
#include <string.h>


#define MIN_PAR 10
Text_Error LineEditError;


MyController::MyController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyController)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    par = parent;
    ui->setupUi(this);

    Validator = new QRegExpValidator(QRegExp("^[+-]?[0-9]{0,5}(\\.|,|$)[0-9]{0,4}$"));
    ui->dxEdit->setValidator(Validator);
    ui->dyEdit->setValidator(Validator);
    ui->dzEdit->setValidator(Validator);
    ui->kxEdit->setValidator(Validator);
    ui->kyEdit->setValidator(Validator);
    ui->kzEdit->setValidator(Validator);
    ui->rot_xEdit->setValidator(Validator);
    ui->rot_yEdit->setValidator(Validator);
    ui->rot_zEdit->setValidator(Validator);
}

void MyController::GetScene(My_Scene *scene1) {
    this->scene.x_center = scene1->x_center;
    this->scene.y_center = scene1->y_center;
    this->scene.scene = scene1->scene;
}

MyController::~MyController()
{
    t_action act;
    act.free = true;
    delete Validator;
    main_controller(scene, act, FREE);
    delete ui;
}


double * MyController::GetData(vector <QLineEdit*> &vec)
{
    QString str;
    double *data = new double[vec.size()];
    double x;
    QString error;
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        str = vec[i]->text();
        x = analyze_text(str);
        switch(LineEditError)
        {
        case EMPTY:
            error = "Область текста пуста.\n Введите данные!";
            break;
        case E_SYMBOL:
            error = "Ошибочный символ\n "
                   "Разрешается использование только цифр, '.'',' и знаков табуляции";
            break;
        }
        if (LineEditError != NO_ER)
        {
            QErrorMessage errorMessage;
            errorMessage.showMessage(error);
            errorMessage.exec();
            break;
        }
        data[i] = x;
    }
   return data;
}


double analyze_text(QString str)
{
    LineEditError = NO_ER;
    if(str == "") {
        LineEditError = EMPTY;
        return 0;
    }
    str.replace(QString(","), QString("."));

    QStringList list = str.split(' ', QString::SkipEmptyParts);
    if(list.size() > 1) {
        LineEditError = E_SYMBOL;
        return 0;
    }

    double x;
    bool ok = true;
    for(int i = 0; i < list.size(); i++) {
        x = list.at(i).toDouble(&ok);
        //cout << tmp.toStdString() << " " << ok << " " << x << endl;
        if(!ok) {
            LineEditError = E_SYMBOL;
            return 0;
        }
    }
    return x;
}


void MyController::on_rotateButton_clicked()
{

    vector<QLineEdit*> edits;
    edits.push_back(ui->rot_xEdit);
    edits.push_back(ui->rot_yEdit);
    edits.push_back(ui->rot_zEdit);

    double *data = GetData(edits);

    if(LineEditError != NO_ER)
        return;


    t_action act;

    act.rotate.x_angle = data[0] * M_PI / 180;
    act.rotate.y_angle = data[1] * M_PI / 180;
    act.rotate.z_angle = data[2] * M_PI / 180;

    main_controller(scene, act, ROTATE);
    main_controller(scene, act, DRAW);
    delete[] data;
}

void MyController::on_scaleButton_clicked()
{

    vector<QLineEdit*> edits;
    edits.push_back(ui->kxEdit);
    edits.push_back(ui->kyEdit);
    edits.push_back(ui->kzEdit);

    double *data = GetData(edits);

    if(LineEditError != NO_ER)
        return;

    t_action act;

    act.scale.kx = data[0];
    act.scale.ky = data[1];
    act.scale.kz = data[2];

    main_controller(scene, act, SCALE);
    main_controller(scene, act, DRAW);
    delete[] data;

}

void MyController::on_moveButton_clicked()
{

    vector<QLineEdit*> edits;
    edits.push_back(ui->dxEdit);
    edits.push_back(ui->dyEdit);
    edits.push_back(ui->dzEdit);

    double *data = GetData(edits);

    if(LineEditError != NO_ER)
        return;


    t_action act;

    act.move.dx = data[0];
    act.move.dy = data[1];
    act.move.dz = data[2];

    main_controller(scene, act, MOVE);
    main_controller(scene, act, DRAW);
    delete[] data;
}


void MyController::on_fileButton_clicked()
{

    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt");
    if(str == "")
        return;
    t_action act;
    strcpy(act.create.fileName, str.toStdString().c_str());
    int res = main_controller(scene, act, CREATE);
    QString error = "";

    if(res == FILE_NOT_FOUND) {
        error = "Cannot open file";
    }
    else if(res == FILE_ERROR) {
        error = "Error format of data";
    }
    else if(res == MEMORY_ERROR) {
        error = "Memory error";
    }
    if(error != "") {
        QErrorMessage errorMessage;
        errorMessage.showMessage(error);
        errorMessage.exec();
        return;
    }
    main_controller(scene, act, DRAW);
}


void MyController::on_saveButton_clicked()
{
    setlocale (LC_ALL, "C");
    QString str = QFileDialog::getSaveFileName(0, "Save", "", "*.txt");

    if(str == "")
        return;

    t_action act;
    strcpy(act.create.fileName, str.toStdString().c_str());

    int res = main_controller(scene, act, SAVE);
    QString error = "";

    if(res == FILE_NOT_FOUND)
    {
        error = "Cannot open file";

    }
    else if (res == FILE_ERROR)
    {
        error = "Error format of data";
    }

    if(error != "") {
        QErrorMessage errorMessage;
        errorMessage.showMessage(error);
        errorMessage.exec();
        return;
    }
}
