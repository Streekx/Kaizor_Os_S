#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>

class ThemeManager
{
public:
    void applyDarkTheme()
    {
        QString theme = R"(

            QWidget {

                background-color: #12141c;
                color: white;
                font-family: Sans;

            }

            QPushButton {

                background: rgba(255,255,255,0.08);
                border-radius: 14px;
                padding: 10px;
                border: none;
                color: white;

            }

            QPushButton:hover {

                background: rgba(255,255,255,0.16);

            }

            QLineEdit {

                background: rgba(255,255,255,0.08);
                border-radius: 12px;
                padding: 8px;
                color: white;
                border: none;

            }

            QListWidget {

                background: rgba(255,255,255,0.05);
                border-radius: 18px;
                border: none;

            }

        )";

        qApp->setStyleSheet(theme);

        qDebug()
            << "Kaizor Theme Applied";
    }

    void createThemeDirectories()
    {
        QDir().mkpath(
            QDir::homePath()
            + "/.kaizor/themes"
        );

        QDir().mkpath(
            QDir::homePath()
            + "/.kaizor/cache"
        );

        qDebug()
            << "Theme directories ready";
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ThemeManager manager;

    manager.createThemeDirectories();

    manager.applyDarkTheme();

    return app.exec();
}
