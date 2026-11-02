#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    int time;
} Tweet;

typedef struct {
    int timestamp;
    bool follows[501][501];
    Tweet tweets[501][10];  // Circular buffer: exactly 10 tweets per user
    int tweet_count[501];   // Tracks total tweets posted by each user
} Twitter;

Twitter* twitterCreate() {
    Twitter* obj = (Twitter*)calloc(1, sizeof(Twitter));
    obj->timestamp = 0;
    return obj;
}

void twitterPostTweet(Twitter* obj, int userId, int tweetId) {
    int idx = obj->tweet_count[userId] % 10;
    obj->tweets[userId][idx].id = tweetId;
    obj->tweets[userId][idx].time = obj->timestamp++;
    obj->tweet_count[userId]++;
}

int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {
    Tweet tempFeed[5010]; // Max possible tweets to sort: 501 users * 10 tweets
    int tempCount = 0;
    
    // Check all users to see if they are followed (or self)
    for (int i = 1; i <= 500; i++) {
        if (i == userId || obj->follows[userId][i]) {
            int count = obj->tweet_count[i];
            int limit = count < 10 ? count : 10;
            for (int j = 0; j < limit; j++) {
                int idx = (count - 1 - j) % 10; 
                tempFeed[tempCount++] = obj->tweets[i][idx];
            }
        }
    }
    
    // Simple Bubble Sort (Extremely fast for highly bounded small arrays)
    for (int i = 0; i < tempCount - 1 && i < 10; i++) {
        for (int j = 0; j < tempCount - i - 1; j++) {
            if (tempFeed[j].time < tempFeed[j+1].time) {
                Tweet swap = tempFeed[j];
                tempFeed[j] = tempFeed[j+1];
                tempFeed[j+1] = swap;
            }
        }
    }
    
    *retSize = tempCount < 10 ? tempCount : 10;
    int* res = (int*)malloc((*retSize) * sizeof(int));
    for (int i = 0; i < *retSize; i++) {
        res[i] = tempFeed[i].id;
    }
    return res;
}

void twitterFollow(Twitter* obj, int followerId, int followeeId) {
    if (followerId != followeeId) {
        obj->follows[followerId][followeeId] = true;
    }
}

void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
    if (followerId != followeeId) {
        obj->follows[followerId][followeeId] = false;
    }
}

void twitterFree(Twitter* obj) {
    free(obj);
}