#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QTimer>

class NotificationCard : public QWidget
{
public:
    NotificationCard(
        const QString &title,
        const QString &message
    )
    {
        setMinimumHeight(110);

        setStyleSheet(R"(

            background: rgba(255,255,255,0.08);
            border-radius: 24px;

        )");

        auto *layout =
            new QVBoxLayout(this);

        layout->setContentsMargins(
            20,
            18,
            20,
            18
        );

        QLabel *head =
            new QLabel(title);

        head->setStyleSheet(R"(

            color: white;
            font-size: 18px;
            font-weight: 700;

        )");

        QLabel *body =
            new QLabel(message);

        body->setWordWrap(true);

        body->setStyleSheet(R"(

            color: rgba(255,255,255,0.75);
            font-size: 14px;

        )");

        layout->addWidget(head);
        layout->addSpacing(8);
        layout->addWidget(body);
    }
};

class NotificationCenter : public QWidget
{
public:
    NotificationCenter()
    {
        resize(460, 620);

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
            24,
            24,
            24,
            24
        );

        main->setSpacing(18);

        QLabel *title =
            new QLabel("Notifications");

        title->setStyleSheet(R"(

            color: white;
            font-size: 30px;
            font-weight: 800;

        )");

        QLabel *sub =
            new QLabel(
                "Recent system activity"
            );

        sub->setStyleSheet(R"(

            color: rgba(255,255,255,0.70);
            font-size: 15px;

        )");

        main->addWidget(title);
        main->addWidget(sub);
        main->addSpacing(10);

        NotificationCard *n1 =
            new NotificationCard(
                "System",
                "Kaizor OS session started successfully."
            );

        NotificationCard *n2 =
            new NotificationCard(
                "Network",
                "WiFi connected to Home Network."
            );

        NotificationCard *n3 =
            new NotificationCard(
                "Updates",
                "New theme assets available."
            );

        NotificationCard *n4 =
            new NotificationCard(
                "Launcher",
                "Applications indexed successfully."
            );

        main->addWidget(n1);
        main->addWidget(n2);
        main->addWidget(n3);
        main->addWidget(n4);
        main->addStretch();

        auto *shadow =
            new QGraphicsDropShadowEffect;

        shadow->setBlurRadius(40);
        shadow->setOffset(0,12);

        setGraphicsEffect(shadow);

        QTimer::singleShot(
            600,
            this,
            [=]() {

                move(
                    QApplication::primaryScreen()
                        ->geometry()
                        .width() - width() - 28,
                    70
                );

            }
        );
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
            34,
            34
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

    NotificationCenter center;

    center.show();

    return app.exec();
}
