
#ifndef COMBO_INPUT_WIDGET_HPP
#define COMBO_INPUT_WIDGET_HPP

#include <QComboBox>
#include <QWheelEvent>

namespace tdx {

    namespace app {

        namespace widget {

            class ComboInputWidget : public QComboBox {

                Q_OBJECT

            public:
                ComboInputWidget(QWidget* parent = NULL)
                : QComboBox(parent) {
                    setFrame(false);
                }

            public slots:

                void wheelEvent(QWheelEvent *e) {
                    if(hasFocus())
                        QComboBox::wheelEvent(e);
                }

            signals:


            };
        }
    }
}


#endif /* COMBO_INPUT_WIDGET_HPP */

