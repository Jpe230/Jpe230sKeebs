// Copyright 2021 Dasky (@daskygit)
// Copyright 2022 Jose Pablo Ramirez (@Jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE
