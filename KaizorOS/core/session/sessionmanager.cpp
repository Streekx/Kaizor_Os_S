#include <QApplication>
#include <QProcess>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QDebug>

class SessionManager
{
public:
    void start()
    {
        startWallpaper();

        QTimer::singleShot(
            600,
            [=]() {

                startTopbar();

            }
        );

        QTimer::singleShot(
            1200,
            [=]() {

                startDock();

            }
        );

        QTimer::singleShot(
            1700,
            [=]() {

                startLauncher();

            }
        );

        QTimer::singleShot(
            2200,
            [=]() {

                startNotifications();

            }
        );
    }

private:

    void startWallpaper()
    {
        QProcess::startDetached(
            "./kaizor-wallpaper"
        );

        qDebug()
            << "Wallpaper Started";
    }

    void startTopbar()
    {
        QProcess::startDetached(
            "./kaizor-topbar"
        );

        qDebug()
            << "Topbar Started";
    }

    void startDock()
    {
        QProcess::startDetached(
            "./kaizor-dock"
        );

        qDebug()
            << "Dock Started";
    }

    void startLauncher()
    {
        QProcess::startDetached(
            "./kaizor-launcher"
        );

        qDebug()
            << "Launcher Started";
    }

    void startNotifications()
    {
        QProcess::startDetached(
            "./kaizor-notifications"
        );

        qDebug()
            << "Notifications Started";
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SessionManager manager;

    manager.start();

    return app.exec();
}
