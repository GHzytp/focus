#############################################################################
# Makefile for building: 2dx_logbrowser.app/Contents/MacOS/2dx_logbrowser
# Generated by qmake (2.01a) (Qt 4.5.3) on: Wed Jan 20 14:04:18 2010
# Project:  qmake.pro
# Template: app
# Command: /usr/bin/qmake -macx -config release -o 2dx_logbrowser.xcodeproj/project.pbxproj qmake.pro
#############################################################################

MOC       = /Developer/Tools/Qt/moc
UIC       = /Developer/Tools/Qt/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/Qt4.5/mkspecs/macx-xcode -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/usr/include -I../include -I. -I/usr/local/include -I/System/Library/Frameworks/CarbonCore.framework/Headers -F/Library/Frameworks
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compilers: ./moc_LBMainWindow.cpp ./moc_LogViewer.cpp ./moc_ViewerContainer.cpp
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_LBMainWindow.cpp moc_LogViewer.cpp moc_ViewerContainer.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_LBMainWindow.cpp moc_LogViewer.cpp moc_ViewerContainer.cpp
moc_LBMainWindow.cpp: ViewerContainer.h \
		LogBrowserCommons.h \
		LogDirectory.h \
		LogViewer.h \
		LogFileReader.h \
		LBMainWindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ LBMainWindow.h -o moc_LBMainWindow.cpp

moc_LogViewer.cpp: LogBrowserCommons.h \
		LogFileReader.h \
		LogViewer.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ LogViewer.h -o moc_LogViewer.cpp

moc_ViewerContainer.cpp: LogBrowserCommons.h \
		LogDirectory.h \
		LogViewer.h \
		LogFileReader.h \
		ViewerContainer.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ ViewerContainer.h -o moc_ViewerContainer.cpp

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

