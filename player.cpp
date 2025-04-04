#include "common.hpp"

bool movingLeft = true;
void updatePlayerMovement(Player& player) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    int dx = 0, dy = 0;
    if (keystate[SDL_SCANCODE_A]) { dx = -1; movingLeft = true; }
    if (keystate[SDL_SCANCODE_D]) { dx = 1; movingLeft = false; } //used for render character moving left/right
    if (keystate[SDL_SCANCODE_W]) dy = -1;
    if (keystate[SDL_SCANCODE_S]) dy = 1;

    float length = sqrt(dx * dx + dy * dy);
    if (length != 0) {
        float normalizedX = dx / length;
        float normalizedY = dy / length;
        int newX = round(player.x + normalizedX * player.speed);
        int newY = round(player.y + normalizedY * player.speed); //consistent move speed

        //limit 50 50 -> 1500 800
        if (newX >= 50 && newX <= 1500) {
            player.x = newX;
        }
        if (newY >= 50 && newY <= 800) {
            player.y = newY;
        }
    }
}


void renderPlayer(SDL_Renderer* renderer, Player& player) {
    SDL_Rect play = {player.x, player.y, player.width, player.height};
    if (!movingLeft){
        SDL_RenderCopy(renderer, player1, NULL, &play); //move left
    }
    else{
        SDL_RenderCopy(renderer, player2, NULL, &play); //move right
    }

}
void renderRemainHealth(SDL_Renderer* renderer, Player& player) {
    SDL_SetRenderDrawColor(renderer, 149, 240, 226, 255);
    SDL_Rect remainhealthBar = { 0, 15, 493 * player.health / player.maxhealth, 75 };
    SDL_RenderFillRect(renderer, &remainhealthBar);
}
void renderHealth(SDL_Renderer* renderer, Player& player) {
    SDL_SetRenderDrawColor(renderer, 87, 222, 203, 255);
    SDL_Rect healthBar = { 0, 15, 493, 75 };
    SDL_RenderFillRect(renderer, &healthBar);
}
void renderIngame(SDL_Renderer *renderer){
    SDL_Rect igame = {0, 0, 1600, 900};
    SDL_RenderCopy(renderer, ingame, NULL, &igame);
}