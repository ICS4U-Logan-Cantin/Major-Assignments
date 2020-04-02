import org.w3c.dom.css.Rect;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.util.*;

import static javafx.application.Platform.exit;

// Point class to take care of all the point logic
class Point {
    // x and y positions, and the width and height of the container
    int x, y, width, height;

    // Returns a value between [low, high]
    private int clamp(int value, int low, int high) {
        if (value < low) {
            return low;
        }
        else if (value > high) {
            return high;
        }
        else {
            return value;
        }
    }

    // Constructor: Takes width and height of container, and the target shape s;
    public Point(int width, int height, Shape s) {
        this.width = width;
        this.height = height;

        // Finding a point that is not inside the target
        do {
            this.x = new Random().nextInt(width - 20) + 10;
            this.y = new Random().nextInt(height - 20) + 10;
        } while (s.contains(x, y));
    }

    // Private constructor for generating points after the first one
    private Point(int oldX, int oldY, int width, int height) {

        // Choosing a direction and moving in that direction
        int direction = new Random().nextInt(4);
        switch (direction) {
            case 0: //Right
                this.x = oldX + 1;
                this.y = oldY;
                break;
            case 1: // Left
                this.x = oldX - 1;
                this.y = oldY;
                break;
            case 2: // Up
                this.x = oldX;
                this.y = oldY + 1;
                break;
            case 3: // Down
                this.x = oldX;
                this.y = oldY - 1;
                break;
        }

        // Setting the width and height
        this.width = width;
        this.height = height;

        // Making sure the point is inside the bounds of the container
        this.x = clamp(this.x, 0, width);
        this.y = clamp(this.y, 0, height);
    }

    // Creating a new point
    Point newPoint() {
        return new Point(x, y, width, height);
    }
}

// Random Walk Class
public class RandomWalk extends JPanel {

    // Variables
    ArrayList<Point> points = new ArrayList<>();
    Shape shape;
    boolean complete = false;
    Random rand = new Random();

    // Constructor requires container size and target shape
    public RandomWalk(int width, int height, Shape s) {

        // Add the first point
        points.add(new Point(width, height, s));
        shape = s;
    }

    // Drawing the component
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        // Drawing the target
        g2d.fill(shape);

        // Adding three new points (reduces CPU load)
        for (int i = 0; i < 3; i++) {
            // Generating new point from the last one
            Point newpoint = points.get(points.size() - 1).newPoint();

            // Checking if it is inside the target
            if (shape.contains(newpoint.x, newpoint.y)) {
                complete = true;
            }

            // Adding the point to the points list
            points.add(newpoint);
        }


        // Setting the hue of the point and the initial color
        float hue = 0.5f;
        Color tempColor = new Color(255, 0, 0);
        g2d.setColor(tempColor);

        // For each of the points,
        for (Point p : points) {
            // Draw the point
            g2d.drawOval(p.x, p.y, 1, 1);

            // Set the color for the next point
            tempColor = Color.getHSBColor(hue, 0.9f, 0.9f);
            g2d.setColor(tempColor);
            hue = hue + 0.0001f;
        }
    }

    // Launch point for the program
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        // Try / catch statement to handle errors
        try {

            // getting the width and height and making sure they are in bounds
            System.out.print("Please enter the width: ");
            int WIDTH = input.nextInt();
            if (WIDTH < 200 || WIDTH > 800) {
                throw new Exception("Invalid input: Enter a width between 200 and 800!");
            }
            System.out.print("Please enter the height: ");
            int HEIGHT = input.nextInt();
            if (HEIGHT < 200 || HEIGHT > 800) {
                throw new Exception("Invalid input: Enter a height between 200 and 800!");
            }

            // Picking the target shape
            System.out.print("What shape would you like? (1: Circle, 2: Square) ");
            int shapeID = input.nextInt();
            Shape shape = new Rectangle(0, 0, 0, 0);

            // Circle
            if (shapeID == 1) {

                // Choosing a radius size that is reasonable and asking user for their input
                int maxRadius = (WIDTH > HEIGHT ? HEIGHT : WIDTH ) / 4;
                int minRadius = 20;
                System.out.printf("What is the radius of your circle? (Between %d and %d) ", minRadius, maxRadius);
                int radius = input.nextInt();

                // Checking the radius is appropriate
                if (radius >= minRadius && radius <= maxRadius) {

                    // Generating a location in bounds and setting the target shape to the circle
                    int randomX = new Random().nextInt(WIDTH - (2 * radius) - 20) + 10;
                    int randomY = new Random().nextInt(HEIGHT - (2 * radius) - 20) + 10;
                    shape = new Ellipse2D.Float(randomX, randomY, 2*radius, 2*radius);
                }
                else {
                    throw new Exception("Please enter a valid radius.");
                }
            }

            //SQUARE
            else if (shapeID == 2) {

                // Setting reasonable constraints for side length and asking the user for their input
                int minSideLength = 20;
                int maxSideLength = (WIDTH > HEIGHT ? HEIGHT : WIDTH) / 2;
                System.out.printf("What would you like the side length of your square to be? (Between %d and %d) ", minSideLength, maxSideLength);
                int sideLength = input.nextInt();

                // Checking the side length
                if (sideLength >= minSideLength && sideLength <= maxSideLength) {

                    // Generating a location in bounds
                    int randomX = new Random().nextInt(WIDTH - sideLength - 20) + 10;
                    int randomY = new Random().nextInt(HEIGHT - sideLength - 20) + 10;

                    // Assigning this square to be the target
                    shape = new Rectangle(randomX, randomY, sideLength, sideLength);
                }
                else {
                    throw new Exception("Please enter a valid side length.");
                }
            }

            // Not an appropriate shape id number
            else {
                throw new Exception("Invalid input: Enter a 1 for a circle or a 2 for a square!");
            }


            // Creating the form and the random walk component
            RandomWalk points = new RandomWalk(WIDTH, HEIGHT, shape);
            JFrame frame = new JFrame("Points");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.add(points);
            frame.setSize(WIDTH, HEIGHT);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);

            // Running the animation while the target has not been hit
            while (!points.complete) {
                frame.repaint();
                Thread.sleep(10);
            }

            // Alerting the user
            JOptionPane.showMessageDialog(null, "You win!");
        }

        // Handling errors
        catch (InputMismatchException e) {
            System.out.println("Please enter an integer!");
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
