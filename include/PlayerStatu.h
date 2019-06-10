#ifndef PLAYERSTATU_H
#define PLAYERSTATU_H

#include <Image.h>
#include <Block.h>
#include <Player.h>

class PlayerStatu
{
public:
    PlayerStatu();
    ~PlayerStatu();

    void Prepare(void);
    void Update(void);
    void Show(void);

    void ShowPlayerHP(void);
    void ShowGameover(void);
    void ShowMaxScore(void);
    void ShowScore(void);

    unsigned GetScore(void);
    void AddScore(void);
    void ScoreCaculate(void);
    void MaxScoreCaculate(void);


    void SetPlayer(Player* ptr) { player = ptr; }
    void SetHPBlock(Block temp) { hp_block = temp; }

    static int score;
    static int max_score;

private:

    //glut window coordination
    Block hp_block;
    Block gameover_block;
    Block score_block;
    Block max_score_block;

    bool show_heathpoint;
    bool show_gameoverskin;
    bool show_maxscore;
    bool show_score;


    static int score_arr[5];
    static int max_score_arr[5];

    Image* HP_skin_ptr;
    Image HP_skin[6];
    Image gameover_skin;

    Image* number_skin_ptr;
    Image number_skin[10];

    Image max_score_skin;
    Image score_skin;

    Player* player;
};

#endif // PLAYERSTATU_H
