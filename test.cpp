//
// Created by Dom on 01.05.2021.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BinaryTree.h"

using testing::Eq;

namespace {
    //template<typename T>
    class ClassDeclaration : public testing::Test{
    public:
        binary_tree<int> obj;
        ClassDeclaration(){
            obj;
        }

    };
}
TEST_F(ClassDeclaration, nameOfTheTest1){//тест insert
    obj.insert(10);
    ASSERT_EQ(obj.get_size(),1);
}
TEST_F(ClassDeclaration, nameOfTheTest2){//тест Reduce
    obj.insert(16);
    obj.insert(8);
    obj.insert(4);
    obj.insert(12);
    obj.insert(1);
    obj.insert(5);
    obj.insert(10);
    obj.insert(14);
    obj.insert(24);
    obj.insert(20);
    obj.insert(18);
    obj.insert(22);
    obj.insert(32);
    obj.insert(30);
    obj.insert(64);
    ASSERT_EQ(obj.Reduce(sum),280);
}
TEST_F(ClassDeclaration, nameOfTheTest3){//тест Map
    obj.insert(16);
    obj.insert(8);
    obj.insert(4);
    obj.insert(12);
    obj.insert(1);
    obj.insert(5);
    obj.insert(10);
    obj.insert(14);
    obj.insert(24);
    obj.insert(20);
    obj.insert(18);
    obj.insert(22);
    obj.insert(32);
    obj.insert(30);
    obj.insert(64);
    obj.Map(sqr);
    ASSERT_EQ(obj.tree_to_string(),"1 16 25 64 100 144 196 256 324 400 484 576 900 1024 4096 ");
}
TEST_F(ClassDeclaration, nameOfTheTest4){//тест Where
    obj.insert(16);
    obj.insert(8);
    obj.insert(4);
    obj.insert(12);
    obj.insert(1);
    obj.insert(5);
    obj.insert(10);
    obj.insert(14);
    obj.insert(24);
    obj.insert(20);
    obj.insert(18);
    obj.insert(22);
    obj.insert(32);
    obj.insert(30);
    obj.insert(64);
    obj.Where(is_more_than_25);
    ASSERT_EQ(obj.tree_to_string(),"1 4 5 8 10 12 14 16 18 20 22 24 ");
}
TEST_F(ClassDeclaration, nameOfTheTest5){//тест find
    obj.insert(16);
    obj.insert(8);
    obj.insert(4);
    obj.insert(12);
    obj.insert(1);
    obj.insert(5);
    obj.insert(10);
    obj.insert(14);
    obj.insert(24);
    obj.insert(20);
    obj.insert(18);
    obj.insert(22);
    obj.insert(32);
    obj.insert(30);
    obj.insert(64);

    ASSERT_EQ(obj.find(4),1);
}
TEST_F(ClassDeclaration, nameOfTheTest6){//тест delete
    obj.insert(16);
    obj.insert(8);
    obj.insert(4);
    obj.insert(12);
    obj.insert(1);
    obj.insert(5);
    obj.insert(10);
    obj.insert(14);
    obj.insert(24);
    obj.insert(20);
    obj.insert(18);
    obj.insert(22);
    obj.insert(32);
    obj.insert(30);
    obj.insert(64);
    obj.delete_elem(4);
    ASSERT_EQ(obj.find(4),0);
}

TEST_F(ClassDeclaration, nameOfTheTest7){//тест get_sub_tree
    obj.insert(16);
    obj.insert(8);
    obj.insert(4);
    obj.insert(12);
    obj.insert(1);
    obj.insert(5);
    obj.insert(10);
    obj.insert(14);
    obj.insert(24);
    obj.insert(20);
    obj.insert(18);
    obj.insert(22);
    obj.insert(32);
    obj.insert(30);
    obj.insert(64);
    binary_tree<int>* tmp = obj.get_sub_tree(24);
    ASSERT_EQ(tmp->tree_to_string(),"18 20 22 24 30 32 64 ");
}
TEST_F(ClassDeclaration, nameOfTheTest8){//тест is_subtree
    obj.insert(16);
    obj.insert(8);
    obj.insert(4);
    obj.insert(12);
    obj.insert(1);
    obj.insert(5);
    obj.insert(10);
    obj.insert(14);
    obj.insert(24);
    obj.insert(20);
    obj.insert(18);
    obj.insert(22);
    obj.insert(32);
    obj.insert(30);
    obj.insert(64);
    binary_tree<int>* tmp = new binary_tree<int>(24);
    tmp->insert(20);
    tmp->insert(32);
    tmp->insert(18);
    tmp->insert(22);
    tmp->insert(30);
    tmp->insert(64);
    ASSERT_EQ(obj.is_subtree(&obj,tmp),1);
}
