C++ logfmt parser

Usage:

	string data {R"X(foo=bar a=14 baz="hello kitty" cool%story=bro f %^asdf)X"};
	unordered_map<string, string> m;
	logfmt::parse(data, m);
	// Now m["foo"] == "bar", etc

The tests require gtest, Google's C++ testing framework.
