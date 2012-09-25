#include <QtGui>
#include <QtCore>

#include <iostream>
#include "../SimpleDIP.h"

void SimpleDIP::createToolDockWidget() {
    toolDockWidget = new QDockWidget(tr("Tool Box"));
    toolDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
            Qt::RightDockWidgetArea);
    tools = new ToolTabs();
    toolDockWidget->setWidget(tools);
    addDockWidget(Qt::RightDockWidgetArea, toolDockWidget);
}

void SimpleDIP::createInfoDockWidget() {
    infoDockWidget = new QDockWidget(tr("Information"));
    infoDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
            Qt::RightDockWidgetArea);
    info = new Information();
    infoDockWidget->setWidget(info);
    addDockWidget(Qt::LeftDockWidgetArea, infoDockWidget);
}
