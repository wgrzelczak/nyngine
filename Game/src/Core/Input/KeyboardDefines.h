#pragma once
#include <GLFW\glfw3.h>

// clang-format off
#define NY_KEY_UNKNOWN          GLFW_KEY_UNKNOWN

#define NY_KEY_SPACE            GLFW_KEY_SPACE
#define NY_KEY_APOSTROPHE       GLFW_KEY_APOSTROPHE
#define NY_KEY_COMMA            GLFW_KEY_COMMA
#define NY_KEY_MINUS            GLFW_KEY_MINUS
#define NY_KEY_PERIOD           GLFW_KEY_PERIOD
#define NY_KEY_SLASH            GLFW_KEY_SLASH
#define NY_KEY_0                GLFW_KEY_0
#define NY_KEY_1                GLFW_KEY_1
#define NY_KEY_2                GLFW_KEY_2
#define NY_KEY_3                GLFW_KEY_3
#define NY_KEY_4                GLFW_KEY_4
#define NY_KEY_5                GLFW_KEY_5
#define NY_KEY_6                GLFW_KEY_6
#define NY_KEY_7                GLFW_KEY_7
#define NY_KEY_8                GLFW_KEY_8
#define NY_KEY_9                GLFW_KEY_9
#define NY_KEY_SEMICOLON        GLFW_KEY_SEMICOLON
#define NY_KEY_EQUAL            GLFW_KEY_EQUAL
#define NY_KEY_A                GLFW_KEY_A
#define NY_KEY_B                GLFW_KEY_B
#define NY_KEY_C                GLFW_KEY_C
#define NY_KEY_D                GLFW_KEY_D
#define NY_KEY_E                GLFW_KEY_E
#define NY_KEY_F                GLFW_KEY_F
#define NY_KEY_G                GLFW_KEY_G
#define NY_KEY_H                GLFW_KEY_H
#define NY_KEY_I                GLFW_KEY_I
#define NY_KEY_J                GLFW_KEY_J
#define NY_KEY_K                GLFW_KEY_K
#define NY_KEY_L                GLFW_KEY_L
#define NY_KEY_M                GLFW_KEY_M
#define NY_KEY_N                GLFW_KEY_N
#define NY_KEY_O                GLFW_KEY_O
#define NY_KEY_P                GLFW_KEY_P
#define NY_KEY_Q                GLFW_KEY_Q
#define NY_KEY_R                GLFW_KEY_R
#define NY_KEY_S                GLFW_KEY_S
#define NY_KEY_T                GLFW_KEY_T
#define NY_KEY_U                GLFW_KEY_U
#define NY_KEY_V                GLFW_KEY_V
#define NY_KEY_W                GLFW_KEY_W
#define NY_KEY_X                GLFW_KEY_X
#define NY_KEY_Y                GLFW_KEY_Y
#define NY_KEY_Z                GLFW_KEY_Z
#define NY_KEY_LEFT_BRACKET     GLFW_KEY_LEFT_BRACKET
#define NY_KEY_BACKSLASH        GLFW_KEY_BACKSLASH
#define NY_KEY_RIGHT_BRACKET    GLFW_KEY_RIGHT_BRACKET
#define NY_KEY_GRAVE_ACCENT     GLFW_KEY_GRAVE_ACCENT
#define NY_KEY_WORLD_1          GLFW_KEY_WORLD_1
#define NY_KEY_WORLD_2          GLFW_KEY_WORLD_2


