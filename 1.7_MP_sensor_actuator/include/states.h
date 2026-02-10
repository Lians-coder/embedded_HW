enum class St
{
  NEED_CALIB,       // start - WHITE fast blinking, press button to start calibration process
  NEED_MIN,         // CYAN stable, cover LDR and press button - min set
  NEED_MAX,         // ORANGE stable, expose to full light and press button - max set
  SUCCESS_CALIB,    // n medium GREEN blinks - successfull completion of calibration
  REGULAR,          // ful range color changes - regular functioning
  ERROR_ABOVE,      // RED fast blinking, above max voltage value (max - 3.3)
  ERROR_BELOW,      // BLUE fast blinking, below min voltage value (0 - min)
  ERROR_UNKNOWN,    // PURPLE fast blinking (voltage <0, > 3.3; OR another problem)
  RESET_COMPLETED,  // n medium CYAN blinks - recover from error above/below on button latched to start over
  FORCE_CALIB,      // from any other states on button latched - n medium BLUE blinks, then NEED_CALIB
};

St currentState = St::NEED_CALIB;
