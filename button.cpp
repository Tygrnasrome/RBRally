#include "button.h"

Button::Button(const char *fn,std::function<void ()> klik)
{
//	button_click = Mix_LoadWAV("music/button_click.wav");
	obr.nacti (fn);
	this->klik = klik;
}
Button::Button(){}
void Button::draw(int x, int y)
{
	obr.umisti(x, y);
	if(ramecek)
	{
		barva(CERVENA);
		obdelnik(obr.x-5 ,obr.y-5 ,obr.x + 5+ obr.w, obr.y + 5 + obr.h);
	}
	obr.kresli();

}

void Button::execute_klik(int x, int y)
{
	if (x > obr.x && x < (obr.x+obr.w) && y > obr.y && y < (obr.y+obr.h))
	{
//		Mix_PlayChannel(-1,button_click,0);
		klik();
	}
}