#define NY_KEY_ESCAPE           GLFW_KEY_ESCAPE
#define NY_KEY_ENTER            GLFW_KEY_ENTER
#define NY_KEY_TAB              GLFW_KEY_TAB
#define NY_KEY_BACKSPACE        GLFW_KEY_BACKSPACE
#define NY_KEY_INSERT           GLFW_KEY_INSERT
#define NY_KEY_DELETE           GLFW_KEY_DELETE
#define NY_KEY_RIGHT            GLFW_KEY_RIGHT
#define NY_KEY_LEFT             GLFW_KEY_LEFT
#define NY_KEY_DOWN             GLFW_KEY_DOWN
#define NY_KEY_UP               GLFW_KEY_UP
#define NY_KEY_PAGE_UP          GLFW_KEY_PAGE_UP
#define NY_KEY_PAGE_DOWN        GLFW_KEY_PAGE_DOWN
#define NY_KEY_HOME             GLFW_KEY_HOME
#define NY_KEY_END              GLFW_KEY_END
#define NY_KEY_CAPS_LOCK        GLFW_KEY_CAPS_LOCK
#define NY_KEY_SCROLL_LOCK      GLFW_KEY_SCROLL_LOCK
#define NY_KEY_NUM_LOCK         GLFW_KEY_NUM_LOCK
#define NY_KEY_PRINT_SCREEN     GLFW_KEY_PRINT_SCREEN
#define NY_KEY_PAUSE            GLFW_KEY_PAUSE
#define NY_KEY_F1               GLFW_KEY_F1
#define NY_KEY_F2               GLFW_KEY_F2
#define NY_KEY_F3               GLFW_KEY_F3
#define NY_KEY_F4               GLFW_KEY_F4
#define NY_KEY_F5               GLFW_KEY_F5
#define NY_KEY_F6               GLFW_KEY_F6
#define NY_KEY_F7               GLFW_KEY_F7
#define NY_KEY_F8               GLFW_KEY_F8
#define NY_KEY_F9               GLFW_KEY_F9
#define NY_KEY_F10              GLFW_KEY_F10
#define NY_KEY_F11              GLFW_KEY_F11
#define NY_KEY_F12              GLFW_KEY_F12
#define NY_KEY_F13              GLFW_KEY_F13
#define NY_KEY_F14              GLFW_KEY_F14
#define NY_KEY_F15              GLFW_KEY_F15
#define NY_KEY_F16              GLFW_KEY_F16
#define NY_KEY_F17              GLFW_KEY_F17
#define NY_KEY_F18              GLFW_KEY_F18
#define NY_KEY_F19              GLFW_KEY_F19
#define NY_KEY_F20              GLFW_KEY_F20
#define NY_KEY_F21              GLFW_KEY_F21
#define NY_KEY_F22              GLFW_KEY_F22
#define NY_KEY_F23              GLFW_KEY_F23
#define NY_KEY_F24              GLFW_KEY_F24
#define NY_KEY_F25              GLFW_KEY_F25
#define NY_KEY_KP_0             GLFW_KEY_KP_0
#define NY_KEY_KP_1             GLFW_KEY_KP_1
#define NY_KEY_KP_2             GLFW_KEY_KP_2
#define NY_KEY_KP_3             GLFW_KEY_KP_3
#define NY_KEY_KP_4             GLFW_KEY_KP_4
#define NY_KEY_KP_5             GLFW_KEY_KP_5
#define NY_KEY_KP_6             GLFW_KEY_KP_6
#define NY_KEY_KP_7             GLFW_KEY_KP_7
#define NY_KEY_KP_8             GLFW_KEY_KP_8
#define NY_KEY_KP_9             GLFW_KEY_KP_9
#define NY_KEY_KP_DECIMAL       GLFW_KEY_KP_DECIMAL
#define NY_KEY_KP_DIVIDE        GLFW_KEY_KP_DIVIDE
#define NY_KEY_KP_MULTIPLY      GLFW_KEY_KP_MULTIPLY
#define NY_KEY_KP_SUBTRACT      GLFW_KEY_KP_SUBTRACT
#define NY_KEY_KP_ADD           GLFW_KEY_KP_ADD
#define NY_KEY_KP_ENTER         GLFW_KEY_KP_ENTER
#define NY_KEY_KP_EQUAL         GLFW_KEY_KP_EQUAL
#define NY_KEY_LEFT_SHIFT       GLFW_KEY_LEFT_SHIFT
#define NY_KEY_LEFT_CONTROL     GLFW_KEY_LEFT_CONTROL
#define NY_KEY_LEFT_ALT         GLFW_KEY_LEFT_ALT
#define NY_KEY_LEFT_SUPER       GLFW_KEY_LEFT_SUPER
#define NY_KEY_RIGHT_SHIFT      GLFW_KEY_RIGHT_SHIFT
#define NY_KEY_RIGHT_CONTROL    GLFW_KEY_RIGHT_CONTROL
#define NY_KEY_RIGHT_ALT        GLFW_KEY_RIGHT_ALT
#define NY_KEY_RIGHT_SUPER      GLFW_KEY_RIGHT_SUPER
#define NY_KEY_MENU             GLFW_KEY_MENU
// clang-format on