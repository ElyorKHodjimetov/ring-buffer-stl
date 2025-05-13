#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "RingBuffer.hpp"

TEST_CASE("push and pop basic functionality", "[RingBuffer]") {
    RingBuffer<int, 3> rb;
    REQUIRE(rb.empty());

    rb.push(10);
    rb.push(20);
    REQUIRE(rb.size() == 2);

    int value;
    REQUIRE(rb.pop(value));  
    REQUIRE(value == 10);

    REQUIRE(rb.pop(value));
    REQUIRE(value == 20);

    REQUIRE_FALSE(rb.pop(value)); // буфер пуст
}

TEST_CASE("overflow overwrites oldest", "[RingBuffer]") {
    RingBuffer<int, 3> rb;
    rb.push(1);
    rb.push(2);
    rb.push(3);
    rb.push(4);  // здесь 1 перезаписан

    REQUIRE(rb.size() == 3);
    REQUIRE(rb[0] == 2);
    REQUIRE(rb[1] == 3);
    REQUIRE(rb[2] == 4);
}