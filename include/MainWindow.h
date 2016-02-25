#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ngl/Vec4.h>
#include "NGLScene.h"
#include <QMainWindow>
#include "ParserLib.h"
#include "button.h"
#include <Qsci/qsciscintilla.h>
#include <vector>

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
    void createButtons();
    void printUniforms();
    ~MainWindow();


private slots:
    void on_btn_loadShader_clicked();

    void on_btn_compileShader_clicked();

    void on_tabs_qsci_currentChanged(int index);

private:
    Ui::MainWindow *m_ui;
        /// @brief our openGL widget
        NGLScene *m_gl;
    parserLib *m_parForButton;
    //std::vector<Button> m_buttonList;

};

#endif // MAINWINDOW_H
