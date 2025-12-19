#include <gtest/gtest.h>
#include "SparseVector.h"

TEST(SparseVectorTest, SetAndGet) {
SparseVector v(10);
v.setElem(3, 5);
EXPECT_EQ(v.getElem(3), 5);
EXPECT_EQ(v.getElem(2), 0);
}

TEST(SparseVectorTest, RemoveElement) {
SparseVector v(5);
v.setElem(1, 7);
v.setElem(1, 0);
EXPECT_EQ(v.getElem(1), 0);
}

TEST(SparseVectorTest, Equality) {
SparseVector a(5), b(5);
a.setElem(2, 9);
b.setElem(2, 9);
EXPECT_TRUE(a == b);
}

TEST(SparseVectorTest, Addition) {
SparseVector a(5), b(5);
a.setElem(1, 3);
b.setElem(1, 4);
SparseVector c = a + b;
EXPECT_EQ(c.getElem(1), 7);
}

