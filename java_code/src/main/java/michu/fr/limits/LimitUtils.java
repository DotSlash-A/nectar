package michu.fr.limits;

import michu.fr.limits.models.LimitRequest;
import michu.fr.limits.models.LimitResponse;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.script.Bindings;
import java.util.Objects;

public class LimitUtils {

    private static final double EPSILON = 1e-9; // Tolerance for numerical comparisons
    private static final double LARGE_NUMBER = 1e15; // Represents "infinity" numerically
    private static final double SMALL_DELTA = 1e-7; // Step size for approaching limit

    // ScriptEngine setup (do once)
    private static final ScriptEngineManager SCRIPT_MANAGER = new ScriptEngineManager();
    private static final ScriptEngine JS_ENGINE = SCRIPT_MANAGER.getEngineByName("JavaScript");

    static {
        if (JS_ENGINE == null) {
            System.err.println("WARNING: JavaScript engine not found. Limit evaluation will fail. Ensure JDK includes Nashorn or GraalVM JS.");
            // Or throw a runtime exception to prevent usage
            // throw new RuntimeException("JavaScript engine not available");
        }
    }


    /**
     * Parses the 'tendingTo' string into a numerical value or identifies infinities.
     *
     * @param tendingToStr The input string (e.g., "1", "inf", "-inf", "pi", "e").
     * @return The numerical value, Double.POSITIVE_INFINITY, or Double.NEGATIVE_INFINITY.
     * @throws IllegalArgumentException if the string is invalid.
     */
    private static double parseLimitPoint(String tendingToStr) {
        String lowerStr = tendingToStr.trim().toLowerCase();
        switch (lowerStr) {
            case "inf":
            case "infinity":
            case "oo":
            case "∞":
                return Double.POSITIVE_INFINITY;
            case "-inf":
            case "-infinity":
            case "-oo":
            case "-∞":
                return Double.NEGATIVE_INFINITY;
            case "pi":
                return Math.PI;
            case "e":
                return Math.E;
            default:
                try {
                    // Attempt to parse as a number directly first
                    return Double.parseDouble(lowerStr);
                } catch (NumberFormatException e) {
                    // If direct parsing fails, try evaluating simple expressions like "pi/2"
                    // SECURITY WARNING: Evaluating arbitrary strings is risky!
                    if (JS_ENGINE != null) {
                        try {
                             Bindings bindings = JS_ENGINE.createBindings();
                             bindings.put("pi", Math.PI);
                             bindings.put("e", Math.E);
                             // Avoid allowing variable names here for safety
                             if (lowerStr.matches(".*[a-zA-Z_]+.*")) {
                                  throw new IllegalArgumentException("Invalid characters in numeric limit point: " + tendingToStr);
                             }
                             Object result = JS_ENGINE.eval(lowerStr.replace('^', '*'), bindings); // Use * for JS eval
                             if (result instanceof Number) {
                                 return ((Number) result).doubleValue();
                             }
                        } catch (ScriptException | ClassCastException | NullPointerException evalEx) {
                             throw new IllegalArgumentException("Cannot parse limit point '" + tendingToStr + "': Not a valid number, infinity, pi, e, or simple expression.", evalEx);
                        }
                    } else {
                         throw new IllegalArgumentException("Cannot parse limit point '" + tendingToStr + "': JS Engine unavailable for expression evaluation.");
                    }
                     throw new IllegalArgumentException("Cannot parse limit point '" + tendingToStr + "': Invalid format.");
                }
        }
    }

