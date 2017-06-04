QT += widgets

DEFINES += OGAM_IMPORT_EXPORT_PLUGIN_EXPORTS

HEADERS       = \
    source/header/mainwindow.h \
    source/header/categories_dockwidget.h \ 
    source/header/assets_dockwidget.h \ 
    source/header/tool_resourcetree_widget.h \
    source/header/constants.h \
    source/header/icons_dialog.h \
    source/header/dynlib.h \
    source/header/dynlib_manager.h \
    source/header/singleton.h \
    source/header/prerequisites.h \
    source/header/plugin_resource_interface.h \
    source/header/plugin_interface.h \
    source/header/media_listwidget.h \
    source/header/tool_default_texturewidget.h \
    source/header/plugin_media_widget_interface.h \
    source/header/core.h \
    source/header/treewidget.h \
    source/header/media_widget.h

SOURCES       = \
    source/src/main.cpp \
    source/src/mainwindow.cpp \
    source/src/categories_dockwidget.cpp \ 
    source/src/assets_dockwidget.cpp \ 
    source/src/tool_resourcetree_widget.cpp \
    source/src/treewidget.cpp \
    source/src/icons_dialog.cpp \
    source/src/dynlib.cpp \
    source/src/dynlib_manager.cpp \
    source/src/media_listwidget.cpp \
    source/src/tool_default_texturewidget.cpp \
    source/src/treewidget.cpp

INCLUDEPATH += "../Ogam/source/header/"

Release:DESTDIR = ../Ogam/bin
Debug:DESTDIR = ../Ogam/bin
target.path = $$[QTDIR]/
INSTALLS += target

