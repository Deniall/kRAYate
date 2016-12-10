/*
 * @author JamesToolenDCU 18th March '16
 * @text 	class for oval drawing
 * 			updated 21st March '16
 */
package draw.shapes;

import java.awt.Color;
import java.awt.Graphics;

import staticThings.StaticVars;

public class Oval extends Shape {

	public Oval(int x, int y, int x2, int y2, Color c) {
		super(x, y, x2, y2, c);
	}

	@Override
	public void render(Graphics g) {
		g.setColor(getColour());
		
		int w = calcWidth();
		int h = calcHeight();
		
		if(w < 0 && h < 0){
			w = Math.abs(w);
			h = Math.abs(h);
			if(StaticVars.shapeFilled)
				g.fillOval(getX2(), getY2(), w, h);
			else
				g.fillOval(getX2(), getY2(), w, h);
			
		}else if( w < 0 && h >= 0){
			w = Math.abs(w);
			h = Math.abs(h);
			
			if(StaticVars.shapeFilled)
				g.fillOval(getX2(), getY(), w, h);
			else
				g.fillOval(getX2(), getY(), w, h);
			
		}else if(w >= 0 && h < 0){
			w = Math.abs(w);
			h = Math.abs(h);
			
			if(StaticVars.shapeFilled)
				g.drawOval(getX(), getY2(), w, h);
			else
				g.drawOval(getX(), getY2(), w, h);
			
		}else{
			if(StaticVars.shapeFilled)
				g.fillOval(getX(), getY(), w, h);
			else
				g.fillOval(getX(), getY(), w, h);
			
		}
	}

}
