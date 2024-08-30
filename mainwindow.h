#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPast_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionNew_triggered();

    void on_actionSave_As_triggered();

    void on_actionEdit_triggered();

    void on_actionSave_triggered();

    void on_actionAbout_triggered();

    void newTab();

    void on_actionNew_Tab_triggered();

    void closeTab(int index);

    void renameTab(int index);

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;
    QString file_path;
    QTabWidget *tabWidget;
    int tabCount;
};
#endif // MAINWINDOW_H
