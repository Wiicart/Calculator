//
// Created by Christopher on 8/6/25.
//

#include "calculation_context.h"

#include <math.h>

CalculationContext calc_context_new(double first, double second, char operator) {
    CalculationContext ctx = {first, second, operator};
    return ctx;
}

double calc_context_compute(CalculationContext ctx) {
    switch (ctx.operator) {
        case '+': return ctx.first + ctx.second;
        case '-': return ctx.first - ctx.second;
        case '*': return ctx.first * ctx.second;
        case '/': return ctx.second != 0 ? ctx.first / ctx.second : 0;
        case '^': return pow(ctx.first, ctx.second);
        default: return 0;
    }
}
