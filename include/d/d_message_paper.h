#ifndef D_MESSAGE_PAPER_H
#define D_MESSAGE_PAPER_H

#include "dolphin/types.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_drawlist.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "SSystem/SComponent/c_xyz.h"

class JUTFont;
class J3DModel;
class JKRSolidHeap;

class sub_msg3_class : public msg_class {
public:
    /* 0x0FC */ u8 field_0xfc[0x116 - 0xFC];
    /* 0x116 */ u8 field_0x116;
    /* 0x117 */ u8 field_0x117;
    /* 0x118 */ fopMsgM_msgDataProc_c screen[3];
    /* 0x8F8 */ u8 field_0x8f8[0x90C - 0x8F8];
    /* 0x90C */ fopMsgM_pane_class field_0x90c[3];
    /* 0x9B4 */ fopMsgM_pane_class field_0x9b4[3];
    /* 0xA5C */ fopMsgM_pane_class field_0xa5c[3];
    /* 0xB04 */ fopMsgM_pane_class field_0xb04[3];
    /* 0xBAC */ fopMsgM_pane_class field_0xbac[2];
    /* 0xC1C */ fopMsgM_pane_class field_0xc1c[2];
    /* 0xC8C */ fopMsgM_pane_class field_0xc8c[2];
    /* 0xCFC */ u8 field_0xcfc[0xE4C - 0xCFC];
    /* 0xE4C */ JUTFont* mx;
    /* 0xE50 */ JUTFont* rx;
    /* 0xE54 */ void* field_0xe54;
    /* 0xE58 */ void* field_0xe58;
    /* 0xE5C */ const char* field_0xe5c;
    /* 0xE60 */ char* field_0xe60[3];
    /* 0xE6C */ char* field_0xe6c[3];
    /* 0xE78 */ char* field_0xe78[3];
    /* 0xE84 */ char* field_0xe84[3];
    /* 0xE90 */ f32 field_0xe90;
    /* 0xE94 */ u8 field_0xe94[0xE98 - 0xE94];
    /* 0xE98 */ u8 field_0xe98[3];
    /* 0xE9B */ u8 field_0xe9b[0xEA0 - 0xE9B];
    /* 0xEA0 */ u16 field_0xea0;
    /* 0xEA2 */ u8 field_0xea2[0xEA4 - 0xEA2];
    /* 0xEA4 */ f32 field_0xea4;
    /* 0xEA8 */ u8 field_0xea8[0xEAC - 0xEA8];
    /* 0xEAC */ int field_0xeac;
    /* 0xEB0 */ u32 field_0xeb0;
    /* 0xEB4 */ u32 field_0xeb4;
    /* 0xEB8 */ u8 field_0xeb8[0xEBC - 0xEB8];
    /* 0xEBC */ u8 field_0xebc;
    /* 0xEBD */ u8 field_0xebd[0xEC0 - 0xEBD];
    /* 0xEC0 */ int field_0xec0;
    /* 0xEC4 */ u8 field_0xec4[0xEC8 - 0xEC4];
    /* 0xEC8 */ int field_0xec8[3];
    /* 0xED4 */ u8 field_0xed4[0xED9 - 0xED4];
    /* 0xED9 */ u8 field_0xed9;
};

class dmsg3_3d_c {
public:
    dmsg3_3d_c();
    virtual ~dmsg3_3d_c();
    void setDummyTexture();
    void set_mtx();
    void exec();
    void draw();

    /* 0x04 */ void* field_0x4;
    /* 0x08 */ u8 field_0x8[0x0C - 0x08];
    /* 0x0C */ void* field_0xc;
    /* 0x10 */ cXyz field_0x10;
    /* 0x1C */ u8 field_0x1c[0x28 - 0x1C];
    /* 0x28 */ csXyz field_0x28;
    /* 0x2E */ u8 field_0x2e[0x30 - 0x2E];
    /* 0x30 */ J3DModel* mModel;
    /* 0x34 */ mDoExt_bckAnm field_0x34;
    /* 0x44 */ u8 field_0x44[0x48 - 0x44];
    /* 0x48 */ JKRSolidHeap* field_0x48;
};

class dDlst_2DMSG3_c : public dDlst_base_c {
public:
    virtual ~dDlst_2DMSG3_c() {}

    void setActorP(sub_msg3_class*) {}

    virtual void draw();
    void outFontDraw();
};

#endif /* D_MESSAGE_PAPER_H */
