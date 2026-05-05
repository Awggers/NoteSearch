#include "mainwindow.h"
#include "src/ui_mainwindow.h"
#include "ui_mainwindow.h"
#include "SearchEngine.h"

#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons to slots
    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);

    // Allows for pressing enter to trigger search
    connect(ui->searchInput, &QLineEdit::returnPressed, this, &MainWindow::onSearchClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBrowseClicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory to Index");

    if (dir.isEmpty()){
        return;
    }

    currentDirectory = dir;
    ui->directoryInput->setText(dir);

    // Build the index from selected directory
    indexer.buildIndex(dir.toStdString());

    const auto& index = indexer.getIndex();
    ui->resultsList->clear();
    ui->resultsList->addItem(QString("Index built. Unique terms: %1").arg(index.size()));
}

void MainWindow::onSearchClicked()
{
    if (currentDirectory.isEmpty()){
        ui->resultsList->clear();
        ui->resultsList->addItem("Please select a directory first.");
        return;
    }

    QString query = ui->searchInput->text().trimmed();

    if (query.isEmpty()){
        return;
    }

    const auto& index = indexer.getIndex();
    SearchEngine engine(index);

    auto results = engine.search(query.toStdString());

    ui->resultsList->clear();

    if (results.empty()){
        ui->resultsList->addItem("No results found.");
        return;
    }

    for (const auto& result : results){
        const std::string& path = result.first;
        int score = result.second;

        // Add result row
        QString resultLine = QString("%1  (score: %2)").arg(QString::fromStdString(path)).arg(score);
        ui->resultsList->addItem(resultLine);

        // Add snippet row
        std::string snippet = engine.getSnippet(path, query.toStdString());
        if (!snippet.empty()){
            QListWidgetItem* snippetItem = new QListWidgetItem("  " + QString::fromStdString(snippet));
            snippetItem->setForeground(Qt::gray);
            ui->resultsList->addItem(snippetItem);
        }
    }
}