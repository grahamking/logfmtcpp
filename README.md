**not ready yet**

# C++ logfmt parser

Build: `make` will build `liblogfmt.a` in the current directory.

Usage:
```
#include "logfmt.h"

string data {R"X(foo=bar a=14 baz="hello kitty" cool%story=bro f %^asdf)X"};
unordered_map<string, string> m;
logfmt::parse(data, m);
// m["foo"] == "bar", m["a"] == 14, m["f"] == "true" etc
```

The tests require gtest, Google's C++ testing framework.
