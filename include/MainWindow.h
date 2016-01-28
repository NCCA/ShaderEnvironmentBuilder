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
    /// @brief our QScintilla widget
    QsciScintilla *m_qsci;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_btn_loadShader_clicked();

    void on_btn_compileShader_clicked();

private:
    Ui::MainWindow *m_ui;
        /// @brief our openGL widget
        NGLScene *m_gl;

};

#endif // MAINWINDOW_H
