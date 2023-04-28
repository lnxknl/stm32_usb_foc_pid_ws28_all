/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include <openglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    OpenGLWidget *openglwidget;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_4;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_5;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBox_10;
    QLabel *label_15;
    QDoubleSpinBox *doubleSpinBox_11;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBox_6;
    QLabel *label_10;
    QSpinBox *spinBox;
    QLabel *label_6;
    QFrame *line_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_3;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_7;
    QLabel *label_12;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_9;
    QDoubleSpinBox *doubleSpinBox_8;
    QFrame *line;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QGridLayout *gridLayout;
    QWidget *page_3;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_4;
    QSpinBox *spinBox_2;
    QLabel *label_16;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QDoubleSpinBox *doubleSpinBox_12;
    QPushButton *pushButton_5;
    QLabel *label_17;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBox_13;
    QPushButton *pushButton_6;
    QLabel *label_19;
    QDoubleSpinBox *doubleSpinBox_14;
    QPushButton *pushButton_7;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        openglwidget = new OpenGLWidget(Widget);
        openglwidget->setObjectName(QString::fromUtf8("openglwidget"));

        gridLayout_2->addWidget(openglwidget, 3, 3, 2, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(20);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_7 = new QLabel(Widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        doubleSpinBox_4 = new QDoubleSpinBox(Widget);
        doubleSpinBox_4->setObjectName(QString::fromUtf8("doubleSpinBox_4"));
        doubleSpinBox_4->setMaximum(5.000000000000000);
        doubleSpinBox_4->setSingleStep(0.010000000000000);

        horizontalLayout_5->addWidget(doubleSpinBox_4);

        label_8 = new QLabel(Widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_5->addWidget(label_8);

        doubleSpinBox_5 = new QDoubleSpinBox(Widget);
        doubleSpinBox_5->setObjectName(QString::fromUtf8("doubleSpinBox_5"));
        doubleSpinBox_5->setMaximum(5.000000000000000);
        doubleSpinBox_5->setSingleStep(0.010000000000000);

        horizontalLayout_5->addWidget(doubleSpinBox_5);

        label_14 = new QLabel(Widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_5->addWidget(label_14);

        doubleSpinBox_10 = new QDoubleSpinBox(Widget);
        doubleSpinBox_10->setObjectName(QString::fromUtf8("doubleSpinBox_10"));
        doubleSpinBox_10->setReadOnly(true);
        doubleSpinBox_10->setMaximum(2000.000000000000000);

        horizontalLayout_5->addWidget(doubleSpinBox_10);

        label_15 = new QLabel(Widget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_5->addWidget(label_15);

        doubleSpinBox_11 = new QDoubleSpinBox(Widget);
        doubleSpinBox_11->setObjectName(QString::fromUtf8("doubleSpinBox_11"));
        doubleSpinBox_11->setMaximum(2000.000000000000000);
        doubleSpinBox_11->setSingleStep(0.010000000000000);

        horizontalLayout_5->addWidget(doubleSpinBox_11);

        label_9 = new QLabel(Widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_5->addWidget(label_9);

        doubleSpinBox_6 = new QDoubleSpinBox(Widget);
        doubleSpinBox_6->setObjectName(QString::fromUtf8("doubleSpinBox_6"));
        doubleSpinBox_6->setMaximum(100.000000000000000);
        doubleSpinBox_6->setSingleStep(0.010000000000000);

        horizontalLayout_5->addWidget(doubleSpinBox_6);

        label_10 = new QLabel(Widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_5->addWidget(label_10);

        spinBox = new QSpinBox(Widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setReadOnly(true);
        spinBox->setMaximum(360);

        horizontalLayout_5->addWidget(spinBox);


        gridLayout_2->addLayout(horizontalLayout_5, 6, 0, 1, 5);

        label_6 = new QLabel(Widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_6, 2, 1, 1, 4);

        line_2 = new QFrame(Widget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShadow(QFrame::Raised);
        line_2->setLineWidth(2);
        line_2->setFrameShape(QFrame::VLine);

        gridLayout_2->addWidget(line_2, 4, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(12);
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(Widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(10);
        comboBox->setFont(font2);

        horizontalLayout->addWidget(comboBox);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 1);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(26);
        font3.setBold(false);
        font3.setWeight(50);
        label->setFont(font3);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        gridLayout_2->addWidget(label, 0, 0, 1, 5);

        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_3->addWidget(pushButton_3, 2, 2, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 0, 0, 1, 1);

        doubleSpinBox_7 = new QDoubleSpinBox(groupBox);
        doubleSpinBox_7->setObjectName(QString::fromUtf8("doubleSpinBox_7"));
        doubleSpinBox_7->setMaximum(3.000000000000000);
        doubleSpinBox_7->setSingleStep(0.010000000000000);

        gridLayout_3->addWidget(doubleSpinBox_7, 0, 1, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 1, 0, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_3->addWidget(pushButton, 0, 2, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_3->addWidget(pushButton_2, 1, 2, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_3->addWidget(label_13, 2, 0, 1, 1);

        doubleSpinBox_9 = new QDoubleSpinBox(groupBox);
        doubleSpinBox_9->setObjectName(QString::fromUtf8("doubleSpinBox_9"));
        doubleSpinBox_9->setMaximum(5.000000000000000);
        doubleSpinBox_9->setSingleStep(0.010000000000000);

        gridLayout_3->addWidget(doubleSpinBox_9, 2, 1, 1, 1);

        doubleSpinBox_8 = new QDoubleSpinBox(groupBox);
        doubleSpinBox_8->setObjectName(QString::fromUtf8("doubleSpinBox_8"));
        doubleSpinBox_8->setMaximum(3.000000000000000);
        doubleSpinBox_8->setSingleStep(0.010000000000000);

        gridLayout_3->addWidget(doubleSpinBox_8, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 4, 1, 1, 1);

        line = new QFrame(Widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setEnabled(true);
        line->setFrameShadow(QFrame::Raised);
        line->setLineWidth(3);
        line->setFrameShape(QFrame::HLine);

        gridLayout_2->addWidget(line, 5, 0, 1, 5);

        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout = new QGridLayout(page_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gridLayout_4 = new QGridLayout(page_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton_4 = new QPushButton(page_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_4->addWidget(pushButton_4, 0, 2, 1, 1);

        spinBox_2 = new QSpinBox(page_3);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setMaximum(360);

        gridLayout_4->addWidget(spinBox_2, 0, 1, 1, 1);

        label_16 = new QLabel(page_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_4->addWidget(label_16, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(page_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        doubleSpinBox_12 = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_12->setObjectName(QString::fromUtf8("doubleSpinBox_12"));

        gridLayout_5->addWidget(doubleSpinBox_12, 0, 1, 1, 1);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout_5->addWidget(pushButton_5, 0, 3, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_5->addWidget(label_17, 0, 0, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_5->addWidget(label_18, 1, 0, 1, 1);

        doubleSpinBox_13 = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_13->setObjectName(QString::fromUtf8("doubleSpinBox_13"));

        gridLayout_5->addWidget(doubleSpinBox_13, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout_5->addWidget(pushButton_6, 1, 3, 1, 1);

        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_5->addWidget(label_19, 2, 0, 1, 1);

        doubleSpinBox_14 = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_14->setObjectName(QString::fromUtf8("doubleSpinBox_14"));

        gridLayout_5->addWidget(doubleSpinBox_14, 2, 1, 1, 1);

        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        gridLayout_5->addWidget(pushButton_7, 2, 3, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 3);

        stackedWidget->addWidget(page_3);

        gridLayout_2->addWidget(stackedWidget, 3, 0, 2, 1);

#if QT_CONFIG(shortcut)
#endif // QT_CONFIG(shortcut)

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "Uq", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "Ud", nullptr));
        label_14->setText(QCoreApplication::translate("Widget", "\347\224\265\346\265\201Iq(ma)", nullptr));
        label_15->setText(QCoreApplication::translate("Widget", "\347\224\265\346\265\201Id(ma)", nullptr));
        label_9->setText(QCoreApplication::translate("Widget", "\351\200\237\345\272\246", nullptr));
        label_10->setText(QCoreApplication::translate("Widget", "\350\247\222\345\272\246", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "\350\277\236\346\216\245\344\270\255......", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\351\200\211\351\241\271", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "\347\251\272\351\227\262", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "\345\274\200\347\216\257\346\216\247\345\210\266", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Widget", "\344\275\215\347\275\256\346\216\247\345\210\266", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Widget", "\345\212\233\347\237\251\346\216\247\345\210\266", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Widget", "\351\200\237\345\272\246\346\216\247\345\210\266", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("Widget", "HID\351\224\256\347\233\230\346\216\247\345\210\266", nullptr));

        label->setText(QCoreApplication::translate("Widget", "ValentineHP_4008_FOC_HID", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\345\205\254\345\205\261\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "\346\233\264\346\226\260", nullptr));
        label_11->setText(QCoreApplication::translate("Widget", "Uq", nullptr));
        label_12->setText(QCoreApplication::translate("Widget", "Ud", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\346\233\264\346\226\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\346\233\264\346\226\260", nullptr));
        label_13->setText(QCoreApplication::translate("Widget", "\351\200\237\345\272\246", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "\346\233\264\346\226\260", nullptr));
        label_16->setText(QCoreApplication::translate("Widget", "\350\247\222\345\272\246  ", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "PID\345\217\202\346\225\260", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Widget", "\346\233\264\346\226\260", nullptr));
        label_17->setText(QCoreApplication::translate("Widget", "P   ", nullptr));
        label_18->setText(QCoreApplication::translate("Widget", "I   ", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Widget", "\346\233\264\346\226\260", nullptr));
        label_19->setText(QCoreApplication::translate("Widget", "D", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Widget", "\346\233\264\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
