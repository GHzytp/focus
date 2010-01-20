#############################################################################
# Makefile for building: 2dx_image.app/Contents/MacOS/2dx_image
# Generated by qmake (2.01a) (Qt 4.5.3) on: Wed Jan 20 14:04:18 2010
# Project:  qmake.pro
# Template: app
# Command: /usr/bin/qmake -macx -config release -o 2dx_image.xcodeproj/project.pbxproj qmake.pro
#############################################################################

MOC       = /Developer/Tools/Qt/moc
UIC       = /Developer/Tools/Qt/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_NO_DEBUG -DQT_WEBKIT_LIB -DQT_SCRIPT_LIB -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/Qt4.5/mkspecs/macx-xcode -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtNetwork.framework/Versions/4/Headers -I/usr/include/QtNetwork -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/Library/Frameworks/QtOpenGL.framework/Versions/4/Headers -I/usr/include/QtOpenGL -I/Library/Frameworks/QtScript.framework/Versions/4/Headers -I/usr/include/QtScript -I/Library/Frameworks/QtWebKit.framework/Versions/4/Headers -I/usr/include/QtWebKit -I/usr/include -I. -I../include -I/opt/local/include -I../include -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/System/Library/Frameworks/AGL.framework/Headers -I. -I/usr/local/include -I/System/Library/Frameworks/CarbonCore.framework/Headers -F/Library/Frameworks
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compilers: ./moc_centralWindow.cpp ./moc_mainWindow.cpp ./moc_navigator.cpp\
	 ./moc_controlActionsGroup.cpp ./moc_progressStamps.cpp ./moc_resultsFile.cpp\
	 ./moc_resultsParser.cpp ./moc_statusViewer.cpp ./moc_warningBox.cpp
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_centralWindow.cpp moc_mainWindow.cpp moc_navigator.cpp moc_controlActionsGroup.cpp moc_progressStamps.cpp moc_resultsFile.cpp moc_resultsParser.cpp moc_statusViewer.cpp moc_warningBox.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_centralWindow.cpp moc_mainWindow.cpp moc_navigator.cpp moc_controlActionsGroup.cpp moc_progressStamps.cpp moc_resultsFile.cpp moc_resultsParser.cpp moc_statusViewer.cpp moc_warningBox.cpp
moc_centralWindow.cpp: controlActionsGroup.h \
		progressStamps.h \
		resultsParser.h \
		statusViewer.h \
		warningBox.h \
		resultsFile.h \
		centralWindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ centralWindow.h -o moc_centralWindow.cpp

moc_mainWindow.cpp: centralWindow.h \
		controlActionsGroup.h \
		progressStamps.h \
		resultsParser.h \
		statusViewer.h \
		warningBox.h \
		resultsFile.h \
		mainWindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ mainWindow.h -o moc_mainWindow.cpp

moc_navigator.cpp: navigator.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ navigator.h -o moc_navigator.cpp

moc_controlActionsGroup.cpp: progressStamps.h \
		controlActionsGroup.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ controlActionsGroup.h -o moc_controlActionsGroup.cpp

moc_progressStamps.cpp: progressStamps.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ progressStamps.h -o moc_progressStamps.cpp

moc_resultsFile.cpp: resultsFile.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ resultsFile.h -o moc_resultsFile.cpp

moc_resultsParser.cpp: resultsParser.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ resultsParser.h -o moc_resultsParser.cpp

moc_statusViewer.cpp: statusViewer.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ statusViewer.h -o moc_statusViewer.cpp

moc_warningBox.cpp: resultsFile.h \
		warningBox.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ warningBox.h -o moc_warningBox.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

