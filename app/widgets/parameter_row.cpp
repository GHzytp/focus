
#include <iostream>
#include <QListView>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QComboBox>
#include <QMessageBox>

#include "parameter_row.hpp"
#include "noScrollComboBox.h"

#include "conf/parameters_configuration.hpp"

#include "repositories/path_repo.hpp"
#include "repositories/icon_repo.hpp"
#include "data/parameter.hpp"
#include "edit_set_widget.hpp"
#include "browser_widget.hpp"
#include "yesno_widget.hpp"
#include "combo_input_widget.hpp"

#include "validator/parameter_validator.hpp"

using namespace tdx::app::widget;
using namespace std;

ParameterInputWidget::ParameterInputWidget(const QString& parameterName, data::Parameter::ConfigContext context, QWidget* parent)
: QWidget(parent), parameterName_(parameterName), context_(context) {


    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    
    layout_ = new QGridLayout(this);
    
    layout_->setMargin(1);
    layout_->setSpacing(2);
    layout_->setAlignment(Qt::AlignLeft);
    
    data::Parameter::TypeInfo typeInfo_ = data::Parameter(parameterName_, context_).typeInfo();
    
    QWidget* input;
    if (typeInfo_.type == data::Parameter::Type::TEXT_EDIT) input = setupEditWidget();
    else if (typeInfo_.type == data::Parameter::Type::INT) input = setupEditWidget();
    else if (typeInfo_.type == data::Parameter::Type::FLOAT) input = setupEditWidget();
    else if (typeInfo_.type == data::Parameter::Type::BOOL) input = setupBoolWidget();
    else if (typeInfo_.type == data::Parameter::Type::FILE) input = setupDirWidget(false);
    else if (typeInfo_.type == data::Parameter::Type::DIRECTORY) input = setupDirWidget(true);
    else if (typeInfo_.type == data::Parameter::Type::DROP_DOWN) input = setupDropDownWidget();
    else input = new QWidget(this);
    layout_->addWidget(input, 0, 0);
    
    setLayout(layout_);
}

void ParameterInputWidget::loadValue(const QString& value) {
    emit shouldLoadValue(value);
}


void ParameterInputWidget::saveValue(const QString& value) {
    data::Parameter parameter(parameterName_, context_);
    
    QVariant valVar = value;
    QStringList errors = validator::ParameterValidator::valueErrors(parameter.typeInfo(), value);
    
    if(errors.size() != 0) {
        QString err, fullErr;
        foreach(err, errors) fullErr += err + "\n";
        QMessageBox::warning(this, tr("Error in setting value for parameter"), fullErr);
        return;
    }
    
    parameter.setValue(valVar);
}

QWidget* ParameterInputWidget::setupDirWidget(bool isDir) {
    BrowserWidget* widget = new BrowserWidget(this);
    if (isDir) widget->setType(BrowserWidget::BrowseType::DIRECTORY);
    widget->setDefaultPath(repo::ProjectRepo::Instance().projectPath());
    
    connect(this, SIGNAL(shouldLoadValue(const QString&)), 
            widget, SLOT(setPath(const QString&)));
    connect(widget, SIGNAL(pathChanged(const QString&)),
            this, SLOT(saveValue(const QString&)));

    return widget;
}

QWidget* ParameterInputWidget::setupDropDownWidget() {
    QComboBox* combo = new ComboInputWidget(this);
    combo->setFocusPolicy( Qt::StrongFocus );
    combo->addItems(data::Parameter(parameterName_, context_).typeInfo().properties);
    
    connect(this, &ParameterInputWidget::shouldLoadValue, 
            [ = ](const QString& value){combo->setCurrentIndex(value.toInt()); });
    connect(combo, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged),
            [ = ](int index){saveValue(QString::number(index));});

    return combo;
}

QWidget* ParameterInputWidget::setupEditWidget() {
    EditSetWidget* widget = new EditSetWidget(data::Parameter(parameterName_, context_).typeInfo().count, this);
    
    connect(this, SIGNAL(shouldLoadValue(const QString&)), 
            widget, SLOT(setValue(const QString&)));
    connect(widget, SIGNAL(valueChanged(const QString&)),
            this, SLOT(saveValue(const QString&)));

    return widget;
}

QWidget* ParameterInputWidget::setupBoolWidget() {
    YesNoWidget* widget = new YesNoWidget(this);
    
    connect(this, &ParameterInputWidget::shouldLoadValue,
            [ = ](const QString& value){bool val = false;
                                        QString valStr = value.trimmed().toLower();
                                        if (valStr == "yes" || valStr == "y" || valStr == "1") val = true;
                                        widget->setValue(val); 
                                        });
    connect(widget, &YesNoWidget::valueChanged,
            [ = ](bool value){QString val = "no";
                            if (value) val = "yes";
                            saveValue(val); });

    return widget;
}


