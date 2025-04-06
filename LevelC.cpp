#include "LevelC.h"
#include "Utility.h"
#include "vector"

#define LEVEL_WIDTH 25
#define LEVEL_HEIGHT 32

//All textures are taken from here
// Source: https://kenney.nl/assets/pico-8-platformer

constexpr char SPRITESHEET_FILEPATH[] = "assets/PlayerSpritesheet.png",
GUARD_FILEPATH[] = "assets/GuardSpritesheet.png",
WALKER_FILEPATH[] = "assets/WalkerSpritesheet.png",
ONE_LIFE_FILEPATH[] = "assets/OneHeart.png",
NO_LIVES_FILEPATH[] = "assets/EmptyHeart.png";




unsigned int LEVELC_DATA[] =
{
    
    2,  2,  25, 2,  2,  2,  2,  2,  2,  2,  2,  38, 85, 43, 39, 2,  44, 86, 0,  27, 2,  2,  2,  2,  25,
    2,  2 , 44, 11, 11, 11, 12, 2,  2,  2,  2,  2,  2,  11, 11, 11, 59, 0,  0,  27, 2,  2,  2,  2,  2,
    2,  44, 59, 0,  0,  76, 85, 12, 2,  2,  2,  2,  25, 0,  0,  38, 0,  0,  0,  27, 2,  2,  2,  2,  2,
    2,  25, 0,  0,  0 , 0,  0,  85, 43, 39, 2,  44, 86, 0,  0,  0,  0,  0,  0,  85, 11, 43, 2,  2,  2,
    11, 86, 0,  0,  0 , 0,  0,  76, 58, 11, 11, 59, 0,  0,  0,  0,  0,  0,  0,  0,  0,  58, 43, 2,  2,
    101,102,0,  0,  0 , 0,  0,  0 , 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  51, 4,  4,
    116,117,0,  0,  0,  0,  0,  0 , 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 , 0,  0,  0,  0,  0,  16,  1,
    40, 41, 41, 71, 0,  0,  0,  60, 0,  0,  0,  0,  0,  0,  0,  0,  0,  60, 70, 41, 71, 0,  0,  1,  20,
    2,  2,  2,  40, 64, 0,  0,  0,  0,  60, 0,  0,  60, 60, 60, 0,  0,  0,  20, 2,  18, 0,  0,  1, 20,
    2,  2,  2,  2,  18, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  20, 2,  18, 0,  0,  1,  20,
    2,  2,  2,  2,  33, 64, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  63, 34, 35, 2,  18, 0,  0,  1,  20,
    2,  2,  2,  2,  2,  33, 34, 34, 34, 64, 1,  1,  1,  1,  1,  63, 35, 3,  4,  5,  18, 0,  0,  1, 20,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  33, 34, 34, 34, 34, 34, 35, 37, 79, 0,  20, 52, 0,  0,  1,  20,
    2,  2 , 37, 4,  4,  4,  5,  2,  2,  2,  2,  2,  3,  4,  4,  4,  52, 0,  0,  62, 0,  0,  0,  1,  2,
    2,  37, 52, 0,  0,  76, 78, 5,  2,  2,  2,  2,  18, 0,  0,  31, 0,  0,  0,  62, 0,  0,  0,  1,  2,
    2,  18, 0,  0,  0 , 0,  0,  78, 36, 39, 2,  37, 79, 0,  0,  0,  0,  0,  0,  77, 0, 63, 64,  1,  1,
    2,  18, 0,  0,  0 , 0,  0,  76, 51, 4, 4, 52, 31,  0,  0,  0,  0,  0,  0,  0,  0,  51, 36, 17,  1,
    4,  79, 0,  0,  0 , 0,  0,  0 , 0,  76, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  51, 5,  17,
    103,104,0,  0,  0,  0,  0,  0 , 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 , 0,  0,  0,  0,  0,  20, 9,
    118,119,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  63, 34, 34, 34, 34, 35, 2,
    34, 34, 34, 34, 64, 0,  0,  0,  0,  60, 0,  0,  0,  60, 0,  0,  0,  0,  20, 2,  39, 2,  24,  2,  2,
    2,  2,  2,  2,  18, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  20, 2,  2,  9,  2,  2,  2,
    2,  2,  2,  2,  2,  64, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  63, 34, 35, 2,  2,  24,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  63, 35, 2,  2,  2,  2,  2,  2,  2,  2

};

