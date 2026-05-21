#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QEnterEvent>

class DockButton : public QPushButton
{
public:
    DockButton(const QString &icon)
    {
        setText(icon);

        setFixedSize(60,60);

        setCursor(Qt::PointingHandCursor);

        setStyleSheet(R"(

            QPushButton {

                background: rgba(255,255,255,0.10);
                color: white;
                border: none;
                border-radius: 20px;
                font-size: 26px;
                font-weight: 700;

            }

            QPushButton:hover {

                background: rgba(255,255,255,0.22);

            }

        )");

        auto *shadow =
            new QGraphicsDropShadowEffect;

        shadow->setBlurRadius(26);
        shadow->setOffset(0,6);

        setGraphicsEffect(shadow);
    }

protected:
    void enterEvent(QEnterEvent *) override
    {
        animate(74);
    }

    void leaveEvent(QEvent *) override
    {
        animate(60);
    }

private:
    void animate(int size)
    {
        auto *anim =
            new QPropertyAnimation(
                this,
                QByteArray()
            );

        anim->setDuration(140);

        anim->setStartValue(
            this->size()
        );

        anim->setEndValue(
            QSize(size,size)
        );

        connect(
            anim,
            &QPropertyAnimation::valueChanged,
            this,
            [=](const QVariant &v) {

                QSize s =
                    v.toSize();

                setFixedSize(s);

            }
        );

        anim->start(
            QAbstractAnimation::DeleteWhenStopped
        );
    }
};

class AnimatedDock : public QWidget
{
public:
    AnimatedDock()
    {
        resize(860, 130);

        auto *layout =
            new QHBoxLayout(this);

        layout->setContentsMargins(
            30,
            24,
            30,
            24
        );

        layout->setSpacing(18);

        QStringList icons = {
            "🌐",
            "📁",
            "🎵",
            "🖼",
            "⚙",
            "📝",
            "🛒"
        };

        for (const QString &icon : icons)
        {
            DockButton *btn =
                new DockButton(icon);

            layout->addWidget(btn);
        }
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
            36,
            36
        );

        p.fillPath(
            path,
            QColor(20,20,30,220)
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

    AnimatedDock dock;

    dock.show();

    return app.exec();
}
