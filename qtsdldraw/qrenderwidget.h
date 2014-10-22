#pragma once

#include <QWidget>

#ifdef Q_WS_WIN
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gfxBlitFunc.h>
#elif defined Q_WS_X11
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif
#undef main

namespace draw
{

class QRenderWidget : public QWidget
{
public:
	QRenderWidget(QWidget *parent = 0);
	~QRenderWidget();

	SDL_Surface *screen;
protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	void showEvent(QShowEvent *e);

	bool windowInitialized;
};

}
