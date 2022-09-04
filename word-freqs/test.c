#include "words-test.h"
#include "utest.h"

UTEST_MAIN()

#define LEN(A) (sizeof(A)/sizeof(A[0]))

#define SET_RANGE(R, CSTR) \
        r.beg = CSTR; r.end = CSTR + LEN(CSTR)

#define SET_RANGE_CSTR(R, PTR, CSTR) \
        PTR = CSTR; r.beg = CSTR; r.end = CSTR + LEN(CSTR)

UTEST(Range, A) {
    char* p = NULL;
    Range r = { .beg = p, .end = p};

    // '\0' is not space
    ASSERT_FALSE(isspace('\0'));

    ASSERT_TRUE(range_is_empty(r));

    SET_RANGE_CSTR(r, p, "0123456789");
    ASSERT_FALSE(range_is_empty(r));

    // The '\0' char is not an empty range
    SET_RANGE_CSTR(r, p, "");
    ASSERT_FALSE(range_is_empty(r));

    SET_RANGE_CSTR(r, p, " 12");
    range_skip_space_or_null(&r);
    ASSERT_EQ(r.beg, p + 1);

    SET_RANGE_CSTR(r, p, "  2");
    range_skip_space_or_null(&r);
    ASSERT_EQ(r.beg, p + 2);


    SET_RANGE_CSTR(r, p, "   ");
    range_skip_space_or_null(&r);
    ASSERT_EQ(r.beg, p + 4);

    SET_RANGE_CSTR(r, p, "  A ");
    ASSERT_EQ(range_move_skip_word(&r), p);

    SET_RANGE_CSTR(r, p, "A ");
    ASSERT_EQ(range_move_skip_word(&r), p + 1);

    SET_RANGE_CSTR(r, p, "ABC ");
    ASSERT_EQ(range_move_skip_word(&r), p + 3);

    //SET_RANGE_CSTR(r, p, "ABC");
    //ASSERT_EQ(range_move_skip_word(&r), p + 3);

}
