#include <emojicode/runtime/Runtime.h>
#include <emojicode/s/Data.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <zstr.hpp>

extern "C" s::Data* decompress(s::Data* data) {
    std::stringstream ss;

    s::Data* output = s::Data::init();
    std::vector<char> chars;

    for(int i = 0; i < data->count; i++) {
        ss << data->data[i];
    }

    zstr::istream is(ss);

    const std::streamsize buff_size = 1 << 16;
    char* buff = new char[buff_size];
    while(true) {
        is.read(buff, buff_size);
        std::streamsize cnt = is.gcount();
        if(cnt == 0) break;
        for(int i = 0; i < cnt; i++) {
            chars.push_back(buff[i]);
        }
    }

    auto bytes = runtime::allocate<runtime::Byte>(chars.size());
    char* b = reinterpret_cast<char *>(bytes.get());

    memcpy(b,chars.data(), chars.size() * sizeof(char));
    output->count = chars.size();
    output->data = bytes;

    std::ofstream myfile;
    myfile.open("cpp.nbt");
    for(const auto &e : chars) myfile << e;
    myfile.close();

    delete [] buff;

    return output; 
}

extern "C" runtime::Integer fixByte(runtime::Byte b) {
    return static_cast<int64_t>(b);
}