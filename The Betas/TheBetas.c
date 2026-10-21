#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define LARGURA_PERSONAGEM 37
#define ALTURA_PERSONAGEM 55
#define TAMANHO_TILE 60
#define LINHAS 25
#define COLUNAS 35
#define CHAO 0
#define PAREDE 1
#define PORTA 2
#define BAIXO 0
#define CIMA 1
#define ESQUERDA 2
#define DIREITA 3
#define QTD_PERGUNTAS 7

typedef struct
{
    char texto[100];
    int resposta;
} Pergunta;

Pergunta perguntas[QTD_PERGUNTAS] = {
    { "2x + 7 = 3x - 5", 12 },
    { "3(x - 2) + 5 = 2x + 7", 8 },
    { "5(x + 2) - 3x = 4x - 10", 10 },
    { "x/2 + x/3 = 15", 18 },
    { "4(2x - 3) = 3(x + 6) - 5", 5 },
    { "7x - 4 = 2x - 24", -4 },
    { "(2x - 1)/3 = (x + 4)/2", 14 }
};

int mapa[LINHAS][COLUNAS] = {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1 },
    { 1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1 },
    { 1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,2,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1 },
    { 1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1 },
    { 1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,2,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1 },
    { 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1 },
    { 1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1 },
    { 1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1 },
    { 1,2,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1 },
    { 1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,2,1 },
    { 1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1 },
    { 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
    { 1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1 },
    { 1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,2,1,0,1,1,1,1,1,0,1,0,1 },
    { 1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1 },
    { 1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
    { 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1 },
    { 1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};


void desenhar_mapa(float camera_x, float camera_y, ALLEGRO_BITMAP* img_parede, ALLEGRO_BITMAP* img_porta)
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            float x = j * TAMANHO_TILE - camera_x;
            float y = i * TAMANHO_TILE - camera_y;

            if (mapa[i][j] == PAREDE)
            {
                al_draw_scaled_bitmap(img_parede, 0, 0,
                    al_get_bitmap_width(img_parede), al_get_bitmap_height(img_parede),
                    x, y, TAMANHO_TILE, TAMANHO_TILE, 0);
            }
            else if (mapa[i][j] == PORTA)
            {
                al_draw_scaled_bitmap(img_porta, 0, 0,
                    al_get_bitmap_width(img_porta), al_get_bitmap_height(img_porta),
                    x, y, TAMANHO_TILE, TAMANHO_TILE, 0);
            }
            else
            {
                al_draw_filled_rectangle(x, y, x + TAMANHO_TILE, y + TAMANHO_TILE, al_map_rgb(180, 180, 180));
            }
        }
    }
}

bool pode_andar(float x, float y)
{
    int esq = (int)x / TAMANHO_TILE;
    int dir = (int)(x + LARGURA_PERSONAGEM - 1) / TAMANHO_TILE;
    int cima = (int)y / TAMANHO_TILE;
    int baixo = (int)(y + ALTURA_PERSONAGEM - 1) / TAMANHO_TILE;
    if (esq < 0 || dir >= COLUNAS || cima < 0 || baixo >= LINHAS)
    {
        return false;
    }
    if (mapa[cima][esq] != CHAO || mapa[cima][dir] != CHAO ||
        mapa[baixo][esq] != CHAO || mapa[baixo][dir] != CHAO)
    {
        return false;
    }

    return true;
}
void abrir_porta(int linha, int coluna)
{
    if (mapa[linha][coluna] == PORTA)
    {
        mapa[linha][coluna] = CHAO;
    }
}
bool clicou(float mx, float my, float x1, float y1, float x2, float y2)
{
    if (mx >= x1 && mx <= x2 && my >= y1 && my <= y2)
    {
        return true;
    }
    return false;
}

void desenhar_botao(ALLEGRO_FONT* fonte, float x1, float y1, float x2, float y2, const char* texto)
{
    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(70, 70, 90));
    al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(220, 220, 220), 2);
    al_draw_text(fonte, al_map_rgb(255, 255, 255), (x1 + x2) / 2, (y1 + y2) / 2 - 4, ALLEGRO_ALIGN_CENTER, texto);
}

