#include "Animation.h"

Animation::Animation(string nm,Texture2D atls,int num_frms,int start_frm,int end_frm,double frm_tmr,int curr_frm,float frm_len) {
    name = nm;
    atlas = atls;
    num_frames = num_frms;
    start_frame = start_frm;
    end_frame = end_frm;
    frame_timer = frm_tmr;
    current_frame = curr_frm;
    frame_length = frm_len; 
}