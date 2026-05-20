#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QScreen>

// -------------------- GlassWidget --------------------
class GlassWidget : public QWidget {
public:
    explicit GlassWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_TranslucentBackground);
        setObjectName("GlassWidget");

        setStyleSheet(
            "#GlassWidget {"
            " background: rgba(18,18,18,0.65);"
            " border: 1px solid rgba(255,255,255,0.10);"
            " border-radius: 26px;"
            "}"
        );

        auto *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(45);
        shadow->setOffset(0, 14);
        shadow->setColor(QColor(0, 0, 0, 210));
        setGraphicsEffect(shadow);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing, true);

        QRect r = rect();
        QPainterPath path;
        path.addRoundedRect(r.adjusted(1, 1, -1, -1), 26, 26);

        QLinearGradient grad(0, 0, 0, height());
        grad.setColorAt(0.0, QColor(255, 255, 255, 16));
        grad.setColorAt(0.4, QColor(255, 255, 255, 6));
        grad.setColorAt(1.0, QColor(0, 0, 0, 35));

        p.fillPath(path, grad);
    }
};

// -------------------- MenuButton --------------------
class MenuButton : public QPushButton {
public:
    explicit MenuButton(const QString &text, QWidget *parent = nullptr)
        : QPushButton(text, parent) {

        setCursor(Qt::PointingHandCursor);
        setFixedHeight(44);

        setStyleSheet(
            "QPushButton {"
            " text-align: left;"
            " padding-left: 16px;"
            " background: rgba(255,255,255,0.06);"
            " border: 1px solid rgba(255,255,255,0.08);"
            " border-radius: 14px;"
            " color: white;"
            " font-size: 14px;"
            " font-weight: 600;"
            "}"
            "QPushButton:hover {"
            " background: rgba(255,255,255,0.14);"
            " border: 1px solid rgba(255,255,255,0.18);"
            "}"
        );
    }
};

// -------------------- AppTile --------------------
class AppTile : public QPushButton {
public:
    explicit AppTile(const QString &text, QWidget *parent = nullptr)
        : QPushButton(text, parent) {

        setCursor(Qt::PointingHandCursor);
        setFixedSize(120, 92);

        setStyleSheet(
            "QPushButton {"
            " background: rgba(255,255,255,0.07);"
            " border: 1px solid rgba(255,255,255,0.10);"
            " border-radius: 18px;"
            " color: white;"
            " font-size: 13px;"
            " font-weight: 700;"
            "}"
            "QPushButton:hover {"
            " background: rgba(255,255,255,0.16);"
            " border: 1px solid rgba(255,255,255,0.22);"
            "}"
            "QPushButton:pressed {"
            " background: rgba(255,255,255,0.24);"
            "}"
        );

        auto *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setOffset(0, 8);
        shadow->setColor(QColor(0, 0, 0, 160));
        setGraphicsEffect(shadow);
    }
};

// -------------------- PowerButton --------------------
class PowerButton : public QPushButton {
public:
    explicit PowerButton(const QString &text, QWidget *parent = nullptr)
        : QPushButton(text, parent) {

        setCursor(Qt::PointingHandCursor);
        setFixedSize(110, 44);

        setStyleSheet(
            "QPushButton {"
            " background: rgba(255,70,70,0.18);"
            " border: 1px solid rgba(255,70,70,0.20);"
            " border-radius: 16px;"
            " color: white;"
            " font-size: 13px;"
            " font-weight: 700;"
            "}"
            "QPushButton:hover {"
            " background: rgba(255,70,70,0.30);"
            " border: 1px solid rgba(255,70,70,0.35);"
            "}"
            "QPushButton:pressed {"
            " background: rgba(255,70,70,0.45);"
            "}"
        );
    }
};

