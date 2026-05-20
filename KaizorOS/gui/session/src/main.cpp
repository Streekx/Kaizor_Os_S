#include <QApplication>
#include <QWidget>
#include <QScreen>
#include <QPainter>
#include <QLinearGradient>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QDateTime>

class TopBar : public QWidget
{
public:
    QLabel *clock;

    TopBar(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setFixedHeight(48);

        QHBoxLayout *layout =
            new QHBoxLayout(this);

        layout->setContentsMargins(20, 8, 20, 8);

        QLabel *logo =
            new QLabel("Kaizor OS");

        logo->setStyleSheet(R"(
            color: white;
            font-size: 18px;
            font-weight: 700;
        )");

        QLabel *wifi =
            new QLabel("WiFi");

        QLabel *bt =
            new QLabel("BT");

        QLabel *battery =
            new QLabel("100%");

        QString style = R"(
            color: rgba(255,255,255,0.85);
            font-size: 13px;
            font-weight: 600;
            padding-left: 12px;
        )";

        wifi->setStyleSheet(style);
        bt->setStyleSheet(style);
        battery->setStyleSheet(style);

        clock = new QLabel;

        clock->setStyleSheet(R"(
            color: white;
            font-size: 14px;
            font-weight: 700;
            padding-left: 18px;
        )");

        layout->addWidget(logo);
        layout->addStretch();
        layout->addWidget(wifi);
        layout->addWidget(bt);
        layout->addWidget(battery);
        layout->addWidget(clock);

        QTimer *timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, [=]() {
            clock->setText(
                QDateTime::currentDateTime()
                .toString("ddd dd MMM  hh:mm")
            );
        });

        timer->start(1000);

        clock->setText(
            QDateTime::currentDateTime()
            .toString("ddd dd MMM  hh:mm")
        );
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);

        p.fillRect(
            rect(),
            QColor(15,15,20,190)
        );

        p.setPen(
            QColor(255,255,255,25)
        );

        p.drawLine(
            0,
            height()-1,
            width(),
            height()-1
        );
    }
};

class Dock : public QWidget
{
public:
    Dock(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setFixedSize(720, 95);

        QHBoxLayout *layout =
            new QHBoxLayout(this);

        layout->setContentsMargins(
            25, 18, 25, 18
        );

        layout->setSpacing(18);

        QStringList icons = {
            "◉","◎","◈","⬢","⬡","◌","⬤"
        };

        for (const QString &icon : icons)
        {
            QPushButton *btn =
                new QPushButton(icon);

            btn->setFixedSize(52,52);

            btn->setStyleSheet(R"(
                QPushButton {
                    background: rgba(255,255,255,0.08);
                    color: white;
                    border: none;
                    border-radius: 18px;
                    font-size: 22px;
                    font-weight: bold;
                }

                QPushButton:hover {
                    background: rgba(255,255,255,0.16);
                }
            )");

            auto *shadow =
                new QGraphicsDropShadowEffect;

            shadow->setBlurRadius(18);
            shadow->setOffset(0,4);

            btn->setGraphicsEffect(shadow);

            layout->addWidget(btn);
        }
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
            32,
            32
        );

        p.fillPath(
            path,
            QColor(20,20,25,220)
        );

        p.setPen(
            QColor(255,255,255,35)
        );

        p.drawPath(path);
    }
};

class Desktop : public QWidget
{
public:
    TopBar *topbar;
    Dock *dock;

    Desktop()
    {
        setWindowFlags(
            Qt::FramelessWindowHint
        );

        resize(
            QGuiApplication::primaryScreen()->size()
        );

        topbar = new TopBar(this);

        topbar->setGeometry(
            0,
            0,
            width(),
            48
        );

        dock = new Dock(this);

        dock->move(
            (width() - dock->width()) / 2,
            height() - 130
        );

        showFullScreen();
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);

        p.setRenderHint(
            QPainter::Antialiasing
        );

        QLinearGradient bg(
            rect().topLeft(),
            rect().bottomRight()
        );

        bg.setColorAt(
            0.0,
            QColor(10,10,18)
        );

        bg.setColorAt(
            0.5,
            QColor(18,18,28)
        );

        bg.setColorAt(
            1.0,
            QColor(28,28,42)
        );

        p.fillRect(rect(), bg);

        p.setPen(
            QColor(255,255,255,40)
        );

        p.setFont(
            QFont("Sans", 42, QFont::Bold)
        );

        p.drawText(
            rect(),
            Qt::AlignCenter,
            "Kaizor OS"
        );
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Desktop desktop;

    desktop.show();

    return app.exec();
}
