# M5Unit - KMETERISO

## Overview

Contains case programs of M5Stack UNIT KMETERISO.

## Related Link

- [Docment - UNIT KMETERISO](https://docs.m5stack.com/en/unit/KMeterISO%20Unit)

## License

[UNIT KMETERISO - MIT](LICENSE)

---

## M5UnitUnified
Library for Unit KMETERISO using [M5UnitUnified](https://github.com/m5stack/M5UnitUnified).  
M5UnitUnified is a library for unified handling of various M5 units products.  
The M5UnitUnified version of the library is located under [src/unit](src/unit).

### Include file
```cpp
#include <M5UnitUnifiedKmeterISO.h> // For UnitUnified
//#include <M5UnitKmeterISO.h> // When using M5UnitUnified, do not use it at the same time as conventional libraries
```

### Required Libraries:

- [M5UnitUnified](https://github.com/m5stack/M5UnitUnified)
- [M5Utility](https://github.com/m5stack/M5Utility)
- [M5HAL](https://github.com/m5stack/M5HAL)

### Examples
See also [examples/UnitUnified](examples/UnitUnified)

### Doxygen document
If you want to generate documents on your local machine, execute the following command

```
bash docs/doxy.sh
```

It will output it under docs/html  
If you want to output Git commit hashes to html, do it for the git cloned folder.

#### Required
- [Doxyegn](https://www.doxygen.nl/)
- [pcregrep](https://formulae.brew.sh/formula/pcre2)
- [Git](https://git-scm.com/) (Output commit hash to html)
