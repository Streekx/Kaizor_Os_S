#include <QApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class AppRegistry
{
public:
    void createRegistry()
    {
        QString path =
            QDir::homePath()
            + "/.kaizor/apps";

        QDir().mkpath(path);

        registerApp(
            path,
            "browser.app",
            "Browser"
        );

        registerApp(
            path,
            "files.app",
            "Files"
        );

        registerApp(
            path,
            "terminal.app",
            "Terminal"
        );

        registerApp(
            path,
            "music.app",
            "Music"
        );

        registerApp(
            path,
            "settings.app",
            "Settings"
        );

        qDebug()
            << "Apps Registered";
    }

private:

    void registerApp(
        const QString &path,
        const QString &file,
        const QString &name
    )
    {
        QFile appFile(
            path + "/" + file
        );

        if (
            appFile.open(
                QFile::WriteOnly |
                QFile::Text
            )
        )
        {
            QTextStream out(&appFile);

            out
                << "name=" << name << "\n"
                << "version=1.0\n"
                << "type=desktop-app\n";

            appFile.close();
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AppRegistry registry;

    registry.createRegistry();

    return app.exec();
}
