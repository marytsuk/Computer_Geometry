import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import javax.swing.*;
import static java.lang.Math.pow;

public class Lagrange extends JPanel
{
    private ArrayList<Point> points = new ArrayList<>();
    private ArrayList<Point> otherpoints = new ArrayList<>();

    private Stroke stroke = new BasicStroke(3, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
    //Передаем в конструктор размер окна, покдлючаем мышку
    public Lagrange() {
        setPreferredSize(new Dimension(800, 600));
        MouseHandler mouseHandler = new MouseHandler();
        addMouseListener(mouseHandler);
        addMouseMotionListener(mouseHandler);
    }
    //Отрисовываем на экране
    @Override
    protected void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        drawPoints((Graphics2D) g);
        drawLagrange((Graphics2D) g);
    }

    private void drawPoints(Graphics2D g) {
        g.setStroke(stroke);
        g.setStroke(new BasicStroke(7));
        for (int p = 0; p < points.size(); p++) { // Пробегаемся по всем точкам
            Point p1 = points.get(p % points.size());
            g.setColor(Color.RED);
            g.drawLine(p1.x, p1.y, p1.x, p1.y);
        }
    }

    private void drawLagrange(Graphics2D g)
    {
        g.setStroke(new BasicStroke(2));
        g.setColor(Color.BLUE);
        int n = otherpoints.size();
        for (int p = 0; p < n; p++)
        {
            Point p1 = otherpoints.get(p % otherpoints.size());
            g.drawLine(p1.x, p1.y, p1.x, p1.y);
        }
    }



    private double func1(double x, int k)
    {
        double f1 = 1;
        for (int i = 0; i < points.size(); i++)
        {
            Point p1 = points.get(i % points.size());
            if (i == k)
                continue;
            f1 = f1 * (x - p1.x);
        }
        return f1;
    }
    private double lagrange(double x)
    {
        double l = 0;
        for (int i = 0; i < points.size(); i++)
        {
            Point p1 = points.get(i % points.size());
            l = l + p1.y * func1(x, i) / func1(p1.x, i);
        }
        return l;
    }

    private int compareTo(Point o1, Point o2)
    {
        return (o1.x - o2.x);
    }

    private void LAGRANGE ()
    {
        double y;
        int n = points.size();
        Collections.sort(points, new Comparator<Point>()
        {
            @Override
            public int compare(Point o1, Point o2) {
                return compareTo(o1, o2);
            }
        });
        Point p1 = points.get(0 % points.size());
        Point p2 = points.get((n-1) % points.size());
        for (double x = p1.x; x < p2.x; x += 0.0005)
        {
            y = lagrange(x);
            otherpoints.add(new Point((int)x, (int)y));
        }
      /* for (int i = 0; i < otherpoints.size(); i++) {
            Point p3 = otherpoints.get(i % otherpoints.size());
            System.out.println(p3.x);
            System.out.println(p3.y);
        }*/
        //points.clear();
    }
    //Инициализация окна
    public static void main(String[] args)
    {
        Lagrange view = new Lagrange();
        JFrame frame = new JFrame();
        frame.add(view);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
    //Обработка мышки
    private class MouseHandler extends MouseAdapter
    {
        @Override
        public void mousePressed(MouseEvent e)
        {
            if (SwingUtilities.isLeftMouseButton(e))
            {
                points.add(new Point(e.getX(), e.getY())); //Добавление в массив точки, получение координат x, y
            }
            else if (SwingUtilities.isRightMouseButton(e))
            {
                LAGRANGE();
            }
            else if (SwingUtilities.isMiddleMouseButton(e))
            {
                points.clear();
                otherpoints.clear();
            }
            repaint();
        }
    }
}
