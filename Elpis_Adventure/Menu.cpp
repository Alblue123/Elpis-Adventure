#include "Menu.hpp"

Menu::Menu()
{
    width_frame = height_frame = 0;


}

Menu::~Menu()
{
   
}

bool Menu::loadMenu(std::string path, SDL_Renderer* renderer) {
    return GameObject::loadIMG(path, renderer);
}

int Menu::ShowMenu(SDL_Renderer* renderer, TTF_Font* font) {
    bool img_menu = loadMenu("graphics//Background1.png", renderer);
    if (img_menu == false) {
        return 1;
    }

    const int kMenuItemNum = 2;
    SDL_Rect pos_arr[kMenuItemNum];


    pos_arr[0].x = 150;
    pos_arr[0].y = 200;

    pos_arr[1].x = 150;
    pos_arr[1].y = 250;

    

    TextObject text_menu[kMenuItemNum];


    text_menu[0].setText("Play Game");
    text_menu[0].setcolor(TextObject::BLACK_TEXT);

    text_menu[1].setText("Exit");
    text_menu[1].setcolor(TextObject::BLACK_TEXT);


    for (int i = 0; i < kMenuItemNum; ++i)
    {
        text_menu[i].loadFromRenderedText(font, renderer);
    }

    pos_arr[0].w = text_menu[0].getWidth();
    pos_arr[0].h = text_menu[0].getHeight();

    pos_arr[1].w = text_menu[1].getWidth();
    pos_arr[1].h = text_menu[1].getHeight();


    bool selected[kMenuItemNum] = { 0, 0 };
    int xm = 0;
    int ym = 0;

    // Event handler
    SDL_Event m_event;

    while (true) {
        SDL_RenderClear(renderer);
        
        SDL_RenderCopy(renderer, this->mTexture, NULL, NULL);
        
        for (int i = 0; i < kMenuItemNum; ++i) 
        {
            text_menu[i].loadFromRenderedText(font, renderer);
            text_menu[i].RenderText(renderer, pos_arr[i].x, pos_arr[i].y);
        }

        // Handle events on queue
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&m_event)) {
            // User requests quit
            switch (m_event.type) {
            case SDL_QUIT:
            {
                return 1;
            }
            break;

            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for (int i = 0; i < kMenuItemNum; i++) {
                    if (CheckFousWithRect(xm, ym, pos_arr[i])) {
                        if (selected[i] == false) {
                            selected[i] = 1;
                            text_menu[i].setcolor(TextObject::RED_TEXT);
                        }
                    }
                    else {
                        if (selected[i] == true) {
                            selected[i] = 0;
                            text_menu[i].setcolor(TextObject::BLACK_TEXT);
                        }
                    }
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                for (int i = 0; i < kMenuItemNum; i++) {
                    if (CheckFousWithRect(xm, ym, pos_arr[i])) {
                        return i;
                    }
                }
            }
            break;
            }
           
        }
    }
    return 0;
}

int Menu::ShowResetMenu(SDL_Renderer* renderer, TTF_Font* font)
{
    bool img_menu = loadMenu("graphics//reset.png", renderer);
    if (img_menu == false) {
        return 1;
    }

    const int kMenuItemNum = 2;
    SDL_Rect pos_arr[kMenuItemNum];


    pos_arr[0].x = 150;
    pos_arr[0].y = 200;

    pos_arr[1].x = 150;
    pos_arr[1].y = 250;

    TextObject text_menu[kMenuItemNum];


    text_menu[0].setText("Replay");
    text_menu[0].setcolor(TextObject::BLACK_TEXT);

    text_menu[1].setText("Exit");
    text_menu[1].setcolor(TextObject::BLACK_TEXT);


    for (int i = 0; i < kMenuItemNum; ++i)
    {
        text_menu[i].loadFromRenderedText(font, renderer);
    }

    pos_arr[0].w = text_menu[0].getWidth();
    pos_arr[0].h = text_menu[0].getHeight();

    pos_arr[1].w = text_menu[1].getWidth();
    pos_arr[1].h = text_menu[1].getHeight();

    bool selected[kMenuItemNum] = { 0, 0 };
    int xm = 0;
    int ym = 0;

    // Event handler
    SDL_Event m_event;

    while (true) {
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, this->mTexture, NULL, NULL);

        for (int i = 0; i < kMenuItemNum; ++i)
        {
            text_menu[i].loadFromRenderedText(font, renderer);
            text_menu[i].RenderText(renderer, pos_arr[i].x, pos_arr[i].y);
        }

        // Handle events on queue
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&m_event)) {
            // User requests quit
            switch (m_event.type) {
            case SDL_QUIT:
            {
                return 1;
            }
            break;

            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for (int i = 0; i < kMenuItemNum; i++) {
                    if (CheckFousWithRect(xm, ym, pos_arr[i])) {
                        if (selected[i] == false) {
                            selected[i] = 1;
                            text_menu[i].setcolor(TextObject::RED_TEXT);
                        }
                    }
                    else {
                        if (selected[i] == true) {
                            selected[i] = 0;
                            text_menu[i].setcolor(TextObject::BLACK_TEXT);
                        }
                    }
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                for (int i = 0; i < kMenuItemNum-1; i++) {
                    if (CheckFousWithRect(xm, ym, pos_arr[i])) {
                        return i;
                    }
                }
            }
            break;
            }

        }
    }
    return 0;
}

bool Menu::CheckFousWithRect(const int& x, const int& y, const SDL_Rect& rect) {
    if (x > rect.x && x <= rect.x + rect.w && y > rect.y && y <= rect.y + rect.h) {
        return true;
    }
    else return false;
}


