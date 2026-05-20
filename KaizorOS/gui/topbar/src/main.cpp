#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QScreen>

class KaizorTopBar : public QWidget
{
public:
    QLabel *clockLabel;

    KaizorTopBar()
    {
        setWindowFlags(
            Qt::FramelessWindowHint |
            Qt::WindowStaysOnTopHint
        );

        setAttribute(Qt::WA_TranslucentBackground);

        QRect screen =
            QGuiApplication::primaryScreen()->geometry();

        resize(screen.width(), 48);

        move(0, 0);

        QHBoxLayout *layout =
            new QHBoxLayout(this);

        layout->setContentsMargins(24, 8, 24, 8);

        QLabel *logo = new QLabel("Kaizor");

        logo->setStyleSheet(R"(
            color: white;
            font-size: 18px;
            font-weight: 700;
        )");

        QLabel *wifi = new QLabel("WiFi");
        QLabel *bt = new QLabel("BT");
        QLabel *battery = new QLabel("100%");

        QString labelStyle = R"(
            color: rgba(255,255,255,0.85);
            font-size: 14px;
            font-weight: 600;
            padding-left: 12px;
        )";

        wifi->setStyleSheet(labelStyle);
        bt->setStyleSheet(labelStyle);
        battery->setStyleSheet(labelStyle);

        clockLabel = new QLabel;

        clockLabel->setStyleSheet(R"(
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
        layout->addWidget(clockLabel);

        QTimer *timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, [=]() {
            clockLabel->setText(
                QDateTime::currentDateTime()
                .toString("ddd dd MMM  hh:mm")
            );
        });

        timer->start(1000);

        clockLabel->setText(
            QDateTime::currentDateTime()
            .toString("ddd dd MMM  hh:mm")
        );
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);

        painter.setRenderHint(
            QPainter::Antialiasing
        );

        painter.fillRect(
            rect(),
            QColor(10, 10, 18, 180)
        );

        painter.setPen(
            QColor(255,255,255,30)
        );

        painter.drawLine(
            0,
            height() - 1,
            width(),
            height() - 1
        );
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    KaizorTopBar topbar;

    topbar.show();

    return app.exec();
}
