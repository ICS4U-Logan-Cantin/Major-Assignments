import java.util.Scanner;

public class MaxRun {

    public static void main(String[] args) {
        Scanner iostream = new Scanner(System.in);
        String input = iostream.nextLine();

        int maxRun = 0;
        int pivot = 0;

        while (pivot < input.length()){
            char tempChar = input.charAt(pivot);
            int tempRun = 1;

            while ((pivot + tempRun < input.length()) && (input.charAt(pivot+tempRun) == tempChar)){
                tempRun++;
            }

            if (tempRun > maxRun){
                maxRun = tempRun;
            }

            pivot += tempRun;
        }

        System.out.println(maxRun);
    }
}
