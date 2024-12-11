#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char  *name;
    int    offset;
    int    count;
    float  percent;
}
Profile_Entry;

static const char    *profile_filename;
static const char    *map_filename;
static int            granularity;
static int           *profile;
static int            profile_len;
static Profile_Entry *functionTable;
static int            numFunctions;
static int            maxFunctions;

static void read_args(int argc, const char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "annotate <profile file> <map file>\n");
        fclose(stderr);
        exit(EXIT_FAILURE);
    }
    profile_filename = argv[1];
    map_filename     = argv[2];
}

static void read_profile()
{
    FILE *in = fopen(profile_filename, "rb");

    if (in == NULL)
    {
        fprintf(stderr, "Failed to open profile file '%s'\n",
                profile_filename);
        fclose(stderr);
        exit(EXIT_FAILURE);
    }

    fseek(in, 0, SEEK_END);
    profile_len = (int)ftell(in)-8;
    fseek(in, 0, SEEK_SET);

    if ((fgetc(in) != 'P') ||
        (fgetc(in) != 'R') ||
        (fgetc(in) != '0') ||
        (fgetc(in) != 'F'))
    {
        fclose(in);
        fprintf(stderr, "'%s' is not a profile file\n",
                profile_filename);
        fclose(stderr);
        exit(EXIT_FAILURE);
    }

    fread(&granularity, 4, 1, in);
    profile = malloc(profile_len);
    if (profile == NULL)
    {
        fclose(in);
        fprintf(stderr, "Out of memory reading profile\n");
        fclose(stderr);
        exit(EXIT_FAILURE);
    }

    fread(profile, 4, profile_len>>2, in);
    fclose(in);
}

static void addFn(const char *text, int offset)
{
    if (numFunctions == maxFunctions)
    {
        int newSize = maxFunctions*2;

        if (newSize == 0)
            newSize = 128;

        functionTable = realloc(functionTable,
                                newSize*sizeof(Profile_Entry));
        if (functionTable == NULL)
        {
            fprintf(stderr, "Out of memory reading mapfile\n");
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
        maxFunctions = newSize;
    }

    functionTable[numFunctions].name    = malloc(strlen(text)+1);
    strcpy(functionTable[numFunctions].name, text);
    functionTable[numFunctions].offset  = offset;
    functionTable[numFunctions].count   = 0;
    functionTable[numFunctions].percent = 0.0;
    //fprintf(stdout, "%s %x\n", functionTable[numFunctions].name,
    //        functionTable[numFunctions].offset);
    numFunctions++;
}

static void read_map()
{
    FILE *in = fopen(map_filename, "rb");
    char  text[2048];

    if (in == NULL)
    {
        fprintf(stderr, "Failed to open map file '%s'\n",
                map_filename);
        fclose(stderr);
        exit(EXIT_FAILURE);
    }

    functionTable = NULL;
    numFunctions  = 0;
    maxFunctions  = 0;

    addFn("Address 0", 0);

    while (!feof(in))
    {
        int   offset;
        char  c;
        char *t;

        /* Skip over any whitespace */
        do
        {
            c = fgetc(in);
        }
        while (((c == 32) || (c == 9)) && (!feof(in)));
        ungetc(c, in);

        /* Try to read an offset */
        if (fscanf(in, "0x%x", &offset) != 1)
        {
            goto over;
        }
        /* Skip over any whitespace */
        do
        {
            c = fgetc(in);
        }
        while ((c == 32) && (!feof(in)));
        ungetc(c, in);

        /* Names never start with . or (*/
        if ((c != '_') &&
            ((c < 'a') || (c > 'z')) &&
            ((c < 'A') || (c > 'Z')))
            goto over;

        /* Read the name */
        t = text;
        do
        {
            c = fgetc(in);
            *t++ = c;
        }
        while (c > 32);
        t[-1] = 0;

        /* Now there should be nothing left on this line */
        if ((c != 10) && (c != 13))
            goto over;

        /* And put the return back */
        ungetc(c, in);

        if (t != text)
        {
            addFn(text, offset);
        }

      over:
        /* Skip to the end of the line */
        do
        {
            c = fgetc(in);
        }
        while ((c >= 32) && (!feof(in)));

        /* Skip over any newlines */
        while (((c == 10) || (c == 13)) && (!feof(in)))
        {
            c = fgetc(in);
        }

        /* And put the first non whitespace/non return char back */
        ungetc(c, in);
    }

    fclose(in);
}

static void show_profile()
{
    int i;

    for (i=0; i < numFunctions; i++)
    {
        fprintf(stdout, "%08x (%6.2f%%: %6d) %s\n",
                functionTable[i].offset,
                functionTable[i].percent,
                functionTable[i].count,
                functionTable[i].name);
    }
}

int byAddress(const void *_e1, const void *_e2)
{
    const Profile_Entry *e1 = (const Profile_Entry *)_e1;
    const Profile_Entry *e2 = (const Profile_Entry *)_e2;

    return e1->offset - e2->offset;
}

int byTime(const void *_e1, const void *_e2)
{
    const Profile_Entry *e1 = (const Profile_Entry *)_e1;
    const Profile_Entry *e2 = (const Profile_Entry *)_e2;

    return e2->count - e1->count;
}

static void process_profile()
{
    int next;
    int fn;
    int idx;
    int max;
    int total;

    /* Sort into address order */
    qsort(functionTable,
          numFunctions,
          sizeof(Profile_Entry),
          byAddress);

    /* Run through the profile adding it to the appropriate function */
    fn   = -1; /* Which function are we looking at */
    next = -1; /* At what address should we move to the next function */
    idx  = 0;  /* Where are we in the profile */
    max = profile_len>>2;
    total = 0;
    for (idx = 0; idx < max; idx++)
    {
        while ((idx<<(granularity+2)) >= next)
        {
            /* Move to the next function */
            fn++;
            //fprintf(stdout, "Will be on fn %s until we pass %x\n",
            //        functionTable[fn].name, functionTable[fn+1].offset);
            next = 0x7FFFFFFF;
            if (fn+1 < numFunctions)
            {
                next = functionTable[fn+1].offset;
            }
        }
        //fprintf(stdout, "fn=%d count=%d idx=%d next=%x\n",
        //        fn, functionTable[fn].count, idx, next);
        functionTable[fn].count += profile[idx];
        total += profile[idx];
    }

    for (fn = 0; fn < numFunctions; fn++)
    {
        functionTable[fn].percent = 100.0*functionTable[fn].count/total;
    }

    fprintf(stdout, "Profile by Address\n");
    show_profile();

    /* Sort into time order */
    qsort(functionTable,
          numFunctions,
          sizeof(Profile_Entry),
          byTime);

    fprintf(stdout, "\n\n");
    fprintf(stdout, "Profile by Time\n");
    show_profile();
}

int main(int argc, const char *argv[])
{
    read_args(argc, argv);

    read_profile();
    read_map();

    process_profile();

    return EXIT_SUCCESS;
}
