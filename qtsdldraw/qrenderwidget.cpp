#include "qrenderwidget.h"

#include "qtcore/qtcore.h"

#include "common/log.h"

#include <QResizeEvent>

namespace draw
{

QRenderWidget::QRenderWidget(QWidget *parent) :
	QWidget(parent),
	screen(NULL),
	windowInitialized(false)
{
	setMouseTracking(true);

	setAttribute(Qt::WA_WState_Created);
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NativeWindow);

	setUpdatesEnabled(false);
}

QRenderWidget::~QRenderWidget()
{
	SDL_Quit();
}

void QRenderWidget::paintEvent(QPaintEvent *event)
{

}

void QRenderWidget::resizeEvent(QResizeEvent *event)
{
	core::Core::getDrawManager()->initGraphics(width(), height());
	if (windowInitialized) {
		screen = SDL_SetVideoMode(width(), height(), 32, SDL_SWSURFACE);
		if (!screen) {
			//log() << "Couldn't set video mode: " << SDL_GetError() << std::endl;
		}
	}
}

void QRenderWidget::showEvent(QShowEvent *e)
{
	if (!windowInitialized) {
		// C'est ici qu'on dis à SDL d'utiliser notre widget
		char windowid[64];
		WId windowIdNumber = winId();
		snprintf(windowid, sizeof(windowid), "SDL_WINDOWID=0x%lx", windowIdNumber);

		log() << "SDL_WINDOWID=0x" << windowIdNumber << "\n";

		putenv(windowid);

		SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);

		// Initialisation du système vidéo de SDL
		if ((SDL_Init(SDL_INIT_VIDEO) == -1)) {
			//log() << "Could not initialize SDL: " << SDL_GetError() << std::endl;
		}

		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		screen = SDL_SetVideoMode(width(), height(), 32, SDL_SWSURFACE);
		if (!screen) {
			//log() << "Couldn't set video mode: " << SDL_GetError() << std::endl;
		}
		windowInitialized = true;
	}

}

}
