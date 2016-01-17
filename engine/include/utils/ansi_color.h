#ifndef _ANSI_COLOR_H_
#define _ANSI_COLOR_H_

#define ESC ""
#define CSI ESC + "["

/* 前景色 */

#define BLK "[30m" /* 黑色 */
#define RED "[31m" /* 红色 */
#define GRN "[32m" /* 绿色 */
#define YEL "[33m" /* 黄色 */
#define BLU "[34m" /* 蓝色 */
#define MAG "[35m" /* 紫色 */
#define CYN "[36m" /* 青色 */
#define WHT "[37m" /* 白色 */

/* 加强前景色 */

#define HIR "[1;31m" /* 亮红 */
#define HIG "[1;32m" /* 亮绿 */
#define HIY "[1;33m" /* 亮黄 */
#define HIB "[1;34m" /* 亮蓝 */
#define HIM "[1;35m" /* 亮紫 */
#define HIC "[1;36m" /* 亮青 */
#define HIW "[1;37m" /* 亮白 */

/* 加强背景色 */

#define HBRED "[41;1m" /* 亮红 */
#define HBGRN "[42;1m" /* 亮绿 */
#define HBYEL "[43;1m" /* 亮黄 */
#define HBBLU "[44;1m" /* 亮蓝 */
#define HBMAG "[45;1m" /* 亮紫 */
#define HBCYN "[46;1m" /* 亮青 */
#define HBWHT "[47;1m" /* 亮白 */

/* 背景色 */

#define BBLK "[40m" /*黑色 */
#define BRED "[41m" /*红色 */
#define BGRN "[42m" /*绿色 */
#define BYEL "[43m" /* 黄色 */
#define BBLU "[44m" /*蓝色 */
#define BMAG "[45m" /*紫色 */
#define BCYN "[46m" /*青色 */
// #define BWHT "[47m" /* 白色 */

#define NOR "[2;37;0m" /* 返回原色 */
#define NOR2 "[0;37;0m" /* 返回原色 */

/* 新增的Ansi颜色定义字符。由 Gothic april 23,1993 */
/* 注意：这些*作符是为VT100终端设计的。 */
/* 在MUD中，它们可能不一定全部都能正常使用。 */

#define BOLD "[1m" /* 打开粗体 */
#define CLR "[2J" /* 清屏 */
#define HOME "[H" /* 发送光标到原处 */
#define REF CLR+HOME /* 清屏和清除光标 */
#define BIGTOP "#3" /* Dbl height characters, top half */
#define BIGBOT "#4" /* Dbl height characters, bottem half */
#define SAVEC "[s" /* Save cursor position */
#define REST "[u" /* Restore cursor to saved position */
//#define REVINDEX "M" /* Scroll screen in opposite direction */
#define SINGW "#5" /* Normal, single-width characters */
#define DBL "#6" /* Creates double-width characters */
#define FRTOP "[2;25r" /* 冻结首行 */
#define FRBOT "[1;24r" /* 冻结底部一行 */
#define UNFR "[r" /* 首行和底部一行解冻 */
#define BLINK "[5m" /* 不断闪亮模式 */
#define U "[4m" /* 下划线模式 */
#define REV "[7m" /* 打开反白模式 */
#define HIREV "[1,7m" /* 亮色彩反白显示 */


#endif


