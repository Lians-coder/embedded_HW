# 2.9 STM32 Blink

## Schematics

[KiCad schematic](https://github.com/Lians-coder/embedded_HW/blob/main/2.9_stm_blink/stm_blink.kicad_sch)

## Project configuration

**CubeMX** [file](https://github.com/Lians-coder/embedded_HW/blob/main/2.9_stm_blink/stm_blink.ioc).  

## Code

### Changes

In **main.c**:  

```c
#include "app.h"

int main(void)
{
  // ... //
  setup();
  while(1)
  {
    loop():
  }
  // ... //
}
```

### App

[app.h](https://github.com/Lians-coder/embedded_HW/blob/main/2.9_stm_blink/stm_blink/include/app.h)  
[app.c](https://github.com/Lians-coder/embedded_HW/blob/main/2.9_stm_blink/stm_blink/src/app.c)  

## Result

[Video](https://drive.google.com/file/d/1tU4LZPMx50c8KyTxmwCpjYlLnnHl4Nkv/view?usp=sharing) of working project.  
