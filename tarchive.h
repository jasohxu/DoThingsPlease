#ifndef TARCHIVE_H
#define TARCHIVE_H
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

class tArchive : public QMainWindow {
    Q_OBJECT
public:
    tArchive();

private:
    QListView* tasksC = nullptr;
};

#endif // TARCHIVE_H
