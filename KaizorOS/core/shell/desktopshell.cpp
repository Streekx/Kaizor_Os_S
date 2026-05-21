#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QProcess>
#include <QTimer>

class DesktopShell : public QWidget
{
public:
    DesktopShell()
    {
        resize(1440, 900);

        setWindowTitle("Kaizor OS");

        auto *main =
            new QVBoxLayout(this);

        main->setContentsMargins(
            0,
            0,
            0,
            0
        );

        main->setSpacing(0);

        QWidget *topbar =
            new QWidget;

        topbar->setFixedHeight(48);

        topbar->setStyleSheet(R"(

            background: rgba(15,15,20,220);
            border-bottom: 1px solid rgba(255,255,255,0.08);

        )");

        auto *topLayout =
            new QHBoxLayout(topbar);

        QLabel *logo =
            new QLabel("Kaizor OS");

        logo->setStyleSheet(R"(

            color: white;
            font-size: 18px;
            font-weight: 800;
            padding-left: 14px;

        )");

        topLayout->addWidget(logo);
        topLayout->addStretch();

        QPushButton *notif =
            new QPushButton("🔔");

        QPushButton *power =
            new QPushButton("⏻");

        QString btnStyle = R"(

            QPushButton {

                background: transparent;
                color: white;
                border: none;
                font-size: 18px;
                padding-right: 10px;

            }

        )";

        notif->setStyleSheet(btnStyle);
        power->setStyleSheet(btnStyle);

        topLayout->addWidget(notif);
        topLayout->addWidget(power);

        QWidget *desktop =
            new QWidget;

        desktop->setStyleSheet(R"(

            background: qlineargradient(
                x1:0,
                y1:0,
                x2:1,
                y2:1,
                stop:0 #0d1117,
                stop:1 #1f2937
            );

        )");

        auto *deskLayout =
            new QVBoxLayout(desktop);

        deskLayout->addStretch();

        QWidget *dock =
            new QWidget;

        dock->setFixedHeight(100);

        dock->setStyleSheet(R"(

            background: rgba(20,20,30,180);
            border-radius: 28px;
            margin: 16px;

        )");

        auto *dockLayout =
            new QHBoxLayout(dock);

        dockLayout->setSpacing(20);

        QStringList apps = {
            "🌐",
            "📁",
            "⚙",
            "🎵",
            "📝"
        };

        for (const QString &app : apps)
        {
            QPushButton *btn =
                new QPushButton(app);

            btn->setFixedSize(64,64);

            btn->setStyleSheet(R"(

                QPushButton {

                    background: rgba(255,255,255,0.08);
                    color: white;
                    border: none;
                    border-radius: 20px;
                    font-size: 26px;

                }

                QPushButton:hover {

                    background: rgba(255,255,255,0.18);

                }

            )");

            dockLayout->addWidget(btn);
        }

        deskLayout->addWidget(
            dock,
            0,
            Qt::AlignHCenter | Qt::AlignBottom
        );

        main->addWidget(topbar);
        main->addWidget(desktop);

        connect(
            notif,
            &QPushButton::clicked,
            this,
            [=]() {

                QProcess::startDetached(
                    "./kaizor-notifications"
                );

            }
        );

        connect(
            power,
            &QPushButton::clicked,
            this,
            [=]() {

                QProcess::startDetached(
                    "./kaizor-powermenu"
                );

            }
        );
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DesktopShell shell;

    shell.show();

    return app.exec();
}
