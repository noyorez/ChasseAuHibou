#ifndef GUI_HPP
#define GUI_HPP

#include "sprite.hpp"
#include <SDL2/SDL_ttf.h>

namespace Colors
{
    inline constexpr SDL_Color white = {255,255,255};
    inline constexpr SDL_Color black = {0,0,0};
    inline constexpr SDL_Color moon_gray = {79,94,140};
    inline constexpr SDL_Color text_gray = {28,37,61,200};
}

class GUI
{
    public :
    GUI(SDL_Renderer *renderer) : renderer(renderer), 
                                  lives_sprite(renderer, "heart.bmp", HEART_WIDTH/SCALE),  
                                  play_button(renderer, "play.bmp", BACKGROUND_WIDTH/SCALE),
                                  credits_button(renderer, "credits_button.bmp", BACKGROUND_WIDTH/SCALE),
                                  exit_button(renderer, "exit.bmp", BACKGROUND_WIDTH/SCALE),
                                  qwerty_button(renderer, "qwerty.bmp", BACKGROUND_WIDTH/SCALE),
                                  azerty_button(renderer, "azerty.bmp", BACKGROUND_WIDTH/SCALE),
                                  credits_sprite(renderer, "credits.bmp", CREDITS_WIDTH){}

    void draw_gui(int lives, int fps)
    {
        draw_lives(lives);
        apply_fps(fps);
    }

    void draw_score(int score, int highscore)
    {
        apply_score(score);
        apply_highscore(highscore);
    }

    void draw_buttons()
    {
        draw_play();
        draw_credits();
        draw_exit();
        draw_qwerty();
        draw_azerty();
    }

    void draw_lives(int lives) 
    {
        SDL_Rect src = lives_sprite.rect(0);
        for (int i = 0; i < lives; i++)
        {
            SDL_Rect dest = {int(livesX), int(livesY) + (HEART_HEIGHT + HEART_DISTANCE)*i, HEART_WIDTH, HEART_HEIGHT};
            SDL_RenderCopy(renderer, lives_sprite.texture, &src, &dest);
        }
    }

    void draw_play() {
        SDL_Rect src = play_button.rect(0);
        SDL_Rect dst = {0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
        SDL_RenderCopy(renderer, play_button.texture, &src, &dst);
    }


    void draw_credits() {
        SDL_Rect src = credits_button.rect(0);
        SDL_Rect dst = {0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
        SDL_RenderCopy(renderer, credits_button.texture, &src, &dst);
    }

    void draw_exit() {
        SDL_Rect src = exit_button.rect(0);
        SDL_Rect dst = {0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
        SDL_RenderCopy(renderer, exit_button.texture, &src, &dst);
    }

    void draw_qwerty() {
        SDL_Rect dst = {0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
        SDL_RenderCopy(renderer, qwerty_button.texture, NULL, &dst);
    }

    void draw_azerty() {
        SDL_Rect dst = {0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
        SDL_RenderCopy(renderer, azerty_button.texture, NULL, &dst);
    }

    void apply_fps(int fps)
    {
        SDL_Rect rec = {SCREEN_WIDTH - 30 - 5, SCREEN_HEIGHT - 40, 30, 40};
        apply_text(renderer, font, &rec, to_string(fps), Colors::moon_gray);
    }

    void apply_score(int score)
    {
        SDL_Rect rec = {moonX + MOON_SIZE/2 - countDigit(score)*27, moonY + 100, countDigit(score)*50, 100};
        apply_text(renderer, font, &rec, to_string(score), Colors::moon_gray);
    }

    void apply_highscore(int highscore)
    {
        SDL_Rect rec = {moonX + MOON_SIZE/2 - countDigit(highscore)*25/2, moonY + 210, countDigit(highscore)*25, 50};
        apply_text(renderer, font, &rec,  to_string(highscore), Colors::moon_gray);
    }

    void apply_lose_message(SDL_Renderer* renderer) {
        SDL_Rect textRect = {SCREEN_WIDTH / 2 - 500, 150, 1000, 200};
        apply_text(renderer, font, &textRect, "Game Over", Colors::white);
    }

    void apply_scores(SDL_Renderer* renderer, int highscores[], int score) {
        SDL_Rect textRect = {SCREEN_WIDTH / 2 - 350, 350, 700, 100};
        apply_text(renderer, font, &textRect, "Highest scores", Colors::white);
        
        for(int i = 0; i < HIGHSCORE_MAX; i++) {
            SDL_Rect rec = {SCREEN_WIDTH / 2 - 75, 450 + i*50, countDigit(highscores[i])*25, 50};
            apply_text(renderer, font, &rec, to_string(highscores[i]), Colors::white);
        }

        SDL_Rect textRect2 = {SCREEN_WIDTH / 2 - 350, 700, 600, 100};
        apply_text(renderer, font, &textRect2, "Your score ", Colors::white);

        SDL_Rect rec2 = {SCREEN_WIDTH / 2 + 250 + countDigit(score)*25/2, 720, countDigit(score)*40, 75};
        apply_text(renderer, font, &rec2, to_string(score), Colors::white);
    }

    void play_credits(Map* map, SDL_Event* event)
    {
        for (int i = 0; i < CREDITS_HEIGHT - SCREEN_HEIGHT; i++)
        {
            SDL_RenderClear(renderer);
            map->draw_background();
            SDL_Rect src = {0, i, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_Rect dst = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_RenderCopy(renderer, credits_sprite.texture, &src, &dst);
            SDL_RenderPresent(renderer);
            SDL_Delay(18);


            while (SDL_PollEvent(event))
            {
            if (event->type == SDL_KEYDOWN)
                {
                    if (event->key.keysym.sym == SDLK_ESCAPE)    // ESC to exit
                    {
                        return;
                    }
                        
                }
            }
        }
    }


    private:    
    int livesX = 5, livesY = 5;
    int moonX = 980, moonY = 80;
    int buttonsX = 0;
    int buttonsY = 0;

    TTF_Font *font = TTF_OpenFont("resources/font2.ttf", 48);

    SDL_Renderer *renderer; // draw here

    const Sprite lives_sprite;
    const Sprite play_button;
    const Sprite credits_button;
    const Sprite exit_button;
    const Sprite qwerty_button;
    const Sprite azerty_button;
    const Sprite credits_sprite;
};

#endif // GUI_HPP
