/********************************************************************************
** Form generated from reading UI file 'matrixwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXWINDOW_H
#define UI_MATRIXWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatrixWindow
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *MatrixWindow)
    {
        if (MatrixWindow->objectName().isEmpty())
            MatrixWindow->setObjectName(QString::fromUtf8("MatrixWindow"));
        MatrixWindow->resize(692, 465);
        scrollArea = new QScrollArea(MatrixWindow);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(20, 20, 651, 421));
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 635, 405));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(MatrixWindow);

        QMetaObject::connectSlotsByName(MatrixWindow);
    } // setupUi

    void retranslateUi(QWidget *MatrixWindow)
    {
        MatrixWindow->setWindowTitle(QCoreApplication::translate("MatrixWindow", "Evolution space", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixWindow: public Ui_MatrixWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXWINDOW_H
