
#include <iostream>

#include <QFont>

#include "parameter_section.hpp"
#include "repositories/icon_repo.hpp"

using namespace tdx::app::widget;

ParameterSectionWidget::ParameterSectionWidget(QString sectionTitle, data::Parameter::ConfigContext context, QWidget *parent)
: QWidget(parent), context_(context) {

    mainLayout_ = new QVBoxLayout;
    mainLayout_->addSpacing(10);
    mainLayout_->setSpacing(0);
    mainLayout_->setMargin(0);
    
    QLabel* title = new QLabel(sectionTitle);
    title->setAlignment(Qt::AlignCenter);
    QFont f = title->font();
    f.setCapitalization(QFont::SmallCaps);
    f.setBold(true);
    title->setFont(f);
    mainLayout_->addWidget(title, Qt::AlignCenter);
    
    groupBox_ = new QGroupBox(this);
    setAutoFillBackground(true);
    formLayout_ = new QFormLayout();
    formLayout_->setRowWrapPolicy(QFormLayout::WrapLongRows);
    formLayout_->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    formLayout_->setFormAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    formLayout_->setLabelAlignment(Qt::AlignLeft);
    formLayout_->setVerticalSpacing(0);
}

void ParameterSectionWidget::addParameter(const QString& parameterName) {
    ParameterInputWidget* inputWidget = new ParameterInputWidget(parameterName, context_, this);
    parameterRowLookup_.insert(parameterName, parameterInputLookup_.size());
    parameterInputLookup_.insert(parameterName, inputWidget);
    data::Parameter paramModel(parameterName, context_);
    formLayout_->addRow(paramModel.property("label"), inputWidget);
}

void ParameterSectionWidget::loadValues() {
    QString parameterName;
    foreach(parameterName, parameterInputLookup_.keys()) {
        QString val = data::Parameter(parameterName, context_).value().toString();
        parameterInputLookup_[parameterName]->loadValue(val);
    }
}

void ParameterSectionWidget::finishAddingParameters() {
    groupBox_->setLayout(formLayout_);
    mainLayout_->addWidget(groupBox_);
    mainLayout_->addSpacing(20);
    setLayout(mainLayout_);
}

/*
void ParameterSectionWidget::updateWhatsThis() {
    data::Parameter param = parameter();
    QString whatsthis = name_ + "<br><br>" + param.property("legend") + "<br><br>";
    bool minDefined = false, maxDefined = false;
    minDefined = param.property("type").contains("min", Qt::CaseInsensitive);
    maxDefined = param.property("type").contains("max", Qt::CaseInsensitive);
    if (minDefined || maxDefined) {
        QString type = param.property("type");
        type.replace(QRegExp("^.*\"(.*)\".*$"), "\\1");
        QStringList fields = type.split(';');
        QString minimum, maximum;
        QMap<int, QStringList> minMaxPairs;
        minDefined = false;
        maxDefined = false;
        bool currentMaxDefined, currentMinDefined;
        int k = 0;

        foreach(QString field, fields) {
            if (minDefined && field.contains("min", Qt::CaseInsensitive)) {
                k++;
                minDefined = false;
                maxDefined = false;
            }
            if (maxDefined && field.contains("max", Qt::CaseInsensitive)) {
                k++;
                minDefined = false;
                maxDefined = false;
            }
            currentMaxDefined = field.contains("max", Qt::CaseInsensitive);
            currentMinDefined = field.contains("min", Qt::CaseInsensitive);

            if (currentMinDefined) {
                minMaxPairs[k].insert(0, field.section('=', -1, -1).trimmed());
                minDefined = true;
            }
            if (currentMaxDefined) {
                minMaxPairs[k].insert(1, field.section('=', -1, -1).trimmed());
                maxDefined = true;
            }
        }

        QMapIterator<int, QStringList> it(minMaxPairs);

        whatsthis += "Range";
        if (minMaxPairs.size() > 1) whatsthis += "s: <br>";
        else whatsthis += ": ";

        foreach(QStringList p, minMaxPairs)
        while (it.hasNext()) {
            it.next();
            if (minMaxPairs.size() > 1) whatsthis += QString::number(it.key() + 1) + ": ";
            QStringList p = it.value();
            maxDefined = false;
            minDefined = false;
            if (p.size() > 0) minDefined = !p[0].isEmpty();
            if (p.size() > 1) maxDefined = !p[1].isEmpty();

            if (minDefined) {
                if (!maxDefined) whatsthis += " Min=";
                whatsthis += p[0];
            }
            if (maxDefined) {
                if (!minDefined) whatsthis += "Max=";
                else whatsthis += " to ";
                whatsthis += p[1];
            }
            whatsthis += "<br>";
        }
        whatsthis += "<br>";
    }
    
    whatsthis += "Example: " + param.property("example") + "<br><br>";
    whatsthis += "<a href=\"" + param.property("help") + "\"> " + param.property("help") + "</a>";
    setWhatsThis(whatsthis);

}
*/



