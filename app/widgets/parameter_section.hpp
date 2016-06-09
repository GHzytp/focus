
#ifndef WIDGETS_PARAMETER_SECTION_WIDGET_HPP
#define WIDGETS_PARAMETER_SECTION_WIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QFormLayout>
#include <QFrame>
#include <QLabel>
#include <QHash>
#include <QString>

#include "data/parameter.hpp"

#include "parameter_row.hpp"

namespace tdx {

    namespace app {

        namespace widget {

            class ParameterSectionWidget : public QWidget {
                Q_OBJECT

            public:
                ParameterSectionWidget(QString sectionTitle, data::Parameter::ConfigContext context, QWidget *parent = NULL);
                void finishAddingParameters();
                
            public slots:
                void loadValues();
                void addParameter(const QString& parameter);
                

            private:
                
                data::Parameter::ConfigContext context_;
                QMap<QString, ParameterInputWidget*> parameterInputLookup_;
                QMap<QString, int> parameterRowLookup_;
                
                QVBoxLayout* mainLayout_;
                QFormLayout* formLayout_;
                QFrame* parameterFrame_;
                
            };
        }
    }
}

#endif
