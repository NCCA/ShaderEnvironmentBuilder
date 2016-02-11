#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NGLScene.h"
#include "button.h"
#include "parserLib.h"
#include <Qsci/qsciscintilla.h>
#include <vector>

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
    void createButtons();
    void printUniforms();
    ~MainWindow();


private slots:
    void on_btn_loadShader_clicked();

    void on_btn_compileShader_clicked();

private:
    Ui::MainWindow *m_ui;
        /// @brief our openGL widget
        NGLScene *m_gl;
    parserLib *m_parForButton;
    std::vector<Button> m_buttonList;

};

#endif // MAINWINDOW_H
