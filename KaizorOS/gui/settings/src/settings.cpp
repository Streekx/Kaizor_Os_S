#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QGraphicsDropShadowEffect>

class SettingsWindow : public QWidget
{
public:
    SettingsWindow()
    {
        resize(1000, 680);

        setWindowFlags(
            Qt::FramelessWindowHint
        );

        setAttribute(
            Qt::WA_TranslucentBackground
        );

        auto *main =
            new QHBoxLayout(this);

        main->setContentsMargins(
            26,
            26,
            26,
            26
        );

        main->setSpacing(24);

        QWidget *sidebar =
            new QWidget;

        sidebar->setFixedWidth(240);

        sidebar->setStyleSheet(R"(

            background: rgba(255,255,255,0.06);
            border-radius: 28px;

        )");

        auto *sideLayout =
            new QVBoxLayout(sidebar);

        sideLayout->setContentsMargins(
            18,
            18,
            18,
            18
        );

        QStringList items = {
            "Appearance",
            "Network",
            "Bluetooth",
            "Sound",
            "Wallpaper",
            "Notifications",
            "Power",
            "About"
        };

        for (const QString &item : items)
        {
            QPushButton *btn =
                new QPushButton(item);

            btn->setFixedHeight(48);

            btn->setStyleSheet(R"(

                QPushButton {

                    background: transparent;
                    color: white;
                    border: none;
                    border-radius: 16px;
                    text-align: left;
                    padding-left: 18px;
                    font-size: 15px;
                    font-weight: 600;

                }

                QPushButton:hover {

                    background: rgba(255,255,255,0.10);

                }

            )");

            sideLayout->addWidget(btn);
        }

        sideLayout->addStretch();

        QWidget *content =
            new QWidget;

        content->setStyleSheet(R"(

            background: rgba(255,255,255,0.05);
            border-radius: 30px;

        )");

        auto *contentLayout =
            new QVBoxLayout(content);

        contentLayout->setContentsMargins(
            30,
            30,
            30,
            30
        );

        QLabel *title =
            new QLabel("Appearance");

        title->setStyleSheet(R"(

            color: white;
            font-size: 32px;
            font-weight: 800;

        )");

        QLabel *subtitle =
            new QLabel(
                "Customize your Kaizor OS experience"
            );

        subtitle->setStyleSheet(R"(

            color: rgba(255,255,255,0.70);
            font-size: 15px;

        )");

        QWidget *card =
            new QWidget;

        card->setMinimumHeight(220);

        card->setStyleSheet(R"(

            background: rgba(255,255,255,0.06);
            border-radius: 26px;

        )");

        auto *cardLayout =
            new QVBoxLayout(card);

        QLabel *brightness =
            new QLabel("Brightness");

        brightness->setStyleSheet(R"(

            color: white;
            font-size: 18px;
            font-weight: 700;

        )");

        QSlider *slider =
            new QSlider(Qt::Horizontal);

        slider->setValue(75);

        QCheckBox *blur =
            new QCheckBox(
                "Enable blur effects"
            );

        blur->setChecked(true);

        blur->setStyleSheet(R"(

            color: white;
            font-size: 15px;

        )");

        QCheckBox *animations =
            new QCheckBox(
                "Enable animations"
            );

        animations->setChecked(true);

        animations->setStyleSheet(R"(

            color: white;
            font-size: 15px;

        )");

        cardLayout->addWidget(brightness);
        cardLayout->addSpacing(10);
        cardLayout->addWidget(slider);
        cardLayout->addSpacing(20);
        cardLayout->addWidget(blur);
        cardLayout->addWidget(animations);
        cardLayout->addStretch();

        contentLayout->addWidget(title);
        contentLayout->addSpacing(8);
        contentLayout->addWidget(subtitle);
        contentLayout->addSpacing(26);
        contentLayout->addWidget(card);
        contentLayout->addStretch();

        auto *shadow =
            new QGraphicsDropShadowEffect;

        shadow->setBlurRadius(35);
        shadow->setOffset(0,10);

        setGraphicsEffect(shadow);

        main->addWidget(sidebar);
        main->addWidget(content);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);

        p.setRenderHint(
            QPainter::Antialiasing
        );

        QPainterPath path;

        path.addRoundedRect(
            rect(),
            36,
            36
        );

        p.fillPath(
            path,
            QColor(18,18,28,235)
        );

        p.setPen(
            QColor(255,255,255,35)
        );

        p.drawPath(path);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SettingsWindow settings;

    settings.show();

    return app.exec();
}
