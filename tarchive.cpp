#include "tarchive.h"

tArchive::tArchive()
{
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainWidget->setLayout(mainLayout);

    QLabel* mainTitle = new QLabel("not bad from where you started", this);
    mainLayout->addWidget(mainTitle);
    mainTitle->setAlignment(Qt::AlignCenter);
    mainTitle->setStyleSheet("font-size: 25pt;");

    tasksC = new QListView(this);
    mainLayout->addWidget(tasksC);

    QFile cFile("archive");
    cFile.open(QFile::ReadOnly);
    QStringList cSList;
    QTextStream cTextStream(&cFile);
    while (true) {
        QString nLine = cTextStream.readLine();
        if (nLine.isNull()) {
            break;
        }
        else {
            cSList.insert(0,nLine);
        }
    }
    cFile.close();

    QStringListModel* cModel = new QStringListModel(this);
    cModel->setStringList(cSList);
    tasksC->setModel(cModel);
    tasksC->setStyleSheet
            ("QListView { font-size: 20pt; font-weight: bold; }"
            "QListView::item { background-color: #FFFF00; }"
            "QListView::item::hover { background-color: #FFA500; }"
            );
}
