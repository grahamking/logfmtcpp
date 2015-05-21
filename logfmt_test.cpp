
#include <string>
#include <chrono>

#include "gtest/gtest.h"
#include "logfmt.h"

using namespace std;

TEST(LogfmtTest, ParseMeasure) {
	string data {R"X(measure.test=1 measure.foo=bar measure.time=2h measure="foo")X"};
	unordered_map<string, string> m;
	logfmt::parse(data, m);
	EXPECT_EQ(m.size(), 4);
	EXPECT_EQ(m["measure.test"], "1");
	EXPECT_EQ(m["measure"], "foo");
}

TEST(LogfmtTest, ParseExample) {
	string data {R"X(foo=bar a=14 baz="hello kitty" cool%story=bro f %^asdf)X"};
	unordered_map<string, string> m;
	logfmt::parse(data, m);
	EXPECT_EQ(m.size(), 6);
	EXPECT_EQ(m["foo"], "bar");
	EXPECT_EQ(m["a"], "14");
	EXPECT_EQ(m["baz"], "hello kitty");
	EXPECT_EQ(m["cool%story"], "bro");
	EXPECT_EQ(m["f"], "true");
	EXPECT_EQ(m["%^asdf"], "true");
}

TEST(LogfmtTest, Benchmark) {
	string data {R"X(measure.test=1 measure.foo=bar measure.time=2h measure="foo")X"};

	const unsigned int iterations = 100000;
	unordered_map<string, string> m;
	auto start = chrono::high_resolution_clock::now();
	for (auto i=0; i < iterations; ++i) {
		logfmt::parse(data, m);
	}
	auto end = chrono::high_resolution_clock::now();
	auto elapsed = end - start;
	auto nanos = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
	cout << nanos / iterations << " ns per iteration\n";
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
