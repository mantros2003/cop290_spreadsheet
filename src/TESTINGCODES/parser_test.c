#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../_parser.h"  // Assumes this defines the response type and declares parse() and print_resp()

// Test case: empty input string → expect status 2.
void test_empty_input() {
    char input[] = "";
    response res = parse(input);
    assert(res.status == 2);
    printf("Test empty input passed: ");
    print_resp(res);
}

// Test case: single-character command 'w' → expect func = 13.
void test_single_char_w() {
    char input[] = "w";
    response res = parse(input);
    assert(res.status == 0);
    assert(res.func == 13);
    printf("Test single-char 'w' passed: ");
    print_resp(res);
}

// Test case: command "disable_output" → expect func = 18.
void test_disable_output() {
    char input[] = "disable_output";
    response res = parse(input);
    assert(res.status == 0);
    assert(res.func == 18);
    printf("Test disable_output passed: ");
    print_resp(res);
}

// Test case: scroll command "scroll_to A1" → expect func = 20, target = 1001, arg_type = 2.
void test_scroll_to() {
    char input[] = "scroll_to A1";
    response res = parse(input);
    // For cell "A1", ValidCell3 should return 1000*1 + 1 = 1001.
    assert(res.status == 0);
    assert(res.func == 20);
    assert(res.target == 1001);
    assert(res.arg_type == 2);
    printf("Test scroll_to passed: ");
    print_resp(res);
}

// Test case: Assignment with integer: "A1=123" → expect func = 1, target = 1001, arg1 = 123, arg_type = 0.
void test_assignment_integer() {
    char input[] = "A1=123";
    response res = parse(input);
    assert(res.status == 0);
    assert(res.func == 1);
    assert(res.target == 1001);
    assert(res.arg1 == 123);
    assert(res.arg_type == 0);
    printf("Test assignment (integer) passed: ");
    print_resp(res);
}

// Test case: Dependency assignment: "A1=B2" → expect func = 2, target = 1001, arg1 = ValidCell3("B2") = 2002, arg_type = 2.
void test_assignment_cell() {
    char input[] = "A1=B2";
    response res = parse(input);
    assert(res.status == 0);
    assert(res.func == 2);
    assert(res.target == 1001);
    // For "B2": column B → 2 and row 2 → returns 2002.
    assert(res.arg1 == 2002);
    assert(res.arg_type == 2);
    printf("Test assignment (cell) passed: ");
    print_resp(res);
}

// Test case: Arithmetic addition: "A1=123+456" → expect func = 3, target = 1001, arg1 = 123, arg2 = 456, arg_type = 0.
void test_arithmetic_addition() {
    char input[] = "A1=123+456";
    response res = parse(input);
    assert(res.status == 0);
    assert(res.func == 3);
    assert(res.target == 1001);
    assert(res.arg1 == 123);
    assert(res.arg2 == 456);
    assert(res.arg_type == 0);
    printf("Test arithmetic addition passed: ");
    print_resp(res);
}

// Test case: Function call: "A1=MIN(B2:B5)" → expect func = 7 (MIN) and target = 1001.
// (The exact values for arg1/arg2 may depend on the implementation details of ParseFunc.)
void test_function_min() {
    char input[] = "A1=MIN(B2:B5)";
    response res = parse(input);
    assert(res.status == 0);
    assert(res.func == 7);
    assert(res.target == 1001);
    printf("Test function MIN passed: ");
    print_resp(res);
}

// Test case: Arithmetic division by zero: "A1=123/0" → expect func = 6, target = 1001, arg1 = 123, arg2 = 0, arg_type = 0.
void test_arithmetic_division_by_zero() {
    char input[] = "A1=123/0";
    response res = parse(input);
    assert(res.status == 0);
    assert(res.func == 6);
    assert(res.target == 1001);
    assert(res.arg1 == 123);
    assert(res.arg2 == 0);
    assert(res.arg_type == 0);
    printf("Test arithmetic division by zero passed: ");
    print_resp(res);
}

// Test case: Invalid expression (e.g. nothing after '='): "A1=" → expect error (status 1).
void test_invalid_expression() {
    char input[] = "A1=";
    response res = parse(input);
    assert(res.status == 1);
    printf("Test invalid expression passed: ");
    print_resp(res);
}

int main(void) {
    test_empty_input();
    test_single_char_w();
    test_disable_output();
    test_scroll_to();
    test_assignment_integer();
    test_assignment_cell();
    test_arithmetic_addition();
    test_function_min();
    test_arithmetic_division_by_zero();
    test_invalid_expression();

    printf("All parser tests passed.\n");
    return 0;
}
