#include "customlabel.h"

#include <QContextMenuEvent>
#include <QApplication>
#include <QClipboard>

#include "customstyledmenu.h"

CustomLabel::CustomLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent,f)
{
    menu_ = new CustomStyledMenu(this);
    QPushButton *btn = menu_->addMenuItem(tr("Copy"));
    connect(btn,&QPushButton::clicked,this,&CustomLabel::copy);
}

void CustomLabel::contextMenuEvent(QContextMenuEvent *ev)
{
    auto text = selectedText();
    if(text.isEmpty()) {
        return;
    }

    menu_->move(ev->globalPos());
    menu_->show();
}

void CustomLabel::copy()
{
    auto text = selectedText();
    if(!text.isEmpty()) {
       QApplication::clipboard()->setText(text);
    }
}
