#include "jsoner.h"
#include <assert.h>
#include <stdlib.h>

#define EXPECT(c, ch)             \
    do                            \
    {                             \
        assert(*c->json == (ch)); \
        c->json++;                \
    } while (0)

typedef struct
{
    const char *json;
} jsoner_context;

static void jsoner_parse_whitespace(jsoner_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static int jsoner_parse_null(jsoner_context *c, jsoner_value *v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return JSONER_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = JSONER_NULL;
    return JSONER_PARSE_OK;
}

static int jsoner_parse_value(jsoner_context *c, jsoner_value *v)
{
    switch (*c->json)
    {
    case 'n':
        return jsoner_parse_null(c, v);
    case '\0':
        return JSONER_PARSE_EXPECT_VALUE;
    default:
        return JSONER_PARSE_INVALID_VALUE;
    }
}

int jsoner_parse(jsoner_value *v, const char *json)
{
    jsoner_context c;
    assert(v != NULL);
    c.json = json;
    v->type = JSONER_NULL;
    jsoner_parse_whitespace(&c);
    return jsoner_parse_value(&c, v);
}

jsoner_type jsoner_get_type(const jsoner_value *v)
{
    assert(v != NULL);
    return v->type;
}