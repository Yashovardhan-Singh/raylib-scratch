#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define WIN_W 1280
#define WIN_H 720
#define Y_INC 32
#define E_W 64
#define E_H 64

typedef struct Enemy {
    bool     right;
    Vector2  position;
    float    speed;
    Vector2  uv;
    uint32_t local_timer;
} Enemy;

void moveEnemy(Enemy *e) {
    e->position.x += e->right ? e->speed : -e->speed;
    if (e->position.x < 0.0f || e->position.x > WIN_W - E_W) {
        e->right = !e->right;
        e->position.y += Y_INC;
    }
}

void animateEnemy(Enemy *e) {
    if (e->local_timer % 15 == 0)
        e->uv.x += (e->uv.x == 0) ? E_W : -E_W;
    e->local_timer++;
}

void drawEnemy(Enemy *e, Texture2D *texture) {
    DrawTextureRec(
        *texture,
        (Rectangle) {.x = e->uv.x, .y = e->uv.y, .height = E_W, .width = E_H},
        e->position, WHITE);
}

typedef struct Player {
    float x;
    bool fired;
    Vector2 bullet_pos;
} Player;

void movePlayer(Player* p) {
    if (IsKeyDown(KEY_A)) p->x -= 3.0f;
    if (IsKeyDown(KEY_D)) p->x += 3.0f;
}

void drawPlayer(Player* p) {
    DrawRectangleRec((Rectangle) {p->x, 620.0f, 64, 64}, WHITE);
}

void fireBullet(Player* p) {
    if (IsKeyPressed(KEY_SPACE) && !p->fired) {
        p->bullet_pos = (Vector2) {
            .x = p->x + 32.0f,
            .y = 620.0f
        };
    }
}

int main() {

    InitWindow(WIN_W, WIN_H, "SPACE INVADERS");
    SetTargetFPS(60);

    Enemy e = {
        .position = (Vector2) {.x = 64.0f, .y = 64.0f },
        .local_timer = 0,
        .right = true,
        .uv = (Vector2) {.x = 0.0f, .y = 0.0f},
        .speed = (float) GetRandomValue(1, 3)
    };

    Player p = {
        .fired = false,
        .x = 100.0f,
    };

    Texture2D e_texture = LoadTexture("assets/alien.png");

    while(!WindowShouldClose()) {

        movePlayer(&p);

        moveEnemy(&e);
        animateEnemy(&e);

        BeginDrawing();
        ClearBackground(BLACK);
        drawEnemy(&e, &e_texture);
        drawPlayer(&p);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
