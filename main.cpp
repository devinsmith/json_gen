// Copyright (c) 2025 Devn Smith <devin@devinsmith.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cJSON.h> // For JSON parsing and construction
                   //
using std::cout;
using std::cerr;

static void handle_json(const cJSON* obj, const std::string& name)
{
  if (cJSON_IsObject(obj)) {
    cout << "cJSON *" << name << " = cJSON_CreateObject();\n";
    cJSON* child = nullptr;
    cJSON_ArrayForEach(child, obj) {
      std::string child_name = name + "_" + child->string;
      handle_json(child, child_name);
      cout << "cJSON_AddItemToObject(" << name << ", \"" << child->string << "\", " << child_name << ");\n";
    }
  } else if (cJSON_IsArray(obj)) {
    cout << "cJSON *" << name << " = cJSON_CreateArray();\n";
    int index = 0;
    cJSON* item = nullptr;
    cJSON_ArrayForEach(item, obj) {
      std::string child_name = name + "_item" + std::to_string(index++);
      handle_json(item, child_name);
      cout << "cJSON_AddItemToArray(" << name << ", " << child_name << ");\n";
    }
  } else if (cJSON_IsString(obj)) {
     cout << "cJSON *" << name << " = cJSON_CreateString(\"" << cJSON_GetStringValue(obj) << "\");\n";
  } else if (cJSON_IsNumber(obj)) {
     cout << "cJSON *" << name << " = cJSON_CreateNumber(" << obj->valuedouble << ");\n";
  } else if (cJSON_IsBool(obj)) {
     cout << "cJSON *" << name << " = cJSON_CreateBool(" << (cJSON_IsTrue(obj) ? "1" : "0") << ");\n";
  } else if (cJSON_IsNull(obj)) {
     cout << "cJSON *" << name << " = cJSON_CreateNull();\n";
  }
}

// Function to generate the C code to create the JSON
void generate_c_code(const cJSON* json_obj, const std::string& var_name)
{
    handle_json(json_obj, var_name);

    cout << "cJSON_Delete(" << var_name << ");\n";
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_json>\n";
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Error: Could not open input file " << argv[1] << '\n';
        return 1;
    }

    std::string json_content((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    cJSON* json_obj = cJSON_Parse(json_content.c_str());
    if (!json_obj) {
        cerr << "Error: Failed to parse JSON - " << cJSON_GetErrorPtr() << std::endl;
        return 1;
    }

    generate_c_code(json_obj, "root");

    cJSON_Delete(json_obj);
    return 0;
}

