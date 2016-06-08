
#ifndef CONFINPUT_H
#define CONFINPUT_H

#include <QWidget>
#include <QEvent>
#include <QWhatsThis>
#include <QWhatsThisClickedEvent>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QIcon>

#include "graphical_button.hpp"
#include "data/parameter.hpp"

namespace tdx {

    namespace app {

        namespace widget {

            class ParameterInputWidget : public QWidget {
                Q_OBJECT

            public:
                ParameterInputWidget(const QString& parameterName, data::Parameter::ConfigContext context, QWidget *parent = NULL);
                
            public slots:
                void loadValue(const QString& value);
                void saveValue(const QString& value);

            signals:
                void shouldLoadValue(const QString& value);

            private:
                
                QWidget* setupDirWidget(bool isDir = false);
                QWidget* setupEditWidget();
                QWidget* setupBoolWidget();
                QWidget* setupDropDownWidget();

                QGridLayout* layout_;
                
                QString parameterName_;
                data::Parameter::ConfigContext context_;


            };
        }
    }
}


#endif
