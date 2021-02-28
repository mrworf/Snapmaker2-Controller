/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfig.h"

//#if FAN_COUNT > 0

#include "../gcode.h"
#include "../../module/motion.h"
#include "../../module/temperature.h"

#if (MOTHERBOARD == BOARD_SNAPMAKER_2_0)
  #include "../../../../snapmaker/src/module/toolhead_3dp.h"
#endif

#if ENABLED(SINGLENOZZLE)
  #define _ALT_P active_extruder
  #define _CNT_P EXTRUDERS
#else
  #define _ALT_P MIN(active_extruder, FAN_COUNT - 1)
  #define _CNT_P FAN_COUNT
#endif

/**
 * M7-M8: Enable fan (coolant emulation)
 */
void GcodeSuite::M7_M8() {
  #if (MOTHERBOARD == BOARD_SNAPMAKER_2_0)
      printer1->SetFan(0, 255);
  #endif // (MOTHERBOARD == BOARD_SNAPMAKER_2_0)
}

/**
 * M9: Disable fan (coolant emulation)
 */
void GcodeSuite::M9() {
  #if (MOTHERBOARD == BOARD_SNAPMAKER_2_0)
    printer1->SetFan(0, 0);
  #endif
}

//#endif // FAN_COUNT > 0
