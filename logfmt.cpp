
#include <string>
#include <unordered_map>
#include <iostream>
#include <chrono>

#include "logfmt.h"

using namespace std;

namespace logfmt {

const string default_value {"true"};
const bool debug{false};

void parse(const string& data, unordered_map<string, string>& m)
{
	if (debug) cout << data << "\n\n";
	unsigned int key_start = 0;
	unsigned int key_end = 0;
	unsigned int val_start = 0;
	unsigned int val_end = 0;
	bool is_key = true;
	bool in_quotes = false;
	bool in_key = false;
	bool in_value = false;
	char c = 0;
	for (unsigned int i=0; i<data.size(); ++i)
	{
		c = data[i];

		if (debug) {
			cout << i << " " << c << ": "
				<< "ks: " << key_start << " "
				<< "ke: " << key_end << " "
				<< "vs: " << val_start << " "
				<< "ve: " << val_end << " "
				<< "iq: " << in_quotes << " ";
		}

		if (is_key && c > ' ' && c != '"' && c != '=')
		{
			if (!in_key) {
				key_start = i;
				in_key=true;
			}
		}
		else if (c == '"')
		{
			if (in_quotes) {
				val_end = i;
			}
			in_quotes = !in_quotes;
		}
		else if (c == '=' && !in_quotes) {
			is_key = false;
			key_end = i;
		}
		else if (c == ' ' && !in_quotes) {
			if (val_end < val_start) {
				val_end = i;
			}
			if (key_end == 0) {
				key_end = key_start+1;
			}
			if (val_start == 0) {
				// empty value
				m.emplace(data.substr(key_start, key_end-key_start), "true");
				if (debug) {
					cout << "Added key: " << data.substr(key_start, key_end-key_start)
						<< " value: empty ";
				}
			} else {
				// normal case
				m.emplace(
						data.substr(key_start, key_end-key_start),
						data.substr(val_start, val_end-val_start)
				);
				if (debug) {
					cout << "Added key: " << data.substr(key_start, key_end-key_start)
						<< " value: " << data.substr(val_start, val_end-val_start);
				}
			}
			is_key = true;
			in_key = false;
			in_value = false;
			key_start = key_end = val_start = val_end = 0;
		}
		else {
			if (!in_value) {
				val_start = i;
				in_value = true;
			}
		}
		if (debug) {
			cout << '\n';
		}
	}

	// add last value
	if (key_end == 0) {
		key_end = data.size();
	}
	if (val_start == 0) {
		// empty value
		m.emplace(data.substr(key_start, key_end-key_start), "true");
		if (debug) {
			cout << "Added key: " << data.substr(key_start, key_end-key_start)
				<< " value: empty\n";
		}
	} else {
		// normal case
		m.emplace(
				data.substr(key_start, key_end-key_start),
				data.substr(val_start, val_end-val_start)
		);
		if (debug) {
			cout << "Added key: " << data.substr(key_start, key_end-key_start)
				<< " value: " << data.substr(val_start, val_end-val_start)
				<< '\n';
		}
	}
}

} // end namespace logfmt
/*
int main() {
	//string data {R"X(foo=bar a=14 baz="hello kitty" cool%story=bro f %^asdf)X"};
	string data {R"X(measure.test=1 measure.foo=bar measure.time=2h measure="foo")X"};

	const unsigned int iterations = 2000000;
	unordered_map<string, string> m;
	auto start = chrono::high_resolution_clock::now();
	for (auto i=0; i < iterations; ++i) {
		logfmt::parse(data, m);
	}
	auto end = chrono::high_resolution_clock::now();
	auto elapsed = end - start;
	auto nanos = chrono::duration_cast<chrono::nanoseconds>(elapsed).count();
	cout << nanos / iterations << " ns per iteration\n";
	for (auto& x : m ) { cout << x.first << ": " << x.second << '\n'; }
}
*/
