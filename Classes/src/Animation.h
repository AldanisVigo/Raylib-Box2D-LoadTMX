#ifndef ANIMATION_H
#define ANIMATION_H
#include <iostream>
#include <raylib.h>

using namespace std;
class Animation {
    public:
        Animation(string,Texture2D,int,int,int,double,int,float);
        string name = "";
        Texture2D atlas;
        int num_frames = 1;
        int start_frame = 0;
        int end_frame = 1;
        double frame_timer = 0.0f;
        int current_frame = 0;
        float frame_length = 0.1f;
};

#endif 