LevelC::~LevelC()
{
    for (Entity* enemy : m_game_state.enemies) {
        delete    enemy;
    }
    m_game_state.enemies.clear();
    delete    m_game_state.player;
    delete    m_game_state.map;

    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeChunk(m_game_state.level_clear_sfx);
    Mix_FreeChunk(m_game_state.death_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelC::initialise()
{
    m_game_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture("assets/tilemap.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELC_DATA, map_texture_id, 1.0f, 15, 10);

    m_game_state.LEFT_EDGE = 4.5f;
    m_game_state.RIGHT_EDGE = LEVEL_WIDTH - 5.5;
    m_game_state.BOTTOM_EDGE = -18.75f;
    m_game_state.TOP_EDGE = -4.25f;


    int player_walking_animation[4][4] =
    {
        { 0, 3, 0, 3 },  // for George to move to the left,
        { 0, 1, 0, 1 }, // for George to move to the right,
        { 4, 4, 4, 4 }, // for George to move upwards,
        { 2, 2, 2, 2 }   // for George to move downwards
    };

    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);

    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);

    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        5.0f,                      // speed
        acceleration,              // acceleration
        6.0f,                      // jumping power
        player_walking_animation,  // animation index sets
        0.0f,                      // animation time
        2,                         // animation frame amount
        0,                         // current animation index
        3,                         // animation column amount
        2,                         // animation row amount
        0.8f,                      // width
        1.0f,                       // height
        PLAYER
    );

    m_game_state.player->set_lives(3);

    m_game_state.player->set_position(glm::vec3(2.0f, -4.0f, 0.0f));



    m_game_state.player->set_jumping_power(3.0f);



    /**
    Enemies' stuff */
    GLuint guard_texture_id  = Utility::load_texture(GUARD_FILEPATH),
        walker_texture_id = Utility::load_texture(WALKER_FILEPATH);

    int guard_walking_animation[4][4] =
            {

                { 0, 3, 0, 3 },  // for George to move to the left,
                { 0, 1, 0, 1 }, // for George to move to the right,
                { 4, 4, 4, 4 }, // for George to move upwards,
                { 2, 2, 2, 2 }   // for George to move downwards
            };



    for (int i = 0; i < ENEMY_COUNT; i++) {

        if (i < 2) {
            

            int enemy_walking_animation[4][4] =
            {

                { 0, 3, 0, 3 },  // for George to move to the left,
                { 0, 1, 0, 1 }, // for George to move to the right,
                { 4, 4, 4, 4 }, // for George to move upwards,
                { 2, 2, 2, 2 }   // for George to move downwards
            };

            m_game_state.enemies.push_back(new Entity(
                guard_texture_id,         // texture id
                1.0f,                      // speed
                acceleration,              // acceleration
                0.0f,                      // jumping power
                enemy_walking_animation,  // animation index sets
                0.0f,                      // animation time
                2,                         // animation frame amount
                0,                         // current animation index
                3,                         // animation column amount
                2,                         // animation row amount
                1.0f,                      // width
                1.0f,                       // height
                ENEMY
            ));
            m_game_state.enemies[i]->set_ai_type(GUARD);
            m_game_state.enemies[i]->set_ai_state(IDLE);
            if (i == 0) {
                m_game_state.enemies[i]->set_position(glm::vec3(13.0f, -3.0f, 0.0f));
                m_game_state.enemies[i]->set_movement(glm::vec3(0.0f));
            }
            else {
                m_game_state.enemies[i]->set_position(glm::vec3(2.0f, -17.0f, 0.0f));
                m_game_state.enemies[i]->set_movement(glm::vec3(0.0f));
            }
            
        }
        else {


            int enemy_walking_animation[4][4] =
            {
                { 0, 1, 0, 1 },
                { 0, 1, 0, 1 },
                { 0, 1, 0, 1 },
                { 0, 1, 0, 1 }
            };

            m_game_state.enemies.push_back(new Entity(
                walker_texture_id,         // texture id
                1.0f,                      // speed
                acceleration,              // acceleration
                0.0f,                      // jumping power
                enemy_walking_animation,  // animation index sets
                0.0f,                      // animation time
                2,                         // animation frame amount
                0,                         // current animation index
                2,                         // animation column amount
                1,                         // animation row amount
                1.0f,                      // width
                1.0f,                       // height
                ENEMY
            ));
            m_game_state.enemies[i]->set_ai_type(WALKER);
            m_game_state.enemies[i]->set_position(glm::vec3(18.0f, -17.0f, 0.0f));
            m_game_state.enemies[i]->set_movement(glm::vec3(0.0f));

        }

        
    }





    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    // Source: https://incompetech.com/music/royalty-free/music.html
    m_game_state.bgm = Mix_LoadMUS("assets/Leaving Home.mp3");


    // Source: https://opengameart.org/content/slime-jump-effect
    m_game_state.jump_sfx = Mix_LoadWAV("assets/slime_jump.wav");
    // Source: https://opengameart.org/content/8-bit-sound-effects-library
    m_game_state.death_sfx = Mix_LoadWAV("assets/death.wav");
    m_game_state.level_clear_sfx = Mix_LoadWAV("assets/Win1.wav");

    Mix_VolumeChunk(
        m_game_state.jump_sfx,     // Set the volume of the bounce sound...
        MIX_MAX_VOLUME / 4  // ... to 1/4th.
    );
    Mix_VolumeChunk(
        m_game_state.death_sfx,     // Set the volume of the bounce sound...
        MIX_MAX_VOLUME / 4  // ... to 1/4th.
    );
    Mix_VolumeChunk(
        m_game_state.level_clear_sfx,     // Set the volume of the bounce sound...
        MIX_MAX_VOLUME / 2  // ... to 1/4th.
    );

    m_game_state.death_flag = false;

}

