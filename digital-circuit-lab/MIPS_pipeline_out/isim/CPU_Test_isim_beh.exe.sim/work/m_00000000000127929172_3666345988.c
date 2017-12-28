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
static const char *ng0 = "C:/Users/ralzq/Study/ISEexp/MIPS_pipeline_out/EX.v";
static int ng1[] = {0, 0};
static unsigned int ng2[] = {0U, 0U};
static unsigned int ng3[] = {1U, 0U};
static unsigned int ng4[] = {2U, 0U};
static unsigned int ng5[] = {3U, 0U};
static int ng6[] = {1, 0};



static void Always_59_0(char *t0)
{
    char t4[8];
    char t32[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    char *t30;
    int t31;

LAB0:    t1 = (t0 + 5888U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(59, ng0);
    t2 = (t0 + 6208);
    *((int *)t2) = 1;
    t3 = (t0 + 5920);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(59, ng0);

LAB5:    xsi_set_current_line(60, ng0);
    t5 = (t0 + 1048U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t6 + 4);
    t7 = *((unsigned int *)t5);
    t8 = (~(t7));
    t9 = *((unsigned int *)t6);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB9;

LAB7:    if (*((unsigned int *)t5) == 0)
        goto LAB6;

LAB8:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;

LAB9:    t13 = (t4 + 4);
    t14 = (t6 + 4);
    t15 = *((unsigned int *)t6);
    t16 = (~(t15));
    *((unsigned int *)t4) = t16;
    *((unsigned int *)t13) = 0;
    if (*((unsigned int *)t14) != 0)
        goto LAB11;

LAB10:    t21 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t21 & 1U);
    t22 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t22 & 1U);
    t23 = (t4 + 4);
    t24 = *((unsigned int *)t23);
    t25 = (~(t24));
    t26 = *((unsigned int *)t4);
    t27 = (t26 & t25);
    t28 = (t27 != 0);
    if (t28 > 0)
        goto LAB12;

LAB13:    xsi_set_current_line(65, ng0);

LAB16:    xsi_set_current_line(67, ng0);
    t2 = (t0 + 3608U);
    t3 = *((char **)t2);

LAB17:    t2 = ((char*)((ng2)));
    t31 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t31 == 1)
        goto LAB18;

LAB19:    t2 = ((char*)((ng3)));
    t31 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t31 == 1)
        goto LAB20;

LAB21:    t2 = ((char*)((ng4)));
    t31 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t31 == 1)
        goto LAB22;

LAB23:    t2 = ((char*)((ng5)));
    t31 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t31 == 1)
        goto LAB24;

LAB25:
LAB26:    xsi_set_current_line(74, ng0);
    t2 = (t0 + 3768U);
    t5 = *((char **)t2);

LAB27:    t2 = ((char*)((ng2)));
    t31 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t31 == 1)
        goto LAB28;

LAB29:    t2 = ((char*)((ng3)));
    t31 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t31 == 1)
        goto LAB30;

LAB31:    t2 = ((char*)((ng4)));
    t31 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t31 == 1)
        goto LAB32;

LAB33:    t2 = ((char*)((ng5)));
    t31 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t31 == 1)
        goto LAB34;

LAB35:
LAB36:    xsi_set_current_line(81, ng0);
    t2 = (t0 + 2328U);
    t6 = *((char **)t2);
    t2 = ((char*)((ng6)));
    memset(t4, 0, 8);
    t12 = (t6 + 4);
    t13 = (t2 + 4);
    t7 = *((unsigned int *)t6);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t12);
    t11 = *((unsigned int *)t13);
    t15 = (t10 ^ t11);
    t16 = (t9 | t15);
    t17 = *((unsigned int *)t12);
    t18 = *((unsigned int *)t13);
    t19 = (t17 | t18);
    t20 = (~(t19));
    t21 = (t16 & t20);
    if (t21 != 0)
        goto LAB40;

LAB37:    if (t19 != 0)
        goto LAB39;

