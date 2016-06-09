
#include <QVBoxLayout>
#include <QFrame>
#include <QtGui/qboxlayout.h>

#include "conf/parameters_configuration.hpp"

#include "parameters_widget.hpp"
#include "repositories/icon_repo.hpp"

using namespace tdx::app::widget;

ParametersWidget::ParametersWidget(QWidget* parent)
: QWidget(parent){
    initialize(data::Parameter::ConfigContext(), 0, conf::GlobalParameterConfiguration().parameters());
}

ParametersWidget::ParametersWidget(data::Parameter::ConfigContext context, QWidget* parent)
: QWidget(parent){
    initialize(context, 0, conf::GlobalParameterConfiguration().parameters());
}

ParametersWidget::ParametersWidget(int userLevel, data::Parameter::ConfigContext context, QWidget *parent)
: QWidget(parent){
    initialize(context, userLevel, conf::GlobalParameterConfiguration().parameters());
}

ParametersWidget::ParametersWidget(QStringList parametersDisplayed, int userLevel, 
        data::Parameter::ConfigContext context, QWidget *parent)
: QWidget(parent){
    initialize(context, userLevel, parametersDisplayed);
}

void ParametersWidget::setSimpleLevel() {
    if (userLevel_ == 0) return;
    userLevel_ = 0;
    basicButton_->setChecked(true);
    advancedButton_->setChecked(false);
    changeFormWidget();
}

void ParametersWidget::setAdvancedLevel() {
    if (userLevel_ == 1) return;
    userLevel_ = 1;
    basicButton_->setChecked(false);
    advancedButton_->setChecked(true);
    changeFormWidget();
}

void ParametersWidget::changeParametersDisplayed(const QStringList& toBeDisplayed) {
    parametersDisplayed_ = toBeDisplayed;
    changeFormWidget();
}

void ParametersWidget::initialize(data::Parameter::ConfigContext context, int userLevel, const QStringList& toBeDisplayed) {
    context_ = context;
    userLevel_ = userLevel;
    parametersDisplayed_ = toBeDisplayed;
    
    toolWidget_ = toolWidget();
    scrollArea_ = new QScrollArea();
    scrollArea_->setWidget(formWidget());
    
    mainLayout_ =  new QHBoxLayout();
    mainLayout_->setSpacing(0);
    mainLayout_->setMargin(0);
    mainLayout_->addWidget(toolWidget_, 0);
    mainLayout_->addWidget(scrollArea_);
    
    setLayout(mainLayout_);
    
}

void ParametersWidget::changeFormWidget() {
    scrollArea_->setWidget(formWidget());
}

QToolBar* ParametersWidget::toolWidget() {
    QToolBar* widget = new QToolBar(this);
    widget->setOrientation(Qt::Vertical);

    
    basicButton_ = new QToolButton(widget);
    basicButton_->setIcon(repo::IconRepository::get("level-simple"));
    basicButton_->setFixedSize(QSize(48,48));
    basicButton_->setText("Basic");
    basicButton_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    basicButton_->setCheckable(true);
    if(userLevel_ == 0)  basicButton_->setChecked(true);
    connect(basicButton_, SIGNAL(clicked()), this, SLOT(setSimpleLevel()));
    

    advancedButton_ = new QToolButton(widget);
    advancedButton_->setIcon(repo::IconRepository::get("level-advanced"));
    advancedButton_->setFixedSize(QSize(48,48));
    advancedButton_->setText("Advanced");
    advancedButton_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    advancedButton_->setCheckable(true);
    if(userLevel_ == 1)  advancedButton_->setChecked(true);
    connect(advancedButton_, SIGNAL(clicked()), this, SLOT(setAdvancedLevel()));

    widget->addWidget(basicButton_);
    widget->addWidget(advancedButton_);
    
    return widget;
}

QWidget* ParametersWidget::formWidget() {

    QWidget* widget = new QWidget();

    QVBoxLayout *generalLayout = new QVBoxLayout();
    generalLayout->setMargin(0);
    generalLayout->setSpacing(10);
    generalLayout->setAlignment(Qt::AlignTop);

    conf::GlobalParameterConfiguration globalParams;
    QString parameter;

    QMap<QString, ParameterSectionWidget*> sectionWidgetLookup_;

    foreach(parameter, globalParams.parameters()) {
        globalParams.setCurrentParameter(parameter);
        QString userLevelString = globalParams.currentParameterProperty("userlevel").toLower();
        int paramUserLevel;
        if (userLevelString == "hidden") paramUserLevel = 2;
        else if (userLevelString == "advanced") paramUserLevel = 1;
        else paramUserLevel = 0;

        if (parametersDisplayed_.contains(parameter) && paramUserLevel <= userLevel_) {
            globalParams.setCurrentParameter(parameter);

            QString section = globalParams.currentParameterProperty("section");

            if (!sectionWidgetLookup_.keys().contains(section)) {
                sectionWidgetLookup_.insert(section, new ParameterSectionWidget(section, context_, this));
            }
            sectionWidgetLookup_[section]->addParameter(parameter);
        }
    }

    QString section;

    foreach(section, sectionWidgetLookup_.keys()) {
        sectionWidgetLookup_[section]->finishAddingParameters();
        sectionWidgetLookup_[section]->loadFromConfig();
        generalLayout->addWidget(sectionWidgetLookup_[section]);
    }

    widget->setLayout(generalLayout);
    return widget;
}
