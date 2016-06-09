
#include <iostream>
#include <QListView>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QComboBox>
#include <QMessageBox>
#include <QList>
#include <QPair>
#include <QMap>
#include <QSize>
#include <QBrush>
#include <QPalette>

#include "parameter_input.hpp"

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

    if (typeInfo_.type == data::Parameter::Type::TEXT_EDIT) inputWidget_ = setupEditWidget();
    else if (typeInfo_.type == data::Parameter::Type::INT) inputWidget_ = setupEditWidget();
    else if (typeInfo_.type == data::Parameter::Type::FLOAT) inputWidget_ = setupEditWidget();
    else if (typeInfo_.type == data::Parameter::Type::BOOL) inputWidget_ = setupBoolWidget();
    else if (typeInfo_.type == data::Parameter::Type::FILE) inputWidget_ = setupDirWidget(false);
    else if (typeInfo_.type == data::Parameter::Type::DIRECTORY) inputWidget_ = setupDirWidget(true);
    else if (typeInfo_.type == data::Parameter::Type::DROP_DOWN) inputWidget_ = setupDropDownWidget();
    else inputWidget_ = new QWidget(this);

    lockButton_ = new GraphicalButton(repo::IconRepository::get("lock"));
    lockButton_->setCheckable(true);
    lockButton_->setFixedSize(QSize(18,18));
    connect(lockButton_, SIGNAL(clicked(bool)), this, SLOT(saveLockState(bool)));

    layout_->addWidget(lockButton_, 0, 0);
    layout_->addWidget(inputWidget_, 0, 1);

    setLayout(layout_);
}

void ParameterInputWidget::loadFromConfig() {
    data::Parameter parameter(parameterName_, context_);
    bool lock = parameter.locked();
    lockButton_->setChecked(lock);
    inputWidget_->setDisabled(lock);

    bool isWrong = parameter.isWrong();
    
    QPalette pal = inputWidget_->palette();
    if (isWrong) {
        QPixmap texturePix = QPixmap(repo::PathRepo::iconsDir().absolutePath() + QString("/is-wrong-bg.png"));
        QBrush texture;
        if (!texturePix.isNull()) texture = QBrush(texturePix);
        else texture = QBrush(Qt::blue, Qt::BDiagPattern);
        pal.setBrush(QPalette::Base, texture);
    } else {
        pal.setColor(QPalette::Base, Qt::white);
    }

    inputWidget_->setPalette(pal);
    
    emit shouldLoadValue(parameter.value().toString());
}

void ParameterInputWidget::saveValue(const QString& value) {
    data::Parameter parameter(parameterName_, context_);

    QVariant valVar = value;
    QStringList errors = validator::ParameterValidator::valueErrors(parameter.typeInfo(), value);

    if (errors.size() != 0) {
        QString err, fullErr;
        foreach(err, errors) fullErr += err + "\n";
        QMessageBox::warning(this, tr("Error in setting value for parameter"), fullErr);
        return;
    }

    parameter.setValue(valVar);
    if(parameter.isWrong()) { 
        parameter.setIsWrong(false);
        QPalette pal = inputWidget_->palette();
        pal.setColor(QPalette::Base, Qt::white);
        inputWidget_->setPalette(pal);
    }
}

void ParameterInputWidget::saveLockState(bool lock) {
    data::Parameter parameter(parameterName_, context_);
    inputWidget_->setDisabled(lock);
    parameter.setLock(lock);
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
    combo->setFocusPolicy(Qt::StrongFocus);
    combo->addItems(data::Parameter(parameterName_, context_).typeInfo().properties);

    connect(this, &ParameterInputWidget::shouldLoadValue,
            [ = ](const QString & value){combo->setCurrentIndex(value.toInt());});
    connect(combo, static_cast<void(QComboBox::*)(int)> (&QComboBox::currentIndexChanged),
            [ = ](int index){saveValue(QString::number(index));});

    return combo;
}

QWidget* ParameterInputWidget::setupEditWidget() {
    data::Parameter::TypeInfo info = data::Parameter(parameterName_, context_).typeInfo();
    EditSetWidget* widget;

    if (info.type == data::Parameter::Type::INT) {
        widget = new EditIntSetWidget(info.count, this);
        static_cast<EditIntSetWidget*> (widget)->setRange(info.deduceMinMaxPairs(info.properties));
    } else if (info.type == data::Parameter::Type::FLOAT) {
        widget = new EditDoubleSetWidget(info.count, this);
        static_cast<EditDoubleSetWidget*> (widget)->setRange(info.deduceMinMaxPairs(info.properties));
    } else {
        widget = new EditSetWidget(info.count, this);
    }

    connect(this, SIGNAL(shouldLoadValue(const QString&)),
            widget, SLOT(setValue(const QString&)));
    connect(widget, SIGNAL(valueChanged(const QString&)),
            this, SLOT(saveValue(const QString&)));

    return widget;
}

QWidget* ParameterInputWidget::setupBoolWidget() {
    YesNoWidget* widget = new YesNoWidget(this);

    connect(this, &ParameterInputWidget::shouldLoadValue,
            [ = ](const QString & value){bool val = false;
        QString valStr = value.trimmed().toLower();
        if (valStr == "yes" || valStr == "y" || valStr == "1") val = true;
                widget->setValue(val);
        });
    connect(widget, &YesNoWidget::valueChanged,
            [ = ](bool value){QString val = "n";
        if (value) val = "y";
                saveValue(val); });

    return widget;
}


