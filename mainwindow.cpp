#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTabWidget>
#include <QTabBar>
#include <QLineEdit>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(true);

    // Add the first tab
    QTextEdit *textEdit = new QTextEdit();
    ui->tabWidget->addTab(textEdit, "Tab 1");

    connect(ui->actionNew_Tab, &QAction::triggered, this, &MainWindow::newTab);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(ui->tabWidget->tabBar(), &QTabBar::tabBarDoubleClicked, this, &MainWindow::renameTab);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newTab()
{
    QTextEdit *newEditor = new QTextEdit();
    int tabIndex = ui->tabWidget->addTab(newEditor, QString("Tab %1").arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(tabIndex);
}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::renameTab(int index)
{
    bool ok;
    QString newTabName = QInputDialog::getText(this, "Rename Tab",
                                               "New tab name:", QLineEdit::Normal,
                                               ui->tabWidget->tabText(index), &ok);
    if (ok && !newTabName.isEmpty()) {
        ui->tabWidget->setTabText(index, newTabName);
    }
}

void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open this file");
    QFile file(file_name);
    file_path = file_name;
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "File not open");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPast_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save this file");
    QFile file(file_name);
    file_path = file_name;
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "File not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "File not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionAbout_triggered()
{
    QString about_text;
    about_text = "Author: Rohit Kasar \n";
    about_text += "Date Created: 30-08-2024 \n";
    QMessageBox::about(this, "About Texter", about_text);
}

void MainWindow::on_actionNew_Tab_triggered()
{
    newTab();
}
