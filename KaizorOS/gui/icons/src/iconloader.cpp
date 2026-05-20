#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

class IconPreview : public QWidget
{
public:
    IconPreview()
    {
        resize(820, 220);

        setWindowTitle("Kaizor Icons");

        auto *layout =
            new QHBoxLayout(this);

        layout->setContentsMargins(
            28,
            28,
            28,
            28
        );

        layout->setSpacing(22);

        QStringList icons = {
            "🖥",
            "🌐",
            "📁",
            "⚙",
            "🎵",
            "📝",
            "🛒",
            "🖼"
        };

        for (const QString &icon : icons)
        {
            QWidget *card =
                new QWidget;

            card->setFixedSize(82, 110);

            card->setStyleSheet(R"(

                background: rgba(28,28,36,0.95);
                border-radius: 24px;

            )");

            auto *shadow =
                new QGraphicsDropShadowEffect;

            shadow->setBlurRadius(24);
            shadow->setOffset(0,6);

            card->setGraphicsEffect(shadow);

            auto *v =
                new QVBoxLayout(card);

            QLabel *iconLabel =
                new QLabel(icon);

            iconLabel->setAlignment(
                Qt::AlignCenter
            );

            iconLabel->setStyleSheet(R"(

                color: white;
                font-size: 34px;

            )");

            QLabel *name =
                new QLabel("App");

            name->setAlignment(
                Qt::AlignCenter
            );

            name->setStyleSheet(R"(

                color: rgba(255,255,255,0.75);
                font-size: 12px;
                font-weight: 600;

            )");

            v->addStretch();
            v->addWidget(iconLabel);
            v->addWidget(name);
            v->addStretch();

            layout->addWidget(card);
        }
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
            QColor(12,12,18)
        );

        bg.setColorAt(
            1.0,
            QColor(22,22,32)
        );

        p.fillRect(rect(), bg);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    IconPreview preview;

    preview.show();

    return app.exec();
}
