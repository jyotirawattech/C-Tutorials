/*
 * Synthetic regression for a known limitation in the historical 0355 archive.
 * This does not fix or replace the archived submission.
 *
 * Run from the repository root, for example:
 *   clang -std=c11 -fsanitize=undefined -fno-sanitize-recover=all \
 *     leetcode/review/0355_feed_order.c -o /tmp/0355_feed_order
 *   /tmp/0355_feed_order
 *
 * Exit 0 means the exact documented counterexample was reproduced, not that
 * the archived feed algorithm is correct. A changed outcome needs review.
 */

#include <stdio.h>
#include "../accepted/0355_design_twitter/submission.c"

int main(void) {
    Twitter* twitter = twitterCreate();
    if (twitter == NULL) return 2;

    /* Every identifier below is synthetic. Later posts have larger timestamps. */
    for (int user = 1; user <= 3; user++) {
        for (int offset = 0; offset < 10; offset++) {
            twitterPostTweet(twitter, user, user * 100 + offset);
        }
    }
    twitterFollow(twitter, 1, 2);
    twitterFollow(twitter, 1, 3);

    int count = 0;
    int* feed = twitterGetNewsFeed(twitter, 1, &count);
    if (feed == NULL) {
        twitterFree(twitter);
        return 2;
    }

    printf("Expected newest-first IDs:");
    for (int i = 0; i < 10; i++) printf(" %d", 309 - i);
    printf("\nObserved newest-first IDs:");
    int documented_counterexample = (count == 10);
    for (int i = 0; i < count; i++) {
        printf(" %d", feed[i]);
        if (i >= 10 || feed[i] != 209 - i) documented_counterexample = 0;
    }
    printf("\n%s\n", documented_counterexample
        ? "Known historical feed-order counterexample reproduced."
        : "Outcome changed; review the archived source and this regression.");

    free(feed);
    twitterFree(twitter);
    return documented_counterexample ? 0 : 1;
}
