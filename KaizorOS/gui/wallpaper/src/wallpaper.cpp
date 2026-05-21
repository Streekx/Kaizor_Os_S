#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QTimer>

class WallpaperEngine : public QWidget
{
public:
    float offset = 0.0f;

    WallpaperEngine()
    {
        resize(1400, 850);

        QTimer *timer =
            new QTimer(this);

        connect(
            timer,
            &QTimer::timeout,
            this,
            [=]() {

                offset += 0.003f;

                if (offset > 1.0f)
                    offset = 0.0f;

                update();

            }
        );

        timer->start(16);
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
            0.5,
            QColor(18,24,42)
        );

        bg.setColorAt(
            1.0,
            QColor(32,38,60)
        );

        p.fillRect(rect(), bg);

        QRadialGradient glow1(
            width() * (0.2 + offset),
            height() * 0.3,
            260
        );

        glow1.setColorAt(
            0.0,
            QColor(90,120,255,120)
        );

        glow1.setColorAt(
            1.0,
            QColor(0,0,0,0)
        );

        p.setBrush(glow1);
        p.setPen(Qt::NoPen);

        p.drawEllipse(
            QPointF(
                width() * (0.2 + offset),
                height() * 0.3
            ),
            260,
            260
        );

        QRadialGradient glow2(
            width() * (0.8 - offset),
            height() * 0.7,
            320
        );

        glow2.setColorAt(
            0.0,
            QColor(180,90,255,120)
        );

        glow2.setColorAt(
            1.0,
            QColor(0,0,0,0)
        );

        p.setBrush(glow2);

        p.drawEllipse(
            QPointF(
                width() * (0.8 - offset),
                height() * 0.7
            ),
            320,
            320
        );

        p.setPen(
            QColor(255,255,255,45)
        );

        p.setFont(
            QFont("Sans", 54, QFont::Bold)
        );

        p.drawText(
            rect(),
            Qt::AlignCenter,
            "Kaizor OS"
        );

        p.setFont(
            QFont("Sans", 18)
        );

        p.setPen(
            QColor(255,255,255,85)
        );

        p.drawText(
            QRect(
                0,
                height()/2 + 55,
                width(),
                40
            ),
            Qt::AlignHCenter,
            "Dynamic Wallpaper Engine"
        );
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WallpaperEngine engine;

    engine.show();

    return app.exec();
}
