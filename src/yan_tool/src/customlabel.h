#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomStyledMenu;

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent=Q_NULLPTR, Qt::WindowFlags f=Qt::WindowFlags());

protected:
    void contextMenuEvent(QContextMenuEvent *ev) Q_DECL_OVERRIDE;

private slots:
    void copy();

private:
    CustomStyledMenu *menu_;
};

#endif // CUSTOMLABEL_H
