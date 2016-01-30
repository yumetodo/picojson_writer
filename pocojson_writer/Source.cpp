#include "picojson.h"
#include <string>
#include <vector>
#include <array>
#include <fstream>
using namespace std;
using namespace picojson;
namespace detail {
	void create_utf8_with_bom_file(const char* filename) {
		std::ofstream file(filename, std::ios::out | std::ios::binary);
		constexpr unsigned char utf8[] = { 0xEF, 0xBB, 0xBF, '\0' };
		file << utf8;
	}
}
void write_utf8_with_bom_file(const char* filename, const picojson::value& tree) {
	detail::create_utf8_with_bom_file(filename);
	std::ofstream file(filename, std::ios::app | std::ios::binary);
	file << tree.serialize(true) << std::endl;
}
void write_utf8_with_bom_file(const std::string& filename, const picojson::value& tree) {
	write_utf8_with_bom_file(filename.c_str(), tree);
}

int main() {
	using picojson::value;
	using picojson::object;
	picojson::object data;
	data[u8"num"] = value(std::to_string(12));
	data[u8"str"] = value(u8"みりあ♡");
	picojson::object o;
	o.insert(make_pair(u8"Data", picojson::value(data)));
	value json = value(o);
	write_utf8_with_bom_file("test.json", json);
	return 0;
}
