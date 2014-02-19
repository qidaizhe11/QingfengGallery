#ifndef DROPAREA_H
#define DROPAREA_H

#include <QtDeclarative/QDeclarativeItem>

class DropArea : public QDeclarativeItem
{
  Q_OBJECT

  Q_PROPERTY(bool acceptingDrops READ isAcceptingDrops WRITE setAcceptingDrops
             NOTIFY acceptingDropsChanged)

public:
  explicit DropArea(QDeclarativeItem *parent = 0);
  bool isAcceptingDrops() const { return m_accepting; }
  void setAcceptingDrops(bool accepting);

signals:
  void dropped(QVariant dr);
  void acceptingDropsChanged();
  void dragEntered();
  void dragLeaved();

protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
  void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);
  void dropEvent(QGraphicsSceneDragDropEvent* event);

private:
  bool m_accepting;
};

#endif // DROPAREA_H
