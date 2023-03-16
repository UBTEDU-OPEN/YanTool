#include "customstyledmenu.h"

#include <QApplication>

CustomStyledMenu::CustomStyledMenu(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(false);

    auto mainLayout = new QVBoxLayout(this);
    auto widget = new QWidget(this);
    mainLayout->addWidget(widget);
    mainLayout->setContentsMargins(0,0,0,0);
    contentLayout_ = new QVBoxLayout(widget);

    qApp->installEventFilter(this);

    setFixedWidth(100);

    setStyleSheet("QWidget{background: white; border-radius: 2px; }" \
                  "QPushButton{background: white; border-radius: 2px;}" \
                  "QPushButton:hover{background:  #EEF5FA;}");
}

CustomStyledMenu::~CustomStyledMenu()
{
}

QPushButton *CustomStyledMenu::addMenuItem(QString text)
{
    auto btn = new QPushButton(text,this);
    contentLayout_->addWidget(btn);
    adjustSize();
    return btn;
}

bool CustomStyledMenu::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::Close:
    case QEvent::MouseButtonPress:
//    case QEvent::MouseButtonRelease:
//    case QEvent::MouseButtonDblClick:
        hide();
        break;
    default:
        break;
    }
    return false;
}
