//
// Created by Christopher on 8/6/25.
//

#ifndef CALCULATION_CONTEXT_H
#define CALCULATION_CONTEXT_H

typedef struct {
    double first, second;
    char operator;
} CalculationContext;

CalculationContext calc_context_new(double first, double second, char operator);

double calc_context_compute(CalculationContext ctx);

#endif //CALCULATION_CONTEXT_H
