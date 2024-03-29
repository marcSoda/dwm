#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#0087D7";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating  external */
	{ NULL,             NULL,       "ncspot",   1 << 8,       0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *passmenu_cmd[]  = { "passmenu", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browser_cmd[]  = { "qutebrowser", NULL };
static const char *screenshot_cmd[] = { "scrot", "/home/marc/working/screenshots/screenshot.jpg", NULL };
static const char *ncspot_cmd[]  = { "alacritty", "--title", "ncspot", "--command", "ncspot", NULL };
static const char *vlc_play_pause_cmd[] = { "playerctl", "-p", "vlc", "play-pause", "play-pause", NULL };
static const char *media_play_pause_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/spotify.sh", "play-pause", NULL };
static const char *media_next_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/spotify.sh", "next", NULL };
static const char *media_previous_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/spotify.sh", "previous", NULL };
static const char *volume_up_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/volume.sh", "up", NULL };
static const char *volume_down_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/volume.sh", "down", NULL };
static const char *volume_mute_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/volume.sh", "mute", NULL };
static const char *brightness_laptop_up_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/brightness.sh", "eDP1", "up", NULL };
static const char *brightness_laptop_down_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/brightness.sh", "eDP1", "down", NULL };
static const char *brightness_external_up_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/brightness.sh", "DP1", "up", NULL };
static const char *brightness_external_down_cmd[] = { "/home/marc/working/environment/dwm/addons/dunst_scripts/brightness.sh", "DP1", "down", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = passmenu_cmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = browser_cmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = ncspot_cmd } },
	{ MODKEY,                       XK_F11,    spawn,          {.v = screenshot_cmd } },
	{ MODKEY,                       XK_F1,     spawn,          {.v = volume_mute_cmd } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = volume_down_cmd } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = volume_up_cmd } },
	{ MODKEY,                       XK_F4,     spawn,          {.v = media_previous_cmd } },
	{ MODKEY,                       XK_F5,     spawn,          {.v = media_play_pause_cmd } },
	{ MODKEY,                       XK_F6,     spawn,          {.v = media_next_cmd } },
	{ MODKEY|ShiftMask,                 XK_F5,     spawn,          {.v = vlc_play_pause_cmd } },
	{ MODKEY,                       XK_Up,     spawn,          {.v = brightness_laptop_up_cmd } },
	{ MODKEY,                       XK_Down,   spawn,          {.v = brightness_laptop_down_cmd } },
	{ MODKEY|ShiftMask,             XK_Up,     spawn,          {.v = brightness_external_up_cmd } },
	{ MODKEY|ShiftMask,             XK_Down,   spawn,          {.v = brightness_external_down_cmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_x,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_j,      focusmon,       {.i = 1 } },
	{ MODKEY|ShiftMask,             XK_k,      focusmon,       {.i = 0 } },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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
