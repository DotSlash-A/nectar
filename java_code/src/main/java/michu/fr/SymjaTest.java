package michu.fr;

import org.matheclipse.core.eval.ExprEvaluator;
import org.matheclipse.core.interfaces.IExpr;

public class SymjaTest {
    public static void main(String[] args) {
        ExprEvaluator util = new ExprEvaluator();
        IExpr result = util.eval("Integrate[x^2, x]");
        System.out.println("Result: " + result.toString());
    }
}