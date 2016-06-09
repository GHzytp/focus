
#include <iostream>

#include <QFont>
#include <QPalette>
#include <QColor>

#include "parameter_section.hpp"
#include "repositories/icon_repo.hpp"

using namespace tdx::app::widget;

ParameterSectionWidget::ParameterSectionWidget(QString sectionTitle, data::Parameter::ConfigContext context, QWidget *parent)
: QWidget(parent), context_(context) {

    mainLayout_ = new QVBoxLayout;
    mainLayout_->setSpacing(10);
    mainLayout_->setMargin(10);

    QLabel* title = new QLabel(sectionTitle);
    title->setAlignment(Qt::AlignLeft);

    QFont f = title->font();
    f.setCapitalization(QFont::Capitalize);
    f.setBold(true);
    title->setFont(f);
    QPalette pal = title->palette();
    pal.setColor(QPalette::WindowText, QColor(31, 92, 207));
    title->setPalette(pal);
    mainLayout_->addWidget(title);

    parameterFrame_ = new QFrame(this);
    parameterFrame_->setFrameShadow(QFrame::Plain);
    parameterFrame_->setFrameShape(QFrame::StyledPanel);

    formLayout_ = new QFormLayout();
    formLayout_->setRowWrapPolicy(QFormLayout::WrapLongRows);
    formLayout_->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    formLayout_->setFormAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    formLayout_->setLabelAlignment(Qt::AlignLeft);
    formLayout_->setVerticalSpacing(0);

    setAutoFillBackground(true);
}

void ParameterSectionWidget::addParameter(const QString& parameterName) {
    ParameterInputWidget* inputWidget = new ParameterInputWidget(parameterName, context_, this);
    parameterRowLookup_.insert(parameterName, parameterInputLookup_.size());
    parameterInputLookup_.insert(parameterName, inputWidget);
    data::Parameter paramModel(parameterName, context_);
    formLayout_->addRow(paramModel.property("label"), inputWidget);
    QWidget* label = formLayout_->labelForField(inputWidget);
    label->setToolTip(getWhatsThis(parameterName));
    if (paramModel.property("userlevel").toLower().trimmed() == "advanced") {
        QFont f = label->font();
        f.setItalic(true);
        label->setFont(f);
    }
}

void ParameterSectionWidget::loadFromConfig() {
    QString parameterName;

    foreach(parameterName, parameterInputLookup_.keys()) {
        parameterInputLookup_[parameterName]->loadFromConfig();
    }
}

void ParameterSectionWidget::finishAddingParameters() {
    parameterFrame_->setLayout(formLayout_);
    mainLayout_->addWidget(parameterFrame_);
    mainLayout_->addSpacing(10);
    setLayout(mainLayout_);
}

QString ParameterSectionWidget::getWhatsThis(QString parameterName) {
    data::Parameter param(parameterName, context_);
    QString whatsthis = parameterName + "<br><br>" + param.property("legend") + "<br>";

    data::Parameter::TypeInfo info = param.typeInfo();
    QMap<int, QStringList> widgetRange = info.deduceMinMaxPairs(info.properties);

    if(!widgetRange.isEmpty()) whatsthis += "Range: <br>";
    foreach(int i, widgetRange.keys()) {
        if(widgetRange.size() >1) {
            whatsthis += QString::number(i+1) + " : ";
        }
        if (!widgetRange.value(i)[0].isEmpty()) {
            whatsthis += " Min=";
            whatsthis += widgetRange.value(i)[0];
        }
        if (widgetRange.value(i).size() > 1 && !widgetRange.value(i)[1].isEmpty()) {
            whatsthis += " and ";
            whatsthis += " Max=";
            whatsthis += widgetRange.value(i)[1];
            whatsthis += " ";
        }
        whatsthis += "<br>";
    }
    whatsthis += "Example: " + param.property("example") + "<br><br>";
    whatsthis += "<a href=\"" + param.property("help") + "\"> " + param.property("help") + "</a>";

    return whatsthis;

}



