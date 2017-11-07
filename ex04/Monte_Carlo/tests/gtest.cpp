#include <iostream>
#include "gtest/gtest.h"


double CalculatingPi(int num) {
    int innerCount;
    double p;

    for(int i = 0; i < num; i++) {

        // Generating random dots "x" and "y"
        double x = (double)rand()/RAND_MAX;
        double y = (double)rand()/RAND_MAX;

        // If the points are in the circle, we increase the counter
        if(x*x + y*y <= 1) {
            innerCount++;
        }
    }

    // Calculate the number Pi
    return p = (double) 4 * innerCount / num;
}

TEST (randTest, First) {
    ASSERT_NE ((double)rand()/RAND_MAX, (double)rand()/RAND_MAX);
}

TEST(randTest, Second) {
    ASSERT_NE ((double)rand()/RAND_MAX, (double)rand()/RAND_MAX);
}

TEST(PiTest, FirstTest) {

    float s = CalculatingPi(1000000);
    float Pi = 3.14;
    s *= 100;
    s = floor(s + 0.5);
    s /= 100;

    ASSERT_EQ (s, Pi);
}





int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



/*
    ASSERT_EQ(ожидаемое, реальное); — проверка, что реальное значение точно равно ожидаемой величине
    ASSERT_NE(ожидаемое, реальное); — проверка, что реальное значение не равно ожидаемой величине
    ASSERT_LT(ожидаемое, реальное); — проверка, что ожидаемое значение < реальная величина
    ASSERT_LE(ожидаемое, реальное); — проверка, что ожидаемое значение <= реальная величина
    ASSERT_GT(ожидаемое, реальное); — проверка, что ожидаемое значение > реальная величина
    ASSERT_GE(ожидаемое, реальное); — проверка, что ожидаемое значение >= реальная величина

    */
