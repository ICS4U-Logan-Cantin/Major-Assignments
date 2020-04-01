import javafx.scene.shape.Ellipse;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.image.ImageObserver;
import java.util.*;
import java.util.List;

class Point {
    int x, y, width, height;

    final int SIZE = 1;

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

    public Point(int width, int height) {
        this.width = width;
        this.height = height;
        this.x = new Random().nextInt(width);
        this.y = new Random().nextInt(height);
    }

    private Point(int oldX, int oldY, int width, int height) {
        int direction = new Random().nextInt(4);
        switch (direction) {
            case 0: //Right
                this.x = oldX + SIZE;
                this.y = oldY;
                break;
            case 1: // Left
                this.x = oldX - SIZE;
                this.y = oldY;
                break;
            case 2: // Up
                this.x = oldX;
                this.y = oldY + SIZE;
                break;
            case 3: // Down
                this.x = oldX;
                this.y = oldY - SIZE;
                break;
        }

        this.width = width;
        this.height = height;

        this.x = clamp(this.x, 0, width);
        this.y = clamp(this.y, 0, height);
    }

    Point newPoint() {
        return new Point(x, y, width, height);
    }
}

public class RandomWalk extends JPanel {
    ArrayList<Point> points = new ArrayList<Point>();
    int width, height;

    public RandomWalk(int width, int height) {
        points.add(new Point(width, height));
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;
        g2d.setBackground(Color.BLACK);

        Point newpoint = points.get(points.size() - 1).newPoint();
        points.add(newpoint);

        float hue = 0.5f;
        Color tempColor = new Color(255, 0, 0);
        g2d.setColor(tempColor);
        for (Point p : points) {
            g2d.drawOval(p.x, p.y, 1, 1);

            tempColor = Color.getHSBColor(hue, 0.9f, 0.9f);
            g2d.setColor(tempColor);
            hue = hue + 0.0001f;
        }
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter the width: ");
        int WIDTH = input.nextInt();
        System.out.print("Enter the height: ");
        int HEIGHT = input.nextInt();

        Polygon p = new Ellipse2D.Float();


        try {
            RandomWalk points = new RandomWalk(WIDTH, HEIGHT);
            JFrame frame = new JFrame("Points");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.add(points);
            frame.setSize(WIDTH, HEIGHT);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);

            while (true) {
                frame.repaint();
            }
        }
        catch (Exception e) {
            System.out.println("Exception");
        }
    }
}
