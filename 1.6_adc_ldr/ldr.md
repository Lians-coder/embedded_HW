# Reading LDR with ADC

## Schematic

KiCad [schematic](https://github.com/Lians-coder/embedded_HW/blob/main/1.6_adc_ldr/ldr.kicad_sch).  

## Outputs

### Regular task outputs

[Code for this part](https://github.com/Lians-coder/embedded_HW/blob/main/1.6_adc_ldr/ldr.cpp)

| Level | Output |
| -- | -- |
| Covered LDR | Voltage (raw): 335<br>Voltage (mV): 289<br>Voltage (calc.): 360<br>Error: 24.57 % |
| Dim light | Voltage (raw): 1607<br>Voltage (mV): 1355<br>Voltage (calc.): 1727<br>Error: 27.45 % |
| Medium light | Voltage (raw): 2382<br>Voltage (mV): 2012<br>Voltage (calc.): 2561<br>Error: 27.29 % |
| Bright light | Voltage (raw): 3189<br>Voltage (mV): 2647<br>Voltage (calc.): 3429<br>Error: 29.54 % |
| Full light | Voltage (raw): 3916<br>Voltage (mV): 3086<br>Voltage (calc.): 4210<br>Error: 36.42 % |

### Optional tasks uotputs

Code for [this part](https://github.com/Lians-coder/embedded_HW/blob/main/1.6_adc_ldr/ldr_adc.cpp).  

For each experiment, the `adcAttenuation`, `adcResolution`, `maxADC` and `vRef` parameters were changed respectively.  

`maxADC` values, corresponding to the ADC resolution chosed:  

| Bits | Max range |
| -- | -- |
| 9 | 511 |
| 10 | 1023 |
| 11 | 2047 |
| 12 | 4095 |

`vRef` value depends on ADC attenuation as follows:

| Attenuation (dB) | Max input (V) |
| -- | -- |
| 0 | 0.8 |
| 2.5 | 1.1 |
| 6 | 1.5 |
| 11 | 3.3 |

#### ADC 0db attenuation and 9 bits resolution

| Level | Output |
| -- | -- |
| Covered LDR |-Voltage (raw): 149<br>Voltage (mV): 258<br>Voltage (calc.): <br>Error: 9.69 % |
| Dim light | Voltage (raw): 511<br>Voltage (mV): 985<br>Voltage (calc.): 800<br>Error: 18.78 % |
| Medium light | Voltage (raw): 511<br>Voltage (mV): 985<br>Voltage (calc.): 800<br>Error: 18.78 % |
| Bright light | Voltage (raw): 511<br>Voltage (mV): 985<br>Voltage (calc.): 800<br>Error: 18.78 % |
| Full light | Voltage (raw): 511<br>Voltage (mV): 985<br>Voltage (calc.): 800<br>Error: 18.78 % |

#### ADC_2_5db attenuation and 10 bits resolution

| Level | Output |
| -- | -- |
| Covered LDR | Voltage (raw): 137<br>Voltage (mV): 152<br>Voltage (calc.): 147<br>Error: 3.29 % |
| Dim light | Voltage (raw): 1023<br>Voltage (mV): 1305<br>Voltage (calc.): 1100<br>Error: 15.71 % |
| Medium light | Voltage (raw): 1023<br>Voltage (mV): 1305<br>Voltage (calc.): 1100<br>Error: 15.71 % |
| Bright light | Voltage (raw): 1023<br>Voltage (mV): 1305<br>Voltage (calc.): 1100<br>Error: 15.71 % |
| Full light | Voltage (raw): 1023<br>Voltage (mV): 1305<br>Voltage (calc.): 1100<br>Error: 15.71 % |

#### ADC_6db attenuation and 11 bits resolution

| Level | Output |
| -- | -- |
| Covered LDR | Voltage (raw): 270<br>Voltage (mV): 235<br>Voltage (calc.): 197<br>Error: 16.17 % |
| Dim light | Voltage (raw): 1333<br>Voltage (mV): 1201<br>Voltage (calc.): 976<br>Error: 18.73 % |
| Medium light | Voltage (raw): 2047<br>Voltage (mV): 1833<br>Voltage (calc.): 1500<br>Error: 18.17 % |
| Bright light | Voltage (raw): 2047<br>Voltage (mV): 1833<br>Voltage (calc.): 1500<br>Error: 18.17 % |
| Full light | Voltage (raw): 2047<br>Voltage (mV): 1833<br>Voltage (calc.): 1500<br>Error: 18.17 % |

#### ADC_11db attenuation and 9 bits resolution

| Level | Output |
| -- | -- |
| Covered LDR | Voltage (raw): 58<br>Voltage (mV): 402<br>Voltage (calc.): 374<br>Error: 6.97 % |
| Dim light | Voltage (raw): 151<br>Voltage (mV): 1029<br>Voltage (calc.): 975<br>Error: 5.25 % |
| Medium light | Voltage (raw): 213<br>Voltage (mV): 1449<br>Voltage (calc.): 1375<br>Error: 5.11 % |
| Bright light | Voltage (raw): 343<br>Voltage (mV): 2316<br>Voltage (calc.): 2215<br>Error: 4.36 % |
| Full light | Voltage (raw): 511<br>Voltage (mV): 3157<br>Voltage (calc.): 3300<br>Error: 4.53 % |

#### ADC_11db attenuation and 10 bits resolution

| Level | Output |
| -- | -- |
| Covered LDR |-Voltage (raw): 39<br>Voltage (mV): 134<br>Voltage (calc.): 125<br>Error: 6.72 % |
| Dim light | Voltage (raw): 283<br>Voltage (mV): 966<br>Voltage (calc.): 912<br>Error: 5.59 %0 |
| Medium light | Voltage (raw): 490<br>Voltage (mV): 1662<br>Voltage (calc.): 1580<br>Error: 4.93 % |
| Bright light | Voltage (raw): 715<br>Voltage (mV): 2404<br>Voltage (calc.): 2306<br>Error: 4.08 % |
| Full light | Voltage (raw): 1023<br>Voltage (mV): 3157<br>Voltage (calc.): 3300<br>Error: 4.53 % |

#### ADC_11db attenuation and 12 bits resolution

| Level | Output |
| -- | -- |
| Covered LDR | Voltage (raw): 213<br>Voltage (mV): 179<br>Voltage (calc.): 171<br>Error: 4.47 % |
| Dim light | Voltage (raw): 1291<br>Voltage (mV): 1098<br>Voltage (calc.): 1040<br>Error: 5.28 % |
| Medium light | Voltage (raw): 2105<br>Voltage (mV): 1779<br>Voltage (calc.): 1696<br>Error: 4.67 % |
| Bright light | Voltage (raw): 3095<br>Voltage (mV): 2581<br>Voltage (calc.): 2494<br>Error: 3.37 % |
| Full light | Voltage (raw): 3449<br>Voltage (mV): 2823<br>Voltage (calc.): 2779<br>Error: 1.56 % |

## Results

The cleanest and highest-quality results were obtained by using the maximum available ADC resolution.  
For lower input voltages, lower attenuation settings were sufficient, preserving finer detail.  
For higher voltage levels, greater attenuation was required to avoid saturation.  
