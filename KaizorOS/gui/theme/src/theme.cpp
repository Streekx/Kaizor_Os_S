#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>

class ThemePreview : public QWidget
{
public:
    ThemePreview()
    {
        resize(1100, 680);

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
            new QLabel("Kaizor Theme Engine");

        title->setStyleSheet(R"(

            color: white;
            font-size: 34px;
            font-weight: 800;

        )");

        QLabel *subtitle =
            new QLabel(
                "Modern Glass UI Components"
            );

        subtitle->setStyleSheet(R"(

            color: rgba(255,255,255,0.65);
            font-size: 16px;

        )");

        main->addWidget(title);
        main->addWidget(subtitle);

        auto *cards =
            new QHBoxLayout;

        cards->setSpacing(22);

        for (int i = 0; i < 3; i++)
        {
            QWidget *card =
                new QWidget;

            card->setMinimumSize(300, 240);

            card->setStyleSheet(R"(

                background: rgba(28,28,36,0.92);
                border-radius: 30px;

            )");

            auto *shadow =
                new QGraphicsDropShadowEffect;

            shadow->setBlurRadius(30);
            shadow->setOffset(0,8);

            card->setGraphicsEffect(shadow);

            auto *layout =
                new QVBoxLayout(card);

            QLabel *head =
                new QLabel("Glass Card");

            head->setStyleSheet(R"(

                color: white;
                font-size: 22px;
                font-weight: 700;

            )");

            QLabel *desc =
                new QLabel(
                    "Unified Kaizor visual component."
                );

            desc->setWordWrap(true);

            desc->setStyleSheet(R"(

                color: rgba(255,255,255,0.70);
                font-size: 14px;

            )");

            QPushButton *btn =
                new QPushButton("Open");

            btn->setFixedHeight(48);

            btn->setStyleSheet(R"(

                QPushButton {
                    background: rgba(255,255,255,0.10);
                    color: white;
                    border: none;
                    border-radius: 16px;
                    font-size: 15px;
                    font-weight: 700;
                }

                QPushButton:hover {
                    background: rgba(255,255,255,0.18);
                }

            )");

            layout->addWidget(head);
            layout->addSpacing(12);
            layout->addWidget(desc);
            layout->addStretch();
            layout->addWidget(btn);

            cards->addWidget(card);
        }

        main->addSpacing(18);
        main->addLayout(cards);
        main->addStretch();
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
            QColor(18,20,32)
        );

        bg.setColorAt(
            1.0,
            QColor(28,32,48)
        );

        p.fillRect(rect(), bg);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ThemePreview preview;

    preview.show();

    return app.exec();
}
