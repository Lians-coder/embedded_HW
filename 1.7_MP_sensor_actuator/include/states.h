enum class St
{
  NEED_CALIB,       // start - WHITE slow blinking, press button to start calibration process
  NEED_MIN,         // CYAN stable, cover LDR and press button - min set
  NEED_MAX,         // ORANGE stable, expose to full light and press button - max set
  SUCCESS_CALIB,    // n fast GREEN blinks - successfull completion of calibration
  REGULAR,          // ful range color changes - regular functioning
  ERROR_ABOVE,      // RED slow blinking, above max voltage value (max - 3.3)
  ERROR_BELOW,      // BLUE slow blinking, below min voltage value (0 - min)
  ERROR_UNKNOWN,    // PURPLE fast blinking (voltage <0, > 3.3; OR another problem)
  RESET_COMPLETED,  // n fast CYAN blinks - recover from error above/below on button latched to start over
  FORCE_CALIB,      // from any other states on button held - n fast BLUE blinks, then NEED_CALIB
};

St currentState = St::NEED_CALIB;
