/*
 * Design Twitter: corrected local practice, 3 November 2026.
 * Adapted with AI assistance from Jyoti's historical C submission 2029610348.
 * This is NOT that unchanged Accepted source and has not been submitted.
 * The original is preserved under leetcode/accepted/0355_design_twitter/.
 *
 * Synthetic, single-threaded, in-memory exercise: IDs 1..500, newest ten posts.
 * Post/follow/unfollow return bool to report invalid inputs; this deliberately
 * differs from the judge's void API. Returned nonempty feeds belong to caller.
 * NULL feed with size zero means empty, invalid input or allocation failure.
 * Callers needing distinct error reasons would need a richer result API.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_USER = 500, FEED_LIMIT = 10 };

typedef struct {
    int id;
    uint64_t time;
} Tweet;

typedef struct {
    uint64_t next_time;
    bool follows[MAX_USER + 1][MAX_USER + 1];
    Tweet tweets[MAX_USER + 1][FEED_LIMIT];
    unsigned char count[MAX_USER + 1];
    unsigned char next[MAX_USER + 1];
} Twitter;

static bool valid_user_id(int id) {
    return id >= 1 && id <= MAX_USER;
}

Twitter *twitterCreate(void) {
    return calloc(1, sizeof(Twitter));
}

bool twitterPostTweet(Twitter *obj, int user, int tweet_id) {
    if (obj == NULL || !valid_user_id(user) || obj->next_time == UINT64_MAX) {
        return false;
    }
    unsigned int slot = obj->next[user];
    obj->tweets[user][slot] = (Tweet){tweet_id, obj->next_time++};
    obj->next[user] = (unsigned char)((slot + 1U) % FEED_LIMIT);
    if (obj->count[user] < FEED_LIMIT) obj->count[user]++;
    return true;
}

bool twitterFollow(Twitter *obj, int follower, int followee) {
    if (obj == NULL || !valid_user_id(follower) || !valid_user_id(followee)) {
        return false;
    }
    if (follower != followee) obj->follows[follower][followee] = true;
    return true;
}

bool twitterUnfollow(Twitter *obj, int follower, int followee) {
    if (obj == NULL || !valid_user_id(follower) || !valid_user_id(followee)) {
        return false;
    }
    if (follower != followee) obj->follows[follower][followee] = false;
    return true;
}

int *twitterGetNewsFeed(Twitter *obj, int user, int *size) {
    if (size == NULL) return NULL;
    *size = 0;
    if (obj == NULL || !valid_user_id(user)) return NULL;

    Tweet candidates[MAX_USER * FEED_LIMIT];
    int total = 0;
    for (int author = 1; author <= MAX_USER; author++) {
        if (author != user && !obj->follows[user][author]) continue;
        for (int offset = 0; offset < obj->count[author]; offset++) {
            int slot = (obj->next[author] + FEED_LIMIT - 1 - offset) % FEED_LIMIT;
            candidates[total++] = obj->tweets[author][slot];
        }
    }
    int limit = total < FEED_LIMIT ? total : FEED_LIMIT;
    if (limit == 0) return NULL;

    /* Each right-to-left pass brings the suffix maximum into prefix[i]. */
    for (int i = 0; i < limit && i < total - 1; i++) {
        for (int j = total - 1; j > i; j--) {
            if (candidates[j - 1].time < candidates[j].time) {
                Tweet swap = candidates[j - 1];
                candidates[j - 1] = candidates[j];
                candidates[j] = swap;
            }
        }
    }
    int *result = malloc((size_t)limit * sizeof(*result));
    if (result == NULL) return NULL;
    for (int i = 0; i < limit; i++) result[i] = candidates[i].id;
    *size = limit;
    return result;
}

void twitterFree(Twitter *obj) {
    free(obj);
}

static void expect_feed(Twitter *obj, int user, const int *expected, int count) {
    int size = -1;
    int *feed = twitterGetNewsFeed(obj, user, &size);
    assert(size == count);
    assert(count == 0 ? feed == NULL : feed != NULL);
    for (int i = 0; i < count; i++) assert(feed[i] == expected[i]);
    free(feed);
}

static void test_fixed_cases(void) {
    Twitter *obj = twitterCreate();
    assert(obj != NULL);
    expect_feed(obj, 1, NULL, 0);
    assert(twitterPostTweet(obj, 1, 5));
    const int own[] = {5};
    expect_feed(obj, 1, own, 1);
    assert(twitterFollow(obj, 1, 2));
    assert(twitterFollow(obj, 1, 2));
    assert(twitterPostTweet(obj, 2, 6));
    const int pair[] = {6, 5};
    expect_feed(obj, 1, pair, 2);
    expect_feed(obj, 1, pair, 2); /* Feed reads do not consume posts. */
    assert(twitterUnfollow(obj, 1, 2));
    assert(twitterUnfollow(obj, 1, 2));
    assert(twitterFollow(obj, 1, 1));
    assert(twitterUnfollow(obj, 1, 1));
    expect_feed(obj, 1, own, 1);
    for (int id = 100; id < 125; id++) assert(twitterPostTweet(obj, 500, id));
    assert(twitterFollow(obj, 1, 500));
    int wrapped[FEED_LIMIT];
    for (int i = 0; i < FEED_LIMIT; i++) wrapped[i] = 124 - i;
    expect_feed(obj, 1, wrapped, FEED_LIMIT);
    twitterFree(obj);
}

