/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

/*
==============================================================================

    1. merge *.txt into cmd_ref.txt
    Run on linux and Windows

==============================================================================
*/

/*
==============================================================================

    Include File

==============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "icli_tool_platform.h"

/*
==============================================================================

    Constant and Macro

==============================================================================
*/
#define __T_E(...) \
    fprintf(stderr, "Error: "); \
    fprintf(stderr, __VA_ARGS__);

#define ___USAGE_PRINT() \
    printf("Usage : icli_cmd_txt <path> <list of *.txt>\n");\
    printf("    <path> : path of cmd_ref.txt and where <list of *.txt> are.\n");\

/*
==============================================================================

    Type Definition

==============================================================================
*/
typedef struct __tag_element {
    char                    *value_str;
    // next element
    struct __tag_element    *next;
} _tag_element_t;

/*
==============================================================================

    Static Variable

==============================================================================
*/
static char             g_line_buf[ICLI_STR_MAX_LEN + 1];
static char             *g_generate_path = NULL;
static char             *g_txt_file = NULL;
static _tag_element_t   *g_command = NULL;

/*
==============================================================================

    Static Function

==============================================================================
*/
/*
    input -
        f : file descriptor
    output -
        str_buf : buffer to store the line read
    return -
        icli_rc_t
*/
static i32 _line_read(FILE *f)
{
    i32     i;

    if ( fgets(g_line_buf, ICLI_STR_MAX_LEN, f) == NULL ) {
        // eof or failed
        return ICLI_RC_ERROR;
    }

    // remove \n, \r and space from tail
    i = mrdc_icli_str_len(g_line_buf);
    for ( --i;
          g_line_buf[i] == '\n' || g_line_buf[i] == '\r' || g_line_buf[i] == ' ';
          g_line_buf[i--] = 0 ) {
        ;
    }

    return ICLI_RC_OK;
}

#define ___t_ALLOC(t,str_len) \
    t = (_tag_element_t *)icli_malloc(sizeof(_tag_element_t));\
    if ( t == NULL ) {\
        __T_E("icli_malloc\n");\
        return FALSE;\
    }\
    memset(t, 0, sizeof(_tag_element_t));\
    t->value_str = (char *)icli_malloc(str_len);\
    if ( t->value_str == NULL ) {\
        __T_E("icli_malloc\n");\
        return FALSE;\
    }\
    memset(t->value_str, 0, str_len);

#define ___TAG_ELEMENT_CREATE()\
    ___t_ALLOC(t, mrdc_icli_str_len(g_line_buf)+1);\
    (void)mrdc_icli_str_cpy(t->value_str, g_line_buf);

#define ___TAG_ELEMENT_INSERT(element)\
    e = element;\
    if ( e ) {\
        for ( p = NULL; e != NULL; p = e, ___NEXT(e)) {\
            if ( mrdc_icli_str_cmp(e->value_str, t->value_str) == 1 ) {\
                break;\
            }\
        }\
        if ( e ) {\
            if ( p ) {\
                p->next = t;\
            } else {\
                element = t;\
            }\
            t->next = e;\
        } else {\
            p->next = t;\
        }\
    } else {\
        element = t;\
    }

#if 0 /* CP, 2012/09/13 15:22, try until ireg_file is generated */
#define __TRY_TIMES     10
#endif

static BOOL _txt_read(
    IN char     *txt_file
)
{
    FILE            *f;
    _tag_element_t  *t, *e, *p;

    /* open file as read/write */
#if 0 /* CP, 2012/09/13 15:22, try until ireg_file is generated */
    i32     i;

    for ( i = 0; i < __TRY_TIMES; ++i ) {
        f = fopen( txt_file, "r" );
        if ( f != NULL ) {
            break;
        } else {
#ifdef WIN32
            Sleep( 500 );
#else
            sleep( 1 );
#endif
        }
    }
#else
    f = fopen( txt_file, "r" );
#endif

    if ( f == NULL ) {
        __T_E("open %s\n", txt_file);
        return FALSE;
    }

    // read and insert
    while (_line_read(f) == ICLI_RC_OK) {
        // create
        ___TAG_ELEMENT_CREATE();

        // insert
        ___TAG_ELEMENT_INSERT( g_command );
    }

    /* close file */
    fclose( f );
    return TRUE;
}

static BOOL _txt_write(void)
{
    FILE            *f;
    _tag_element_t  *t;

    /* open file as read/write */
    f = fopen( g_txt_file, "w" );
    if ( f == NULL ) {
        __T_E("open %s\n", g_txt_file);
        return FALSE;
    }

    for ( t = g_command; t != NULL; ___NEXT(t) ) {
        fprintf(f, "%s\n", t->value_str);
    }

    /* close file */
    fclose( f );
    return TRUE;
}

/*
==============================================================================

    Public Function

==============================================================================
*/
int main(i32 argc, char *argv[])
{
    int     i;

    if ( argc < 3 ) {
        ___USAGE_PRINT();
        return ICLI_RC_ERROR;
    }

    // get g_generate_path
    i = mrdc_icli_str_len( argv[1] );
    g_generate_path = icli_malloc(i + 1);
    if ( g_generate_path == NULL ) {
        __T_E("fail to allocate memory for g_generate_path\n");
        return ICLI_RC_ERROR;
    }
    (void)mrdc_icli_str_cpy(g_generate_path, argv[1]);

    // get cmd_ref.txt
    g_txt_file = icli_malloc(i + 32);
    if ( g_txt_file == NULL ) {
        __T_E("fail to allocate memory for g_txt_file\n");
        return ICLI_RC_ERROR;
    }
    icli_sprintf(g_txt_file, "%s/cmd_ref.txt", g_generate_path);

    for ( i = 2; i < argc; ++i ) {
        /* read txt */
        if ( _txt_read(argv[i]) == FALSE ) {
            __T_E("fail to read %s\n", argv[i]);
            return ICLI_RC_ERROR;
        }
    }

    // write cmd_ref.txt
    if ( _txt_write() == FALSE ) {
        __T_E("fail to write %s\n", g_txt_file);
        return ICLI_RC_ERROR;
    }

    return ICLI_RC_OK;
}

