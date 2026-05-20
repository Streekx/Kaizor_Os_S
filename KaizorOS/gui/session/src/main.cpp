#include <QApplication>
#include <QWidget>
#include <QScreen>
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDateTime>

class GlassDock : public QWidget
{
public:
    GlassDock(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setFixedSize(760, 100);

        auto *layout = new QHBoxLayout(this);

        layout->setContentsMargins(26, 18, 26, 18);
        layout->setSpacing(18);

        QStringList apps = {
            "⌘","◉","◎","⬢","⬡","◈","⬤"
        };

        for (const QString &app : apps)
        {
            QPushButton *btn =
                new QPushButton(app);

            btn->setFixedSize(58,58);

            btn->setCursor(Qt::PointingHandCursor);

            btn->setStyleSheet(R"(

                QPushButton {
                    background: rgba(255,255,255,0.10);
                    color: white;
                    border: none;
                    border-radius: 20px;
                    font-size: 24px;
                    font-weight: 700;
                }

                QPushButton:hover {
                    background: rgba(255,255,255,0.22);
                }

            )");

            auto *shadow =
                new QGraphicsDropShadowEffect;

            shadow->setBlurRadius(24);
            shadow->setOffset(0,6);

            btn->setGraphicsEffect(shadow);

            layout->addWidget(btn);
        }
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);

        p.setRenderHint(QPainter::Antialiasing);

        QPainterPath path;

        path.addRoundedRect(
            rect(),
            34,
            34
        );

        p.fillPath(
            path,
            QColor(20,20,30,215)
        );

        p.setPen(
            QColor(255,255,255,35)
        );

        p.drawPath(path);
    }
};

class TopBar : public QWidget
{
public:
    QLabel *clock;

    TopBar(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setFixedHeight(52);

        auto *layout =
            new QHBoxLayout(this);

        layout->setContentsMargins(
            22,
            10,
            22,
            10
        );

        QLabel *logo =
            new QLabel("Kaizor");

        logo->setStyleSheet(R"(

            color: white;
            font-size: 18px;
            font-weight: 700;

        )");

        QLabel *wifi =
            new QLabel("WiFi");

        QLabel *battery =
            new QLabel("100%");

        QString style = R"(

            color: rgba(255,255,255,0.85);
            font-size: 13px;
            font-weight: 600;
            padding-left: 12px;

        )";

        wifi->setStyleSheet(style);
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
        layout->addWidget(battery);
        layout->addWidget(clock);

        auto *timer =
            new QTimer(this);

        connect(
            timer,
            &QTimer::timeout,
            this,
            [=]() {

                clock->setText(
                    QDateTime::currentDateTime()
                    .toString("ddd dd MMM  hh:mm")
                );

            }
        );

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
            QColor(12,12,20,185)
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

class Desktop : public QWidget
{
public:
    TopBar *topbar;
    GlassDock *dock;

    Desktop()
    {
        setWindowFlags(
            Qt::FramelessWindowHint
        );

        resize(
            QGuiApplication::primaryScreen()->size()
        );

        topbar =
            new TopBar(this);

        topbar->setGeometry(
            0,
            0,
            width(),
            52
        );

        dock =
            new GlassDock(this);

        dock->move(
            (width() - dock->width()) / 2,
            height() - 140
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
            QColor(8,10,18)
        );

        bg.setColorAt(
            0.45,
            QColor(18,22,38)
        );

        bg.setColorAt(
            1.0,
            QColor(30,34,52)
        );

        p.fillRect(rect(), bg);

        p.setPen(
            QColor(255,255,255,35)
        );

        p.setFont(
            QFont("Sans", 58, QFont::Bold)
        );

        p.drawText(
            QRect(
                0,
                0,
                width(),
                height()-120
            ),
            Qt::AlignCenter,
            "Kaizor OS"
        );

        p.setFont(
            QFont("Sans", 16)
        );

        p.setPen(
            QColor(255,255,255,90)
        );

        p.drawText(
            QRect(
                0,
                height()/2 + 40,
                width(),
                40
            ),
            Qt::AlignHCenter,
            "Next Generation Desktop Experience"
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
