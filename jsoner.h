#ifndef JSONER_H__
#define JSONER_H__

typedef enum
{
    JSONER_NULL,
    JSONER_FALSE,
    JSONER_TRUE,
    JSONER_NUMBER,
    JSONER_STRING,
    JSONER_ARRAY,
    JSONER_OBJECT
} jsoner_type;

typedef struct
{
    jsoner_type type;
} jsoner_value;

enum
{
    JSONER_PARSE_OK = 0,
    JSONER_PARSE_EXPECT_VALUE,
    JSONER_PARSE_INVALID_VALUE,
    JSONER_PARSE_ROOT_NOT_SINGULAR // 确认json数据的根是否为单一
};

int jsoner_parse(jsoner_value *v, const char *json);

jsoner_type jsoner_get_type(const jsoner_value *v);

#endif /* JSONER_H__ */