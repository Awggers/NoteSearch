#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Indexer.h"
#include "SearchEngine.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onBrowseClicked();
    void onSearchClicked();

private:
    Ui::MainWindow *ui;
    Indexer indexer;
    QString currentDirectory;
};

#endif // MAINWINDOW_H