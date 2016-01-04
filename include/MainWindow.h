#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NGLScene.h"
#include <Qsci/qsciscintilla.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *m_ui;
		/// @brief our openGL widget
		NGLScene *m_gl;
    /// @brief our QScintilla widget
    QsciScintilla *m_qsci;
};

#endif // MAINWINDOW_H
