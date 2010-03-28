/********************************************************************************
** Form generated from reading ui file 'screenshotdialog.ui'
**
** Created: Sun Mar 28 16:45:47 2010
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SCREENSHOTDIALOG_H
#define UI_SCREENSHOTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenshotUi
{
public:
    QWidget *dockWidgetContents;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *drawSettingsLayout;
    QLabel *penLabel;
    QSpinBox *penBox;
    QSpacerItem *drawSettingsSpacer;
    QPushButton *colorButton;
    QHBoxLayout *drawToolLayout;
    QSpacerItem *drawToolSpacer;
    QPushButton *freeButton;
    QPushButton *lineButton;
    QPushButton *rectButton;
    QPushButton *ellipseButton;
    QPushButton *textButton;
    QPushButton *rubberButton;
    QHBoxLayout *undoLayout;
    QPushButton *undoButton;
    QPushButton *redoButton;
    QPushButton *clearButton;
    QFrame *line;
    QHBoxLayout *imageSizeLayout;
    QSpacerItem *imageSizeSpacer;
    QLabel *widthLabel;
    QSpinBox *widthBox;
    QLabel *heightLabel;
    QSpinBox *heightBox;
    QHBoxLayout *formatLayout;
    QLabel *formatLabel;
    QComboBox *formatBox;
    QHBoxLayout *pathLayout;
    QLabel *pathLabel;
    QLineEdit *pathLine;
    QPushButton *pathButton;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *saveSpacer;
    QPushButton *saveButton;

    void setupUi(QDockWidget *ScreenshotUi)
    {
        if (ScreenshotUi->objectName().isEmpty())
            ScreenshotUi->setObjectName(QString::fromUtf8("ScreenshotUi"));
        ScreenshotUi->resize(305, 325);
        ScreenshotUi->setFocusPolicy(Qt::StrongFocus);
        ScreenshotUi->setFloating(true);
        ScreenshotUi->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        ScreenshotUi->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dockWidgetContents->setMouseTracking(true);
        dockWidgetContents->setFocusPolicy(Qt::StrongFocus);
        verticalLayoutWidget = new QWidget(dockWidgetContents);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 291, 281));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        drawSettingsLayout = new QHBoxLayout();
        drawSettingsLayout->setObjectName(QString::fromUtf8("drawSettingsLayout"));
        penLabel = new QLabel(verticalLayoutWidget);
        penLabel->setObjectName(QString::fromUtf8("penLabel"));

        drawSettingsLayout->addWidget(penLabel);

        penBox = new QSpinBox(verticalLayoutWidget);
        penBox->setObjectName(QString::fromUtf8("penBox"));
        penBox->setMinimum(1);
        penBox->setMaximum(5);

        drawSettingsLayout->addWidget(penBox);

        drawSettingsSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        drawSettingsLayout->addItem(drawSettingsSpacer);

        colorButton = new QPushButton(verticalLayoutWidget);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));
        colorButton->setMinimumSize(QSize(100, 0));

        drawSettingsLayout->addWidget(colorButton);


        verticalLayout->addLayout(drawSettingsLayout);

        drawToolLayout = new QHBoxLayout();
        drawToolLayout->setObjectName(QString::fromUtf8("drawToolLayout"));
        drawToolSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        drawToolLayout->addItem(drawToolSpacer);

        freeButton = new QPushButton(verticalLayoutWidget);
        freeButton->setObjectName(QString::fromUtf8("freeButton"));
        freeButton->setMinimumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/usr/share/extcalc/data/free.png"), QSize(), QIcon::Normal, QIcon::On);
        freeButton->setIcon(icon);

        drawToolLayout->addWidget(freeButton);

        lineButton = new QPushButton(verticalLayoutWidget);
        lineButton->setObjectName(QString::fromUtf8("lineButton"));
        lineButton->setMinimumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/usr/share/extcalc/data/line.png"), QSize(), QIcon::Normal, QIcon::On);
        lineButton->setIcon(icon1);

        drawToolLayout->addWidget(lineButton);

        rectButton = new QPushButton(verticalLayoutWidget);
        rectButton->setObjectName(QString::fromUtf8("rectButton"));
        rectButton->setMinimumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/usr/share/extcalc/data/rect.png"), QSize(), QIcon::Normal, QIcon::On);
        rectButton->setIcon(icon2);

        drawToolLayout->addWidget(rectButton);

        ellipseButton = new QPushButton(verticalLayoutWidget);
        ellipseButton->setObjectName(QString::fromUtf8("ellipseButton"));
        ellipseButton->setMinimumSize(QSize(30, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/usr/share/extcalc/data/circle.png"), QSize(), QIcon::Normal, QIcon::On);
        ellipseButton->setIcon(icon3);

        drawToolLayout->addWidget(ellipseButton);

        textButton = new QPushButton(verticalLayoutWidget);
        textButton->setObjectName(QString::fromUtf8("textButton"));
        textButton->setMinimumSize(QSize(30, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/usr/share/extcalc/data/text.png"), QSize(), QIcon::Normal, QIcon::On);
        textButton->setIcon(icon4);

        drawToolLayout->addWidget(textButton);

        rubberButton = new QPushButton(verticalLayoutWidget);
        rubberButton->setObjectName(QString::fromUtf8("rubberButton"));
        rubberButton->setMinimumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/usr/share/extcalc/data/rubber.png"), QSize(), QIcon::Normal, QIcon::On);
        rubberButton->setIcon(icon5);

        drawToolLayout->addWidget(rubberButton);

        drawToolLayout->setStretch(0, 1);

        verticalLayout->addLayout(drawToolLayout);

        undoLayout = new QHBoxLayout();
        undoLayout->setObjectName(QString::fromUtf8("undoLayout"));
        undoButton = new QPushButton(verticalLayoutWidget);
        undoButton->setObjectName(QString::fromUtf8("undoButton"));

        undoLayout->addWidget(undoButton);

        redoButton = new QPushButton(verticalLayoutWidget);
        redoButton->setObjectName(QString::fromUtf8("redoButton"));

        undoLayout->addWidget(redoButton);

        clearButton = new QPushButton(verticalLayoutWidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        undoLayout->addWidget(clearButton);


        verticalLayout->addLayout(undoLayout);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        imageSizeLayout = new QHBoxLayout();
        imageSizeLayout->setObjectName(QString::fromUtf8("imageSizeLayout"));
        imageSizeSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        imageSizeLayout->addItem(imageSizeSpacer);

        widthLabel = new QLabel(verticalLayoutWidget);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));

        imageSizeLayout->addWidget(widthLabel);

        widthBox = new QSpinBox(verticalLayoutWidget);
        widthBox->setObjectName(QString::fromUtf8("widthBox"));
        widthBox->setMinimum(1);
        widthBox->setMaximum(1024);
        widthBox->setValue(512);

        imageSizeLayout->addWidget(widthBox);

        heightLabel = new QLabel(verticalLayoutWidget);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));

        imageSizeLayout->addWidget(heightLabel);

        heightBox = new QSpinBox(verticalLayoutWidget);
        heightBox->setObjectName(QString::fromUtf8("heightBox"));
        heightBox->setMinimum(1);
        heightBox->setMaximum(1024);
        heightBox->setValue(512);

        imageSizeLayout->addWidget(heightBox);


        verticalLayout->addLayout(imageSizeLayout);

        formatLayout = new QHBoxLayout();
        formatLayout->setObjectName(QString::fromUtf8("formatLayout"));
        formatLabel = new QLabel(verticalLayoutWidget);
        formatLabel->setObjectName(QString::fromUtf8("formatLabel"));

        formatLayout->addWidget(formatLabel);

        formatBox = new QComboBox(verticalLayoutWidget);
        formatBox->setObjectName(QString::fromUtf8("formatBox"));

        formatLayout->addWidget(formatBox);


        verticalLayout->addLayout(formatLayout);

        pathLayout = new QHBoxLayout();
        pathLayout->setObjectName(QString::fromUtf8("pathLayout"));
        pathLabel = new QLabel(verticalLayoutWidget);
        pathLabel->setObjectName(QString::fromUtf8("pathLabel"));

        pathLayout->addWidget(pathLabel);

        pathLine = new QLineEdit(verticalLayoutWidget);
        pathLine->setObjectName(QString::fromUtf8("pathLine"));

        pathLayout->addWidget(pathLine);

        pathButton = new QPushButton(verticalLayoutWidget);
        pathButton->setObjectName(QString::fromUtf8("pathButton"));
        pathButton->setMinimumSize(QSize(30, 30));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/usr/share/extcalc/data/open.png"), QSize(), QIcon::Normal, QIcon::On);
        pathButton->setIcon(icon6);

        pathLayout->addWidget(pathButton);


        verticalLayout->addLayout(pathLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        saveSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(saveSpacer);

        saveButton = new QPushButton(verticalLayoutWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout_4->addWidget(saveButton);


        verticalLayout->addLayout(horizontalLayout_4);

        ScreenshotUi->setWidget(dockWidgetContents);

        retranslateUi(ScreenshotUi);

        QMetaObject::connectSlotsByName(ScreenshotUi);
    } // setupUi

    void retranslateUi(QDockWidget *ScreenshotUi)
    {
        ScreenshotUi->setWindowTitle(QApplication::translate("ScreenshotUi", "Screenshot", 0, QApplication::UnicodeUTF8));
        penLabel->setText(QApplication::translate("ScreenshotUi", "Pen Width", 0, QApplication::UnicodeUTF8));
        colorButton->setText(QApplication::translate("ScreenshotUi", "Color", 0, QApplication::UnicodeUTF8));
        freeButton->setText(QString());
        lineButton->setText(QString());
        rectButton->setText(QString());
        ellipseButton->setText(QString());
        textButton->setText(QString());
        rubberButton->setText(QString());
        undoButton->setText(QApplication::translate("ScreenshotUi", "Undo", 0, QApplication::UnicodeUTF8));
        redoButton->setText(QApplication::translate("ScreenshotUi", "Redo", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("ScreenshotUi", "Clear", 0, QApplication::UnicodeUTF8));
        widthLabel->setText(QApplication::translate("ScreenshotUi", "Image width:", 0, QApplication::UnicodeUTF8));
        heightLabel->setText(QApplication::translate("ScreenshotUi", "height:", 0, QApplication::UnicodeUTF8));
        formatLabel->setText(QApplication::translate("ScreenshotUi", "File Format", 0, QApplication::UnicodeUTF8));
        pathLabel->setText(QApplication::translate("ScreenshotUi", "Path:", 0, QApplication::UnicodeUTF8));
        pathButton->setText(QString());
        saveButton->setText(QApplication::translate("ScreenshotUi", "Save", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ScreenshotUi);
    } // retranslateUi

};

namespace Ui {
    class ScreenshotUi: public Ui_ScreenshotUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENSHOTDIALOG_H
