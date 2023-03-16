#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>

namespace Ui {
class CustomButton;
}

class CustomButton : public QWidget
{
    Q_OBJECT

public:
    explicit CustomButton(QWidget *parent = 0);
    ~CustomButton();
    void setBgUrl(QString url, QString pressedUrl);
    void setText(QString text);

signals:
    void btnClicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::CustomButton *ui;
    QString bgUrl_;
    QString bgPressedUrl_;
    QString currentUrl_;
};

#endif // CUSTOMBUTTON_H
