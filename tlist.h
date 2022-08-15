#ifndef LIST_H
#define LIST_H
#include "tarchive.h"
#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include <QLabel>
#include <QBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QObject>
#include <QTextStream>
#include <QFile>
#include <time.h>
#include <iomanip>

class tList : public QMainWindow {
    Q_OBJECT
public:
    tList();
    ~tList();


protected slots:
    void add();
    void complete();
    void remove();
    void showArchive();



private:
    QListView* tasksNC = nullptr;
    QAction* aAdd = nullptr;
    QAction* aArchive = nullptr;
    QAction* aRemove = nullptr;
    QAction* aShowArchive = nullptr;
};

#endif // LIST_H
