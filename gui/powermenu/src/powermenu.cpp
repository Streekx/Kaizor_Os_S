#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

class PowerMenu : public QWidget
{
public:
    PowerMenu()
    {
        resize(520, 360);

        setWindowFlags(
            Qt::FramelessWindowHint |
            Qt::WindowStaysOnTopHint
        );

        setAttribute(
            Qt::WA_TranslucentBackground
        );

        auto *main =
            new QVBoxLayout(this);

        main->setContentsMargins(
            30,
            30,
            30,
            30
        );

        main->setSpacing(24);

        QLabel *title =
            new QLabel("Power");

        title->setStyleSheet(R"(

            color: white;
            font-size: 32px;
            font-weight: 800;

        )");

        QLabel *sub =
            new QLabel(
                "Choose an action"
            );

        sub->setStyleSheet(R"(

            color: rgba(255,255,255,0.70);
            font-size: 15px;

        )");

        auto *buttons =
            new QHBoxLayout;

        buttons->setSpacing(18);

        QStringList items = {
            "⏻",
            "↻",
            "🌙"
        };

        QStringList labels = {
            "Shutdown",
            "Restart",
            "Sleep"
        };

        for (int i = 0; i < items.size(); i++)
        {
            QWidget *card =
                new QWidget;

            card->setMinimumSize(130, 170);

            card->setStyleSheet(R"(

                background: rgba(255,255,255,0.08);
                border-radius: 28px;

            )");

            auto *layout =
                new QVBoxLayout(card);

            QLabel *icon =
                new QLabel(items[i]);

            icon->setAlignment(
                Qt::AlignCenter
            );

            icon->setStyleSheet(R"(

                color: white;
                font-size: 46px;

            )");

            QLabel *name =
                new QLabel(labels[i]);

            name->setAlignment(
                Qt::AlignCenter
            );

            name->setStyleSheet(R"(

                color: white;
                font-size: 16px;
                font-weight: 700;

            )");

            QPushButton *btn =
                new QPushButton("Select");

            btn->setFixedHeight(42);

            btn->setStyleSheet(R"(

                QPushButton {

                    background: rgba(255,255,255,0.10);
                    color: white;
                    border: none;
                    border-radius: 14px;
                    font-size: 14px;
                    font-weight: 700;

                }

                QPushButton:hover {

                    background: rgba(255,255,255,0.18);

                }

            )");

            layout->addStretch();
            layout->addWidget(icon);
            layout->addSpacing(10);
            layout->addWidget(name);
            layout->addStretch();
            layout->addWidget(btn);

            buttons->addWidget(card);
        }

        auto *shadow =
            new QGraphicsDropShadowEffect;

        shadow->setBlurRadius(35);
        shadow->setOffset(0,10);

        setGraphicsEffect(shadow);

        main->addWidget(title);
        main->addWidget(sub);
        main->addSpacing(10);
        main->addLayout(buttons);
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

    PowerMenu menu;

    menu.show();

    return app.exec();
}
