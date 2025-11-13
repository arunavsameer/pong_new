// #include <board.cpp>
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <E:\Random\pong\board.hpp>
#include <E:\Random\pong\ball.hpp>
#include <E:\Random\pong\slider.hpp>

using namespace std;
mt19937 rng_main(time(0));

#define RESET "\033[0m"

map <int,string> colors;

class game{
    board game_board;
    ball game_ball;
    slider game_slider;
    vector <vector <char>> display;
    char kbd_buff = ' ';
    int color_counter = 0;
    

public:
    bool game_over = false;
    game(board b, ball bl, slider s) : game_board(b), game_ball(bl), game_slider(s){
        display.resize(game_board.height, vector<char>(game_board.width, ' '));
    }

    game() : game_board(20, 10), game_ball(5, 5, 1, -1), game_slider(7, 12){
        display.resize(game_board.height, vector<char>(game_board.width, ' '));
    }

    // bool transition(){
    //     auto [slider_start, slider_end] = game_slider.get_location();
    //     auto [ball_x, ball_y] = game_ball.get_location();
    //     if(ball_y <= 0){
    //         if((ball_x >= slider_start) and (ball_x <= slider_end)){
    //             game_ball.flip_v_y();
    //             game_ball.change_v((rng_main() % 3) - 1, 0);
    //         }
    //         else{
    //             game_over = true;
    //         }
    //         return true;
    //     }
    //     if(ball_y >= game_board.height - 1){
    //         game_ball.flip_v_y();
    //     }
    //     if((ball_x <= 0) or (ball_x >= game_board.width - 1)){
    //         game_ball.flip_v_x();
    //     }
    //     game_board.remove_brick(ball_x, ball_y);
    //     return false;
    // }

    bool transition_x (){
        auto [slider_start, slider_end] = game_slider.get_location();
        auto [ball_x, ball_y] = game_ball.get_location();
        if(ball_y <= 0){
            if((ball_x >= slider_start) and (ball_x <= slider_end)){
                game_ball.flip_v_y();
                game_ball.change_v((rng_main() % 3) - 1, 0);
            }
            else{
                game_over = true;
            }
            return true;
        }
        if((ball_x <= 0) or (ball_x >= game_board.width - 1)){
            game_ball.flip_v_x();
        }
        game_board.remove_brick(ball_x, ball_y);
        return false;
    }

        bool transition_y (){
        auto [slider_start, slider_end] = game_slider.get_location();
        auto [ball_x, ball_y] = game_ball.get_location();
        if(ball_y <= 0){
            if((ball_x >= slider_start) and (ball_x <= slider_end)){
                game_ball.flip_v_y();
                game_ball.change_v((rng_main() % 3) - 1, 0);
            }
            else{
                game_over = true;
            }
            return true;
        }
         if(ball_y >= game_board.height - 1){
            game_ball.flip_v_y();
        }
        game_board.remove_brick(ball_x, ball_y);
        return false;
    }
    

    void move_slider(){
        auto [slider_start, slider_end] = game_slider.get_location();
        if(kbd_buff == 'a'){
            if(slider_start > 1) game_slider.move_slider_left();
        }
        else if(kbd_buff == 'd'){
            if(slider_end < game_board.width - 2)game_slider.move_slider_right();
        }
    }

    // void input(){
    //     if(_kbhit()){
    //         // cout.flush();
    //         kbd_buff = _getch();
    //         cin.clear();
    //     }
    // }

    void input() {
        if (GetAsyncKeyState('A') & 0x8000) {
            kbd_buff = 'a';
        }
        else if (GetAsyncKeyState('D') & 0x8000) {
            kbd_buff = 'd';
        }
        else {
            kbd_buff = ' ';
        }
    }

    void input_clear(){
        kbd_buff = ' ';
    }

    void trans(){
        game_ball.move_ball_y();
        if (transition_y()) return;
        for(int i = 0; i < abs(game_ball.get_vx()); i++){
            if(transition_x()) break;
            game_ball.move_ball_x();
        }
    }

    void render(){

        for(int i = 0; i < game_board.height; i++){
            for(int j = 0; j < game_board.width; j++){
                if(game_board.is_brick_here(j, i)){
                    display[i][j] = '#';
                }
                else{
                    display[i][j] = ' ';
                }
            }
        }

        auto [slider_start, slider_end] = game_slider.get_location();
        for(int j = slider_start; j <= slider_end; j++){
            display[0][j] = '=';
        }

        auto [ball_x, ball_y] = game_ball.get_location();
        display[ball_y][ball_x] = 'O';
        system("cls");
        for(int i = game_board.height - 1; i >= 0; i--){
            for(int j = 0; j < game_board.width; j++){
                if (display[i][j] == '#'){
                    cout << colors[(game_board.brick_color[i][j] + color_counter)%3];
                }
                cout << display[i][j];
                cout << RESET;
            }
            cout << endl;
        }
         color_counter++;
    }
    
};

int main(){
    colors[0] = "\033[31m";
    colors[1] = "\033[32m";
    colors[2] = "\033[34m";

    ios::sync_with_stdio(0);
    cin.tie(0);
    board b(20, 40, 2, rng_main());
    ball bl(20, 10, 1, 1);
    slider s(15, 20, 2);
    game g(b, bl, s);

    while(!g.game_over){
        cout << "\x1b[?25l";
        g.input();
        // g.transition();
        g.trans();
        g.move_slider();
        g.input_clear();
        g.render();
        // for (int i = 1 ; i <= 5 ; i++){
        //     g.render();
        //     this_thread::sleep_for(chrono::milliseconds(10));
        // }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "\x1b[?25h";
    cout << "Game Over!" << endl;

    return 0;
}