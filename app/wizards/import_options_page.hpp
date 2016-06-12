/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   import_images.hpp
 * Author: biyanin
 *
 * Created on June 10, 2016, 11:07 AM
 */

#ifndef IMPORT_IMAGES_WIZARD_PAGE_HPP
#define IMPORT_IMAGES_WIZARD_PAGE_HPP

#include <QWizardPage>
#include <QFormLayout>
#include <QComboBox>
#include <QString>
#include <QStringList>
#include <QLineEdit>

#include "conf/project_images.hpp"
#include "conf/project_preferences.hpp"

#include "repositories/icon_repo.hpp"

#include "widgets/browser_widget.hpp"
#include "widgets/combo_input_widget.hpp"
#include "widgets/edit_set_widget.hpp"

namespace tdx {

    namespace app {

        namespace wizard {

            class ImportOptionsWizardPage : public QWizardPage {

                Q_OBJECT

            public:
                ImportOptionsWizardPage(QWidget* parent = NULL)
                : QWizardPage(parent) {

                    setTitle("Import images and movies");
                    setSubTitle(QString("Select the directory containing averaged images") +
                            QString(" and (optionally) select the corresponding movie/stacks") +
                            QString(" directory. Note that the names of the corresponding images and stacks") +
                            QString(" should be same for correct import"));

                    
                    widget::BrowserWidget* filesDirBrowser_ = new widget::BrowserWidget(widget::BrowserWidget::BrowseType::DIRECTORY);
                    QString currImagePath = conf::ProjectPreferences().importImageDir();
                    if (currImagePath != "") filesDirBrowser_->setPath(currImagePath);
                    connect(filesDirBrowser_, &widget::BrowserWidget::pathChanged,
                            [ = ] (const QString & value){conf::ProjectPreferences().setImportImageDir(value);});  
                            
                    
                    widget::BrowserWidget* moviesDirBrowser_ = new widget::BrowserWidget(widget::BrowserWidget::BrowseType::DIRECTORY);
                    QString currMoviePath = conf::ProjectPreferences().importMovieDir();
                    if (currMoviePath != "") moviesDirBrowser_->setPath(currMoviePath);
                    connect(moviesDirBrowser_, &widget::BrowserWidget::pathChanged,
                            [ = ] (const QString & value){conf::ProjectPreferences().setImportMoiveDir(value);});
                    
                    widget::EditSetWidget* ignoreImagePattern = new widget::EditSetWidget;
                    ignoreImagePattern->setValue(conf::ProjectPreferences().importIgnorePattern());
                    connect(ignoreImagePattern, &widget::EditSetWidget::valueChanged,
                            [ = ] (const QString & value){conf::ProjectPreferences().setImportIgnorePattern(value);});

                    widget::ComboInputWidget* addToGroup_;
                    addToGroup_ = new widget::ComboInputWidget();
                    addToGroup_->setEditable(true);
                    addToGroup_->addItems(conf::ProjectImages().imageGroups());
                    addToGroup_->setCurrentText(conf::ProjectPreferences().importGroup());
                    addToGroup_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                    connect(addToGroup_, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentTextChanged),
                            [ = ] (const QString & value){conf::ProjectPreferences().setImportGroup(value);});
                    
                    widget::EditIntSetWidget* numberLength_ = new widget::EditIntSetWidget();
                    numberLength_->setAllRanges(5, 10);
                    int pastNumberLength = conf::ProjectPreferences().importImageLength();
                    if(pastNumberLength >= 5 && pastNumberLength <=10) numberLength_->setValue(QString::number(pastNumberLength));
                    else {
                        numberLength_->setValue("5");
                        conf::ProjectPreferences().setImportImageLength(5);
                    }
                    connect(numberLength_, &widget::EditSetWidget::valueChanged,
                            [ = ] (const QString & value){conf::ProjectPreferences().setImportImageLength(value.toInt());});

                    QFormLayout* layout = new QFormLayout;
                    layout->setRowWrapPolicy(QFormLayout::WrapLongRows);
                    layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
                    layout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
                    layout->setLabelAlignment(Qt::AlignRight);
                    layout->addRow("Averaged Images directory", filesDirBrowser_);
                    layout->addRow("Stacks directory", moviesDirBrowser_);
                    layout->addRow("String to be ignored at the end of image file names", ignoreImagePattern);
                    layout->addRow("Add the imported images to group", addToGroup_);
                    layout->addRow("Length of the target image number string (>=5 & <=10)", numberLength_);

                    setLayout(layout);

                }


            };
        }
    }
}


#endif

