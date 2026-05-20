// File: KaizorOS/gui/panel/src/main.cpp
// Kaizor Panel (Modern macOS/Zorin style dock panel)

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QTimer>
#include <QPainter>
#include <QScreen>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

// -------------------- DockButton --------------------
class DockButton : public QPushButton {
public:
    DockButton(const QString &text, QWidget *parent = nullptr)
        : QPushButton(text, parent) {

        setFixedSize(46, 46);
        setCursor(Qt::PointingHandCursor);

        setStyleSheet(
            "QPushButton {"
            " background: rgba(255,255,255,0.10);"
            " color: white;"
            " font-size: 14px;"
            " font-weight: 600;"
            " border: 1px solid rgba(255,255,255,0.10);"
            " border-radius: 16px;"
            "}"
            "QPushButton:hover {"
            " background: rgba(255,255,255,0.18);"
            " border: 1px solid rgba(255,255,255,0.25);"
            "}"
            "QPushButton:pressed {"
            " background: rgba(255,255,255,0.25);"
            "}"
        );

        auto *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setOffset(0, 6);
        shadow->setColor(QColor(0, 0, 0, 160));
        setGraphicsEffect(shadow);
    }
};

// -------------------- GlassPanel --------------------
class GlassPanel : public QWidget {
public:
    explicit GlassPanel(QWidget *parent = nullptr)
        : QWidget(parent) {

        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setObjectName("GlassPanel");

        setStyleSheet(
            "#GlassPanel {"
            " background: rgba(20,20,20,0.55);"
            " border: 1px solid rgba(255,255,255,0.10);"
            " border-radius: 22px;"
            "}"
        );

        auto *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(35);
        shadow->setOffset(0, 10);
        shadow->setColor(QColor(0, 0, 0, 200));
        setGraphicsEffect(shadow);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing, true);

        QRect r = rect();
        QPainterPath path;
        path.addRoundedRect(r.adjusted(1, 1, -1, -1), 22, 22);

        // Glass gradient overlay (modern feel)
        QLinearGradient grad(0, 0, 0, height());
        grad.setColorAt(0.0, QColor(255, 255, 255, 18));
        grad.setColorAt(0.5, QColor(255, 255, 255, 8));
        grad.setColorAt(1.0, QColor(0, 0, 0, 35));

        p.fillPath(path, grad);
    }
};

// -------------------- KaizorPanel --------------------
class KaizorPanel : public GlassPanel {
public:
    KaizorPanel() {
        setFixedHeight(72);

        auto *mainLayout = new QHBoxLayout(this);
        mainLayout->setContentsMargins(18, 12, 18, 12);
        mainLayout->setSpacing(14);

        // Left section: Kaizor start button
        DockButton *startButton = new DockButton("K");
        startButton->setFixedSize(52, 48);
        startButton->setStyleSheet(
            "QPushButton {"
            " background: rgba(70,120,255,0.55);"
            " color: white;"
            " font-size: 18px;"
            " font-weight: 700;"
            " border: 1px solid rgba(255,255,255,0.20);"
            " border-radius: 18px;"
            "}"
            "QPushButton:hover {"
            " background: rgba(70,120,255,0.70);"
            "}"
            "QPushButton:pressed {"
            " background: rgba(70,120,255,0.85);"
            "}"
        );

        mainLayout->addWidget(startButton);

        // Center dock icons (placeholder apps)
        QWidget *dock = new QWidget();
        dock->setAttribute(Qt::WA_TranslucentBackground);

        auto *dockLayout = new QHBoxLayout(dock);
        dockLayout->setContentsMargins(0, 0, 0, 0);
        dockLayout->setSpacing(10);

        dockLayout->addWidget(new DockButton("Files"));
        dockLayout->addWidget(new DockButton("Web"));
        dockLayout->addWidget(new DockButton("Term"));
        dockLayout->addWidget(new DockButton("Set"));
        dockLayout->addWidget(new DockButton("Store"));

        mainLayout->addStretch();
        mainLayout->addWidget(dock);
        mainLayout->addStretch();

        // Right tray (wifi, bt, sound + clock)
        QWidget *tray = new QWidget();
        tray->setAttribute(Qt::WA_TranslucentBackground);

        auto *trayLayout = new QHBoxLayout(tray);
        trayLayout->setContentsMargins(0, 0, 0, 0);
        trayLayout->setSpacing(10);

        DockButton *wifi = new DockButton("WiFi");
        DockButton *bt = new DockButton("BT");
        DockButton *vol = new DockButton("Vol");

        wifi->setFixedSize(54, 42);
        bt->setFixedSize(54, 42);
        vol->setFixedSize(54, 42);

        trayLayout->addWidget(wifi);
        trayLayout->addWidget(bt);
        trayLayout->addWidget(vol);

        clockLabel = new QLabel();
        clockLabel->setStyleSheet(
            "QLabel {"
            " color: white;"
            " font-size: 13px;"
            " font-weight: 600;"
            " padding-left: 12px;"
            " padding-right: 12px;"
            " padding-top: 10px;"
            " padding-bottom: 10px;"
            " background: rgba(255,255,255,0.08);"
            " border: 1px solid rgba(255,255,255,0.10);"
            " border-radius: 16px;"
            "}"
        );

        trayLayout->addWidget(clockLabel);

        mainLayout->addWidget(tray);

        // Clock updater
        auto *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &KaizorPanel::updateClock);
        timer->start(1000);
        updateClock();

        // Position panel bottom center
        placeBottomCenter();
    }

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            dragPos = event->globalPosition().toPoint();
            windowPos = this->pos();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            QPoint delta = event->globalPosition().toPoint() - dragPos;
            move(windowPos + delta);
        }
    }

private:
    QLabel *clockLabel;
    QPoint dragPos;
    QPoint windowPos;

    void updateClock() {
        QString time = QDateTime::currentDateTime().toString("ddd  dd MMM   hh:mm");
        clockLabel->setText(time);
    }

    void placeBottomCenter() {
        QRect screen = QGuiApplication::primaryScreen()->geometry();
        int width = 880;
        setFixedWidth(width);

        int x = (screen.width() - width) / 2;
        int y = screen.height() - height() - 14;
        move(x, y);
    }
};

// -------------------- MAIN --------------------
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    KaizorPanel panel;
    panel.show();

    return app.exec();
}
