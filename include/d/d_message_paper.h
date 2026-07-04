#ifndef D_MESSAGE_PAPER_H
#define D_MESSAGE_PAPER_H

#include "dolphin/types.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"

class sub_msg3_class : public msg_class {
public:
    /* 0x0FC */ u8 field_0xfc[0x90C - 0xFC];
    /* 0x90C */ fopMsgM_pane_class field_0x90c[6];
    /* 0xA5C */ fopMsgM_pane_class field_0xa5c[6];
    /* 0xBAC */ fopMsgM_pane_class field_0xbac[2];
    /* 0xC1C */ fopMsgM_pane_class field_0xc1c[2];
    /* 0xC8C */ fopMsgM_pane_class field_0xc8c[2];
    /* 0xCFC */ u8 field_0xcfc[0xED9 - 0xCFC];
    /* 0xED9 */ u8 field_0xed9;
};

class dmsg3_3d_c {
public:
    dmsg3_3d_c();
    ~dmsg3_3d_c();
    void setDummyTexture();
    void set_mtx();
    void exec();
    void draw();
};

class dDlst_2DMSG3_c {
public:
    void setActorP(sub_msg3_class*) {}
    
    void draw();
    void outFontDraw();
};

#endif /* D_MESSAGE_PAPER_H */
