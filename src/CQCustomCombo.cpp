#include <CQCustomCombo.h>
#include <QListWidgetItem>
#include <QItemDelegate>
#include <QPainter>
#include <QApplication>

class CQCustomComboItem : public QListWidgetItem {
 public:
  CQCustomComboItem(CQCustomCombo *combo, const QString &str);

  virtual ~CQCustomComboItem() { }

  void setIsTitle(bool b) {
    isTitle_ = b;

    if (isTitle_)
      setSelectable(false);
  }

  bool isTitle() const { return isTitle_; }

  void setSelectable(bool selectable) {
    selectable_ = selectable;

    if (selectable_)
      setFlags(flags() |  (Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
    else
      setFlags(flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
  }

  bool isSelectable() const {
    return (flags() & (Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
  }

 private:
  CQCustomCombo *combo_;
  bool           isTitle_;
  bool           selectable_;
};

//------

class CQCustomComboDelegate : public QItemDelegate {
 public:
  CQCustomComboDelegate(CQCustomCombo *combo) :
   combo_(combo) {
  }

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const {
<<<<<<< HEAD
    CQCustomComboItem *item = static_cast<CQCustomComboItem *>(combo_->list()->item(index.row()));
=======
    int row = index.row();

    CQCustomComboItem *item = static_cast<CQCustomComboItem *>(combo_->list()->item(row));

    //painter->save();
>>>>>>> 14bd61b68d7f0e1815af59bdfd719ec9088c4c09

    QStyleOptionMenuItem opt = getStyleOption(option, index, item);

    painter->fillRect(opt.rect, opt.palette.background());

    combo_->style()->drawControl(QStyle::CE_MenuItem, &opt, painter, combo_);
<<<<<<< HEAD
  }

  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    CQCustomComboItem *item = static_cast<CQCustomComboItem *>(combo_->list()->item(index.row()));

    QStyleOptionMenuItem opt = getStyleOption(option, index, item);

    return combo_->style()->sizeFromContents(QStyle::CT_MenuItem, &opt, option.rect.size(), combo_);
=======

    //painter->restore();
  }

  QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &index) const {
    QFontMetrics fm(combo_->font());

    int row = index.row();

    QString text = combo_->itemText(row);

    return QSize(fm.width(text) + 4, fm.height() + 4);
>>>>>>> 14bd61b68d7f0e1815af59bdfd719ec9088c4c09
  }

  QStyleOptionMenuItem getStyleOption(const QStyleOptionViewItem &option,
                                      const QModelIndex &index, CQCustomComboItem *item) const {
    QStyleOptionMenuItem menuOption;

    QPalette resolvedpalette = option.palette.resolve(QApplication::palette("QMenu"));

    QBrush textBrush = resolvedpalette.brush(QPalette::Active, QPalette::Text);

    QVariant value = index.data(Qt::ForegroundRole);

    if (value.canConvert<QBrush>())
      textBrush = qvariant_cast<QBrush>(value);

    if (! item->isSelectable())
      textBrush = resolvedpalette.brush(QPalette::Disabled, QPalette::Text);

    if (item->isTitle())
      textBrush = resolvedpalette.brush(QPalette::Active, QPalette::HighlightedText);

    resolvedpalette.setBrush(QPalette::WindowText, textBrush);
    resolvedpalette.setBrush(QPalette::ButtonText, textBrush);
    resolvedpalette.setBrush(QPalette::Text      , textBrush);

    menuOption.palette = resolvedpalette;
    menuOption.state   = QStyle::State_None;

    if (combo_->window()->isActiveWindow())
      menuOption.state = QStyle::State_Active;

    if ((option.state & QStyle::State_Enabled) && (index.model()->flags(index) & Qt::ItemIsEnabled))
      menuOption.state |= QStyle::State_Enabled;
    else
      menuOption.palette.setCurrentColorGroup(QPalette::Disabled);

    if (option.state & QStyle::State_Selected)
      menuOption.state |= QStyle::State_Selected;

    menuOption.checkType = QStyleOptionMenuItem::NonExclusive;
    menuOption.checked   = (combo_->currentIndex() == index.row());

    if (isSeparator(index))
      menuOption.menuItemType = QStyleOptionMenuItem::Separator;
    else
      menuOption.menuItemType = QStyleOptionMenuItem::Normal;

    QVariant variant = index.model()->data(index, Qt::DecorationRole);

#if 0
    switch (variant.type()) {
      case QVariant::Icon:
        menuOption.icon = qvariant_cast<QIcon>(variant);
        break;
      case QVariant::Color: {
        static QPixmap pixmap(option.decorationSize);
        pixmap.fill(qvariant_cast<QColor>(variant));
        menuOption.icon = pixmap;
        break; }
      default:
        menuOption.icon = qvariant_cast<QPixmap>(variant);
        break;
    }
#endif

    QBrush bgBrush = menuOption.palette.brush(QPalette::Background);

    if (index.data(Qt::BackgroundRole).canConvert<QBrush>())
      bgBrush = qvariant_cast<QBrush>(index.data(Qt::BackgroundRole));

    if (item->isTitle())
      bgBrush = resolvedpalette.brush(QPalette::Active, QPalette::Highlight);

    menuOption.palette.setBrush(QPalette::All, QPalette::Background, bgBrush);

    menuOption.text = index.model()->data(index, Qt::DisplayRole).toString();
<<<<<<< HEAD
  //menuOption.text = menuOption.text.replace(QLatin1Char('&'), QLatin1String("&&"));
=======
    //menuOption.text = menuOption.text.replace(QLatin1Char('&'), QLatin1String("&&"));
>>>>>>> 14bd61b68d7f0e1815af59bdfd719ec9088c4c09

    menuOption.tabWidth     = 0;
    menuOption.maxIconWidth = option.decorationSize.width() + 4;
    menuOption.menuRect     = option.rect;
    menuOption.rect         = option.rect;
    menuOption.font         = combo_->font();
    menuOption.fontMetrics  = QFontMetrics(menuOption.font);

    if (item->isTitle())
      menuOption.font.setBold(true);

    return menuOption;
  }

  static bool isSeparator(const QModelIndex &index) {
    return (index.data(Qt::AccessibleDescriptionRole).toString() == "separator");
  }

 private:
  CQCustomCombo *combo_;
};

//------

class CQCustomComboTitle : public CQCustomComboItem {
 public:
  CQCustomComboTitle(CQCustomCombo *combo, const QString &str) :
   CQCustomComboItem(combo, str) {
    setSelectable(false);

    setIsTitle(true);
  }
};

//------

CQCustomComboItem::
CQCustomComboItem(CQCustomCombo *combo, const QString &str) :
 QListWidgetItem(str), combo_(combo), isTitle_(false), selectable_(true)
{
}

//------

CQCustomCombo::
CQCustomCombo(QWidget *parent) :
 QComboBox(parent), list_(0)
{
  list_ = new QListWidget;
  list_->setItemDelegate(new CQCustomComboDelegate(this));

  setModel(list_->model());
  setView(list_);
}

void
CQCustomCombo::
addTitle(const QString &text)
{
  list_->addItem(new CQCustomComboTitle(this, text));

  resetCurrentInd();
}

void
CQCustomCombo::
addItem(const QString &text)
{
  list_->addItem(new CQCustomComboItem(this, text));

  resetCurrentInd();
}

void
CQCustomCombo::
setIsTitle(int ind, bool b)
{
  CQCustomComboItem *item = dynamic_cast<CQCustomComboItem *>(list_->item(ind));

  item->setIsTitle(b);

  resetCurrentInd();
}

void
CQCustomCombo::
setSelectable(int ind, bool b)
{
  CQCustomComboItem *item = dynamic_cast<CQCustomComboItem *>(list_->item(ind));

  item->setSelectable(b);

  resetCurrentInd();
}

void
CQCustomCombo::
resetCurrentInd()
{
  CQCustomComboItem *item = static_cast<CQCustomComboItem *>(list()->item(currentIndex()));

  if (item->isSelectable())
    return;

  for (int i = 0; i < count(); ++i) {
    CQCustomComboItem *item = static_cast<CQCustomComboItem *>(list()->item(i));

    if (item->isSelectable()) {
      setCurrentIndex(i);
      break;
    }
  }
}
