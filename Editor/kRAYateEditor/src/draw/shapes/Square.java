/*
 * @author JamesToolenDCU 18th March '16
 * @text class for drawing squares
 */
package draw.shapes;

import java.awt.Color;
import java.awt.Graphics;

import staticThings.StaticVars;

public class Square extends Shape {

	public Square(int x, int y, int x2, int y2, Color c){
		super(x, y, x2, y2, c);
	}
	
	@Override
	public void render(Graphics g) {
		g.setColor(getColour());
		if(StaticVars.shapeFilled)
			g.fillRect(getX(), getY(), calcWidth(), calcHeight());
		else
			g.drawRect(getX(), getY(), calcWidth(), calcHeight());
	}

}
