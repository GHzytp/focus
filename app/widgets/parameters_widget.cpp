
#include "conf/parameters_configuration.hpp"

#include "parameters_widget.hpp"

using namespace tdx::app::widget;

ParametersWidget::ParametersWidget(QStringList parametersDisplayed, int userLevel, 
                                data::Parameter::ConfigContext context, 
                                QWidget *parent)
: QWidget(parent) {
    initialize(parametersDisplayed, userLevel, context);
}

ParametersWidget::ParametersWidget(int userLevel, 
                                data::Parameter::ConfigContext context, 
                                QWidget *parent)
: QWidget(parent) {
    initialize(conf::GlobalParameterConfiguration().parameters(), userLevel, context);
}

void ParametersWidget::initialize(QStringList parametersDisplayed, int userLevel, 
                                data::Parameter::ConfigContext context) {
    QVBoxLayout *generalLayout = new QVBoxLayout(this);
    generalLayout->setMargin(0);
    generalLayout->setSpacing(10);
    generalLayout->setAlignment(Qt::AlignTop);

    conf::GlobalParameterConfiguration globalParams;
    QString parameter;

    foreach(parameter, globalParams.parameters()) {
        globalParams.setCurrentParameter(parameter);
        QString userLevelString = globalParams.currentParameterProperty("userlevel").toLower();
        int paramUserLevel;
        if (userLevelString == "hidden") paramUserLevel = 2;
        else if (userLevelString == "advanced") paramUserLevel = 1;
        else paramUserLevel = 0;
        
        if(parametersDisplayed.contains(parameter) && paramUserLevel <= userLevel) {
            globalParams.setCurrentParameter(parameter);
            
            QString section = globalParams.currentParameterProperty("section");
        
            if (!sectionWidgetLookup_.keys().contains(section)) {
                sectionWidgetLookup_.insert(section, new ParameterSectionWidget(section, context, this));
            }
            sectionWidgetLookup_[section]->addParameter(parameter);
        }
    }

    QString section;
    foreach(section, sectionWidgetLookup_.keys()) {
        sectionWidgetLookup_[section]->finishAddingParameters();
        sectionWidgetLookup_[section]->loadValues();
        generalLayout->addWidget(sectionWidgetLookup_[section]);
    }
    
    setLayout(generalLayout);
}
