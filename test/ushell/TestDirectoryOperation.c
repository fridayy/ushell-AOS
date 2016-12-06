//
// Created by bnjm on 12/5/16.
//
#include "../../src/ushell/DirectoryOperation.h"
#include "../unity/unity.h"
#include "../TestFileHelper.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void test_mymkdirCreatesDirectoryCorrectly(void) {
    TEST_ASSERT_EQUAL(0, mymkdir("test"));

    DIR *dir = opendir("test");
    TEST_ASSERT_NOT_EQUAL(NULL, dir);
    if(dir != NULL) {
        closedir(dir);
    }

    rmdir("test");
}

void test_mymkdirReturnsErrorIfDirectoryAlreadyExists(void) {
    TEST_ASSERT_EQUAL(0, mymkdir("test"));
    TEST_ASSERT_EQUAL(-1, mymkdir("test"));

    rmdir("test");
}

void test_myrmdirRemovesDirectoryCorrectly(void) {
    mkdir("test", 0755);
    TEST_ASSERT_EQUAL(0, myrmdir("test"));
}

void test_myrmdirOnFilesReturnsError(void) {
    char *file = createFileWithContent("testfile.txt", "abc");

    TEST_ASSERT_EQUAL(-1,myrmdir(file));

    remove(file);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_mymkdirCreatesDirectoryCorrectly);
    RUN_TEST(test_mymkdirReturnsErrorIfDirectoryAlreadyExists);
    RUN_TEST(test_myrmdirRemovesDirectoryCorrectly);
    RUN_TEST(test_myrmdirOnFilesReturnsError);

    return UNITY_END();
}
