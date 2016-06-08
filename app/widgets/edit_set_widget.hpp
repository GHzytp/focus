
#ifndef EDIT_SET_WIDGET_HPP
#define EDIT_SET_WIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QList>
#include <QHBoxLayout>
#include <QString>
#include <QStringList>

namespace tdx {

    namespace app {

        namespace widget {

            class EditSetWidget : public QWidget {

                Q_OBJECT

            public:

                EditSetWidget(int count = 1, QWidget* parent = NULL)
                : QWidget(parent) {
                    QHBoxLayout* layout = new QHBoxLayout(this);
                    layout->setMargin(0);

                    for (int i = 0; i < count; ++i) {
                        QLineEdit* widget = new QLineEdit(this);
                        widget->setFrame(false);
                        widgets_.append(widget);
                        connect(widget, SIGNAL(editingFinished()), this, SLOT(updateValues()));
                        layout->addWidget(widget, 1);
                    }
                    
                    setLayout(layout);
                }

            public slots:

                void updateValues() {
                    QString v;
                    for (int i = 0; i < widgets_.size() - 1; i++)
                        v += widgets_[i]->text() + ',';
                    v += widgets_.last()->text();
                    
                    emit valueChanged(v);
                }
                
                void setValue(const QString& value) {
                    QStringList vals = value.trimmed().split(',');
                    for (int i = 0; i < vals.size(); i++) {
                        if(i < widgets_.size()) widgets_[i]->setText(vals[i]);
                    }
                }

            signals:

                void valueChanged(const QString& value);

            private:
                QList<QLineEdit*> widgets_;

            };
        }
    }
}


#endif /* EDIT_SET_WIDGET_HPP */

