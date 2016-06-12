/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   import_result.hpp
 * Author: biyanin
 *
 * Created on June 10, 2016, 4:17 PM
 */

#ifndef IMPORT_RESULT_HPP
#define IMPORT_RESULT_HPP

#include <iostream>

#include <QWizardPage>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QLabel>
#include <QProgressDialog>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QMap>
#include <QPair>

#include "conf/project_images.hpp"
#include "conf/project_preferences.hpp"

#include "repositories/project_repo.hpp"

#include "data/parameter.hpp"

namespace tdx {

    namespace app {

        namespace wizard {

            class ImportResultWizardPage : public QWizardPage {

                Q_OBJECT

            public:
                ImportResultWizardPage(QWidget* parent = NULL) {


                    setTitle("Selection results");
                    setSubTitle("Following actions would be taken with the options selected");

                    createFilesTable();
                    filesFoundLabel = new QLabel(this);

                    QVBoxLayout *mainLayout = new QVBoxLayout;
                    mainLayout->addWidget(filesFoundLabel);
                    mainLayout->addWidget(filesTable);
                    setLayout(mainLayout);
                }

            public slots:

                void initializePage() override {
                    analyzeImport();
                    if (numberToName_.keys().isEmpty()) {
                        filesFoundLabel->setText("No such files could be found. (if not intended, please check the options again.)");
                        filesFoundLabel->setWordWrap(true);
                        filesTable->hide();
                        setCommitPage(false);
                    } else {
                        showFiles();
                        setCommitPage(true);
                    }
                }

                bool validatePage() override {

                    if (!numberToName_.keys().isEmpty()) {
                        QDir imagesDir(repo::ProjectRepo::Instance().imagesDir());
                        if(!imagesDir.exists()) QDir().mkpath(imagesDir.absolutePath());
                        
                        QStringList numbers =  numberToName_.keys();
                        
                        QProgressDialog progressDialog(this);
                        progressDialog.setCancelButtonText(tr("&Cancel"));
                        progressDialog.setRange(0, numbers.size());
                        progressDialog.setWindowTitle(tr("Setting up images"));
                                                
                        for(int i=0; i<numberToName_.keys().size(); ++i) {
                            
                            progressDialog.setValue(i);
                            progressDialog.setLabelText(tr("Importing image %1 of %2...")
                                    .arg(i).arg(numbers.size()));
                            qApp->processEvents();
                            
                            if (progressDialog.wasCanceled()) break;
                            
                            QString number = numbers.at(i);
                            imagesDir.mkdir(number);
                            conf::ProjectImages().setImageProperties(number, imagesDir.absolutePath() + "/" + number, group_);
                            
                            //Copy Files
                            QFile origImageFile(imagesDirPath_+"/"+numberToName_[number]);
                            origImageFile.copy(imagesDir.absolutePath() + "/" + number + "/" + number + "_raw.mrc");
                            
                            data::Parameter::ConfigContext context;
                            context.levelUp(group_);
                            context.levelUp(number);
                            
                            data::Parameter("imagename", context).setValue(number);
                            data::Parameter("nonmaskimagename", context).setValue(number);
                            data::Parameter("imagenumber", context).setValue(number);
                            data::Parameter("imagename_original", context).setValue(imagesDirPath_+"/"+numberToName_[number]);
                            
                            //Check for movie files
                            if(numberToSizes_[number].second > 0) {
                                QFile origMovieFile(moviesDirPath_+"/"+numberToName_[number]);
                                origMovieFile.copy(imagesDir.absolutePath() + "/" + number + "/" + number + "_stack.mrc");
                                data::Parameter("movie_stackname", context).setValue(moviesDirPath_+"/"+numberToName_[number]);
                            }
                            
                        }
                    }
                    return true;
                }




            private:

