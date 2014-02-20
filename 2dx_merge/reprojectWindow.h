#ifndef REPROJECTWINDOW_H
#define REPROJECTWINDOW_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <Qt>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QSize>
#include <QProcess>


#include "confData.h"

//#include "../kernel/mrc/source/2dx_single_particle_lib/2dxSingleParticle.hpp"

class reprojectWindow : public QWidget
{
    Q_OBJECT

public:
    reprojectWindow(confData* config, QWidget *parent = 0);


signals:


public slots:
	void selectPrevParticle();
    void selectNextParticle();
    void updateProjection();
	void lauch2dxImage();
	void particleChanged();


protected:
	void setupGUI();

	

private:
	QLabel* particleLabel;
    QComboBox* particleSelection;
    

    QLabel* taxisLabel;
    QLabel* tanglLabel;
    QLabel* taxaLabel;
    
    QSpinBox* taxisSpinBox;
    QSpinBox* tanglSpinBox;
    QSpinBox* taxaSpinBox;
    
    QSlider* taxisSlider;
    QSlider* tanglSlider;
    QSlider* taxaSlider;

	QVBoxLayout *layout;
	QHBoxLayout* particlePanel;
	QVBoxLayout* anglesLayout;
	
	QHBoxLayout* taxisValueLayout;
	QVBoxLayout* taxisLayout;
	QHBoxLayout* tanglValueLayout;
	QHBoxLayout* taxaValueLayout;
	QVBoxLayout* taxaLayout;
	
	QPixmap pixmap_part;
	QPixmap pixmap_proj;
	
	QLabel* projPixmapLabel;
	QLabel* particlePixmapLabel;
	
	QPushButton* nextParticleButton;
	QPushButton* prevParticleButton;
	QPushButton* updateProjectionButton;
	QPushButton* launch2dxImageButton;
	
	
	
	
	confData* config_gui;

};

#endif 
