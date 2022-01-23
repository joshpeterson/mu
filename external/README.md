# External depdendencies

The μ VM depends on these third-party libraries. The source code for each library
is committed directly to this repository to avoid the complexity of git submodules.

## Doctest

The code uses [Doctest](https://github.com/doctest/doctest) for unit testing and
documentation of expected behavior.

To update Doctest, get the latest version of its [header
file](https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h)
and copy it to `external/doctest/doctest.h` in this repository. A custom
`CMakeLists.txt` file in `external/doctest` ensure that it can be included in any
source file in the project using `#include <doctest.h>`.

## Fmt

The code uses [Fmt](https://fmt.dev) for string formatting.

To update Fmt, download the latest version from the site above, extract it, replace
all files in the `external/fmt` directory. The Fmt library uses CMake, so no
special CMake setup is required to use it with the code.
