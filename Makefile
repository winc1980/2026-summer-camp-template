# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

BLOCKSDS	?= /opt/blocksds/core

# User config

NAME		:= your_game
GAME_TITLE	:= Your Game
GAME_SUBTITLE	:= NDS Game Template

COMPDB := 1

# Source code paths
# -----------------

GFXDIRS		:= graphics

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile