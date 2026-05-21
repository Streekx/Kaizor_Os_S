#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QGraphicsDropShadowEffect>

class SearchPanel : public QWidget
{
public:
    SearchPanel()
    {
        resize(760, 520);

        setWindowFlags(
            Qt::FramelessWindowHint
        );

        setAttribute(
            Qt::WA_TranslucentBackground
        );

        auto *main =
            new QVBoxLayout(this);

        main->setContentsMargins(
            26,
            26,
            26,
            26
        );

        main->setSpacing(22);

        QLineEdit *search =
            new QLineEdit;

        search->setPlaceholderText(
            "Search apps, settings, files..."
        );

        search->setFixedHeight(58);

        search->setStyleSheet(R"(

            QLineEdit {

                background: rgba(255,255,255,0.10);
                color: white;
                border: none;
                border-radius: 18px;
                padding-left: 18px;
                font-size: 16px;

            }

        )");

        QListWidget *results =
            new QListWidget;

        results->setStyleSheet(R"(

            QListWidget {

                background: rgba(255,255,255,0.05);
                border: none;
                border-radius: 24px;
                color: white;
                font-size: 15px;
                padding: 12px;

            }

            QListWidget::item {

                height: 42px;
                padding-left: 12px;
                border-radius: 12px;

            }

            QListWidget::item:selected {

                background: rgba(255,255,255,0.14);

            }

        )");

        QStringList items = {
            "Browser",
            "Files",
            "Terminal",
            "Music",
            "Settings",
            "Wallpaper",
            "Bluetooth",
            "WiFi",
            "Notifications",
            "Power"
        };

        results->addItems(items);

        auto *shadow =
            new QGraphicsDropShadowEffect;

        shadow->setBlurRadius(35);
        shadow->setOffset(0,10);

        setGraphicsEffect(shadow);

        main->addWidget(search);
        main->addWidget(results);
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
            QColor(18,18,26,235)
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

    SearchPanel panel;

    panel.show();

    return app.exec();
}
