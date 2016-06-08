

#ifndef WIDGETS_GRAPHICALBUTTON_H
#define WIDGETS_GRAPHICALBUTTON_H

#include <QCheckBox>
#include <QPainter>
#include <QIcon>

namespace tdx {

    namespace app {

        namespace widget {

            class GraphicalButton : public QAbstractButton {
                Q_OBJECT
                
            public:
                GraphicalButton(QIcon icon, QWidget *parent = NULL);

            public slots:
                void changeState(bool checked);

            signals:
                void stateChanged(int state);

            protected:
                virtual void paintEvent(QPaintEvent* event);

            private:
                
                QIcon icon_;
            };
        }
    }
}



#endif