LAB38:    *((unsigned int *)t4) = 1;

LAB40:    t23 = (t4 + 4);
    t22 = *((unsigned int *)t23);
    t24 = (~(t22));
    t25 = *((unsigned int *)t4);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB41;

LAB42:    xsi_set_current_line(84, ng0);
    t2 = (t0 + 4808);
    t6 = (t2 + 56U);
    t12 = *((char **)t6);
    t13 = (t0 + 4488);
    xsi_vlogvar_wait_assign_value(t13, t12, 0, 0, 32, 0LL);

LAB43:    xsi_set_current_line(86, ng0);
    t2 = (t0 + 2168U);
    t6 = *((char **)t2);
    t2 = ((char*)((ng6)));
    memset(t4, 0, 8);
    t12 = (t6 + 4);
    t13 = (t2 + 4);
    t7 = *((unsigned int *)t6);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t12);
    t11 = *((unsigned int *)t13);
    t15 = (t10 ^ t11);
    t16 = (t9 | t15);
    t17 = *((unsigned int *)t12);
    t18 = *((unsigned int *)t13);
    t19 = (t17 | t18);
    t20 = (~(t19));
    t21 = (t16 & t20);
    if (t21 != 0)
        goto LAB47;

LAB44:    if (t19 != 0)
        goto LAB46;

LAB45:    *((unsigned int *)t4) = 1;

LAB47:    t23 = (t4 + 4);
    t22 = *((unsigned int *)t23);
    t24 = (~(t22));
    t25 = *((unsigned int *)t4);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB48;

LAB49:    xsi_set_current_line(89, ng0);
    t2 = (t0 + 4968);
    t6 = (t2 + 56U);
    t12 = *((char **)t6);
    t13 = (t0 + 4648);
    xsi_vlogvar_wait_assign_value(t13, t12, 0, 0, 32, 0LL);

LAB50:    xsi_set_current_line(91, ng0);
    t2 = (t0 + 4808);
    t6 = (t2 + 56U);
    t12 = *((char **)t6);
    t13 = (t0 + 4328);
    xsi_vlogvar_wait_assign_value(t13, t12, 0, 0, 32, 0LL);
    xsi_set_current_line(93, ng0);
    t2 = (t0 + 2648U);
    t6 = *((char **)t2);
    t2 = ((char*)((ng6)));
    memset(t4, 0, 8);
    t12 = (t6 + 4);
    t13 = (t2 + 4);
    t7 = *((unsigned int *)t6);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t12);
    t11 = *((unsigned int *)t13);
    t15 = (t10 ^ t11);
    t16 = (t9 | t15);
    t17 = *((unsigned int *)t12);
    t18 = *((unsigned int *)t13);
    t19 = (t17 | t18);
    t20 = (~(t19));
    t21 = (t16 & t20);
    if (t21 != 0)
        goto LAB54;

LAB51:    if (t19 != 0)
        goto LAB53;

LAB52:    *((unsigned int *)t4) = 1;

LAB54:    t23 = (t4 + 4);
    t22 = *((unsigned int *)t23);
    t24 = (~(t22));
    t25 = *((unsigned int *)t4);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB55;

LAB56:    xsi_set_current_line(96, ng0);
    t2 = (t0 + 1848U);
    t6 = *((char **)t2);
    t2 = (t0 + 4168);
    xsi_vlogvar_wait_assign_value(t2, t6, 0, 0, 5, 0LL);

LAB57:
LAB14:    goto LAB2;

LAB6:    *((unsigned int *)t4) = 1;
    goto LAB9;

LAB11:    t17 = *((unsigned int *)t4);
    t18 = *((unsigned int *)t14);
    *((unsigned int *)t4) = (t17 | t18);
    t19 = *((unsigned int *)t13);
    t20 = *((unsigned int *)t14);
    *((unsigned int *)t13) = (t19 | t20);
    goto LAB10;

LAB12:    xsi_set_current_line(60, ng0);

