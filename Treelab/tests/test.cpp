#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "Tree.h"

TEST_CASE("Tree with null constructor", "[tree]") {
    Tree<int> tree = Tree<int>();

    SECTION("tree is null") {
        REQUIRE(tree.getRightThread().empty());
        REQUIRE(tree.toStringDirect().empty());
        REQUIRE(tree.toStringSymmetric().empty());
        REQUIRE(tree.toStringReverse().empty());
        tree.remove(10);
        REQUIRE(tree.toStringDirect().empty());
        REQUIRE(tree.height() == 0);
    }

    SECTION("tree with one element") {
        tree.insert(5);
        REQUIRE(tree.getRightThread().empty());
        REQUIRE(tree.toStringDirect() == "5");
        REQUIRE(tree.toStringSymmetric() == "5");
        REQUIRE(tree.toStringReverse() == "5");
        tree.remove(10);
        REQUIRE(tree.toStringDirect() == "5");
        REQUIRE(tree.height() == 1);
        tree.remove(5);
        REQUIRE(tree.toStringDirect().empty());
        REQUIRE(tree.height() == 0);
    }

    SECTION("tree with several elements") {
        tree.insert(5);
        tree.insert(3);
        tree.insert(10);
        tree.insert(1);
        tree.insert(4);
        tree.insert(7);
        tree.insert(12);
        REQUIRE(tree.getRightThread() == "1->3 4->5 7->10");
        REQUIRE(tree.toStringDirect() == "5 3 1 4 10 7 12");
        REQUIRE(tree.toStringSymmetric() == "1 3 4 5 7 10 12");
        REQUIRE(tree.toStringReverse() == "1 4 3 7 12 10 5");

        tree.insert(5);
        REQUIRE(tree.getRightThread() == "1->3 4->5 7->10");
        REQUIRE(tree.toStringDirect() == "5 3 1 4 10 7 12");
        REQUIRE(tree.toStringSymmetric() == "1 3 4 5 7 10 12");
        REQUIRE(tree.toStringReverse() == "1 4 3 7 12 10 5");

        tree.remove(15);
        REQUIRE(tree.toStringDirect() == "5 3 1 4 10 7 12");
        REQUIRE(tree.height() == 3);

        tree.remove(4);
        REQUIRE(tree.getRightThread() == "1->3 3->5 7->10");
        REQUIRE(tree.toStringDirect() == "5 3 1 10 7 12");
        REQUIRE(tree.toStringSymmetric() == "1 3 5 7 10 12");
        REQUIRE(tree.toStringReverse() == "1 3 7 12 10 5");
        REQUIRE(tree.height() == 3);

        tree.remove(5);
        REQUIRE(tree.getRightThread() == "1->3 3->7");
        REQUIRE(tree.toStringDirect() == "7 3 1 10 12");
        REQUIRE(tree.toStringSymmetric() == "1 3 7 10 12");
        REQUIRE(tree.toStringReverse() == "1 3 12 10 7");
        REQUIRE(tree.height() == 3);

        tree.remove(7);
        tree.remove(3);
        REQUIRE(tree.getRightThread() == "1->10");
        REQUIRE(tree.toStringDirect() == "10 1 12");
        REQUIRE(tree.toStringSymmetric() == "1 10 12");
        REQUIRE(tree.toStringReverse() == "1 12 10");
        REQUIRE(tree.height() == 2);

        tree.remove(1);
        tree.remove(12);
        REQUIRE(tree.getRightThread().empty());
        REQUIRE(tree.toStringDirect() == "10");
        REQUIRE(tree.toStringSymmetric() == "10");
        REQUIRE(tree.toStringReverse() == "10");
        REQUIRE(tree.height() == 1);

        tree.remove(10);
        REQUIRE(tree.toStringDirect().empty());
        REQUIRE(tree.height() == 0);
    }
}

TEST_CASE("Tree with array constructor", "[tree]") {
    int arr[5] = {5, 4, 10, 7, 12};
    SECTION("Array without elements") {
        auto tree = Tree(arr, 0);
        REQUIRE(tree.getRightThread().empty());
        REQUIRE(tree.toStringDirect().empty());
        REQUIRE(tree.toStringSymmetric().empty());
        REQUIRE(tree.toStringReverse().empty());
        REQUIRE(tree.height() == 0);
        tree.remove(10);
    }
    SECTION("Array with several elements") {
        auto tree = Tree(arr, 5);
        REQUIRE(tree.getRightThread() == "4->5 7->10");
        REQUIRE(tree.toStringDirect() == "5 4 10 7 12");
        REQUIRE(tree.toStringSymmetric() == "4 5 7 10 12");
        REQUIRE(tree.toStringReverse() == "4 7 12 10 5");
        REQUIRE(tree.height() == 3);

        tree.insert(15);
        REQUIRE(tree.getRightThread() == "4->5 7->10");
        REQUIRE(tree.toStringDirect() == "5 4 10 7 12 15");
        REQUIRE(tree.toStringSymmetric() == "4 5 7 10 12 15");
        REQUIRE(tree.toStringReverse() == "4 7 15 12 10 5");
        REQUIRE(tree.height() == 4);

        tree.remove(12);
        REQUIRE(tree.getRightThread() == "4->5 7->10");
        REQUIRE(tree.toStringDirect() == "5 4 10 7 15");
        REQUIRE(tree.toStringSymmetric() == "4 5 7 10 15");
        REQUIRE(tree.toStringReverse() == "4 7 15 10 5");
        REQUIRE(tree.height() == 3);
    }
}

int main(int argc, char *argv[]) {
    Catch::Session().run(argc, argv);
}