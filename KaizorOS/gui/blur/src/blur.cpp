#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>

class BlurPanel : public QWidget
{
public:
    BlurPanel(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        resize(1200, 760);

        auto *main =
            new QVBoxLayout(this);

        main->setContentsMargins(
            40,
            40,
            40,
            40
        );

        main->setSpacing(26);

        QLabel *title =
            new QLabel("Kaizor Blur Engine");

        title->setStyleSheet(R"(

            color: white;
            font-size: 34px;
            font-weight: 800;

        )");

        QLabel *sub =
            new QLabel(
                "Glassmorphism + Frosted UI Rendering"
            );

        sub->setStyleSheet(R"(

            color: rgba(255,255,255,0.70);
            font-size: 16px;

        )");

        main->addWidget(title);
        main->addWidget(sub);

        QWidget *glass =
            new QWidget;

        glass->setMinimumHeight(320);

        glass->setStyleSheet(R"(

            background: rgba(255,255,255,0.08);
            border-radius: 36px;
            border: 1px solid rgba(255,255,255,0.10);

        )");

        auto *blur =
            new QGraphicsBlurEffect;

        blur->setBlurRadius(12);

        glass->setGraphicsEffect(blur);

        auto *shadow =
            new QGraphicsDropShadowEffect;

        shadow->setBlurRadius(35);
        shadow->setOffset(0,10);

        glass->setGraphicsEffect(shadow);

        auto *glassLayout =
            new QVBoxLayout(glass);

        glassLayout->setContentsMargins(
            30,
            30,
            30,
            30
        );

        QLabel *panelTitle =
            new QLabel("Frosted Panel");

        panelTitle->setStyleSheet(R"(

            color: white;
            font-size: 24px;
            font-weight: 700;

        )");

        QLabel *panelText =
            new QLabel(
                "Unified modern translucent rendering layer for Kaizor OS."
            );

        panelText->setWordWrap(true);

        panelText->setStyleSheet(R"(

            color: rgba(255,255,255,0.75);
            font-size: 15px;

        )");

        QPushButton *button =
            new QPushButton("Open");

        button->setFixedSize(160,52);

        button->setStyleSheet(R"(

            QPushButton {

                background: rgba(255,255,255,0.10);
                color: white;
                border: none;
                border-radius: 18px;
                font-size: 15px;
                font-weight: 700;

            }

            QPushButton:hover {

                background: rgba(255,255,255,0.18);

            }

        )");

        glassLayout->addWidget(panelTitle);
        glassLayout->addSpacing(12);
        glassLayout->addWidget(panelText);
        glassLayout->addStretch();
        glassLayout->addWidget(button);

        main->addSpacing(24);
        main->addWidget(glass);
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
            QColor(8,10,18)
        );

        bg.setColorAt(
            0.5,
            QColor(18,22,36)
        );

        bg.setColorAt(
            1.0,
            QColor(30,34,50)
        );

        p.fillRect(rect(), bg);

        QRadialGradient glow1(
            width()*0.25,
            height()*0.3,
            260
        );

        glow1.setColorAt(
            0.0,
            QColor(80,120,255,90)
        );

        glow1.setColorAt(
            1.0,
            QColor(0,0,0,0)
        );

        p.setBrush(glow1);
        p.setPen(Qt::NoPen);

        p.drawEllipse(
            QPointF(
                width()*0.25,
                height()*0.3
            ),
            260,
            260
        );

        QRadialGradient glow2(
            width()*0.8,
            height()*0.7,
            320
        );

        glow2.setColorAt(
            0.0,
            QColor(180,90,255,90)
        );

        glow2.setColorAt(
            1.0,
            QColor(0,0,0,0)
        );

        p.setBrush(glow2);

        p.drawEllipse(
            QPointF(
                width()*0.8,
                height()*0.7
            ),
            320,
            320
        );
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BlurPanel panel;

    panel.show();

    return app.exec();
}