                void analyzeImport() {
                    
                    numberToName_.clear();
                    numberToSizes_.clear();
                    
                    conf::ProjectPreferences projectConfig;
                    conf::ProjectImages imageConfig;
                    imagesDirPath_ = projectConfig.importImageDir();
                    if (imagesDirPath_.isEmpty() || !QFileInfo(imagesDirPath_).exists()) {
                        std::cerr << "The import image path does not exist\n";
                        return;
                    }

                    QDir imageDir(imagesDirPath_);
                    QStringList images = imageDir.entryList(QStringList("*.mrc"), QDir::Files | QDir::NoSymLinks);
                    
                    QString moviesDirPath_ = projectConfig.importMovieDir();
                    QDir movieDir(moviesDirPath_);

                    group_ = projectConfig.importGroup();
                    if (group_.isEmpty()) group_ = "auto";

                    int strLength = projectConfig.importImageLength();

                    int uid = imageConfig.getLastImageNumber();

                    foreach(QString image, images) {
                        qint64 imageSize = QFileInfo(imageDir.absoluteFilePath(image)).size();
                        uid = uid+1;
                        QString imageUid = commitIntToStringLength(uid, strLength);

                        qint64 movieSize = -1;
                        if (QFileInfo(movieDir.absoluteFilePath(image)).exists()) {
                            movieSize = QFileInfo(movieDir.absoluteFilePath(image)).size();
                        }

                        numberToName_.insert(imageUid, image);
                        numberToSizes_.insert(imageUid, QPair<int, int>(imageSize, movieSize));
                    }
                }

                void showFiles() {

                    filesTable->show();
                    filesTable->setRowCount(0);
                    
                    foreach(QString number, numberToName_.keys()) {

                        QTableWidgetItem *fileNumberItem = new QTableWidgetItem(number);
                        QTableWidgetItem *fileNameItem = new QTableWidgetItem(numberToName_[number]);

                        QTableWidgetItem *imageItem = new QTableWidgetItem(tr("%1 MB")
                                .arg(int((numberToSizes_[number].first + 1048575) / 1048576)));
                        imageItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                        imageItem->setFlags(imageItem->flags() ^ Qt::ItemIsEditable);

                        QTableWidgetItem *movieItem;
                        if (numberToSizes_[number].second < 0) {
                            movieItem = new QTableWidgetItem("-");
                        } else {
                            movieItem = new QTableWidgetItem(tr("%1 MB")
                                    .arg(int((numberToSizes_[number].second + 1048575) / 1048576)));
                            movieItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                            movieItem->setFlags(movieItem->flags() ^ Qt::ItemIsEditable);
                        }

                        int row = filesTable->rowCount();
                        filesTable->insertRow(row);
                        filesTable->setItem(row, 0, fileNameItem);
                        filesTable->setItem(row, 1, fileNumberItem);
                        filesTable->setItem(row, 2, imageItem);
                        filesTable->setItem(row, 3, movieItem);
                    }
                    filesFoundLabel->setText(tr("%1 image(s) would be added to the project in group <").arg(numberToName_.keys().size()) 
                                                + group_ + tr(">"));
                    filesFoundLabel->setWordWrap(true);
                }

                void createFilesTable() {
                    filesTable = new QTableWidget(0, 4);
                    filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

                    QStringList labels;
                    labels << tr("File Name") << tr("Target Number") << tr("Image") << tr("Stack");
                    filesTable->setHorizontalHeaderLabels(labels);
                    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
                    filesTable->verticalHeader()->hide();
                    filesTable->setShowGrid(false);
                }

                QString commitIntToStringLength(int num, int length) {
                    QString value = QString::number(num);
                    int diff = length - value.size();
                    for (int i = 0; i < diff; ++i) {
                        value.push_front('0');
                    }
                    return value;
                }

                QMap<QString, QString> numberToName_;
                QMap<QString, QPair<int, int>> numberToSizes_;
                
                QString imagesDirPath_;
                QString moviesDirPath_;
                QString group_;
                QStringList errorMessages_;

                //Widgets
                QTableWidget *filesTable;
                QLabel *filesFoundLabel;

            };
        }
    }
}


#endif /* IMPORT_RESULT_HPP */