static void test_historical_counterexample(void) {
    Twitter *obj = twitterCreate();
    assert(obj != NULL);
    for (int user = 1; user <= 3; user++) {
        for (int j = 0; j < FEED_LIMIT; j++) {
            assert(twitterPostTweet(obj, user, user * 100 + j));
        }
    }
    assert(twitterFollow(obj, 1, 2));
    assert(twitterFollow(obj, 1, 3));
    int expected[FEED_LIMIT];
    for (int i = 0; i < FEED_LIMIT; i++) expected[i] = 309 - i;
    expect_feed(obj, 1, expected, FEED_LIMIT);
    twitterFree(obj);
}

static void test_all_users_and_invalid_inputs(void) {
    Twitter *obj = twitterCreate();
    assert(obj != NULL);
    for (int user = 1; user <= MAX_USER; user++) {
        assert(twitterFollow(obj, 500, user));
        for (int j = 0; j < FEED_LIMIT; j++) {
            assert(twitterPostTweet(obj, user, user * 100 + j));
        }
    }
    int expected[FEED_LIMIT];
    for (int i = 0; i < FEED_LIMIT; i++) expected[i] = 50009 - i;
    expect_feed(obj, 500, expected, FEED_LIMIT);
    const int invalid[] = {-1, 0, MAX_USER + 1};
    for (size_t i = 0; i < sizeof(invalid) / sizeof(invalid[0]); i++) {
        assert(!twitterPostTweet(obj, invalid[i], 1));
        assert(!twitterFollow(obj, 1, invalid[i]));
        assert(!twitterFollow(obj, invalid[i], 1));
        assert(!twitterUnfollow(obj, invalid[i], 1));
        assert(!twitterUnfollow(obj, 1, invalid[i]));
        expect_feed(obj, invalid[i], NULL, 0);
    }
    assert(!twitterPostTweet(NULL, 1, 1));
    assert(!twitterFollow(NULL, 1, 2));
    assert(!twitterUnfollow(NULL, 1, 2));
    expect_feed(NULL, 1, NULL, 0);
    assert(twitterGetNewsFeed(obj, 1, NULL) == NULL);
    obj->next_time = UINT64_MAX;
    assert(!twitterPostTweet(obj, 500, 999));
    expect_feed(obj, 500, expected, FEED_LIMIT); /* Rejection is nonmutating. */
    twitterFree(obj);
    twitterFree(NULL);
}

/* Independent oracle: keep ALL posts in global order, scan newest backward. */
enum { MODEL_OPERATIONS = 2048 };
typedef struct {
    int author[MODEL_OPERATIONS];
    int id[MODEL_OPERATIONS];
    int count;
    bool follows[MAX_USER + 1][MAX_USER + 1];
} Model;

static void compare_model(Twitter *obj, const Model *model, int viewer) {
    int expected[FEED_LIMIT];
    int count = 0;
    for (int i = model->count - 1; i >= 0 && count < FEED_LIMIT; i--) {
        int author = model->author[i];
        if (author == viewer || model->follows[viewer][author]) {
            expected[count++] = model->id[i];
        }
    }
    expect_feed(obj, viewer, expected, count);
}

static uint32_t next_random(uint32_t *state) {
    /* Deterministic synthetic fixture; never a security RNG. */
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static void test_against_full_history_model(void) {
    Twitter *obj = twitterCreate();
    Model *model = calloc(1, sizeof(*model));
    assert(obj != NULL && model != NULL);
    const int users[] = {1, 2, 3, 4, 5, 6, 500};
    uint32_t state = UINT32_C(355);
    for (int step = 0; step < MODEL_OPERATIONS; step++) {
        int a = users[next_random(&state) % 7];
        int b = users[next_random(&state) % 7];
        unsigned int operation = next_random(&state) % 4;
        if (operation <= 1) {
            assert(twitterPostTweet(obj, a, step));
            model->author[model->count] = a;
            model->id[model->count++] = step;
        } else if (operation == 2) {
            assert(twitterFollow(obj, a, b));
            if (a != b) model->follows[a][b] = true;
        } else {
            assert(twitterUnfollow(obj, a, b));
            if (a != b) model->follows[a][b] = false;
        }
        compare_model(obj, model, a);
        compare_model(obj, model, b);
    }
    for (size_t i = 0; i < sizeof(users) / sizeof(users[0]); i++) {
        compare_model(obj, model, users[i]);
    }
    free(model);
    twitterFree(obj);
}

int main(void) {
    test_historical_counterexample();
    test_fixed_cases();
    test_all_users_and_invalid_inputs();
    test_against_full_history_model();
    puts("0355 adapted practice: fixed cases, 500-user boundary and 2048 model operations passed.");
    return 0;
}
