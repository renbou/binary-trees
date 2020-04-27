#ifndef GRAPHICSVIEWZOOM_H
#define GRAPHICSVIEWZOOM_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>

class graphicsViewZoom : public QGraphicsView {
  Q_OBJECT
public:
	graphicsViewZoom(QGraphicsScene *t_scene, QWidget* parent = nullptr);
	void gentle_zoom(double factor);
	void set_modifiers(Qt::KeyboardModifiers modifiers);
	void set_zoom_factor_base(double value);
private:
  Qt::KeyboardModifiers _modifiers;
  double _zoom_factor_base;
  QPointF target_scene_pos, target_viewport_pos;
  QPoint origMousePos;
  bool leftPressed;
  bool eventFilter(QObject* object, QEvent* event);

signals:
  void zoomed();
};

#endif // GRAPHICSVIEWZOOM_H
