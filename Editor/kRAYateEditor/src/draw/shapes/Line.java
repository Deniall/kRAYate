/*
 * @author JamesToolenDCU 18th March '16
 * @text class for line drawing
 */

package draw.shapes;

import java.awt.Color;
import java.awt.Graphics;

public class Line extends Shape {

	public Line(int x, int y, int x2, int y2, Color c) {
		super(x, y, x2, y2, c);
	}

	@Override
	public void render(Graphics g) {
		g.setColor(getColour());
		System.out.println(getX());
		g.drawLine(getX(), getY(), getX2(), getY2());
	}

}