LAB15:    xsi_set_current_line(61, ng0);
    t29 = ((char*)((ng1)));
    t30 = (t0 + 4488);
    xsi_vlogvar_wait_assign_value(t30, t29, 0, 0, 32, 0LL);
    xsi_set_current_line(61, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 4648);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 32, 0LL);
    xsi_set_current_line(62, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 4328);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 32, 0LL);
    xsi_set_current_line(63, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 4168);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 5, 0LL);
    goto LAB14;

LAB18:    xsi_set_current_line(68, ng0);
    t5 = (t0 + 1208U);
    t6 = *((char **)t5);
    t5 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t5, t6, 0, 0, 32, 0LL);
    goto LAB26;

LAB20:    xsi_set_current_line(69, ng0);
    t5 = (t0 + 3288U);
    t6 = *((char **)t5);
    t5 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t5, t6, 0, 0, 32, 0LL);
    goto LAB26;

LAB22:    xsi_set_current_line(70, ng0);
    t5 = (t0 + 3128U);
    t6 = *((char **)t5);
    t5 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t5, t6, 0, 0, 32, 0LL);
    goto LAB26;

LAB24:    xsi_set_current_line(71, ng0);
    t5 = (t0 + 3448U);
    t6 = *((char **)t5);
    t5 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t5, t6, 0, 0, 32, 0LL);
    goto LAB26;

LAB28:    xsi_set_current_line(75, ng0);
    t6 = (t0 + 1368U);
    t12 = *((char **)t6);
    t6 = (t0 + 4808);
    xsi_vlogvar_wait_assign_value(t6, t12, 0, 0, 32, 0LL);
    goto LAB36;

LAB30:    xsi_set_current_line(76, ng0);
    t6 = (t0 + 3288U);
    t12 = *((char **)t6);
    t6 = (t0 + 4808);
    xsi_vlogvar_wait_assign_value(t6, t12, 0, 0, 32, 0LL);
    goto LAB36;

LAB32:    xsi_set_current_line(77, ng0);
    t6 = (t0 + 3128U);
    t12 = *((char **)t6);
    t6 = (t0 + 4808);
    xsi_vlogvar_wait_assign_value(t6, t12, 0, 0, 32, 0LL);
    goto LAB36;

LAB34:    xsi_set_current_line(78, ng0);
    t6 = (t0 + 3448U);
    t12 = *((char **)t6);
    t6 = (t0 + 4808);
    xsi_vlogvar_wait_assign_value(t6, t12, 0, 0, 32, 0LL);
    goto LAB36;

LAB39:    t14 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB40;

LAB41:    xsi_set_current_line(82, ng0);
    t29 = (t0 + 1528U);
    t30 = *((char **)t29);
    t29 = (t0 + 4488);
    xsi_vlogvar_wait_assign_value(t29, t30, 0, 0, 32, 0LL);
    goto LAB43;

LAB46:    t14 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB47;

LAB48:    xsi_set_current_line(87, ng0);
    t29 = (t0 + 1688U);
    t30 = *((char **)t29);
    memcpy(t32, t30, 8);
    t29 = (t0 + 4648);
    xsi_vlogvar_wait_assign_value(t29, t32, 0, 0, 32, 0LL);
    goto LAB50;

LAB53:    t14 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB54;

LAB55:    xsi_set_current_line(94, ng0);
    t29 = (t0 + 2008U);
    t30 = *((char **)t29);
    t29 = (t0 + 4168);
    xsi_vlogvar_wait_assign_value(t29, t30, 0, 0, 5, 0LL);
    goto LAB57;

}


extern void work_m_00000000000127929172_3666345988_init()
{
	static char *pe[] = {(void *)Always_59_0};
	xsi_register_didat("work_m_00000000000127929172_3666345988", "isim/CPU_Test_isim_beh.exe.sim/work/m_00000000000127929172_3666345988.didat");
	xsi_register_executes(pe);
}
