#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QMainWindow>

class WindowManager : public QMainWindow {
  Q_OBJECT
public:
  explicit WindowManager(QWidget *parent = nullptr);

signals:
};

#endif // WINDOWMANAGER_H
