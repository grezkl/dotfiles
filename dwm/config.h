/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2;         /* border pixel of windows */
static const unsigned int snap     = 32;        /* snap pixel */
static const unsigned int gaps     = 20;
static const unsigned int gappih   = gaps;      /* horiz inner gap between windows */
static const unsigned int gappiv   = gaps;      /* vert inner gap between windows */
static const unsigned int gappoh   = gaps;      /* horiz outer gap between windows and screen edge */
static const unsigned int gappov   = gaps;      /* vert outer gap between windows and screen edge */
static const int smartgaps         = 0;         /* 1 means no outer gap when there is only one window */
static const int showbar           = 1;         /* 0 means no bar */
static const int topbar            = 1;         /* 0 means bottom bar */
static const char *fonts[]         = {
    "SarasaMonoCL:style=Semibold:size=10", "FontAwesome5Free:style=Solid:size=9",
    "FontAwesome5Free:style=Regular:size=9", "FontAwesome5Brands:style=Regular:size=9"};
static const char dmenufont[] = "SarasaMonoCLSemibold:size=10";

static const char col_pink[]   = "#D7005F";
static const char col_blue[]   = "#00bbff";
static const char col_black[]  = "#1a1a1a";
static const char col_gray[]   = "#202020";
static const char col_cyan[]   = "#00ffff";
static const char col_green[]  = "#44ff00";
static const char col_white[]  = "#c0c0c0";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_pink, col_black, col_pink},
    [SchemeSel]  = {col_blue, col_gray, col_blue},
};

/* tagging */
static const char *tags[] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
// static const char *tags[] = { "Ⅰ", "Ⅱ", "Ⅲ", "Ⅳ", "Ⅴ", "Ⅵ", "Ⅶ", "Ⅷ", "Ⅸ" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
    { "feh",                    NULL,         NULL,        0,      1,     -1 },
    { "mpv",                    NULL,         NULL,        0,      1,     -1 },
    { "obs",                    NULL,         NULL,        0,      1,     -1 },
    { "qv2ray",                 NULL,         NULL,        0,      1,     -1 },
    { "qBittorrent",            NULL,         NULL,        0,      1,     -1 },
    { "Pcmanfm",                NULL,         NULL,        0,      1,     -1 },
    { "TelegramDesktop",        NULL,         NULL,        0,      1,     -1 },
    { "VirtualBox Manager",     NULL,         NULL,        0,      1,     -1 },
};

/* layout(s) */
static const float mfact     = 0.49; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[G]",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
// '[' and ']'
#define XK_bl XK_bracketleft
#define XK_br XK_bracketright
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_white, "-sb", col_cyan, "-sf", col_gray, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_r,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_r,      incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_r,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_n,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|AltMask,               XK_e,      quit,           {0} },
    
	// [patch] next prev tag
	{ MODKEY,                       XK_h,      view_adjacent, {.i = -1 } },
	{ MODKEY,                       XK_l,      view_adjacent, {.i = +1 } },

    // [patch] dwm-vanitygaps-20200610-f09418b.diff
 	{ MODKEY|Mod1Mask,              XK_t,      incrgaps,       {.i = +1 } },
 	{ MODKEY|Mod1Mask,              XK_y,      incrgaps,       {.i = -1 } },
 	{ MODKEY|Mod1Mask|ShiftMask,    XK_t,      incrogaps,      {.i = +1 } },
 	{ MODKEY|Mod1Mask|ShiftMask,    XK_y,      incrogaps,      {.i = -1 } },
 	{ MODKEY|Mod1Mask|ControlMask,  XK_t,      incrigaps,      {.i = +1 } },
 	{ MODKEY|Mod1Mask|ControlMask,  XK_y,      incrigaps,      {.i = -1 } },
 	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
 	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },

 	{ MODKEY|Mod1Mask,              XK_v,      incrihgaps,     {.i = +1 } },
 	{ MODKEY|Mod1Mask,              XK_b,      incrihgaps,     {.i = -1 } },
 	{ MODKEY|ControlMask,           XK_v,      incrivgaps,     {.i = +1 } },
 	{ MODKEY|ControlMask,           XK_b,      incrivgaps,     {.i = -1 } },
 	{ MODKEY|Mod1Mask|ShiftMask,    XK_v,      incrohgaps,     {.i = +1 } },
 	{ MODKEY|Mod1Mask|ShiftMask,    XK_b,      incrohgaps,     {.i = -1 } },
 	{ MODKEY|ShiftMask,             XK_v,      incrovgaps,     {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_b,      incrovgaps,     {.i = -1 } },

	{ MODKEY|AltMask,   XK_r,       spawn,   SHCMD("killall dwmstatus") },
	{ MODKEY|AltMask,   XK_q,       spawn,   SHCMD("pkill dwm") },
	{ MODKEY|ShiftMask, XK_Return,  spawn,   SHCMD("urxvt") },
	{ MODKEY,           XK_u,       spawn,   SHCMD("scrot -sbmpe 'mv $f ~/Downloads/screenshots/'")},
	{ MODKEY,           XK_i,       spawn,   SHCMD("scrot -ubmpe 'mv $f ~/Downloads/screenshots/'") },
	{ MODKEY,           XK_o,       spawn,   SHCMD("scrot -bmpe 'mv $f ~/Downloads/screenshots/'") },
	{ MODKEY|ShiftMask, XK_i,       spawn,   SHCMD("scrot -bmpq 100 -e 'mv $f ~/Downloads/screenshots/'") },
	{ MODKEY|ShiftMask, XK_o,       spawn,   SHCMD("scrot -bmpq 100 -cd 5 -e 'mv $f ~/Downloads/screenshots/'") },
	{ MODKEY|AltMask,   XK_p,       spawn,   SHCMD("i3lock -n -B picom --indicator -k --timecolor=\"D7005F\" --datecolor=\"D7005F\" --ringcolor=\"1a1a1a\" --keyhlcolor=\"D7005f\"") },

	{ MODKEY|ShiftMask,             XK_bl,     spawn,   SHCMD("amixer set Master playback 5-") },
	{ MODKEY|ShiftMask,             XK_br,     spawn,   SHCMD("amixer set Master playback 5+") },
	{ MODKEY|AltMask,               XK_bl,     spawn,   SHCMD("xbacklight -dec 5") },
	{ MODKEY|AltMask,               XK_br,     spawn,   SHCMD("xbacklight -inc 5") },
    { MODKEY|ControlMask,           XK_m,      spawn,   SHCMD("pactl set-sink-mute 0 toggle") },
	{ MODKEY,                       XK_z,      spawn,   SHCMD("mpc prev") },
	{ MODKEY,                       XK_c,      spawn,   SHCMD("mpc next") },
	{ MODKEY,                       XK_x,      spawn,   SHCMD("mpc toggle") },

	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 5") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 5") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("amixer set Master playback 5+") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("amixer set Master playback 5-") },
	{ 0, XF86XK_AudioMute,	        spawn,		SHCMD("pactl set-sink-mute 0 toggle") },
	{ 0, XF86XK_AudioPrev,		    spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		    spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioStop,		    spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioPlay,		    spawn,		SHCMD("mpc toggle") },
	
	// not work
	// amixer -q -D pulse set Master toggle
	// amixer set Master toggle
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
