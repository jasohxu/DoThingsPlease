#include "tlist.h"

tList::tList() {
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainWidget->setLayout(mainLayout);

    QLabel* mainTitle = new QLabel("do this stuff you lazy bum", this);
    mainLayout->addWidget(mainTitle);
    mainTitle->setAlignment(Qt::AlignCenter);
    mainTitle->setStyleSheet("font-size: 25pt;");

    tasksNC = new QListView(this);
    mainLayout->addWidget(tasksNC);

    QFile ncFile("current");
    ncFile.open(QFile::ReadOnly);
    QStringList ncSList;
    QTextStream ncTextStream(&ncFile);
    while (true) {
        QString nLine = ncTextStream.readLine();
        if (nLine.isNull()) {
            break;
        }
        else {
            ncSList.append(nLine);
        }
    }
    ncFile.close();

    QStringListModel* ncModel = new QStringListModel(this);
    ncModel->setStringList(ncSList);
    tasksNC->setModel(ncModel);
    tasksNC->setStyleSheet
            ("QListView { font-size: 20pt; font-weight: bold; }"
            "QListView::item { background-color: #FFFF00; }"
            "QListView::item::hover { background-color: #FFA500; }"
            );

    QToolBar* mainToolBar = new QToolBar(this);
    addToolBar(mainToolBar);

    aAdd = new QAction(this);
    connect(aAdd, SIGNAL(triggered()), this, SLOT(add()));
    aAdd->setIcon(QIcon(":/icons/plus.png"));
    mainToolBar->addAction(aAdd);

    aArchive = new QAction(this);
    connect(aArchive, SIGNAL(triggered()), this, SLOT(complete()));
    aArchive->setIcon(QIcon(":/icons/check.png"));
    mainToolBar->addAction(aArchive);

    aRemove = new QAction(this);
    connect(aRemove, SIGNAL(triggered()), this, SLOT(remove()));
    aRemove->setIcon(QIcon(":/icons/trash.png"));
    mainToolBar->addAction(aRemove);

    aShowArchive = new QAction(this);
    connect(aShowArchive, SIGNAL(triggered()), this, SLOT(showArchive()));
    aShowArchive->setIcon(QIcon(":/icons/list-check.png"));
    mainToolBar->addAction(aShowArchive);

}

tList::~tList() {
    QFile ncFile("current");
    ncFile.open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text);
    QTextStream ncOut(&ncFile);

    tasksNC->setSelectionMode(QAbstractItemView::MultiSelection);
    tasksNC->selectAll();
    foreach (const QModelIndex &index, tasksNC->selectionModel()->selectedIndexes())
        ncOut << (index.data(Qt::DisplayRole).toString()) << endl;
    ncFile.close();
}


void tList::add() {
    tasksNC->model()->insertRow(tasksNC->model()->rowCount());
    QModelIndex nIndex = tasksNC->model()->index(tasksNC->model()->rowCount()-1, 0);
    tasksNC->edit(nIndex);
}

void tList::complete() {
    QFile cFile("archive");
    cFile.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream cOut(&cFile);
    foreach (const QModelIndex &index, tasksNC->selectionModel()->selectedIndexes()) {
        time_t rTime = time(0);
        struct tm* sTime = localtime(&rTime);

        QString timeString = asctime(sTime);
        while (true) {
            if (timeString.endsWith("\n") or timeString.endsWith("\r")) {
                timeString.chop(1);
            }
            else {
                break;
            }
        }


        cOut << timeString << " | " << (index.data(Qt::DisplayRole).toString()) << endl;
        tasksNC->model()->removeRow(index.row());
    }
    cFile.close();
}

void tList::remove() {
    QModelIndex nIndex = tasksNC->currentIndex();
    tasksNC->model()->removeRow(nIndex.row());
}

void tList::showArchive() {
    QMainWindow* tA = new tArchive();
    tA->show();
}
