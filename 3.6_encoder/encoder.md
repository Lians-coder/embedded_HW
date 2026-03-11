# 3.6 Encoder

## Schematic

[KiCad schematic](https://github.com/Lians-coder/embedded_HW/blob/main/3.6_encoder/encoder.kicad_sch)  

## Code

[main.cpp](https://github.com/Lians-coder/embedded_HW/blob/main/3.6_encoder/src/main.cpp)  

### Quadrature lookup table

> #### Direction
>
> - **CW:** `00` -> `01` -> `11` -> `10` -> `00`
> - **CCW:** `00` -> `10` -> `11` -> `01` -> `00`

| Last \ New | 00 | 01 | 10 | 11 |
| - | - | - | - | - |
| 00 | 0 | +1 | -1 | 0 |
| 01 | -1 | 0 | 0 | +1 |
| 10 | +1 | 0 | 0 | -1 |
| 11 | 0 | -1 | +1 | 0 |

## Result

### Output

<details>

<summary>Output for <strong>failure</strong></summary>

```txt
SAFE LOCKED
        Trial: 1
[4][4][1][2] 
WRONG PIN!
        Trial: 2
[8][2][3][5] 
WRONG PIN!
        Trial: 3
[3][1] 
RESET
        Trial: 3
[6][4][8][0] 
WRONG PIN!
You're out of all 3 trials!
ALARM!!!
```

</details>

<details>

<summary>Output for <strong>success</strong></summary>

```txt
SAFE LOCKED
        Trial: 1
[7][9][0]8
RESET
        Trial: 1
[8]4
RESET
[0][7][1][4] 
WRONG PIN!
        Trial: 2
 
RESET
        Trial: 2
[6][3] 
RESET
        Trial: 2
[7][9][0][6] 
WRONG PIN!
        Trial: 3
8
RESET
        Trial: 3
[7][9][0][3] 
SAFE OPENED!
```

</details>

### Video

[Video]()  
