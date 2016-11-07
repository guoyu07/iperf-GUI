#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>

class WelcomeScreen : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeScreen(QWidget *parent = 0);

signals:

public slots:
    void onClientButtonClicked();
    void onExitButtonClicked();
};

#endif // WELCOMESCREEN_H
