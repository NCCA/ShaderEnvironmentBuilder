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
    /// @brief our QScintilla widget1 (vertex)
    QsciScintilla *m_qsci1;
    /// @brief our QScintilla widget2 (fragment)
    QsciScintilla *m_qsci2;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_btn_loadShader_clicked();

    void on_btn_compileShader_clicked();

    void on_tabs_qsci_currentChanged(int index);

private:
    Ui::MainWindow *m_ui;
        /// @brief our openGL widget
        NGLScene *m_gl;

};

#endif // MAINWINDOW_H