int main()
{
    srand(time(NULL));

    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    al_set_window_position(display, 200, 100);
    al_set_window_title(display, "The Betas");

    ALLEGRO_FONT* fonte = al_create_builtin_font();
    ALLEGRO_BITMAP* sprites = al_load_bitmap("personagem_spritesheet.png");
    ALLEGRO_BITMAP* img_parede = al_load_bitmap("tileparede_mapa1.png");
    ALLEGRO_BITMAP* img_porta = al_load_bitmap("porta_mapa.png");

    if (sprites == NULL || img_parede == NULL || img_porta == NULL)
    {
        printf("Erro ao carregar uma das imagens.\n");
        return 1;
    }

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* fila = al_create_event_queue();
    al_register_event_source(fila, al_get_display_event_source(display));
    al_register_event_source(fila, al_get_timer_event_source(timer));
    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_mouse_event_source());
    al_start_timer(timer);

    float x = 80;
    float y = 60;
    float velocidade = 3;
    int direcao = BAIXO;
    bool andando = false;
    bool rodando = true;
    bool desenhar = true;
    bool perguntando = false;

    char resposta[20] = "";
    int tamanho = 0;
    int pergunta_atual = 0;
    char mensagem[50] = "";
    int porta_linha = -1;
    int porta_coluna = -1;
    float camera_x = 0;
    float camera_y = 0;

    while (rodando)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN && perguntando)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                perguntando = false;
                resposta[0] = '\0';
                tamanho = 0;
            }
        }

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && perguntando && ev.mouse.button == 1)
        {
            float mx = ev.mouse.x;
            float my = ev.mouse.y;
            for (int k = 0; k < 12; k++)
            {
                float bx = 380 + (k % 3) * 80;
                float by = 290 + (k / 3) * 55;

                if (clicou(mx, my, bx, by, bx + 70, by + 45))
                {
                    mensagem[0] = '\0';

                    if (k == 11)
                    {
                        if (tamanho > 0)
                        {
                            tamanho--;
                            resposta[tamanho] = '\0';
                        }
                    }
                    else if (k == 9)
                    {
                        if (tamanho == 0)
                        {
                            resposta[0] = '-';
                            resposta[1] = '\0';
                            tamanho = 1;
                        }
                    }
                    else
                    {
                        if (tamanho < 6)
                        {
                            if (k < 9)
                            {
                                resposta[tamanho] = '1' + k;
                            }
                            else
                            {
                                resposta[tamanho] = '0';
                            }
                            tamanho++;
                            resposta[tamanho] = '\0';
                        }
                    }
                }
            }

            if (clicou(mx, my, 640, 290, 900, 350))
            {
                if (tamanho > 0 && !(tamanho == 1 && resposta[0] == '-'))
                {
                    if (atoi(resposta) == perguntas[pergunta_atual].resposta)
                    {
                        abrir_porta(porta_linha, porta_coluna);
                        perguntando = false;
                    }
                    else
                    {
                        sprintf_s(mensagem, sizeof(mensagem), "Resposta errada");
                    }

                    resposta[0] = '\0';
                    tamanho = 0;
                }
            }
            if (clicou(mx, my, 640, 370, 900, 430))
            {
                perguntando = false;
                resposta[0] = '\0';
                tamanho = 0;
            }
        }
        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            ALLEGRO_KEYBOARD_STATE teclado;
            al_get_keyboard_state(&teclado);
            andando = false;
            float novo_x = x;
            float novo_y = y;
            if (!perguntando)
            {
                if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT))
                {
                    novo_x += velocidade;
                    direcao = DIREITA;
                    andando = true;
                }
                if (al_key_down(&teclado, ALLEGRO_KEY_LEFT))
                {
                    novo_x -= velocidade;
                    direcao = ESQUERDA;
                    andando = true;
                }
                if (pode_andar(novo_x, y))
                {
                    x = novo_x;
                }
                if (al_key_down(&teclado, ALLEGRO_KEY_UP))
                {
                    novo_y -= velocidade;
                    direcao = CIMA;
                    andando = true;
                }
                if (al_key_down(&teclado, ALLEGRO_KEY_DOWN))
                {
                    novo_y += velocidade;
                    direcao = BAIXO;
                    andando = true;
                }
                if (pode_andar(x, novo_y))
                {
                    y = novo_y;
                }
                if (al_key_down(&teclado, ALLEGRO_KEY_E))
                {
                    int coluna = (int)(x + LARGURA_PERSONAGEM / 2) / TAMANHO_TILE;
                    int linha = (int)(y + ALTURA_PERSONAGEM / 2) / TAMANHO_TILE;

                    for (int i = linha - 1; i <= linha + 1; i++)
                    {
                        for (int j = coluna - 1; j <= coluna + 1; j++)
                        {
                            if (i >= 0 && i < LINHAS && j >= 0 && j < COLUNAS)
                            {
                                if (mapa[i][j] == PORTA)
                                {
                                    porta_linha = i;
                                    porta_coluna = j;
                                    perguntando = true;
                                    pergunta_atual = rand() % QTD_PERGUNTAS;
                                    resposta[0] = '\0';
                                    tamanho = 0;
                                    mensagem[0] = '\0';
                                }
                            }
                        }
                    }
                }
            }
            camera_x = x + LARGURA_PERSONAGEM / 2 - 1280 / 2;
            camera_y = y + ALTURA_PERSONAGEM / 2 - 720 / 2;
            if (camera_x < 0)
            {
                camera_x = 0;
            }
            if (camera_y < 0)
            {
                camera_y = 0;
            }
            if (camera_x > COLUNAS * TAMANHO_TILE - 1280)
            {
                camera_x = COLUNAS * TAMANHO_TILE - 1280;
            }
            if (camera_y > LINHAS * TAMANHO_TILE - 720)
            {
                camera_y = LINHAS * TAMANHO_TILE - 720;
            }

            desenhar = true;
        }

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            rodando = false;
        }
        if (desenhar && al_is_event_queue_empty(fila))
        {
            desenhar = false;

            al_clear_to_color(al_map_rgb(20, 20, 20));
            desenhar_mapa(camera_x, camera_y, img_parede, img_porta);
            int linha_sprite = 0;
            if (andando)
            {
                linha_sprite = 1;
            }
            al_draw_scaled_bitmap(sprites, direcao * 52, linha_sprite * 96, 52, 96,
                x - camera_x, y - camera_y, LARGURA_PERSONAGEM, ALTURA_PERSONAGEM, 0);
            if (perguntando)
            {
                al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(0, 0, 0, 180));

                al_draw_filled_rectangle(300, 150, 980, 570, al_map_rgb(35, 35, 45));
                al_draw_rectangle(300, 150, 980, 570, al_map_rgb(220, 220, 220), 2);

                al_draw_text(fonte, al_map_rgb(255, 255, 255), 640, 170, ALLEGRO_ALIGN_CENTER, "PORTA BLOQUEADA - RESOLVA A EQUACAO");
                al_draw_text(fonte, al_map_rgb(255, 255, 0), 640, 205, ALLEGRO_ALIGN_CENTER, perguntas[pergunta_atual].texto);
                al_draw_text(fonte, al_map_rgb(200, 200, 200), 640, 225, ALLEGRO_ALIGN_CENTER, "Qual o valor de x?");
                al_draw_filled_rectangle(380, 240, 900, 280, al_map_rgb(15, 15, 20));
                al_draw_rectangle(380, 240, 900, 280, al_map_rgb(180, 180, 180), 2);
                al_draw_text(fonte, al_map_rgb(255, 255, 255), 640, 256, ALLEGRO_ALIGN_CENTER, resposta);
                const char* nomes[12] = { "1","2","3","4","5","6","7","8","9","-","0","<" };
                for (int k = 0; k < 12; k++)
                {
                    float bx = 380 + (k % 3) * 80;
                    float by = 290 + (k / 3) * 55;
                    desenhar_botao(fonte, bx, by, bx + 70, by + 45, nomes[k]);
                }

                desenhar_botao(fonte, 640, 290, 900, 350, "CONFIRMAR");
                desenhar_botao(fonte, 640, 370, 900, 430, "FECHAR");
                al_draw_text(fonte, al_map_rgb(255, 80, 80), 640, 530, ALLEGRO_ALIGN_CENTER, mensagem);
            }
            al_flip_display();
        }
    }

    al_destroy_bitmap(img_porta);
    al_destroy_bitmap(img_parede);
    al_destroy_bitmap(sprites);
    al_destroy_font(fonte);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(fila);

    return 0;
}