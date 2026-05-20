#include <QApplication>
#include <QWidget>
#include <QScreen>
#include <QPainter>
#include <QPainterPath>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>

class KaizorPanel : public QWidget
{
public:
    KaizorPanel()
    {
        setWindowFlags(
            Qt::FramelessWindowHint |
            Qt::WindowStaysOnTopHint
        );

        setAttribute(Qt::WA_TranslucentBackground);

        resize(700, 90);

        QRect screen =
            QGuiApplication::primaryScreen()->geometry();

        move(
            (screen.width() - width()) / 2,
            screen.height() - 130
        );

        auto *layout = new QHBoxLayout(this);

        layout->setContentsMargins(25, 18, 25, 18);
        layout->setSpacing(18);

        QStringList icons = {
            "◉", "◎", "◈", "⬢", "⬡", "◌", "⬤"
        };

        for (const QString &icon : icons)
        {
            QPushButton *btn = new QPushButton(icon);

            btn->setFixedSize(52, 52);

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

            auto *shadow = new QGraphicsDropShadowEffect;
            shadow->setBlurRadius(18);
            shadow->setOffset(0, 4);

            btn->setGraphicsEffect(shadow);

            layout->addWidget(btn);
        }

        setLayout(layout);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);

        painter.setRenderHint(QPainter::Antialiasing);

        QPainterPath path;

        path.addRoundedRect(rect(), 32, 32);

        painter.fillPath(
            path,
            QColor(20, 20, 20, 220)
        );

        painter.setPen(
            QColor(255,255,255,40)
        );

        painter.drawPath(path);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    KaizorPanel panel;

    panel.show();

    return app.exec();
}
