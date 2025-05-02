package michu.fr.matrix;

import michu.fr.matrix.models;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.script.Bindings;
import java.util.List;
import java.util.ArrayList;
import java.util.Objects;


public class MatrixUtils {
    private static final double EPSILON = 1e-9;

    private static double[][]  validateAndConvertMatrix(List<List<Double>> matrixList){
        if (matrixList==null || matrixList.isEmpty()) {
            throw new IllegalArgumentException("Matrix cannot be null or empty");
        }
        int rows= matrixList.size();
        List<Double> firstRow = matrixList.get(0);
        if (firstRow==null || firstRow.isEmpty()) {
            throw new IllegalArgumentException("Matrix cannot be null or empty");
        }
        int cols= firstRow.size();
        double [][] matrixArray= new double[rows][cols];
        for (int i=0;i<rows;i++){
            List<Double> currentRow= matrixList.get(i);
            if (currentRow==null || currentRow.size()!=cols) {
                throw new IllegalArgumentException("Matrix rows must have the same number of columns");
            }
            if (currentRow.size()!=cols) {
                throw new IllegalArgumentException("Matrix rows must have the same number of columns");
            }
            for (int j =0, j<cols; j++){
                Double value= currentRow.get(j);
                if (value==null) {
                    throw new IllegalArgumentException("Matrix cannot contain null values");
                }
                matrixArray[i][j]= value;
            }
        }
        return matrixArray;

    }

    private static String getDimensionString(List<List<Double>> matrixList){
        if (matrixList==null || matrixList.isEmpty()) {
            throw new IllegalArgumentException("Matrix cannot be null or empty");
        }
        int rows = matrixList.size();
        int cols= matrixList.get(0).size();
        for (int i =1; i<rows;i++){
            if (matrixList.get(i)==null || matrixList.get(i).size()!=cols) {
                return "Invalid";

            }
        }
        return rows + "x" + cols;
    }

    private static double[][] getSubmatrix(double[][], int excludingRow, int excludingCol) {
        int n = matrix.length;
        if (n<=1){
            return new double[0][0];
        }
        double[][] submatrix= new double[n-1][n-1];
        int rSub=0;
        for (int r=0; r<n; r++){

        }
    }
    


    
}















    

