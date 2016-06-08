
#ifndef CONFINTERFACE_H
#define CONFINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QStringList>
#include <QMap>

#include "parameter_section.hpp"

namespace tdx {
    
    namespace app {
        
        namespace widget {

            class ParametersWidget : public QWidget {
                Q_OBJECT

            public:
                ParametersWidget(QStringList parametersDisplayed, int userLevel=0, 
                                data::Parameter::ConfigContext context = data::Parameter::ConfigContext(), 
                                QWidget *parent = NULL);
                
                ParametersWidget(int userLevel=0, 
                                data::Parameter::ConfigContext context = data::Parameter::ConfigContext(), 
                                QWidget *parent = NULL);
                

            private:
                void initialize(QStringList parametersDisplayed, int userLevel, 
                                data::Parameter::ConfigContext context);
                QMap<QString, ParameterSectionWidget*> sectionWidgetLookup_;

            };
        }
    }
}

#endif
