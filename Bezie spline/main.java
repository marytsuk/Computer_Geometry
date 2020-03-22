import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.lang.reflect.Array;
import java.util.ArrayList;
import javax.swing.*;
import static java.lang.Math.pow;
import java.awt.List;

public class Bezie1 extends JPanel
{
    private ArrayList<Point> points = new ArrayList<>();
    private ArrayList<Point> points1 = new ArrayList<>();
    private ArrayList<Point> otherpoints = new ArrayList<>();
    private ArrayList<Point> otherpoints1 = new ArrayList<>();
    double[] w;
    private Stroke stroke = new BasicStroke(3, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
    //Передаем в конструктор размер окна, покдлючаем мышку
    public Bezie1() {
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
        drawBezie((Graphics2D) g);
    }

    private int fact(int N)
    {
        int n = 1;
        if (N == 0)
            return 1;
        for (int i = 1; i <= N; i++)
        {
            n = n * i;
        }
        return n;
    }

    private void drawPoints(Graphics2D g) {
        g.setStroke(stroke);
        g.setStroke(new BasicStroke(7));
        for (int p = 0; p < points.size(); p++) { // Пробегаемся по всем точкам
            Point p1 = points.get(p % points.size());
            g.setColor(Color.RED);
            g.drawLine(p1.x, p1.y, p1.x, p1.y);
            g.setColor(Color.BLUE);
            Point p2 = points1.get(p % points.size());
            g.drawLine(p2.x , p2.y, p2.x, p2.y );
        }
    }

    private void drawBezie(Graphics2D g)
    {
        g.setStroke(new BasicStroke(2));
        g.setColor(Color.BLUE);
        int n = otherpoints.size();
        for (int p = 0; p < n; p++)
        {
            g.setColor(Color.BLUE);
            Point p1 = otherpoints.get(p % otherpoints.size());
            g.drawLine(p1.x, p1.y, p1.x, p1.y);
            g.setColor(Color.MAGENTA);
            Point p2 = otherpoints1.get(p % otherpoints1.size());
            g.drawLine(p2.x, p2.y, p2.x, p2.y);
        }
       // int n = otherpoints1.size();

    }
    private double sum(double t)
    {
        double s = 0;
        int n = points.size();
        for (int i = 0; i < points.size(); i++)
        {
            s = s + (fact(n-1) / (fact(i) * fact(n-1-i))) * pow(t, i) * pow((1-t), n-1-i) * w[i];
        }
        return s;
    }
    private void Bezie ()
    {
        double x, x1;
        double y, y1;
        int n = points.size();
        w = new double[n];
        for (int i = 0; i < n; i++)
        {
            w[i] = 1;
        }
        System.out.println("Веса:");
        System.out.println(w[0]);
        for (int i = 1; i < n - 1; i++)
        {
            w[i] = Math.random() * 10;
            System.out.println(w[i]);
        }
        System.out.println(w[n - 1]);
        for (double t = 0; t <= 1; t += 0.00005)
        {   x = 0;
            y = 0;
            x1 = 0;
            y1 = 0;
            for (int i = 0; i < points.size(); i++)
            {
                Point p1 = points.get(i % points.size());
                Point p2 = points1.get(i % points1.size());
                x = x + (fact(n-1) / (fact(i) * fact(n-1-i))) * pow(t, i) * pow((1-t), n-1-i) * p2.x * (w[i] / sum(t));
                y = y + (fact(n-1) / (fact(i) * fact(n-1-i))) * pow(t, i) * pow((1-t), n-1-i) * p2.y * (w[i] / sum(t));
                x1 = x1 + (fact(n-1) / (fact(i) * fact(n-1-i))) * pow(t, i) * pow((1-t), n-1-i) * p1.x;
                y1 = y1 + (fact(n-1) / (fact(i) * fact(n-1-i))) * pow(t, i) * pow((1-t), n-1-i) * p1.y;
            }
            otherpoints.add(new Point((int)x1, (int)y1));
            otherpoints1.add(new Point((int)x,(int)y));
        }
        for (int i = 0; i < otherpoints.size(); i++) {
            Point p2 = otherpoints.get(i % otherpoints.size());
            //System.out.println(p2.x);
            //System.out.println(p2.y);
        }
        //points.clear();
    }
    //Инициализация окна
    public static void main(String[] args)
    {
        Bezie1 view = new Bezie1();
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
                points.add(new Point(e.getX(), e.getY()));
                points1.add(new Point(e.getX() + 300, e.getY()));
                //Добавление в массив точки, получение координат x, y
            }
            else if (SwingUtilities.isRightMouseButton(e))
            {
                Bezie();
            }
            else if (SwingUtilities.isMiddleMouseButton(e))
            {
                points.clear();
                points1.clear();
                otherpoints.clear();
                otherpoints1.clear();
            }
            repaint();
        }
    }
}
