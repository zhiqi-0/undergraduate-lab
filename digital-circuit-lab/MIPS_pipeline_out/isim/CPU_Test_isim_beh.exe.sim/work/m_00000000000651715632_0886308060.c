/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/ralzq/Study/ISEexp/MIPS_pipeline_out/ALU.v";
static int ng1[] = {0, 0};
static unsigned int ng2[] = {1U, 0U};
static unsigned int ng3[] = {2U, 0U};
static unsigned int ng4[] = {3U, 0U};
static unsigned int ng5[] = {4U, 0U};
static unsigned int ng6[] = {5U, 0U};
static unsigned int ng7[] = {6U, 0U};
static unsigned int ng8[] = {7U, 0U};
static unsigned int ng9[] = {8U, 0U};
static int ng10[] = {16, 0};
static unsigned int ng11[] = {9U, 0U};
static unsigned int ng12[] = {16U, 0U};
static unsigned int ng13[] = {0U, 0U};



static void Initial_28_0(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(28, ng0);

LAB2:    xsi_set_current_line(29, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3264);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB1:    return;
}

static void Always_37_1(char *t0)
{
    char t10[8];
    char t11[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;

LAB0:    t1 = (t0 + 4592U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(37, ng0);
    t2 = (t0 + 5160);
    *((int *)t2) = 1;
    t3 = (t0 + 4624);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(37, ng0);

LAB5:    xsi_set_current_line(38, ng0);
    t4 = (t0 + 2864U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng2)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t4, 5);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t2, 5);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t2, 5);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t2, 5);
    if (t6 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng6)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t2, 5);
    if (t6 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng7)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t2, 5);
    if (t6 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng8)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t2, 5);
    if (t6 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng9)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t2, 5);
    if (t6 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng11)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t2, 5);
    if (t6 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng12)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 5, t2, 5);
    if (t6 == 1)
        goto LAB25;

LAB26:
LAB28:
LAB27:
LAB29:    goto LAB2;

LAB7:    xsi_set_current_line(39, ng0);
    t7 = (t0 + 2544U);
    t8 = *((char **)t7);
    t7 = (t0 + 2704U);
    t9 = *((char **)t7);
    memset(t10, 0, 8);
    xsi_vlog_signed_add(t10, 32, t8, 32, t9, 32);
    t7 = (t0 + 3264);
    xsi_vlogvar_assign_value(t7, t10, 0, 0, 32);
    goto LAB29;

LAB9:    xsi_set_current_line(40, ng0);
    t3 = (t0 + 2544U);
    t4 = *((char **)t3);
    t3 = (t0 + 2704U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_signed_minus(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 3264);
    xsi_vlogvar_assign_value(t3, t10, 0, 0, 32);
    goto LAB29;

LAB11:    xsi_set_current_line(41, ng0);
    t3 = (t0 + 2544U);
    t4 = *((char **)t3);
    t3 = (t0 + 2704U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_signed_bit_and(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 3264);
    xsi_vlogvar_assign_value(t3, t10, 0, 0, 32);
    goto LAB29;

LAB13:    xsi_set_current_line(42, ng0);
    t3 = (t0 + 2544U);
    t4 = *((char **)t3);
    t3 = (t0 + 2704U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_signed_bit_or(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 3264);
    xsi_vlogvar_assign_value(t3, t10, 0, 0, 32);
    goto LAB29;

LAB15:    xsi_set_current_line(43, ng0);
    t3 = (t0 + 2544U);
    t4 = *((char **)t3);
    t3 = (t0 + 2704U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_signed_bit_xor(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 3264);
    xsi_vlogvar_assign_value(t3, t10, 0, 0, 32);
    goto LAB29;

LAB17:    xsi_set_current_line(44, ng0);
    t3 = (t0 + 2544U);
    t4 = *((char **)t3);
    t3 = (t0 + 2704U);
    t7 = *((char **)t3);
    memset(t11, 0, 8);
    xsi_vlog_signed_bit_or(t11, 32, t4, 32, t7, 32);
    memset(t10, 0, 8);
    t3 = (t10 + 4);
    t8 = (t11 + 4);
    memcpy(t10, t11, 8);
    t12 = *((unsigned int *)t10);
    t13 = (~(t12));
    t14 = *((unsigned int *)t3);
    t15 = (t13 | t14);
    *((unsigned int *)t10) = t15;
    t16 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t16 & 4294967295U);
    t17 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t17 & 4294967295U);
    t9 = (t0 + 3264);
    xsi_vlogvar_assign_value(t9, t10, 0, 0, 32);
    goto LAB29;

LAB19:    xsi_set_current_line(45, ng0);
    t3 = ((char*)((ng1)));
    t4 = (t0 + 3264);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 32);
    goto LAB29;

LAB21:    xsi_set_current_line(46, ng0);
    t3 = (t0 + 2704U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng10)));
    memset(t10, 0, 8);
    xsi_vlog_signed_lshift(t10, 32, t4, 32, t3, 32);
    t7 = (t0 + 3264);
    xsi_vlogvar_assign_value(t7, t10, 0, 0, 32);
    goto LAB29;

LAB23:    xsi_set_current_line(47, ng0);
    t3 = (t0 + 2704U);
    t4 = *((char **)t3);
    t3 = (t0 + 2544U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_signed_lshift(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 3264);
    xsi_vlogvar_assign_value(t3, t10, 0, 0, 32);
    goto LAB29;

LAB25:    xsi_set_current_line(48, ng0);
    t3 = (t0 + 2704U);
    t4 = *((char **)t3);
    t3 = (t0 + 2544U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_signed_rshift(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 3264);
    xsi_vlogvar_assign_value(t3, t10, 0, 0, 32);
    goto LAB29;

}

static void Always_53_2(char *t0)
{
    char t8[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    char *t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    char *t31;

LAB0:    t1 = (t0 + 4840U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(53, ng0);
    t2 = (t0 + 5176);
    *((int *)t2) = 1;
    t3 = (t0 + 4872);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(53, ng0);

LAB5:    xsi_set_current_line(54, ng0);
    t4 = (t0 + 3264);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = ((char*)((ng1)));
    memset(t8, 0, 8);
    t9 = (t6 + 4);
    t10 = (t7 + 4);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = *((unsigned int *)t9);
    t15 = *((unsigned int *)t10);
    t16 = (t14 ^ t15);
    t17 = (t13 | t16);
    t18 = *((unsigned int *)t9);
    t19 = *((unsigned int *)t10);
    t20 = (t18 | t19);
    t21 = (~(t20));
    t22 = (t17 & t21);
    if (t22 != 0)
        goto LAB9;

LAB6:    if (t20 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t8) = 1;

LAB9:    t24 = (t8 + 4);
    t25 = *((unsigned int *)t24);
    t26 = (~(t25));
    t27 = *((unsigned int *)t8);
    t28 = (t27 & t26);
    t29 = (t28 != 0);
    if (t29 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(57, ng0);
    t2 = ((char*)((ng13)));
    t3 = (t0 + 3424);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB12:    goto LAB2;

LAB8:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(55, ng0);
    t30 = ((char*)((ng2)));
    t31 = (t0 + 3424);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    goto LAB12;

}


extern void work_m_00000000000651715632_0886308060_init()
{
	static char *pe[] = {(void *)Initial_28_0,(void *)Always_37_1,(void *)Always_53_2};
	xsi_register_didat("work_m_00000000000651715632_0886308060", "isim/CPU_Test_isim_beh.exe.sim/work/m_00000000000651715632_0886308060.didat");
	xsi_register_executes(pe);
}
