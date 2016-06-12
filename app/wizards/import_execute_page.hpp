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

            class ImportExecuteWizardPage : public QWizardPage {

                Q_OBJECT

            public:
                ImportExecuteWizardPage(QWidget* parent = NULL) {
                    setTitle("Execute the import");

                    createFilesTable();
                    resultLabel_ = new QLabel(this);

                    QVBoxLayout *mainLayout = new QVBoxLayout;
                    mainLayout->addWidget(resultLabel_);
                    mainLayout->addWidget(resultsTable_);
                    setLayout(mainLayout);
                }

            public slots:

                void initializePage() override {
                    analyzeImport();
                    if (numberToImage_.keys().isEmpty()) {

                        resultLabel_->setText("No such files could be found. (if not intended, please check the options again.)");
                        resultLabel_->setWordWrap(true);
                        resultsTable_->hide();
                        setCommitPage(false);
                    } else {
                        setSubTitle("Following actions would be executed. Please check and edit. Once committed, you won't be able to change it back.!");
                        showFiles();
                        setCommitPage(true);
                    }
                }

                bool validatePage() override {

                    if (!numberToImage_.keys().isEmpty()) {
                        QDir imagesDir(repo::ProjectRepo::Instance().imagesDir());
                        if (!imagesDir.exists()) QDir().mkpath(imagesDir.absolutePath());
                        
                        QStringList numbers = numberToImage_.keys();

                        QProgressDialog progressDialog(this);
                        progressDialog.setCancelButtonText(tr("&Cancel"));
                        progressDialog.setRange(0, numbers.size());
                        progressDialog.setWindowTitle(tr("Setting up images"));

                        for (int i = 0; i < numberToImage_.keys().size(); ++i) {

                            progressDialog.setValue(i);
                            progressDialog.setLabelText(tr("Importing image %1 of %2...")
                                    .arg(i).arg(numbers.size()));
                            qApp->processEvents();

                            if (progressDialog.wasCanceled()) break;

                            QString number = numbers.at(i);
                            imagesDir.mkdir(number);
                            conf::ProjectImages().setImageProperties(number, imagesDir.absolutePath() + "/" + number, importGroup_);

                            //Copy Image File
                            QFile(numberToImage_[number]).copy(imagesDir.absolutePath() + "/" + number + "/" + number + "_raw.mrc");

                            data::Parameter::ConfigContext context;
                            context.levelUp(importGroup_);
                            context.levelUp(number);

                            data::Parameter("imagename", context).setValue(number);
                            data::Parameter("nonmaskimagename", context).setValue(number);
                            data::Parameter("imagenumber", context).setValue(number);
                            data::Parameter("imagename_original", context).setValue(numberToImage_[number]);

                            //Check for movie files
                            if (numberToMovie_.contains(number)) {
                                QFile(numberToMovie_[number]).copy(imagesDir.absolutePath() + "/" + number + "/" + number + "_stack.mrc");
                                data::Parameter("movie_stackname", context).setValue(numberToMovie_[number]);
                            }

                        }
                    }
                    return true;
                }




            private:

                void analyzeImport() {

                    numberToImage_.clear();
                    numberToMovie_.clear();

                    conf::ProjectPreferences projectConfig;
                    conf::ProjectImages imageConfig;
                    importImagesPath_ = projectConfig.importImageDir();
                    if (importImagesPath_.isEmpty() || !QFileInfo(importImagesPath_).exists()) {
                        std::cerr << "The import image path does not exist\n";
                        return;
                    }

                    importMoviesPath_ = projectConfig.importMovieDir();
                    QDir movieDir(importMoviesPath_);

                    importGroup_ = projectConfig.importGroup();
                    if (importGroup_.isEmpty()) importGroup_ = "auto";

                    QString ignoreImagePattern = projectConfig.importIgnorePattern();
                    int imageNumberLength = projectConfig.importImageLength();

                    int uid = imageConfig.getLastImageNumber();

                    foreach(QString image, QDir(importImagesPath_).entryList(QStringList("*.mrc"), QDir::Files | QDir::NoSymLinks)) {
                        QString imageNumber = commitIntToStringLength(++uid, imageNumberLength);
                        numberToImage_.insert(imageNumber, QDir(importImagesPath_).absoluteFilePath(image));

                        //Check if the file exist in the movie dir
                        if (movieDir.exists()) {
                            QString baseName = QFileInfo(importImagesPath_ + "/" + image).completeBaseName();
                            if (!ignoreImagePattern.isEmpty()) {
                                baseName.contains(ignoreImagePattern, Qt::CaseInsensitive);
                                baseName.remove(ignoreImagePattern, Qt::CaseInsensitive);
                            }

                            QStringList possibleMovieFiles = movieDir.entryList(QStringList(baseName + "*.mrc*"), QDir::Files | QDir::NoSymLinks);
                            if (!possibleMovieFiles.isEmpty()) numberToMovie_.insert(imageNumber, movieDir.absoluteFilePath(possibleMovieFiles[0]));

                        }
                    }
                }

                void showFiles() {

                    resultsTable_->show();
                    resultsTable_->setRowCount(0);

                    foreach(QString number, numberToImage_.keys()) {

                        QTableWidgetItem* numberItem = new QTableWidgetItem(number);
                        numberItem->setFlags(numberItem->flags() ^ Qt::ItemIsEditable);
                        
                        QTableWidgetItem* imageItem = new QTableWidgetItem(QFileInfo(numberToImage_[number]).fileName());
                        imageItem->setFlags(imageItem->flags() ^ Qt::ItemIsEditable);

                        QTableWidgetItem *movieItem;
                        if (numberToMovie_.contains(number)) {
                            movieItem = new QTableWidgetItem(QFileInfo(numberToMovie_[number]).fileName());     
                        } else {
                            movieItem = new QTableWidgetItem("-");
                        }
                        movieItem->setFlags(movieItem->flags() ^ Qt::ItemIsEditable);

                        int row = resultsTable_->rowCount();
                        resultsTable_->insertRow(row);
                        resultsTable_->setItem(row, 0, numberItem);
                        resultsTable_->setItem(row, 1, imageItem);
                        resultsTable_->setItem(row, 2, movieItem);
                    }
                    
                    resultLabel_->setText(tr("%1 image(s) would be added to the project in group <").arg(numberToImage_.keys().size())
                            + importGroup_ + tr(">"));
                    resultLabel_->setWordWrap(true);
                }

                void createFilesTable() {
                    resultsTable_ = new QTableWidget(0, 3);
                    resultsTable_->setSelectionBehavior(QAbstractItemView::SelectRows);

                    QStringList labels;
                    labels << tr("Target Number") << tr("Found Image") << tr("Found Stack");
                    resultsTable_->setHorizontalHeaderLabels(labels);
                    resultsTable_->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
                    resultsTable_->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
                    resultsTable_->verticalHeader()->hide();
                    resultsTable_->setShowGrid(false);
                    resultsTable_->setAlternatingRowColors(true);
                }

                QString commitIntToStringLength(int num, int length) {
                    QString value = QString::number(num);
                    int diff = length - value.size();
                    for (int i = 0; i < diff; ++i) {
                        value.push_front('0');
                    }
                    return value;
                }

                QMap<QString, QString> numberToImage_;
                QMap<QString, QString> numberToMovie_;

                QString importImagesPath_;
                QString importMoviesPath_;
                QString importGroup_;

                //Widgets
                QTableWidget *resultsTable_;
                QLabel *resultLabel_;

            };
        }
    }
}


#endif /* IMPORT_RESULT_HPP */

