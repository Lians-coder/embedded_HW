# 3.7 Refactoring

## Schematics

[KiCad](https://github.com/Lians-coder/embedded_HW/blob/main/3.7_MP_refactoring/servo_ldr.kicad_sch) shematics.  

## Code

[main.cpp](https://github.com/Lians-coder/embedded_HW/blob/main/3.7_MP_refactoring/src/main.cpp)  

## Result

### Output

<details>

<summary>ESP logs</summary>

```txt
I (3508) Servo: Angle: 170
I (3508) Servo: Pulse US: 2500  Duty: 511
I (3528) LDR: Raw ADC Value: 4095       Voltage Value: 3157 mV
I (3528) Servo: Angle: 170
I (3528) Servo: Pulse US: 2500  Duty: 511
I (3548) LDR: Raw ADC Value: 3988       Voltage Value: 3146 mV
I (3548) Servo: Angle: 170
I (3548) Servo: Pulse US: 2500  Duty: 511
I (3568) LDR: Raw ADC Value: 3769       Voltage Value: 3110 mV
I (3568) Servo: Angle: 170
I (3568) Servo: Pulse US: 2500  Duty: 511
I (3588) LDR: Raw ADC Value: 3559       Voltage Value: 3044 mV
I (3588) Servo: Angle: 170
I (3588) Servo: Pulse US: 2500  Duty: 511
I (3608) LDR: Raw ADC Value: 3355       Voltage Value: 2946 mV
I (3608) Servo: Angle: 167
I (3608) Servo: Pulse US: 2464  Duty: 504
I (3628) LDR: Raw ADC Value: 3174       Voltage Value: 2826 mV
I (3628) Servo: Angle: 160
I (3628) Servo: Pulse US: 2382  Duty: 487
I (3648) LDR: Raw ADC Value: 3013       Voltage Value: 2703 mV
I (3648) Servo: Angle: 153
I (3648) Servo: Pulse US: 2300  Duty: 470
I (3668) LDR: Raw ADC Value: 2867       Voltage Value: 2581 mV
I (3668) Servo: Angle: 147
I (3668) Servo: Pulse US: 2229  Duty: 456
I (3688) LDR: Raw ADC Value: 2719       Voltage Value: 2463 mV
I (3688) Servo: Angle: 140
I (3688) Servo: Pulse US: 2147  Duty: 439
I (3708) LDR: Raw ADC Value: 2591       Voltage Value: 2350 mV
I (3708) Servo: Angle: 134
I (3708) Servo: Pulse US: 2076  Duty: 425
I (3728) LDR: Raw ADC Value: 2460       Voltage Value: 2240 mV
I (3728) Servo: Angle: 128
I (3728) Servo: Pulse US: 2005  Duty: 410
I (3748) LDR: Raw ADC Value: 2331       Voltage Value: 2131 mV
I (3748) Servo: Angle: 122
I (3748) Servo: Pulse US: 1935  Duty: 396
I (3768) LDR: Raw ADC Value: 2213       Voltage Value: 2027 mV
I (3768) Servo: Angle: 117
I (3768) Servo: Pulse US: 1876  Duty: 384
I (3788) LDR: Raw ADC Value: 2089       Voltage Value: 1923 mV
I (3788) Servo: Angle: 111
I (3788) Servo: Pulse US: 1805  Duty: 369
I (3808) LDR: Raw ADC Value: 1967       Voltage Value: 1821 mV
I (3808) Servo: Angle: 106
I (3808) Servo: Pulse US: 1747  Duty: 357
I (3828) LDR: Raw ADC Value: 1839       Voltage Value: 1718 mV
I (3828) Servo: Angle: 100
I (3828) Servo: Pulse US: 1676  Duty: 343
I (3848) LDR: Raw ADC Value: 1707       Voltage Value: 1612 mV
I (3848) Servo: Angle: 94
I (3848) Servo: Pulse US: 1605  Duty: 328
I (3868) LDR: Raw ADC Value: 1571       Voltage Value: 1504 mV
I (3868) Servo: Angle: 88
I (3868) Servo: Pulse US: 1535  Duty: 314
I (3888) LDR: Raw ADC Value: 1423       Voltage Value: 1390 mV
I (3888) Servo: Angle: 82
I (3888) Servo: Pulse US: 1464  Duty: 299
I (3908) LDR: Raw ADC Value: 1268       Voltage Value: 1270 mV
I (3908) Servo: Angle: 76
I (3908) Servo: Pulse US: 1394  Duty: 285
I (3928) LDR: Raw ADC Value: 1122       Voltage Value: 1148 mV
I (3928) Servo: Angle: 69
I (3928) Servo: Pulse US: 1311  Duty: 268
I (3948) LDR: Raw ADC Value: 959        Voltage Value: 1021 mV
I (3948) Servo: Angle: 62
I (3948) Servo: Pulse US: 1229  Duty: 251
I (3968) LDR: Raw ADC Value: 793        Voltage Value: 890 mV
I (3968) Servo: Angle: 55
I (3968) Servo: Pulse US: 1147  Duty: 234
I (3988) LDR: Raw ADC Value: 623        Voltage Value: 756 mV
I (3988) Servo: Angle: 48
I (3988) Servo: Pulse US: 1064  Duty: 217
I (4008) LDR: Raw ADC Value: 441        Voltage Value: 612 mV
I (4008) Servo: Angle: 40
I (4008) Servo: Pulse US: 970   Duty: 198
I (4028) LDR: Raw ADC Value: 279        Voltage Value: 468 mV
I (4028) Servo: Angle: 32
I (4028) Servo: Pulse US: 876   Duty: 179
I (4048) LDR: Raw ADC Value: 123        Voltage Value: 323 mV
I (4048) Servo: Angle: 24
I (4048) Servo: Pulse US: 782   Duty: 160
I (4068) LDR: Raw ADC Value: 0  Voltage Value: 187 mV
I (4068) Servo: Angle: 17
I (4068) Servo: Pulse US: 700   Duty: 143
I (4088) LDR: Raw ADC Value: 0  Voltage Value: 90 mV
I (4088) Servo: Angle: 12
I (4088) Servo: Pulse US: 641   Duty: 131
I (4108) LDR: Raw ADC Value: 0  Voltage Value: 27 mV
I (4108) Servo: Angle: 10
I (4108) Servo: Pulse US: 617   Duty: 126
I (4128) LDR: Raw ADC Value: 0  Voltage Value: 0 mV
I (4128) Servo: Angle: 10
I (4128) Servo: Pulse US: 617   Duty: 126
I (4148) LDR: Raw ADC Value: 0  Voltage Value: 0 mV

[...]

I (4448) Servo: Angle: 10
I (4448) Servo: Pulse US: 617   Duty: 126
I (4468) LDR: Raw ADC Value: 0  Voltage Value: 0 mV
I (4468) Servo: Angle: 10
I (4468) Servo: Pulse US: 617   Duty: 126
I (4488) LDR: Raw ADC Value: 19 Voltage Value: 4 mV
I (4488) Servo: Angle: 10
I (4488) Servo: Pulse US: 617   Duty: 126
I (4508) LDR: Raw ADC Value: 105        Voltage Value: 27 mV
I (4508) Servo: Angle: 10
I (4508) Servo: Pulse US: 617   Duty: 126
I (4528) LDR: Raw ADC Value: 229        Voltage Value: 78 mV
I (4528) Servo: Angle: 11
I (4528) Servo: Pulse US: 629   Duty: 128
I (4548) LDR: Raw ADC Value: 350        Voltage Value: 156 mV
I (4548) Servo: Angle: 15
I (4548) Servo: Pulse US: 676   Duty: 138
I (4568) LDR: Raw ADC Value: 470        Voltage Value: 255 mV
I (4568) Servo: Angle: 21
I (4568) Servo: Pulse US: 747   Duty: 152
I (4588) LDR: Raw ADC Value: 588        Voltage Value: 361 mV
I (4588) Servo: Angle: 26
I (4588) Servo: Pulse US: 805   Duty: 164
I (4608) LDR: Raw ADC Value: 703        Voltage Value: 463 mV
I (4608) Servo: Angle: 32
I (4608) Servo: Pulse US: 876   Duty: 179
I (4628) LDR: Raw ADC Value: 842        Voltage Value: 567 mV
I (4628) Servo: Angle: 38
I (4628) Servo: Pulse US: 947   Duty: 193
I (4648) LDR: Raw ADC Value: 981        Voltage Value: 675 mV
I (4648) Servo: Angle: 43
I (4648) Servo: Pulse US: 1005  Duty: 205
I (4668) LDR: Raw ADC Value: 1127       Voltage Value: 788 mV
I (4668) Servo: Angle: 50
I (4668) Servo: Pulse US: 1088  Duty: 222
I (4688) LDR: Raw ADC Value: 1295       Voltage Value: 911 mV
I (4688) Servo: Angle: 56
I (4688) Servo: Pulse US: 1158  Duty: 237
I (4708) LDR: Raw ADC Value: 1460       Voltage Value: 1039 mV
I (4708) Servo: Angle: 63
I (4708) Servo: Pulse US: 1241  Duty: 254
I (4728) LDR: Raw ADC Value: 1615       Voltage Value: 1171 mV
I (4728) Servo: Angle: 70
I (4728) Servo: Pulse US: 1323  Duty: 270
I (4748) LDR: Raw ADC Value: 1780       Voltage Value: 1308 mV
I (4748) Servo: Angle: 78
I (4748) Servo: Pulse US: 1417  Duty: 290
I (4768) LDR: Raw ADC Value: 1943       Voltage Value: 1443 mV
I (4768) Servo: Angle: 85
I (4768) Servo: Pulse US: 1500  Duty: 307
I (4788) LDR: Raw ADC Value: 2104       Voltage Value: 1578 mV
I (4788) Servo: Angle: 92
I (4788) Servo: Pulse US: 1582  Duty: 323
I (4808) LDR: Raw ADC Value: 2228       Voltage Value: 1707 mV
I (4808) Servo: Angle: 99
I (4808) Servo: Pulse US: 1664  Duty: 340
I (4828) LDR: Raw ADC Value: 2318       Voltage Value: 1819 mV
I (4828) Servo: Angle: 105
I (4828) Servo: Pulse US: 1735  Duty: 355
I (4848) LDR: Raw ADC Value: 2391       Voltage Value: 1913 mV
I (4848) Servo: Angle: 111
I (4848) Servo: Pulse US: 1805  Duty: 369
I (4868) LDR: Raw ADC Value: 2474       Voltage Value: 1990 mV
I (4868) Servo: Angle: 115
I (4868) Servo: Pulse US: 1852  Duty: 379
I (4888) LDR: Raw ADC Value: 2557       Voltage Value: 2058 mV
I (4888) Servo: Angle: 118
I (4888) Servo: Pulse US: 1888  Duty: 386
I (4908) LDR: Raw ADC Value: 2664       Voltage Value: 2129 mV
I (4908) Servo: Angle: 122
I (4908) Servo: Pulse US: 1935  Duty: 396
I (4928) LDR: Raw ADC Value: 2739       Voltage Value: 2200 mV
I (4928) Servo: Angle: 126
I (4928) Servo: Pulse US: 1982  Duty: 405
I (4948) LDR: Raw ADC Value: 2846       Voltage Value: 2274 mV
I (4948) Servo: Angle: 130
I (4948) Servo: Pulse US: 2029  Duty: 415
I (4968) LDR: Raw ADC Value: 2924       Voltage Value: 2347 mV
I (4968) Servo: Angle: 134
I (4968) Servo: Pulse US: 2076  Duty: 425
I (4988) LDR: Raw ADC Value: 3046       Voltage Value: 2422 mV
I (4988) Servo: Angle: 138
I (4988) Servo: Pulse US: 2123  Duty: 434
I (5008) LDR: Raw ADC Value: 3183       Voltage Value: 2506 mV
I (5008) Servo: Angle: 143
I (5008) Servo: Pulse US: 2182  Duty: 446
I (5028) LDR: Raw ADC Value: 3349       Voltage Value: 2599 mV
I (5028) Servo: Angle: 148
I (5028) Servo: Pulse US: 2241  Duty: 458
I (5048) LDR: Raw ADC Value: 3496       Voltage Value: 2700 mV
I (5048) Servo: Angle: 153
I (5048) Servo: Pulse US: 2300  Duty: 470
I (5068) LDR: Raw ADC Value: 3687       Voltage Value: 2807 mV
I (5068) Servo: Angle: 159
I (5068) Servo: Pulse US: 2370  Duty: 485
I (5088) LDR: Raw ADC Value: 3803       Voltage Value: 2903 mV
I (5088) Servo: Angle: 164
I (5088) Servo: Pulse US: 2429  Duty: 497
I (5108) LDR: Raw ADC Value: 3947       Voltage Value: 2988 mV
I (5108) Servo: Angle: 169
I (5108) Servo: Pulse US: 2488  Duty: 509
I (5128) LDR: Raw ADC Value: 4095       Voltage Value: 3063 mV
I (5128) Servo: Angle: 170
I (5128) Servo: Pulse US: 2500  Duty: 511
I (5148) LDR: Raw ADC Value: 4095       Voltage Value: 3110 mV
I (5148) Servo: Angle: 170
I (5148) Servo: Pulse US: 2500  Duty: 511
I (5168) LDR: Raw ADC Value: 4095       Voltage Value: 3142 mV
I (5168) Servo: Angle: 170
I (5168) Servo: Pulse US: 2500  Duty: 511
I (5188) LDR: Raw ADC Value: 4095       Voltage Value: 3157 mV
I (5188) Servo: Angle: 170
I (5188) Servo: Pulse US: 2500  Duty: 511
I (5208) LDR: Raw ADC Value: 4095       Voltage Value: 3157 mV
I (5208) Servo: Angle: 170
I (5208) Servo: Pulse US: 2500  Duty: 511
I (5228) LDR: Raw ADC Value: 4095       Voltage Value: 3157 mV
I (5228) Servo: Angle: 170
I (5228) Servo: Pulse US: 2500  Duty: 511
I (5248) LDR: Raw ADC Value: 4095       Voltage Value: 3157 mV
I (5248) Servo: Angle: 170
I (5248) Servo: Pulse US: 2500  Duty: 511
I (5268) LDR: Raw ADC Value: 4095       Voltage Value: 3157 mV
I (5268) Servo: Angle: 170
I (5268) Servo: Pulse US: 2500  Duty: 511
I (5288) LDR: Raw ADC Value: 4095       Voltage Value: 3157 mV
I (5288) Servo: Angle: 170
I (5288) Servo: Pulse US: 2500  Duty: 511
I (5308) LDR: Raw ADC Value: 4059       Voltage Value: 3153 mV
I (5308) Servo: Angle: 170
I (5308) Servo: Pulse US: 2500  Duty: 511
I (5328) LDR: Raw ADC Value: 3849       Voltage Value: 3127 mV
I (5328) Servo: Angle: 170
I (5328) Servo: Pulse US: 2500  Duty: 511
I (5348) LDR: Raw ADC Value: 3641       Voltage Value: 3074 mV
I (5348) Servo: Angle: 170
I (5348) Servo: Pulse US: 2500  Duty: 511
I (5368) LDR: Raw ADC Value: 3439       Voltage Value: 2990 mV
I (5368) Servo: Angle: 169
I (5368) Servo: Pulse US: 2488  Duty: 509
I (5388) LDR: Raw ADC Value: 3253       Voltage Value: 2877 mV
I (5388) Servo: Angle: 163
I (5388) Servo: Pulse US: 2417  Duty: 494
I (5408) LDR: Raw ADC Value: 3067       Voltage Value: 2753 mV
I (5408) Servo: Angle: 156
I (5408) Servo: Pulse US: 2335  Duty: 478
I (5428) LDR: Raw ADC Value: 2909       Voltage Value: 2627 mV
I (5428) Servo: Angle: 149
I (5428) Servo: Pulse US: 2252  Duty: 461
I (5448) LDR: Raw ADC Value: 2733       Voltage Value: 2497 mV
I (5448) Servo: Angle: 142
I (5448) Servo: Pulse US: 2170  Duty: 444
I (5468) LDR: Raw ADC Value: 2570       Voltage Value: 2367 mV
I (5468) Servo: Angle: 135
I (5468) Servo: Pulse US: 2088  Duty: 427
I (5488) LDR: Raw ADC Value: 2431       Voltage Value: 2241 mV
I (5488) Servo: Angle: 128
I (5488) Servo: Pulse US: 2005  Duty: 410
I (5508) LDR: Raw ADC Value: 2319       Voltage Value: 2122 mV
I (5508) Servo: Angle: 122
I (5508) Servo: Pulse US: 1935  Duty: 396
I (5528) LDR: Raw ADC Value: 2227       Voltage Value: 2018 mV
I (5528) Servo: Angle: 116
I (5528) Servo: Pulse US: 1864  Duty: 381
I (5548) LDR: Raw ADC Value: 2167       Voltage Value: 1934 mV
I (5548) Servo: Angle: 112
I (5548) Servo: Pulse US: 1817  Duty: 372
I (5568) LDR: Raw ADC Value: 2125       Voltage Value: 1871 mV
I (5568) Servo: Angle: 108
I (5568) Servo: Pulse US: 1770  Duty: 362
I (5588) LDR: Raw ADC Value: 2108       Voltage Value: 1826 mV
I (5588) Servo: Angle: 106
I (5588) Servo: Pulse US: 1747  Duty: 357
I (5608) LDR: Raw ADC Value: 2108       Voltage Value: 1801 mV
I (5608) Servo: Angle: 104
I (5608) Servo: Pulse US: 1723  Duty: 352
I (5628) LDR: Raw ADC Value: 2134       Voltage Value: 1795 mV
I (5628) Servo: Angle: 104
I (5628) Servo: Pulse US: 1723  Duty: 352
I (5648) LDR: Raw ADC Value: 2198       Voltage Value: 1810 mV
I (5648) Servo: Angle: 105
I (5648) Servo: Pulse US: 1735  Duty: 355
I (5668) LDR: Raw ADC Value: 2279       Voltage Value: 1846 mV
I (5668) Servo: Angle: 107
I (5668) Servo: Pulse US: 1758  Duty: 359
I (5688) LDR: Raw ADC Value: 2381       Voltage Value: 1903 mV
I (5688) Servo: Angle: 110
I (5688) Servo: Pulse US: 1794  Duty: 367
I (5708) LDR: Raw ADC Value: 2485       Voltage Value: 1976 mV
I (5708) Servo: Angle: 114
I (5708) Servo: Pulse US: 1841  Duty: 376
I (5728) LDR: Raw ADC Value: 2617       Voltage Value: 2062 mV
I (5728) Servo: Angle: 119
I (5728) Servo: Pulse US: 1900  Duty: 389
I (5748) LDR: Raw ADC Value: 2749       Voltage Value: 2158 mV
I (5748) Servo: Angle: 124
I (5748) Servo: Pulse US: 1958  Duty: 400
I (5768) LDR: Raw ADC Value: 2910       Voltage Value: 2264 mV
I (5768) Servo: Angle: 130
I (5768) Servo: Pulse US: 2029  Duty: 415
I (5788) LDR: Raw ADC Value: 3043       Voltage Value: 2375 mV
I (5788) Servo: Angle: 136
I (5788) Servo: Pulse US: 2100  Duty: 429
I (5808) LDR: Raw ADC Value: 3207       Voltage Value: 2488 mV
I (5808) Servo: Angle: 142
I (5808) Servo: Pulse US: 2170  Duty: 444
I (5828) LDR: Raw ADC Value: 3345       Voltage Value: 2600 mV
I (5828) Servo: Angle: 148
I (5828) Servo: Pulse US: 2241  Duty: 458
I (5848) LDR: Raw ADC Value: 3503       Voltage Value: 2704 mV
I (5848) Servo: Angle: 153
I (5848) Servo: Pulse US: 2300  Duty: 470
I (5868) LDR: Raw ADC Value: 3645       Voltage Value: 2805 mV
I (5868) Servo: Angle: 159
I (5868) Servo: Pulse US: 2370  Duty: 485
I (5888) LDR: Raw ADC Value: 3783       Voltage Value: 2895 mV
I (5888) Servo: Angle: 164
```

</details>

### Video

[Video](https://drive.google.com/file/d/1VmAnRAhWsT0NWzg8gb7g7xAXOedm7G5u/view?usp=sharing) of working project.  
