#include "client.h"
#include "trafficlight.h"
#include "numpad.h"
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QSlider>
#include <QSettings>

Client::Client(QWidget *parent) : QWidget(parent)
{
    QSettings settings;

    setFixedSize(800, 480);
    QGridLayout *layout = new QGridLayout();
    listening = true;

    //traffic light
    tl = new TrafficLight();
    tl->setColor(TrafficLight::yellow);

    //labels
    QFont font;
    font.setBold(true);
    font.setPointSize(20);

    QFont font2;
    font2.setBold(true);
    font2.setPointSize(15);

    QLabel *labelIP = new QLabel("IP");
    labelIP->setFont(font);
    QLabel *labelModus = new QLabel("Modus");
    labelModus->setFont(font);
    QLabel *labelRuntime = new QLabel("Laufzeit");
    labelRuntime->setFont(font);
    QLabel *labelBandwidth = new QLabel("Bandbreite");
    labelBandwidth->setFont(font);
    labelBandwidth->setFixedWidth(180);

    //data entry fields
    fieldIP = new QLineEdit();
    fieldIP->setFont(font);
    fieldIP->setPlaceholderText("z.B. 10.22.0.160");

    simplex = new QRadioButton("Simplex");
    simplex->setFont(font2);
    duplex = new QRadioButton("Duplex");
    duplex->setFont(font2);
    duplex->setChecked(true);

    fieldRuntime = new QLineEdit();
    fieldRuntime->setFixedWidth(100);
    fieldRuntime->setPlaceholderText("10-1000s");

    fieldBandwidth = new QLineEdit();
    fieldBandwidth->setFixedWidth(100);
    fieldBandwidth->setPlaceholderText("1-100 Mbit/s");

    //sliders
    sliderRuntime = new QSlider(Qt::Horizontal);
    sliderRuntime->setRange(1, 100);

    sliderBandwidth = new QSlider(Qt::Horizontal);
    sliderBandwidth->setRange(1, 100);

    //buttons
    QPushButton *exitButton = new QPushButton("Schliessen");
    startButton = new QPushButton("Starten");
    QPushButton *keyboard = new QPushButton("...");
    keyboard->setFixedWidth(30);

    //set position in grid
    layout->addWidget(tl, 0, 0, 4, 1, Qt::AlignCenter);
    layout->addWidget(labelIP, 0, 1);
    layout->addWidget(labelModus, 1, 1);
    layout->addWidget(labelRuntime, 2, 1);
    layout->addWidget(labelBandwidth, 3, 1);
    layout->addWidget(fieldIP, 0, 2, 1, 2);
    layout->addWidget(duplex, 1, 2);
    layout->addWidget(simplex, 1, 3);
    layout->addWidget(fieldRuntime, 2, 2);
    layout->addWidget(fieldBandwidth, 3, 2);
    layout->addWidget(sliderRuntime, 2, 3);
    layout->addWidget(sliderBandwidth, 3, 3);
    layout->addWidget(keyboard, 0, 4);
    layout->addWidget(startButton, 4, 1, 1, 2);
    layout->addWidget(exitButton, 4, 3, 1, 1);

    //connectors
    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()));
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    QObject::connect(keyboard, SIGNAL(clicked()), this, SLOT(onKeyboardClicked()));
    QObject::connect(sliderRuntime, SIGNAL(valueChanged(int)), this, SLOT(onRuntimeChanged(int)));
    QObject::connect(sliderBandwidth, SIGNAL(valueChanged(int)), this, SLOT(onBandwidthChanged(int)));

    // set default form values (and trigger "valueChanged" signal automatically)
    sliderRuntime->setValue(settings.value("default.runtime").toInt());
    sliderBandwidth->setValue(settings.value("default.bandwidth").toInt());

    setLayout(layout);
}

void Client::onExitButtonClicked()
{
    this->close();
}

void Client::onStartButtonClicked()
{
    if(listening){
        tl->setColor(TrafficLight::green);
        listening = false;
        startButton->setText("Stop");

    }else{
        tl->setColor(TrafficLight::red);
        startButton->setText("Fortsetzen");
        listening = true;

    }

}

void Client::onKeyboardClicked()
{
    NumPad *keyboard = new NumPad(this);
    keyboard->showFullScreen();
}

void Client::onRuntimeChanged(int value)
{
    fieldRuntime->setText(QString::number(value*10)+" s");
}

void Client::onBandwidthChanged(int value)
{
    fieldBandwidth->setText(QString::number(value)+" Mbit/s");
}

void Client::setIP(QString s)
{
    fieldIP->setText(s);
}

QString Client::getIP()
{
    return fieldIP->text();
}
