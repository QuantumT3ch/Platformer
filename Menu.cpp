#include "Menu.h"
#include "Utility.h"

#define LEVEL_WIDTH 22
#define LEVEL_HEIGHT 10

constexpr char SPRITESHEET_FILEPATH[] = "assets/PlayerSpritesheet.png",
ENEMY_FILEPATH[] = "assets/soph.png",
FONT_FILEPATH[] = "assets/font1.png";


unsigned int MENU_DATA[] =
{
    0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  
    0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  
    0, 0,  47, 0,  0,  47, 0,  47, 0,  0,  0,  0 , 0 , 0 , 6,  49,  7, 0,  0,  0,  0,  0, 
    0, 0,  62, 0,  0,  62, 0,  62, 0,  0,  0,  0 , 0,  0 , 77, 0,  62, 0,  0,  0,  0,  0, 
    0, 0,  78, 50, 0,  77, 0,  78, 50, 0,  0, 107, 0 , 0 , 0 , 0,  62, 0,  0,  0,  0,  0,   
    0 ,0,  0,  0,  0,  0,  0,  0,  0,  0,  60, 60, 0,  0,  0,  48, 18, 0,  0 , 0,  0,  0,   
    0, 0,  63, 49, 50, 0,  47, 0,  47, 0,  47, 0,  47, 0,  0,  0,  62, 0 , 0,  0,  0,  0, 
    0, 0,  62, 0,  15, 0,  62, 0,  62, 0,  51, 34, 52, 0,  47, 0,  62, 0 , 0,  0,  0,  0,
    0, 0,  78, 49, 50, 0,  78, 49, 79, 0,  0,  77, 0,  0,  51, 49, 52, 0 , 0,  0,  0,  0,
    0 ,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0

};

Menu::~Menu()
{
    
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void Menu::initialise()
{
    m_game_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture("assets/tilemap.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, MENU_DATA, map_texture_id, 0.5f, 15, 10);
    
}

void Menu::update(float delta_time)
{

    //m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, 0, m_game_state.map);

    //m_game_state.enemies->update(delta_time, m_game_state.enemies, m_game_state.player, 1, m_game_state.map);

    //if (m_game_state.player->get_position().y < -10.0f) m_game_state.next_scene_id = 1;
}

void Menu::render(ShaderProgram* program)
{
    m_game_state.map->render(program);
    Utility::draw_text(program, Utility::load_texture(FONT_FILEPATH), "Press Enter to Start", 0.5f, 0.001f,
        glm::vec3(0.2f, -5.0f, 0.0f));
    //m_game_state.player->render(program);
}