// -------------------- KaizorLauncher --------------------
class KaizorLauncher : public GlassWidget {
public:
    KaizorLauncher() {
        setFixedSize(960, 620);
        setWindowTitle("Kaizor Launcher");
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

        auto *mainLayout = new QHBoxLayout(this);
        mainLayout->setContentsMargins(22, 22, 22, 22);
        mainLayout->setSpacing(18);

        // Left Sidebar
        QWidget *sidebar = new QWidget();
        sidebar->setFixedWidth(240);
        sidebar->setStyleSheet(
            "background: rgba(255,255,255,0.04);"
            "border: 1px solid rgba(255,255,255,0.06);"
            "border-radius: 20px;"
        );

        auto *sideLayout = new QVBoxLayout(sidebar);
        sideLayout->setContentsMargins(14, 14, 14, 14);
        sideLayout->setSpacing(10);

        QLabel *logo = new QLabel("Kaizor OS");
        logo->setStyleSheet("color:white; font-size:18px; font-weight:800;");
        sideLayout->addWidget(logo);

        QLabel *sub = new QLabel("Applications");
        sub->setStyleSheet("color:rgba(255,255,255,0.70); font-size:13px;");
        sideLayout->addWidget(sub);

        sideLayout->addSpacing(6);

        sideLayout->addWidget(new MenuButton("All Apps"));
        sideLayout->addWidget(new MenuButton("Favorites"));
        sideLayout->addWidget(new MenuButton("Settings"));
        sideLayout->addWidget(new MenuButton("System Tools"));
        sideLayout->addWidget(new MenuButton("Utilities"));

        sideLayout->addStretch();

        QLabel *footer = new QLabel("Kaizor Launcher v0.1");
        footer->setStyleSheet("color:rgba(255,255,255,0.45); font-size:12px;");
        sideLayout->addWidget(footer);

        // Center content
        QWidget *center = new QWidget();
        center->setStyleSheet("background: transparent;");

        auto *centerLayout = new QVBoxLayout(center);
        centerLayout->setContentsMargins(0, 0, 0, 0);
        centerLayout->setSpacing(14);

        QLabel *title = new QLabel("Pinned Apps");
        title->setStyleSheet("color:white; font-size:18px; font-weight:800;");
        centerLayout->addWidget(title);

        QWidget *gridWrap = new QWidget();
        gridWrap->setStyleSheet("background: transparent;");

        auto *grid = new QGridLayout(gridWrap);
        grid->setContentsMargins(0, 0, 0, 0);
        grid->setHorizontalSpacing(14);
        grid->setVerticalSpacing(14);

        grid->addWidget(new AppTile("Files"), 0, 0);
        grid->addWidget(new AppTile("Settings"), 0, 1);
        grid->addWidget(new AppTile("Terminal"), 0, 2);
        grid->addWidget(new AppTile("Browser"), 0, 3);

        grid->addWidget(new AppTile("Store"), 1, 0);
        grid->addWidget(new AppTile("Monitor"), 1, 1);
        grid->addWidget(new AppTile("Music"), 1, 2);
        grid->addWidget(new AppTile("Editor"), 1, 3);

        grid->addWidget(new AppTile("Calculator"), 2, 0);
        grid->addWidget(new AppTile("Photos"), 2, 1);
        grid->addWidget(new AppTile("Video"), 2, 2);
        grid->addWidget(new AppTile("Updater"), 2, 3);

        centerLayout->addWidget(gridWrap);
        centerLayout->addStretch();

        // Bottom bar: search + power buttons
        QWidget *bottomBar = new QWidget();
        bottomBar->setFixedHeight(72);
        bottomBar->setStyleSheet(
            "background: rgba(255,255,255,0.05);"
            "border: 1px solid rgba(255,255,255,0.08);"
            "border-radius: 20px;"
        );

        auto *bottomLayout = new QHBoxLayout(bottomBar);
        bottomLayout->setContentsMargins(16, 12, 16, 12);
        bottomLayout->setSpacing(12);

        QLineEdit *search = new QLineEdit();
        search->setPlaceholderText("Search apps, files, settings...");
        search->setFixedHeight(48);
        search->setStyleSheet(
            "QLineEdit {"
            " background: rgba(0,0,0,0.30);"
            " border: 1px solid rgba(255,255,255,0.10);"
            " border-radius: 16px;"
            " color: white;"
            " padding-left: 14px;"
            " font-size: 14px;"
            " font-weight: 600;"
            "}"
            "QLineEdit:focus {"
            " border: 1px solid rgba(120,160,255,0.55);"
            "}"
        );

        bottomLayout->addWidget(search, 1);

        bottomLayout->addWidget(new PowerButton("Logout"));
        bottomLayout->addWidget(new PowerButton("Restart"));
        bottomLayout->addWidget(new PowerButton("Shutdown"));

        centerLayout->addWidget(bottomBar);

        // Add to main
        mainLayout->addWidget(sidebar);
        mainLayout->addWidget(center, 1);

        // Position launcher
        placeBottomLeft();
    }

private:
    void placeBottomLeft() {
        QRect screen = QGuiApplication::primaryScreen()->geometry();

        int x = 18;
        int y = screen.height() - height() - 96;

        move(x, y);
    }
};

// -------------------- MAIN --------------------
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    KaizorLauncher launcher;
    launcher.show();

    return app.exec();
}
