#include <CQCustomComboTest.h>
#include <CQCustomCombo.h>
#include <QApplication>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQCustomComboTest *test = new CQCustomComboTest;

  test->show();

  return app.exec();
}

CQCustomComboTest::
CQCustomComboTest()
{
  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->setMargin(2); layout->setSpacing(2);

  CQCustomCombo *combo = new CQCustomCombo;

  combo->addTitle("Scope");
  combo->addItem ("In entire design");
  combo->addItem ("In selection");
  combo->addItem ("Of selection");
  combo->addItem ("In search results");
  combo->addItem ("In chosen search results");

  combo->setSelectable(3, false);
  combo->setSelectable(5, false);

  layout->addWidget(combo);
}
