#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
public slots:
  void pushButtonClicked();

private:
  QWidget *widget;
  QVBoxLayout *v_box_layout;
  QHBoxLayout *h_box_layout;
  QVBoxLayout *v_box_layout_operator;
  QGridLayout *grid_layout;
  QLineEdit *line_edit_input;
  QLineEdit *line_edit_output;
  QPushButton *push_button_number;
  QPushButton *push_button_operator;
};

#endif // MAINWINDOW_H