    /**
     * Evaluates the given mathematical expression string for a specific variable value.
     * Uses the JavaScript engine.
     *
     * @param expression The expression string (using JS math syntax).
     * @param variableName The name of the variable.
     * @param variableValue The numerical value to substitute for the variable.
     * @return The numerical result of the evaluation.
     * @throws ScriptException If the expression has syntax errors.
     * @throws IllegalArgumentException If the result is not a number.
     * @throws RuntimeException If the JS engine is unavailable.
     */
    private static double evaluateExpression(String expression, String variableName, double variableValue) throws ScriptException {
        if (JS_ENGINE == null) {
            throw new RuntimeException("JavaScript engine unavailable for expression evaluation.");
        }

        Bindings bindings = JS_ENGINE.createBindings();
        // Map common math functions and constants to JS equivalents
        bindings.put("sin", Math.sin(0)); // Provide functions via Math object
        bindings.put("cos", Math.cos(0));
        bindings.put("tan", Math.tan(0));
        bindings.put("ln", Math.log(1)); // JS Math.log is natural log
        bindings.put("log", Math.log10(1)); // JS Math.log10 is base 10 log
        bindings.put("sqrt", Math.sqrt(1));
        bindings.put("exp", Math.exp(1));
        bindings.put("abs", Math.abs(1));
        bindings.put("pi", Math.PI);
        bindings.put("e", Math.E);
        // Add cot, sec, csc if needed (e.g., 1/Math.tan(x)) - requires careful definition

        // Put the variable's current value
        bindings.put(variableName, variableValue);

        // Prepare expression for JS (e.g., use Math.pow for powers)
        // A simple replacement for ^ is often okay for basic cases, but complex expressions might fail.
        // Using Math.pow is more robust in JS. Let's try a regex replacement.
        // Replace 'x^y' with 'Math.pow(x,y)', handling potential parenthesis needs.
        // This regex is basic and might fail on complex nested powers.
        String jsExpression = expression.replaceAll("([a-zA-Z0-9_.]+)\\s*\\^\\s*([a-zA-Z0-9_.]+)", "Math.pow($1, $2)");
         // Replace constants/functions if not using the Math object directly in JS
         // jsExpression = jsExpression.replace("pi", String.valueOf(Math.PI)); // Alternative

        // Add Math prefix to functions if not done via bindings trick above
         jsExpression = jsExpression.replaceAll("(?<!\\.)\\b(sin|cos|tan|log|ln|sqrt|exp|abs)\\b", "Math.$1");


        // **SECURITY NOTE:** Evaluating arbitrary code via `eval` is dangerous.
        // Sanitize 'expression' string rigorously if it comes from external sources.
        Object result = JS_ENGINE.eval(jsExpression, bindings);

        if (result instanceof Number) {
            return ((Number) result).doubleValue();
        } else {
            throw new IllegalArgumentException("Expression did not evaluate to a number. Result: " + result);
        }
    }

