#include "DropArea.h"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>

DropArea::DropArea(QDeclarativeItem *parent) :
  QDeclarativeItem(parent),
  m_accepting(true)
{
  setAcceptDrops(m_accepting);
}

void DropArea::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
  event->acceptProposedAction();
  setCursor(Qt::DragMoveCursor);
  emit dragEntered();
}

void DropArea::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
  unsetCursor();
  emit dragLeaved();
}

void DropArea::dropEvent(QGraphicsSceneDragDropEvent *event)
{
  QVariantList result;
  for (int i = 0; i < event->mimeData()->urls().count(); ++i) {
    result << event->mimeData()->urls().at(i);
  }

  emit dropped(QVariant(result));
  unsetCursor();
}

void DropArea::setAcceptingDrops(bool accepting)
{
  if (accepting == m_accepting) {
    return;
  }

  m_accepting = accepting;
  setAcceptDrops(m_accepting);
  emit acceptingDropsChanged();
}
