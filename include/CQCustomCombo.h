#ifndef CQCustomCombo_H
#define CQCustomCombo_H

#include <QComboBox>

class QListWidget;

class CQCustomCombo : public QComboBox {
  Q_OBJECT

 public:
  CQCustomCombo(QWidget *parent=0);

  QListWidget *list() { return list_; }

  void addTitle(const QString &text);
  void addItem (const QString &text);

  void setIsTitle(int ind, bool b);
  void setSelectable(int ind, bool b);

 private:
  void resetCurrentInd();

 private:
  QListWidget *list_;
};

#endif
