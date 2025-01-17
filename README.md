# json\_gen

JSON code generation for C and C++. This tool process input JSON and generates
C code for using Dave Gamble's cJSON library to create the same JSON input.

The output is sent to stdout and should be redirected to a file.

# Dependencies

* cJSON
* C++11 compiler.
* Make

# Small Example

```json
{
  "test1": {
    "boolean": false,
    "property": null,
    "array": [
      { "abc": 1234,
        "def": "xyz"
      }
    ]
  }
}
```

```
cJSON *root = cJSON_CreateObject();
cJSON *root_test1 = cJSON_CreateObject();
cJSON *root_test1_boolean = cJSON_CreateBool(0);
cJSON_AddItemToObject(root_test1, "boolean", root_test1_boolean);
cJSON *root_test1_property = cJSON_CreateNull();
cJSON_AddItemToObject(root_test1, "property", root_test1_property);
cJSON *root_test1_array = cJSON_CreateArray();
cJSON *root_test1_array_item0 = cJSON_CreateObject();
cJSON *root_test1_array_item0_abc = cJSON_CreateNumber(1234);
cJSON_AddItemToObject(root_test1_array_item0, "abc", root_test1_array_item0_abc);
cJSON *root_test1_array_item0_def = cJSON_CreateString("xyz");
cJSON_AddItemToObject(root_test1_array_item0, "def", root_test1_array_item0_def);
cJSON_AddItemToArray(root_test1_array, root_test1_array_item0);
cJSON_AddItemToObject(root_test1, "array", root_test1_array);
cJSON_AddItemToObject(root, "test1", root_test1);
cJSON_Delete(root);
```

