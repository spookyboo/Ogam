/****************************************************************************
**
** Copyright (C) 2016 - 2017
**
** This file is generated by the Magus toolkit
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#ifndef AssetsDOCWIDGET_H
#define AssetsDOCWIDGET_H

#include "constants.h"
#include <QtWidgets>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>
#include <QTabWidget>

QT_BEGIN_NAMESPACE
class QDockWidget;
QT_END_NAMESPACE

class MainWindow;
class ResourceWidget;

/****************************************************************************
 This class represents a DockWidget
 ***************************************************************************/
class _OgamExport AssetsDockWidget : public QDockWidget
{
	Q_OBJECT

	public:
		AssetsDockWidget(QString title, MainWindow* parent, Qt::WindowFlags flags = 0);
		~AssetsDockWidget(void);

        // Add a widget
        void addWidget (QWidget* widget,
                        QString fullQualifiedIconName,
                        QString tabName);

	private slots:
        void tabSelected(int index);

	private:
		MainWindow* mParent;
        QMainWindow* mInnerMain;
        QTabWidget* mTabWidget;
        bool mResourcesAdded; // Determines wether a ResourceWidget was added
};

#endif

