
#ifndef CONFINTERFACE_H
#define CONFINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QToolBar>
#include <QToolButton>
#include <QString>
#include <QStringList>
#include <QMap>

#include "graphical_button.hpp"
#include "parameter_section.hpp"

namespace tdx {
    
    namespace app {
        
        namespace widget {

            class ParametersWidget : public QWidget {
                Q_OBJECT

            public:
                ParametersWidget(QWidget *parent = NULL);
                
                ParametersWidget(data::Parameter::ConfigContext context, 
                                QWidget *parent = NULL);
                
                ParametersWidget(int userLevel, 
                                data::Parameter::ConfigContext context = data::Parameter::ConfigContext(), 
                                QWidget *parent = NULL);
                
                ParametersWidget(QStringList parametersDisplayed, int userLevel=0, 
                                data::Parameter::ConfigContext context = data::Parameter::ConfigContext(), 
                                QWidget *parent = NULL);
                
                
            public slots:
                void setSimpleLevel();
                void setAdvancedLevel();
                void changeParametersDisplayed(const QStringList& toBeDisplayed);

            private:
                
                void initialize(data::Parameter::ConfigContext context, int userLevel, const QStringList& toBeDisplayed);
                void changeFormWidget();;
                
                QWidget* formWidget();
                QToolBar* toolWidget();
                
                QHBoxLayout* mainLayout_;
                QScrollArea* scrollArea_;
                QToolBar* toolWidget_;
                QToolButton* basicButton_;
                QToolButton* advancedButton_;
                
                data::Parameter::ConfigContext context_;
                int userLevel_;
                QStringList parametersDisplayed_;

            };
        }
    }
}

#endif
