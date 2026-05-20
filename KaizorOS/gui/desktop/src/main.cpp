#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QScreen>
#include <QLinearGradient>
#include <QTimer>
#include <QDateTime>

class KaizorDesktop : public QWidget
{
public:
    KaizorDesktop()
    {
        setWindowFlags(
            Qt::FramelessWindowHint
        );

        resize(
            QGuiApplication::primaryScreen()->size()
        );

        showFullScreen();

        QTimer *timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, [=]() {
            update();
        });

        timer->start(1000);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);

        painter.setRenderHint(
            QPainter::Antialiasing
        );

        QLinearGradient bg(
            rect().topLeft(),
            rect().bottomRight()
        );

        bg.setColorAt(0.0, QColor(10, 10, 18));
        bg.setColorAt(0.5, QColor(18, 18, 30));
        bg.setColorAt(1.0, QColor(28, 28, 45));

        painter.fillRect(rect(), bg);

        painter.setPen(
            QColor(255,255,255,30)
        );

        painter.setFont(
            QFont("Sans", 42, QFont::Bold)
        );

        painter.drawText(
            rect(),
            Qt::AlignCenter,
            "Kaizor OS"
        );

        painter.setPen(
            QColor(255,255,255,120)
        );

        painter.setFont(
            QFont("Sans", 16)
        );

        QString time =
            QDateTime::currentDateTime()
            .toString("hh:mm AP");

        painter.drawText(
            QRect(0, 40, width(), 40),
            Qt::AlignHCenter,
            time
        );
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    KaizorDesktop desktop;

    desktop.show();

    return app.exec();
}
