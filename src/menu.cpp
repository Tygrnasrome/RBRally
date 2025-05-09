#include "menu.h"

Menu::Menu()
{
	title = new Obrazek();
	background = new Obrazek();
	background->nacti("textures/banners/FIyOg.png");
	background->umisti(obrazovka->x,obrazovka->y);
	title->nacti("textures/banners/main.larger.jpg");
	title->umisti(obrazovka->w/2,50);
}

void Menu::add(Button *b)
{
    buttons.push_back(b);
}

void Menu::draw()
{
	for(int i = 0; i < 2 ; i++)
	{
		background->umisti(obrazovka->x+i*background->w,obrazovka->y);
		background->kresli();
	}

	title->kresli();
	int starth = obrazovka->h/2 - buttons.size()*40+15;   /*promenna starth = pozice zacatku
			    vykreslovani tlacitek*/
	int h = 0;
	for (int i = 0 ;i < buttons.size() ; i++)
	{

	    buttons[i]->draw(obrazovka->w/2-106, starth+h);  /*cislo pred + h urcuje
			startovni pozici kresleni tlacitek*/

	    h=h+80;				/*cislo za h+ urcuje mezeru mezi tlacitkama,
			    ale realna mezera je cislo za h+ - 50,
			    coz v tomto pripade je 80-50*/
	}

}
void Menu::update()
{
	title->umisti(obrazovka->w/2-title->w/2,obrazovka->y);
	background->umisti(obrazovka->x,obrazovka->y);
}
void Menu::event(SDL_Event* e)
{
	for (int i = 0 ;i < buttons.size() ; i++)
	{
	if(e->button.x > buttons[i]->obr.x && e->button.x < (buttons[i]->obr.x+buttons[i]->obr.w) && e->button.y > buttons[i]->obr.y && e->button.y < (buttons[i]->obr.y+buttons[i]->obr.h))
	{
//		if(!(buttons[i]->ramecek))
//			Mix_PlayChannel(-1,button_beep,0);
		buttons[i]->ramecek = true;
	}
	else {
		buttons[i]->ramecek = false;
	}
	}
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{

		for (int i = 0 ;i < buttons.size() ; i++)
		{
				buttons[i]->execute_klik(e->button.x, e->button.y);

		}
	}
}
void Menu::keystate(Uint8* kst)
{

}

