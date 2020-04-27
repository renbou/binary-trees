#include "graphicsViewZoom.h"
#include <QMouseEvent>
#include <QApplication>
#include <QScrollBar>
#include <qmath.h>

graphicsViewZoom::graphicsViewZoom(QGraphicsScene *t_scene, QWidget *parent)
  : QGraphicsView(t_scene, parent)
{
  viewport()->installEventFilter(this);
  setMouseTracking(true);
  //_modifiers = Qt::ControlModifier;
  _modifiers = Qt::NoModifier;
  _zoom_factor_base = 1.0015;
}

void graphicsViewZoom::gentle_zoom(double factor) {
  scale(factor, factor);
  centerOn(target_scene_pos);
  QPointF delta_viewport_pos = target_viewport_pos - QPointF(viewport()->width() / 2.0,
															 viewport()->height() / 2.0);
  QPointF viewport_center = mapFromScene(target_scene_pos) - delta_viewport_pos;
  centerOn(mapToScene(viewport_center.toPoint()));
  emit zoomed();
}

void graphicsViewZoom::set_modifiers(Qt::KeyboardModifiers modifiers) {
  _modifiers = modifiers;

}

void graphicsViewZoom::set_zoom_factor_base(double value) {
  _zoom_factor_base = value;
}

bool graphicsViewZoom::eventFilter(QObject *object, QEvent *event) {
	if (event->type() == QEvent::MouseButtonPress) {
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
		if (mouse_event->button() == Qt::LeftButton) {
			leftPressed = true;
			origMousePos = mouse_event->pos();
			return true;
		}
		return QObject::event(event);
	} else if (event->type() == QEvent::MouseButtonRelease) {
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
		if (mouse_event->button() == Qt::LeftButton) {
			leftPressed = false;
			origMousePos = mouse_event->pos();
			return true;
		}
		return QObject::event(event);
	} else if (event->type() == QEvent::MouseMove) {
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
		if (leftPressed) {
			horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (mouse_event->x() - origMousePos.x()));
			verticalScrollBar()->setValue(verticalScrollBar()->value() - (mouse_event->y() - origMousePos.y()));
			origMousePos = mouse_event->pos();
			QPointF delta = target_viewport_pos - mouse_event->pos();
			if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
			  target_viewport_pos = mouse_event->pos();
			  target_scene_pos = mapToScene(mouse_event->pos());
			}
		} else {
			QPointF delta = target_viewport_pos - mouse_event->pos();
			if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
			  target_viewport_pos = mouse_event->pos();
			  target_scene_pos = mapToScene(mouse_event->pos());
			}
		}
	} else if (event->type() == QEvent::Wheel) {
		QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
		if (QApplication::keyboardModifiers() == _modifiers) {
			if (wheel_event->orientation() == Qt::Vertical) {
				double angle = wheel_event->angleDelta().y();
				double factor = qPow(_zoom_factor_base, angle);
				gentle_zoom(factor);
				return true;
			}
		}
  }
  Q_UNUSED(object)
  return QObject::event(event);
}
