#include "customtextedit.h"

#include <QContextMenuEvent>
#include <QApplication>
#include <QClipboard>

#include "customstyledmenu.h"

CustomTextEdit::CustomTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    menu_ = new CustomStyledMenu(this);
    QPushButton *btn = menu_->addMenuItem(tr("Copy"));
    connect(btn,&QPushButton::clicked,this,&CustomTextEdit::copy);
    btn = menu_->addMenuItem(tr("Cut"));
    connect(btn,&QPushButton::clicked,this,&CustomTextEdit::cut);
    btn = menu_->addMenuItem(tr("Paste"));
    connect(btn,&QPushButton::clicked,this,&CustomTextEdit::paste);
    btn = menu_->addMenuItem(tr("Undo"));
    connect(btn,&QPushButton::clicked,this,&CustomTextEdit::undo);
    btn = menu_->addMenuItem(tr("Redo"));
    connect(btn,&QPushButton::clicked,this,&CustomTextEdit::redo);
}

void CustomTextEdit::contextMenuEvent(QContextMenuEvent *ev)
{
    menu_->move(ev->globalPos());
    menu_->show();
}
