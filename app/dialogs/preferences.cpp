/* 
 * Author: Nikhil Biyani - nikhil(dot)biyani(at)gmail(dot)com
 *
 * This file is a part of 2dx.
 * 
 * 2dx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or any 
 * later version.
 * 
 * 2dx is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details <http://www.gnu.org/licenses/>.
 */

#include <QtWidgets>
#include <QSettings>
#include <QFontDatabase>
#include <QPalette>
#include <QColor>

#include "preferences.hpp"

#include "repositories/icon_repo.hpp"
#include "repositories/path_repo.hpp"

#include "conf/user_preferences.hpp"

using namespace tdx::app::dialog;

PreferencesDialog::PreferencesDialog()
{
    contentsWidget_ = new QListWidget;
    contentsWidget_->setViewMode(QListView::IconMode);
    contentsWidget_->setIconSize(QSize(96, 84));
    contentsWidget_->setMovement(QListView::Static);
    contentsWidget_->setMaximumWidth(128);
    contentsWidget_->setSpacing(12);

    pagesWidget_ = new QStackedWidget;
    pagesWidget_->addWidget(getApperancePage());
    pagesWidget_->addWidget(getViewersPage());
    pagesWidget_->addWidget(getAppsPage());

    QPushButton *closeButton = new QPushButton(tr("Close"));

    createIcons();
    contentsWidget_->setCurrentRow(0);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget_);
    horizontalLayout->addWidget(pagesWidget_, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Preferences"));
}

void PreferencesDialog::createIcons()
{
    QListWidgetItem *appearanceButton = new QListWidgetItem(contentsWidget_);
    appearanceButton->setIcon(repo::IconRepository::get("appearance"));
    appearanceButton->setText(tr("Appearance"));
    appearanceButton->setTextAlignment(Qt::AlignHCenter);
    appearanceButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *viewersButton = new QListWidgetItem(contentsWidget_);
    viewersButton->setIcon(repo::IconRepository::get("viewer"));
    viewersButton->setText(tr("Viewers"));
    viewersButton->setTextAlignment(Qt::AlignHCenter);
    viewersButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *externalButton = new QListWidgetItem(contentsWidget_);
    externalButton->setIcon(repo::IconRepository::get("external"));
    externalButton->setText(tr("Linked Apps"));
    externalButton->setTextAlignment(Qt::AlignHCenter);
    externalButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget_, &QListWidget::currentItemChanged, this, &PreferencesDialog::changePage);
}

void PreferencesDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget_->setCurrentIndex(contentsWidget_->row(current));
}


QWidget* PreferencesDialog::getApperancePage()
{
    QWidget* widget = new QWidget();
    
    //---------------------
    // Font
    //---------------------
    QGroupBox *fontGroup = new QGroupBox(tr("Font"));

    //Font Size
    QLabel *fontSizeLabel = new QLabel(tr("Size"));
    
    conf::UserPreferences manager;
    
    QComboBox *fontSizeCombo = new QComboBox;
    for(int i=8; i<16; ++i)  fontSizeCombo->addItem(QString::number(i));
    fontSizeCombo->setCurrentText(QString::number(QApplication::font().pointSize()));
    
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(const QString&)), 
            &manager, SLOT(setFontSize(const QString&)));
    
    //Font Weight
    QLabel *fontWeightLabel = new QLabel(tr("Weight"));
    QComboBox *fontWeightCombo = new QComboBox;
    fontWeightCombo->addItems(QStringList() << "0" << "25" << "50" << "75");
    fontWeightCombo->setCurrentText(QString::number(QApplication::font().weight()));
    
    connect(fontWeightCombo, SIGNAL(currentIndexChanged(const QString&)), 
            &manager, SLOT(setFontWeight(const QString&)));
    
    //Font Family
    QLabel *fontFamilyLabel = new QLabel(tr("Family"));
    QComboBox *fontFamilyCombo = new QComboBox;
    fontFamilyCombo->addItems(QFontDatabase().families(QFontDatabase::Latin));
    fontFamilyCombo->setCurrentText(QApplication::font().family());
    
    connect(fontFamilyCombo, SIGNAL(currentIndexChanged(const QString&)), 
            &manager, SLOT(setFontFamily(const QString&)));

    QGridLayout *fontLayout = new QGridLayout;
    fontLayout->addWidget(fontSizeLabel, 0, 0);
    fontLayout->addWidget(fontSizeCombo, 0, 1);
    fontLayout->addWidget(fontWeightLabel, 1, 0);
    fontLayout->addWidget(fontWeightCombo, 1, 1);
    fontLayout->addWidget(fontFamilyLabel, 2, 0);
    fontLayout->addWidget(fontFamilyCombo, 2, 1);

    fontGroup->setLayout(fontLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fontGroup);
    mainLayout->addStretch(1);
    widget->setLayout(mainLayout);
    return widget;
}

QWidget* PreferencesDialog::getViewersPage()
{
    QWidget* widget = new QWidget();
    QGroupBox *updateGroup = new QGroupBox(tr("Package selection"));
    QCheckBox *systemCheckBox = new QCheckBox(tr("Update system"));
    QCheckBox *appsCheckBox = new QCheckBox(tr("Update applications"));
    QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));

    QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

    QListWidget *packageList = new QListWidget;
    QListWidgetItem *qtItem = new QListWidgetItem(packageList);
    qtItem->setText(tr("Qt"));
    QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
    qsaItem->setText(tr("QSA"));
    QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
    teamBuilderItem->setText(tr("Teambuilder"));

    QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

    QVBoxLayout *updateLayout = new QVBoxLayout;
    updateLayout->addWidget(systemCheckBox);
    updateLayout->addWidget(appsCheckBox);
    updateLayout->addWidget(docsCheckBox);
    updateGroup->setLayout(updateLayout);

    QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);
    packageGroup->setLayout(packageLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
    mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    widget->setLayout(mainLayout);
    return widget;
}

QWidget* PreferencesDialog::getAppsPage()
{
    QWidget* widget = new QWidget();
    QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLineEdit *nameEdit = new QLineEdit;

    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

    QSpinBox *hitsSpinBox = new QSpinBox;
    hitsSpinBox->setPrefix(tr("Return up to "));
    hitsSpinBox->setSuffix(tr(" results"));
    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    hitsSpinBox->setMinimum(1);
    hitsSpinBox->setMaximum(100);
    hitsSpinBox->setSingleStep(10);

    QPushButton *startQueryButton = new QPushButton(tr("Start query"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesLayout->addWidget(nameLabel, 0, 0);
    packagesLayout->addWidget(nameEdit, 0, 1);
    packagesLayout->addWidget(releasesCheckBox, 2, 0);
    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
    packagesGroup->setLayout(packagesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startQueryButton);
    mainLayout->addStretch(1);
    widget->setLayout(mainLayout);
    return widget;
}



