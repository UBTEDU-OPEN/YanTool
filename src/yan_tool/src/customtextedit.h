#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>

class CustomStyledMenu;

class CustomTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit CustomTextEdit(QWidget *parent = Q_NULLPTR);

protected:
    void contextMenuEvent(QContextMenuEvent *ev) Q_DECL_OVERRIDE;

private:
    CustomStyledMenu *menu_;
};

#endif // CUSTOMTEXTEDIT_H