    /**
     * Attempts to calculate the limit of an expression numerically.
     *
     * @param request The LimitRequest containing expression, variable, and tendingTo point.
     * @return A LimitResponse with the approximated result or status.
     */
    public static LimitResponse calculateLimitApprox(LimitRequest request) {
        Objects.requireNonNull(request, "Limit request cannot be null.");
        String expr = request.getExpression();
        String var = request.getVariable();
        String tendingToStr = request.getTendingTo();
        String resultStr = "Calculation Error";
        String explanation = "An error occurred.";

        try {
            double limitPoint = parseLimitPoint(tendingToStr);

            if (Double.isInfinite(limitPoint)) {
                // --- Limit at Infinity ---
                double valAtLarge = evaluateExpression(expr, var, limitPoint > 0 ? LARGE_NUMBER : -LARGE_NUMBER);

                if (Double.isNaN(valAtLarge)) {
                    resultStr = "NaN";
                    explanation = "Result is indeterminate when approaching infinity.";
                } else if (Double.isInfinite(valAtLarge)) {
                    resultStr = (valAtLarge > 0 ? "Infinity" : "-Infinity");
                    explanation = "The function tends towards infinity.";
                } else {
                    // Check if it stabilizes by evaluating at an even larger number
                    double valAtLarger = evaluateExpression(expr, var, limitPoint > 0 ? LARGE_NUMBER * 100 : -LARGE_NUMBER * 100);
                     if (Math.abs(valAtLarge - valAtLarger) < Math.abs(valAtLarge * EPSILON) + EPSILON) { // Relative/Absolute check
                         resultStr = String.format("%.6g", valAtLarge);
                         explanation = "The function appears to converge to a finite value.";
                     } else {
                          resultStr = "Does Not Exist";
                          explanation = "The function does not appear to converge to a single value at infinity (potential oscillation or slow convergence).";
                     }
                }
            } else {
                // --- Limit at a Finite Point ---
                double leftVal, rightVal;
                boolean leftEvalOk = true, rightEvalOk = true;

                // Evaluate slightly to the left
                try {
                    leftVal = evaluateExpression(expr, var, limitPoint - SMALL_DELTA);
                } catch (Exception e) {
                    leftVal = Double.NaN; // Mark as failed
                    leftEvalOk = false;
                     System.err.println("Warn: Eval failed left of limit point: " + e.getMessage());
                }

                // Evaluate slightly to the right
                 try {
                    rightVal = evaluateExpression(expr, var, limitPoint + SMALL_DELTA);
                 } catch (Exception e) {
                     rightVal = Double.NaN; // Mark as failed
                     rightEvalOk = false;
                     System.err.println("Warn: Eval failed right of limit point: " + e.getMessage());
                 }

                 // Analyze results
                 if (!leftEvalOk && !rightEvalOk) {
                      resultStr = "Evaluation Error";
                      explanation = "Could not evaluate the expression near the limit point.";
                 } else if (Double.isNaN(leftVal) || Double.isNaN(rightVal)) {
                      // Check direct substitution (might work if hole is removable)
                      try {
                           double directVal = evaluateExpression(expr, var, limitPoint);
                           if (!Double.isNaN(directVal) && !Double.isInfinite(directVal)) {
                                resultStr = String.format("%.6g", directVal);
                                explanation = "Approaching limit yields NaN, but direct substitution gives a finite value (possible removable discontinuity).";
                           } else {
                                resultStr = "NaN / Indeterminate";
                                explanation = "Numerical evaluation yields NaN near the limit point.";
                           }
                      } catch (Exception directExc) {
                           resultStr = "NaN / Indeterminate / Error";
                           explanation = "Numerical evaluation yields NaN near the limit point, and direct substitution failed.";
                      }

                 } else if (Double.isInfinite(leftVal) && Double.isInfinite(rightVal)) {
                      if ((leftVal > 0 && rightVal > 0) || (leftVal < 0 && rightVal < 0)) {
                           resultStr = (leftVal > 0 ? "Infinity" : "-Infinity");
                           explanation = "The function tends towards infinity from both sides.";
                      } else {
                           resultStr = "Does Not Exist";
                           explanation = "The function tends towards opposite infinities from the left and right.";
                      }
                 } else if (Double.isInfinite(leftVal) || Double.isInfinite(rightVal)) {
                      resultStr = "Does Not Exist";
                      explanation = "The function tends towards infinity from one side but is finite on the other.";
                 } else if (Math.abs(leftVal - rightVal) < EPSILON * (Math.abs(leftVal) + Math.abs(rightVal)) + EPSILON) {
                      // Values are close (use relative and absolute tolerance)
                      double avgVal = (leftVal + rightVal) / 2.0;
                       resultStr = String.format("%.6g", avgVal); // Use significant figures formatting
                       explanation = "The function appears to converge to a finite value.";
                 } else {
                      resultStr = "Does Not Exist";
                      explanation = "Left-hand and right-hand limits appear different (or function oscillates).";
                      System.out.println("Debug: Left=" + leftVal + ", Right=" + rightVal); // Debug info
                 }
            }

        } catch (IllegalArgumentException e) { // Catch parsing errors
            resultStr = "Input Error";
            explanation = "Error parsing input: " + e.getMessage();
             System.err.println("Limit Calc Input Error: " + e.getMessage());
        } catch (ScriptException e) {
            resultStr = "Expression Error";
            explanation = "Error evaluating expression (syntax?): " + e.getMessage();
             System.err.println("Limit Calc Script Error: " + e.getMessage());
        } catch (RuntimeException e) { // Catch JS engine missing
            resultStr = "Engine Error";
            explanation = "Internal setup error: " + e.getMessage();
             System.err.println("Limit Calc Runtime Error: " + e.getMessage());
        } catch (Exception e) { // Catch unexpected errors
            resultStr = "Unexpected Error";
            explanation = "An unexpected error occurred: " + e.getMessage();
             System.err.println("Limit Calc Unexpected Error: " + e.toString());
             e.printStackTrace(); // Log stack trace for debugging
        }

        return new LimitResponse(expr, var, tendingToStr, resultStr, explanation);
    }

} // End of LimitUtils class