#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>


int main(int args, char* argv[]){
    testing::InitGoogleTest(&args, argv);
    RUN_ALL_TESTS();
    return 0;
}