void LevelC::update(float delta_time)
{
    if (m_game_state.player->is_dead()) {
        if (!m_game_state.death_flag) {
            m_game_state.death_flag = true;

            m_game_state.player->set_movement(glm::vec3(0.0f));
            m_game_state.player->set_velocity(glm::vec3(0.0f, 1.0f, 0.0f));
            m_game_state.player->set_acceleration(glm::vec3(0.0f, -5.0f, 0.0f));

            Mix_PlayChannel(-1, m_game_state.death_sfx, 0);
        }

        m_game_state.player->update(delta_time, m_game_state.player, m_game_state.empty_vector, 0, NULL);

        if (m_game_state.player->get_position().y < m_game_state.player->get_death_height() - 2.0f) {
            m_game_state.player->set_lives(2);
        }


    }
    else {
        m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);

        for (int i = 0; i < ENEMY_COUNT; i++)
        {
            m_game_state.enemies[i]->update(delta_time, m_game_state.player, m_game_state.empty_vector, 0, m_game_state.map);
        }

        if (m_game_state.player->get_position().x < 0.8f && m_game_state.player->get_position().y < -2.0f) {
            Mix_PlayChannel(-1, m_game_state.level_clear_sfx, 0);
            m_game_state.next_scene_id = 4;
        }
    }

}

void LevelC::render(ShaderProgram* program)
{
    m_game_state.map->render(program);
    m_game_state.player->render(program);


    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i]->render(program);
    }

    //m_game_state.enemies[0].render(program);


}